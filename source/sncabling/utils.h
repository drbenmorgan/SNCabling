//! \file    sncabling/utils.h
//! \brief   SuperNEMO Cabling utilities
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

#ifndef SNCABLING_UTILS_H
#define SNCABLING_UTILS_H

// Standard Library:
#include <string>
#include <set>
#include <map>
#include <memory>

namespace sncabling {

  enum system_tag_type {
    SYSTEM_UNDEF         = 0, ///< Undefined system
    SYSTEM_CALOHV        = 1, ///< SuperNEMO Calorimeter HV system (CaloHV)
    SYSTEM_CALOSIGNAL    = 2, ///< SuperNEMO Calorimeter signal readout system (CaloSignal)
    SYSTEM_TRACKERHV     = 3, ///< SuperNEMO Tracker HV system (TrackerHV)
    SYSTEM_TRACKERSIGNAL = 4, ///< SuperNEMO Tracker signal readout system (TrackerSignal)
    SYSTEM_LIS           = 5, ///< SuperNEMO Light Injection system (LIS)
    SYSTEM_SDS           = 6  ///< SuperNEMO Source Deployment system (SDS)
  };

  struct system_description {
    std::string     label;
    std::string     description ;
    system_tag_type id;
    std::string     default_map; 
  };

  typedef std::map<system_tag_type, system_description> system_map_type;

  system_tag_type system_label_to_tag(const std::string & label_);

  const system_map_type & systems_map();

  const std::set<system_tag_type> & list_of_system_tags();

} // namespace sncabling

#endif // SNCABLING_UTILS_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --

