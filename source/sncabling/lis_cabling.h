//! \file    sncabling/lis_cabling.h
//! \brief   LIS cabling table
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

#ifndef SNCABLING_LIS_CABLING_H
#define SNCABLING_LIS_CABLING_H

// Standard Library:
#include <map>
#include <vector>
#include <iostream>

// Third Party:
#include <bayeux/datatools/bit_mask.h>

// This project:
#include <sncabling/om_id.h>
#include <sncabling/lis_id.h>

namespace sncabling {

  class lis_cabling
  {
  public:

    struct fiber_connections {
      om_id  om;
      lis_id led;
    };
    
    typedef std::map<lis_id, fiber_connections> fiber_cabling_map_type;

    lis_cabling();

    bool has_fiber(const lis_id &) const;

    void add_fiber(const lis_id & fiber_,
                   const lis_id & from_led_,
                   const om_id & to_om_);
    
    const om_id & get_om(const lis_id & fiber_) const;
    
    const lis_id & get_led(const lis_id & fiber_) const;
    
    const fiber_cabling_map_type & get_table() const;

    void print(std::ostream & out_ = std::clog) const;

    bool om_has_fiber(const om_id & om_, const bool secondary_ = false) const;

    void build_om_from_led(const lis_id & led_, std::vector<om_id> & list_, const bool secondary_ = false) const;

    bool build_led_from_om(const om_id & om_, lis_id & led_, const bool secondary_ = false) const;

    enum load_tag {
      LOAD_DEBUG = datatools::bit_mask::bit00,
      LOAD_LED_BUNDLE_MATCH = datatools::bit_mask::bit01
    };
    void load(const std::string & filename_, const unsigned int tags_ = 0);
    
  private:
    
    fiber_cabling_map_type _table_;
    
  };
  
} // namespace sncabling

#endif // SNCABLING_LIS_CABLING_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
