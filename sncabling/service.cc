// sncabling/service.cc - Implementation of the SuperNEMO cabling service
//
// Copyright (c) 2018 by François Mauger <mauger@lpccaen.in2p3.fr>
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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SNCabling. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <sncabling/service.h>

// This project;
#include <sncabling/calo_hv_cabling.h>
#include <sncabling/calo_signal_cabling.h>
#include <sncabling/lis_cabling.h>
#include <sncabling/utils.h>

namespace sncabling {

  // Registration :
  DATATOOLS_SERVICE_REGISTRATION_IMPLEMENT(service, "sncabling::service")

  struct service::pimpl_type
  {
    std::unique_ptr<calo_hv_cabling>     default_calo_hv_ptr;
    std::unique_ptr<calo_signal_cabling> default_calo_signal_ptr;
    std::unique_ptr<lis_cabling>         default_lis_ptr;
  };

  service::service()
  {
    _pimpl_.reset(new pimpl_type);
  }

  service::~service()
  {
    if (this->service::is_initialized()) {
      this->service::reset();
    }
    _pimpl_.reset();
  }

  bool service::is_initialized() const
  {
    return _initialized_;
  }

  int service::initialize(const datatools::properties & config_,
                          datatools::service_dict_type & /* service_dict_ */)
  {
    DT_THROW_IF(is_initialized(), std::logic_error,
                "Cabling service '" << get_name() << "' is already initialized ! ");

    base_service::common_initialize(config_);

    std::string calohv_default_map;
    std::string calosignal_default_map;
    std::string lis_default_map;

    if (config_.has_key("CaloHV.default_map")) {
      calohv_default_map = config_.fetch_path("CaloHV.default_map");
    }

    if (config_.has_key("CaloSignal.default_map")) {
      calosignal_default_map = config_.fetch_path("CaloSignal.default_map");
     }

    if (config_.has_key("LIS.default_map")) {
      lis_default_map = config_.fetch_path("LIS.default_map");
    }

    if (calohv_default_map.empty()) {
      const ::sncabling::system_description & sysdesc
        = ::sncabling::systems_map().find(::sncabling::SYSTEM_CALOHV)->second;
      if (!sysdesc.default_map.empty()) {
        DT_LOG_DEBUG(get_logging_priority(),
                    "Set the default map for CaloHV cabling...");
        calohv_default_map = sysdesc.default_map;
      }
    }

    if (calosignal_default_map.empty()) {
      const ::sncabling::system_description & sysdesc
        = ::sncabling::systems_map().find(::sncabling::SYSTEM_CALOSIGNAL)->second;
      if (!sysdesc.default_map.empty()) {
        DT_LOG_DEBUG(get_logging_priority(),
                    "Set the default map for CaloSignal cabling...");
        calosignal_default_map = sysdesc.default_map;
      }
    }

    if (lis_default_map.empty()) {
      const ::sncabling::system_description & sysdesc
        = ::sncabling::systems_map().find(::sncabling::SYSTEM_LIS)->second;
      if (!sysdesc.default_map.empty()) {
        DT_LOG_DEBUG(get_logging_priority(),
                    "Set the default map for LIS cabling...");
        lis_default_map = sysdesc.default_map;
      }
    }

    // Initialization operations:
    if (! calohv_default_map.empty()) {
      _pimpl_->default_calo_hv_ptr.reset(new calo_hv_cabling);
      _pimpl_->default_calo_hv_ptr->load(calohv_default_map);
    }

    if (! calosignal_default_map.empty()) {
      _pimpl_->default_calo_signal_ptr.reset(new calo_signal_cabling);
      _pimpl_->default_calo_signal_ptr->load(calosignal_default_map);
    }

    if (! lis_default_map.empty()) {
      _pimpl_->default_lis_ptr.reset(new lis_cabling);
      _pimpl_->default_lis_ptr->load(lis_default_map);
    }

    _initialized_ = true;
    return EXIT_SUCCESS;
  }

  int service::reset()
  {
    DT_THROW_IF(!is_initialized(), std::logic_error,
                "Electronics service '" << get_name() << "' is not initialized ! ");
    _initialized_ = false;

    if (_pimpl_->default_calo_hv_ptr) {
      _pimpl_->default_calo_hv_ptr->clear();
    }

    if (_pimpl_->default_calo_signal_ptr) {
      _pimpl_->default_calo_signal_ptr->clear();
    }

    if (_pimpl_->default_lis_ptr) {
      _pimpl_->default_lis_ptr->clear();
    }

    _pimpl_->default_lis_ptr.reset();
    _pimpl_->default_calo_signal_ptr.reset();
    _pimpl_->default_calo_hv_ptr.reset();

    return EXIT_SUCCESS;
  }

  const calo_hv_cabling & service::get_calo_hv_cabling(const time_mark & /* tm_ */) const
  {
    return *_pimpl_->default_calo_hv_ptr;
  }

  const calo_signal_cabling & service::get_calo_signal_cabling(const time_mark & /* tm_ */) const
  {
    return *_pimpl_->default_calo_signal_ptr;
  }

  const lis_cabling & service::get_lis_cabling(const time_mark & /* tm_ */) const
  {
    return *_pimpl_->default_lis_ptr;
  }

} // namespace sncabling
