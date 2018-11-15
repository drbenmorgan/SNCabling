// sncabling/sncabling_library.cc - Implementation of SNCabling system singleton
//

// Ourselves:
#include <sncabling/sncabling_library.h>

// Standard library
#include <cstdlib>
#include <memory>
#include <string>

// Third party:
// Boost:
#include <boost/filesystem.hpp>
// Bayeux:
#include <bayeux/datatools/kernel.h>
#include <bayeux/datatools/library_info.h>
// #include <bayeux/datatools/urn_to_path_resolver_service.h>
// #include <bayeux/datatools/urn_db_service.h>

// This project;
#include "sncabling/version.h"
#include "sncabling/resource_files.h"
#include "sncabling_binreloc.h"

namespace {
  //! Convert BrInitError code to a string describing the error
  //! \todo add errno to returned string
  std::string BRErrorAsString(const BrInitError& err) {
    std::string errMsg;
    switch (err) {
    case BR_INIT_ERROR_NOMEM:
      errMsg = "Unable to open /proc/self/maps";
    case BR_INIT_ERROR_OPEN_MAPS:
      errMsg = "Unable to read from /proc/self/maps";
    case BR_INIT_ERROR_READ_MAPS:
      errMsg = "The file format of /proc/self/maps";
    case BR_INIT_ERROR_INVALID_MAPS:
      errMsg = "The file format of /proc/self/maps is invalid";
    case BR_INIT_ERROR_DISABLED:
      errMsg = "Binary relocation disabled";
    default:
      BOOST_ASSERT_MSG(1,"Invalid BrInitError");
    }
    return errMsg;
  }
}

namespace sncabling {

  directories_initialization_exception::directories_initialization_exception(const std::string& msg)
    : std::runtime_error(msg)
  {
  }

  void init_directories() {
    BrInitError err;
    int initSuccessful = br_init_lib(&err);
    DT_THROW_IF(initSuccessful != 1,
                sncabling::directories_initialization_exception,
                "Initialization of SNCabling library's directories failed : "
                << err
                << " ("
                << BRErrorAsString(err)
                << ")");
  }

  // static
  const std::string & sncabling_library::setup_db_name()
  {
    static const std::string _n("sncablingSystemSetupDb");
    return _n;
  }

  // static
  const std::string & sncabling_library::resource_resolver_name()
  {
    static const std::string _n("sncablingSystemResourceResolver");
    return _n;
  }

  datatools::logger::priority sncabling_library::process_logging_env()
  {
    datatools::logger::priority logging = datatools::logger::PRIO_FATAL;
    char * l = getenv("SNCABLING_LIBRARY_LOGGING");
    if (l) {
      std::string level_label(l);
      ::datatools::logger::priority prio
          = ::datatools::logger::get_priority(level_label);
      if (prio != ::datatools::logger::PRIO_UNDEFINED) {
        logging = prio;
      }
    }
    return logging;
  }

  // static
  sncabling_library * sncabling_library::_instance_ = nullptr;

  sncabling_library::sncabling_library()
  {
    _logging_ = sncabling_library::process_logging_env();
    if (_logging_ == ::datatools::logger::PRIO_UNDEFINED) {
      DT_LOG_WARNING(::datatools::logger::PRIO_WARNING,
                     "Ignoring invalid SNCABLING_LIBRARY_LOGGING=\"" << getenv("SNCABLING_LIBRARY_LOGGING") << "\" environment!");
      _logging_ = ::datatools::logger::PRIO_FATAL;
    }
    DT_LOG_TRACE_ENTERING(_logging_);
    DT_LOG_TRACE(_logging_, "Initializing SNCabling library's resource files directories...");
    sncabling::init_directories();

    DT_THROW_IF(sncabling_library::_instance_ != nullptr,
                std::logic_error,
                "SNCabling library system singleton is already set!");
    sncabling_library::_instance_ = this;
    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  sncabling_library::~sncabling_library()
  {
    DT_LOG_TRACE_ENTERING(_logging_);
    if (is_initialized()) {
      DT_LOG_TRACE(_logging_, "Shuting down SNCabling library system singleton...");
      shutdown();
    }
    sncabling_library::_instance_ = nullptr;
    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  datatools::logger::priority sncabling_library::get_logging() const
  {
    return _logging_;
  }

  bool sncabling_library::is_initialized() const
  {
    return _initialized_;
  }

  void sncabling_library::initialize()
  {
    DT_LOG_TRACE_ENTERING(_logging_);
    DT_THROW_IF(is_initialized(), std::logic_error, "SNCabling library system singleton is already initialized!");

    // Register library informations in the Bayeux/datatools' kernel:
    _libinfo_registration_();

    // Setup services:
    DT_LOG_TRACE(_logging_, "SNCabling library system singleton services...");
    _services_.set_name("sncablingLibrarySystemServices");
    _services_.set_description("SNCabling Library System Singleton Services");
    _services_.set_allow_dynamic_services(true);
    _services_.initialize();

    // Start URN services:
    _initialize_urn_services_();

    _initialized_ = true;
    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  void sncabling_library::shutdown()
  {
    DT_LOG_TRACE_ENTERING(_logging_);
    DT_THROW_IF(!is_initialized(), std::logic_error, "SNCabling library system singleton is not initialized!");
    _initialized_ = false;

    // Terminate services:
    if (_services_.is_initialized()) {
      _shutdown_urn_services_();
      DT_LOG_TRACE(_logging_, "Terminating SNCabling library system singleton services...");
      _services_.reset();
    }

    // Deregister library informations from the Bayeux/datatools' kernel:
    _libinfo_deregistration_();

    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  datatools::service_manager & sncabling_library::grab_services()
  {
    return _services_;
  }

  const datatools::service_manager & sncabling_library::get_services() const
  {
    return _services_;
  }

  // static
  bool sncabling_library::is_instantiated()
  {
    return _instance_ != nullptr;
  }

  // static
  sncabling_library & sncabling_library::instance()
  {
    return *_instance_;
  }

  // static
  const sncabling_library & sncabling_library::const_instance()
  {
    return *_instance_;
  }

  // static
  sncabling_library & sncabling_library::instantiate()
  {
    if (! sncabling_library::is_instantiated()) {
      static std::unique_ptr<sncabling_library> _sys_handler;
      if (! _sys_handler) {
        // Allocate the SNCabling sys library singleton and initialize it:
        _sys_handler.reset(new sncabling_library);
      }
    }
    return sncabling_library::instance();
  }

  void sncabling_library::_libinfo_registration_()
  {
    DT_LOG_TRACE_ENTERING(_logging_);

    DT_THROW_IF(!datatools::kernel::is_instantiated(),
                std::runtime_error,
                "The Bayeux/datatools' kernel is not instantiated !");
    datatools::kernel & krnl = datatools::kernel::instance();

    // Populate the library info register:
    datatools::library_info & lib_info_reg = krnl.grab_library_info_register();

    // Bundled submodules:
    {
      DT_LOG_TRACE(_logging_, "Registration of SNCabling library in the Bayeux/datatools' kernel...");
      // SNCabling itself:
      DT_THROW_IF (lib_info_reg.has("sncabling"),
                   std::logic_error,
                   "SNCabling is already registered !");
      datatools::properties & sncabling_lib_infos
        = lib_info_reg.registration("sncabling",
                                    "SNCabling provides a offline and real-time software environment for the description, control,"
                                    "monitoring and running of an experiment.",
                                    sncabling::version::get_version()
                                    );
      DT_LOG_TRACE(_logging_, "SNCabling library entry is now registered in the Bayeux/datatools' kernel.");

      // Register the SNCabling resource path in the datatools' kernel:
      // std::cerr << "[devel] ******* sncabling_library::_libinfo_registration_ = '" << sncabling::get_resource_files_dir() << "'" << std::endl;
      sncabling_lib_infos.store_string(datatools::library_info::keys::install_resource_dir(),
                                       sncabling::get_resource_files_dir());
      DT_LOG_TRACE(_logging_, "SNCabling resource files dir is documented.");

      // If the 'SNCABLING_RESOURCE_FILES_DIR' environment variable is set, it will supersede
      // the official registered resource path above through the 'datatools::fetch_path_with_env'
      // function:
      sncabling_lib_infos.store_string(datatools::library_info::keys::env_resource_dir(),
                                       "SNCABLING_RESOURCE_FILES_DIR");
      DT_LOG_TRACE(_logging_, "SNCabling resource files dir env is documented.");
      DT_LOG_TRACE(_logging_, "SNCabling library has been registered in the Bayeux/datatools' kernel.");
    }

    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  void sncabling_library::_libinfo_deregistration_()
  {
    DT_LOG_TRACE_ENTERING(_logging_);

    if (datatools::kernel::is_instantiated()) {
      datatools::kernel & krnl = datatools::kernel::instance();
      if (krnl.has_library_info_register()) {
        // Access to the datatools kernel library info register:
        datatools::library_info & lib_info_reg = krnl.grab_library_info_register();
        // Unregistration of all registered submodules from the kernel's library info register:
        if (lib_info_reg.has("sncabling")) {
          DT_LOG_TRACE(_logging_, "Deregistration of the SNCabling library from the Bayeux/datatools' kernel...");
          lib_info_reg.unregistration("sncabling");
          DT_LOG_TRACE(_logging_, "SNCabling library has been deregistered from the Bayeux/datatools' kernel.");
        }
      }
    }

    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  void sncabling_library::_initialize_urn_services_()
  {
    DT_LOG_TRACE_ENTERING(_logging_);
    if (_services_.is_initialized()) {

      /*
      // Activate an URN info DB service:
      {
        datatools::urn_db_service & urnSetupDb =
          dynamic_cast<datatools::urn_db_service &>(_services_.load_no_init("sncablingSystemDb",
                                                                            "datatools::urn_db_service"));
        urnSetupDb.set_logging_priority(_logging_);
        std::string urn_db_conf_file = "@sncabling:urn/db/service.conf";
        datatools::fetch_path_with_env(urn_db_conf_file);
        datatools::properties urn_db_conf;
        urn_db_conf.read_configuration(urn_db_conf_file);
        urnSetupDb.initialize_standalone(urn_db_conf);
        if (datatools::logger::is_debug(_logging_)) {
          urnSetupDb.tree_dump(std::cerr, urnSetupDb.get_name() + ": ", "[debug] ");
        }
        DT_LOG_TRACE(_logging_, "Publishing the URN info DB '" << urnSetupDb.get_name() << "' to the Bayeux/datatools' kernel...");
        urnSetupDb.kernel_push();
        DT_LOG_TRACE(_logging_, "URN info DB has been plugged in the Bayeux/datatools' kernel.");
      }

      // Activate an URN resolver service:
      {
        datatools::urn_to_path_resolver_service & urnResourceResolver =
          dynamic_cast<datatools::urn_to_path_resolver_service &>(_services_.load_no_init("sncablingSystemPathResolver",
                                                                                          "datatools::urn_to_path_resolver_service"));
        urnResourceResolver.set_logging_priority(_logging_);
        std::string urn_resolver_conf_file = "@sncabling:urn/resolvers/service.conf";
        datatools::fetch_path_with_env(urn_resolver_conf_file);
        datatools::properties urn_resolver_conf;
        urn_resolver_conf.read_configuration(urn_resolver_conf_file);
        urnResourceResolver.initialize_standalone(urn_resolver_conf);
        if (datatools::logger::is_debug(_logging_)) {
          urnResourceResolver.tree_dump(std::cerr, urnResourceResolver.get_name() + ": ", "[debug] ");
        }
        DT_LOG_TRACE(_logging_, "Publishing the URN path resolver '" << urnResourceResolver.get_name() << "' to the Bayeux/datatools' kernel...");
        urnResourceResolver.kernel_push();
        DT_LOG_TRACE(_logging_, "URN path resolver has been plugged in the Bayeux/datatools' kernel.");
      }
      */
    }

    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

  void sncabling_library::_shutdown_urn_services_()
  {
    DT_LOG_TRACE_ENTERING(_logging_);

    if (_services_.is_initialized()) {

      /*
      // Deactivate the URN resolver:
      if (_services_.has(resource_resolver_name())) {
        DT_LOG_TRACE(_logging_, "Accessing URN path resolver...");
        datatools::urn_to_path_resolver_service & urnResourceResolver =
          _services_.grab<datatools::urn_to_path_resolver_service &>("sncablingSystemPathResolver");
        DT_LOG_TRACE(_logging_, "Removing URN path resolver '" << urnResourceResolver.get_name() << "' from the  Bayeux/datatools's kernel...");
        urnResourceResolver.kernel_pop();
        DT_LOG_TRACE(_logging_, "URN path resolver has been removed from the Bayeux/datatools kernel.");
        urnResourceResolver.reset();
      }

      // DeActivate the URN info setup DB:
      if (_services_.has(setup_db_name())){
        DT_LOG_TRACE(_logging_, "Accessing URN info setup DB...");
        datatools::urn_db_service & urnSetupDb =
          _services_.grab<datatools::urn_db_service &>("sncablingSystemDb");
        DT_LOG_TRACE(_logging_, "Removing URN info setup DB '" << urnSetupDb.get_name() << "' from the  Bayeux/datatools's kernel...");
        urnSetupDb.kernel_pop();
        DT_LOG_TRACE(_logging_, "URN info setup DB has been removed from the Bayeux/datatools kernel.");
        urnSetupDb.reset();
      }
      */
    }

    DT_LOG_TRACE_EXITING(_logging_);
    return;
  }

} // namespace sncabling
