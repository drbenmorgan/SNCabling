//! \file    sncabling/calo_hv_id.h
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

#ifndef SNCABLING_CALO_HV_ID_H
#define SNCABLING_CALO_HV_ID_H

// Standard library;
#include <string>

namespace sncabling {
 
  class label;

  enum calohv_type {
    CALOHV_UNDEF   = -1,
    CALOHV_CRATE   =  0,
    CALOHV_BOARD   =  1,
    CALOHV_CHANNEL =  2,
    CALOHV_EXTHARNESS = 3,
    CALOHV_INTHARNESS = 4,
    CALOHV_INTCABLE  = 5
  };
  
  class calo_hv_id
  {
  public:
    
    calo_hv_id(const calohv_type = CALOHV_UNDEF,
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
    bool is_external_harness() const;
    bool is_internal_harness() const;
    bool is_internal_cable() const;

    int get_crate() const;
    int get_board() const;
    int get_channel() const;
    int get_harness() const;
    int get_cable() const;

    static int compare(const calo_hv_id & lhs_, const calo_hv_id & rhs_);
    bool operator<(const calo_hv_id & other_) const;
    bool operator>(const calo_hv_id & other_) const;
    bool operator==(const calo_hv_id & other_) const;

    bool from_label(const label & lbl_);
    label to_label() const;

    /// Extract the crate ID from the board or channel ID
    calo_hv_id get_crate_id() const;
    
    /// Extract the board ID from the channel ID
    calo_hv_id get_board_id() const;
    
    /// Extract the internal harness ID from the cable ID
    calo_hv_id get_internal_harness_id() const;

  private:

    calohv_type _type_ = CALOHV_UNDEF; //!< Type of calorimeter HV identifier
    int  _crate_    = -1; //!< Crate number
    int  _board_    = -1; //!< Board number
    int  _channel_  = -1; //!< Channel number
    int  _harness_   = -1; //!< Harness number
    int  _cable_    = -1; //!< Cable number
    
  };

} // namespace sncabling 

#endif // SNCABLING_CALO_HV_ID_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
