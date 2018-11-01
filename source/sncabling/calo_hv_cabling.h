//! \file    sncabling/calo_hv_cabling.h
//! \brief   Calorimeter HV system cabling table
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

#ifndef SNCABLING_CALO_HV_CABLING_H
#define SNCABLING_CALO_HV_CABLING_H

// Standard Library:
#include <map>
#include <vector>
#include <iostream>

// Third Party:
#include <bayeux/datatools/bit_mask.h>

// This project:
#include <sncabling/om_id.h>
#include <sncabling/calo_hv_id.h>

namespace sncabling {

  /// \brief Calorimeter HV cabling
  ///
  ///
  class calo_hv_cabling
  {
  public:

    struct hv_connections {
      calo_hv_id channel;
      calo_hv_id extharness;
      calo_hv_id intcable;
    };
    
    typedef std::map<om_id, hv_connections> hv_cabling_map_type;

    calo_hv_cabling();

    bool has_om(const om_id &) const;

    bool has_channel(const calo_hv_id &) const;

    void add(const om_id & om_,
             const calo_hv_id & channel_,
             const calo_hv_id & extharness_,
             const calo_hv_id & intcable_);

    const calo_hv_id & get_channel(const om_id & om_) const;

    const calo_hv_id & get_int_cable(const om_id & om_) const;
        
    const om_id & get_om(const calo_hv_id & channel_) const;
 
    const hv_cabling_map_type & get_table() const;

    void build_om_from_board(const calo_hv_id & board_,
                             std::vector<om_id> & list_) const;

    void build_om_from_crate(const calo_hv_id & crate_,
                             std::vector<om_id> & list_) const;

    void print(std::ostream & out_ = std::clog) const;
    
    enum load_tag {
      LOAD_DEBUG = datatools::bit_mask::bit00
      //LOAD_UNDLE_MATCH = datatools::bit_mask::bit01
    };
    void load(const std::string & filename_, const unsigned int tags_ = 0);
    
  private:
    
    hv_cabling_map_type _table_;
    
  };
  
} // namespace sncabling

#endif // SNCABLING_CALO_HV_CABLING_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --

