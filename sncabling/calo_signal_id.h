//! \file    sncabling/calo_signal_id.h
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

#ifndef SNCABLING_CALO_SIGNAL_ID_H
#define SNCABLING_CALO_SIGNAL_ID_H

// Standard library;
#include <string>

namespace sncabling {
 
  class label;

  enum calosignal_type {
    CALOSIGNAL_UNDEF      = -1,
    CALOSIGNAL_CRATE      =  0,
    CALOSIGNAL_BOARD      =  1,
    CALOSIGNAL_CHANNEL    =  2,
    CALOSIGNAL_EXTHARNESS =  3,
    CALOSIGNAL_INTHARNESS =  4,
    CALOSIGNAL_EXTCABLE   =  5,
    CALOSIGNAL_INTCABLE   =  6
  };
  
  class calo_signal_id
  {
  public:
    
    calo_signal_id(const calosignal_type = CALOSIGNAL_UNDEF,
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
    bool is_external_cable() const;
    bool is_internal_cable() const;

    int get_crate() const;
    int get_board() const;
    int get_channel() const;
    int get_harness() const;
    int get_cable() const;

    static int compare(const calo_signal_id & lhs_, const calo_signal_id & rhs_);
    bool operator<(const calo_signal_id & other_) const;
    bool operator>(const calo_signal_id & other_) const;
    bool operator==(const calo_signal_id & other_) const;

    bool from_label(const label & lbl_);
    label to_label() const;

    /// Extract the crate ID from the board or channel ID
    calo_signal_id get_crate_id() const;
    
    /// Extract the board ID from the channel ID
    calo_signal_id get_board_id() const;
    
    /// Extract the internal harness ID from the internal cable ID
    calo_signal_id get_internal_harness_id() const;
   
    /// Extract the external harness ID from the external cable ID
    calo_signal_id get_external_harness_id() const;

  private:

    calosignal_type _type_ = CALOSIGNAL_UNDEF; //!< Type of calorimeter signal readout identifier
    int  _crate_    = -1; //!< Crate number
    int  _board_    = -1; //!< Board number
    int  _channel_  = -1; //!< Channel number
    int  _harness_  = -1; //!< Harness number
    int  _cable_    = -1; //!< Cable number
    
  };

} // namespace sncabling 

#endif // SNCABLING_CALO_SIGNAL_ID_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
