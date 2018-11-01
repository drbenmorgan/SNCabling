//! \file    sncabling/calo_feb_id.h
//! \brief   Calorimeter Frontend Board ID
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

#ifndef SNCABLING_CALO_FEB_ID_H
#define SNCABLING_CALO_FEB_ID_H

// Standard library;
#include <string>

namespace sncabling {
 
  class label;

  enum calofeb_type {
    CALOFEB_UNDEF   = -1,
    CALOFEB_CRATE   =  0,
    CALOFEB_BOARD   =  1,
    CALOFEB_CHANNEL =  2
  };
  
  class calo_feb_id
  {
  public:
    
    calo_feb_id(const calofeb_type = CALOFEB_UNDEF,
                const int addr0_ = -1,
                const int addr1_ = -1,
                const int addr2_ = -1);
    void invalidate();
    bool is_valid() const;
    int get_type() const;
    std::string what() const;
    bool is_crate() const;
    bool is_board() const;
    bool is_channel() const;
    int get_crate() const;
    int get_board() const;
    int get_channel() const;
    static int compare(const calo_feb_id & lhs_, const calo_feb_id & rhs_);
    bool operator<(const calo_feb_id & other_) const;
    bool operator>(const calo_feb_id & other_) const;
    bool operator==(const calo_feb_id & other_) const;

    bool from_label(const label & lbl_);
    label to_label() const;

    calo_feb_id get_crate_id() const;
    calo_feb_id get_board_id() const;

  private:

    calofeb_type _type_ = CALOFEB_UNDEF;
    int  _crate_    = -1;
    int  _board_    = -1;
    int  _channel_  = -1;
    
  };

} // namespace sncabling 

#endif // SNCABLING_CALO_FEB_ID_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
