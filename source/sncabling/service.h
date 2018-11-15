//! \file    sncabling/service.h
//! \brief   SuperNEMO Cabling Service
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

#ifndef SNCABLING_SERVICE_H
#define SNCABLING_SERVICE_H

// Standard Library:
#include <memory>

// Third Party:
#include <bayeux/datatools/base_service.h>
#include <bayeux/datatools/service_tools.h>

// This project;
#include <sncabling/time_mark.h>

namespace sncabling {

  class calo_hv_cabling;
  class calo_signal_cabling;
  
  /// \brief Cabling service
  class service
    : public datatools::base_service
  {
  public:
    
    /// Default constructor
    service();
    
    /// Destructor
    virtual ~service();
  
    /// Check initialization flag
    virtual bool is_initialized() const;

    /// Initialization
    virtual int initialize(const datatools::properties & config_,
                           datatools::service_dict_type & service_dict_);

    /// Termination
    virtual int reset();

    /// Access to the calorimeter HV system cabling table
    ///
    /// If several cabling tables are available depending on some experimental period, it is possible to
    /// identify a given time mark (default: unused)
    const calo_hv_cabling & get_calo_hv_cabling(const time_mark & tm_ = time_mark::invalid_time_mark()) const;
    
    /// Access to the calorimeter signal readout system cabling table 
    ///
    /// If several cabling tables are available depending on some experimental period, it is possible to
    /// identify a given time mark (default: unused)
    const calo_signal_cabling & get_calo_signal_cabling(const time_mark & tm_ = time_mark::invalid_time_mark()) const;
    
  private:
    
    // Management:
    bool _initialized_ = false;  //!< Initialization flag

    // Configuration:

    // Working
    struct pimpl_type;
    std::unique_ptr<pimpl_type> _pimpl_; //!< Private implementation
    
    // Registration :
    DATATOOLS_SERVICE_REGISTRATION_INTERFACE(service)
  };
  
} // namespace sncabling

#endif // SNCABLING_SERVICE_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --

