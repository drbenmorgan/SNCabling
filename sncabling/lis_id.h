//! \file    sncabling/lis_id.h
//! \brief   LIS object ID
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

#ifndef SNCABLING_LIS_ID_H
#define SNCABLING_LIS_ID_H

// Standard library:
#include <string>
// #include <functional>

namespace sncabling {

  class label;
  
  enum lis_type {
    LIS_UNDEF  = -1,
    LIS_LED    =  0,
    LIS_BUNDLE =  1,
    LIS_FIBER  =  2
  };

  class lis_id
  {
  public:

    lis_id(const lis_type = LIS_UNDEF,
           const int addr0_ = -1,
           const int addr1_ = -1,
           const bool secondary_ = false);
    void invalidate();
    bool is_valid() const;
    int get_type() const;
    std::string what() const;
    bool is_led() const;
    bool is_bundle() const;
    bool is_fiber() const;
    bool is_primary() const;
    bool is_secondary() const;
    int get_led() const;
    int get_bundle() const;
    int get_fiber() const;
    static int compare(const lis_id & lhs_, const lis_id & rhs_);
    bool operator<(const lis_id & other_) const;
    bool operator>(const lis_id & other_) const;
    bool operator==(const lis_id & other_) const;
    bool from_label(const label & lbl_);
    label to_label() const;
   
  private:
      
    lis_type _type_ = LIS_UNDEF;
    bool _secondary_ = false;
    int  _led_     = -1;
    int  _bundle_  = -1;
    int  _fiber_   = -1;
    
  };

} // namespace sncabling 

#endif // SNCABLING_LIS_ID_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
