//! \file    sncabling/sncabling_library.h
//! \brief   Provide SNCabling library system singleton
//! \details
//
// Copyright (c) 2018 by Francois Mauger <mauger@lpccaen.in2p3.fr>
//
// This file is part of SNCabling.
//
// SNCabling is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SNCabling is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SNCabling.  If not, see <http://www.gnu.org/licenses/>.


#ifndef SNCABLING_SNCABLING_LIBRARY_H
#define SNCABLING_SNCABLING_LIBRARY_H

// Standard Library
#include <string>
#include <stdexcept>

// Third party:
#include <boost/core/noncopyable.hpp>
#include <bayeux/datatools/logger.h>
#include <bayeux/datatools/service_manager.h>

namespace sncabling {

  //! Exception class for directories initialization failure
  class directories_initialization_exception
    : public std::runtime_error
  {
  public:
    directories_initialization_exception(const std::string & msg);
  };

  //! Initialize the library resource paths
  //! \throw directories_initialization_exception when library cannot self locate
  void init_directories();

  //! \brief SNCabling system singleton
  class sncabling_library
    : private boost::noncopyable
  {
  public:

    /// Return the name of the SNCabling library's URN database service for supported setups (geometry, simulation...)
    static const std::string & setup_db_name();

    /// Return the name of the SNCabling library's URN to resource path resolver service
    static const std::string & resource_resolver_name();

    /// Extract the verbosity from the SNCABLING_LIBRARY_LOGGING environment variable (if any)
    static datatools::logger::priority process_logging_env();

    /// Default constructor
    sncabling_library();

    /// Destructor
    virtual ~sncabling_library();

    /// Return the logging priority
    datatools::logger::priority get_logging() const;

    /// Check initialization flag
    bool is_initialized() const;

    /// Initialize
    void initialize();

    /// Shutdown
    void shutdown();

    /// Return a mutable reference to the embedded service manager
    datatools::service_manager & grab_services();

    /// Return a non mutable reference to the embedded service manager
    const datatools::service_manager & get_services() const;

    /// Check if the SNCabling system singleton is instantiated
    static bool is_instantiated();

    /// Return a mutable reference to the SNCabling system singleton instance
    static sncabling_library & instance();

    /// Return a non-mutable reference to the SNCabling system singleton instance
    static const sncabling_library & const_instance();

    /// Instantiate the SNCabling system singleton
    static sncabling_library & instantiate();

  private:

    void _libinfo_registration_();

    void _libinfo_deregistration_();

    void _initialize_urn_services_();

    void _shutdown_urn_services_();

  private:

    // Management:
    bool _initialized_ = false;            //!< Initialization flag
    datatools::logger::priority _logging_ = datatools::logger::PRIO_FATAL; //!< Logging priority threshold

    // Working internal data:
    datatools::service_manager _services_; //!< Embedded services

    // Singleton:
    static sncabling_library * _instance_;  //!< SNCabling library system singleton handle

  };

} // namespace sncabling

#endif // SNCABLING_SNCABLING_LIBRARY_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
