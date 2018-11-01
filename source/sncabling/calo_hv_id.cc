// sncabling/calo_hv_id.cc - Implementation of Calorimeter FEB ID
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
#include <sncabling/calo_hv_id.h>

// Standard Library:
#include <string>
#include <sstream>

// This Project:
#include <sncabling/label.h>

namespace sncabling {
  
  calo_hv_id::calo_hv_id(const calohv_type type_,
                         const int addr0_,
                         const int addr1_,
                         const int addr2_)
  {
    _type_ = type_;
    if (_type_ == CALOHV_CRATE) {
      _crate_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOHV_BOARD) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
    }
    if (_type_ == CALOHV_CHANNEL) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
      _channel_ = addr2_ < 0 ? -1 : addr2_;
    }
    if (_type_ == CALOHV_EXTHARNESS) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOHV_INTHARNESS) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOHV_INTCABLE) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
      _cable_ = addr1_ < 0 ? -1 : addr1_  ;
    }
    return;
  }

  bool calo_hv_id::is_valid() const
  {
    if (_type_ == CALOHV_UNDEF) return false;
    if (_type_ == CALOHV_CRATE) {
      if (_crate_ < 0) return false;
    }
    if (_type_ == CALOHV_BOARD) {
      if (_crate_ < 0) return false;
      if (_board_ < 0) return false;
    }
    if (_type_ == CALOHV_CHANNEL) {
      if (_crate_ < 0) return false;
      if (_board_ < 0) return false;
      if (_channel_ < 0) return false;
    }
    if (_type_ == CALOHV_EXTHARNESS) {
      if (_harness_ < 0) return false;
    }
    if (_type_ == CALOHV_INTHARNESS) {
      if (_harness_ < 0) return false;
    }
    if (_type_ == CALOHV_INTCABLE) {
      if (_harness_ < 0) return false;
      if (_cable_ < 0) return false;
    }
    return true;
  }

  std::string calo_hv_id::what() const
  {
    switch(_type_) {
    case CALOHV_CRATE :
      return "calo_hv_crate";
    case CALOHV_BOARD :
      return "calo_hv_board";
    case CALOHV_CHANNEL :
      return "calo_hv_channel";
    case CALOHV_EXTHARNESS :
      return "calo_hv_external_harness";
    case CALOHV_INTHARNESS :
      return "calo_hv_internal_harness";
    case CALOHV_INTCABLE :
      return "calo_hv_internal_cable";
    }
    return "";
  }

  void calo_hv_id::invalidate()
  {
    _type_ = CALOHV_UNDEF;
    _crate_    = -1;
    _board_    = -1;
    _channel_  = -1;
    _harness_   = -1;
    _cable_    = -1;
    return;
  }

  int calo_hv_id::get_type() const
  {
    return _type_;
  }

  bool calo_hv_id::is_crate() const
  {
    return _type_== CALOHV_CRATE;
  }
  
  bool calo_hv_id::is_board() const
  {
    return _type_== CALOHV_BOARD;
  }
  
  bool calo_hv_id::is_channel() const
  {
    return _type_== CALOHV_CHANNEL;
  }

  bool calo_hv_id::is_external_harness() const
  {
    return _type_ == CALOHV_EXTHARNESS;
  }

  bool calo_hv_id::is_internal_harness() const
  {
    return _type_ == CALOHV_INTHARNESS;
  }
  
  bool calo_hv_id::is_internal_cable() const
  {
    return _type_ == CALOHV_INTCABLE;
  }

  int calo_hv_id::get_crate() const
  {
    return _crate_;
  }
  
  int calo_hv_id::get_board() const
  {
    return _board_;
  }
  
  int calo_hv_id::get_channel() const
  {
    return _channel_;
  }
 
  int calo_hv_id::get_harness() const
  {
    return _harness_;
  }
   
  int calo_hv_id::get_cable() const
  {
    return _cable_;
  }

  label calo_hv_id::to_label() const
  {
    label lbl;
    switch(_type_) {
    case CALOHV_CRATE :
      lbl.set_symbol('C');
      lbl.append_address(_crate_);
      break;
    case CALOHV_BOARD :
      lbl.set_symbol('B');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      break;
    case CALOHV_CHANNEL :
      lbl.set_symbol('H');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      lbl.append_address(_channel_);
      break;
    case CALOHV_EXTHARNESS :
      lbl.set_symbol('E');
      lbl.append_address(_harness_);
      break;
    case CALOHV_INTHARNESS :
      lbl.set_symbol('I');
      lbl.append_address(_harness_);
      break;
    case CALOHV_INTCABLE :
      lbl.set_symbol('A');
      lbl.append_address(_harness_);
      lbl.append_address(_cable_);
      break;
    }
    return lbl;
  }
  
  bool calo_hv_id::from_label(const label & lbl_)
  {
    bool ok = false;
    if (!ok && lbl_.is('C', 1)) {
      *this = calo_hv_id(CALOHV_CRATE,
                         lbl_.get_address()[0]);
      ok  = true;
    } 
    if (!ok && lbl_.is('B', 2)) {
      *this = calo_hv_id(CALOHV_BOARD,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1]);
      ok  = true;
    } 
    if (!ok && lbl_.is('H', 3)) {
      *this = calo_hv_id(CALOHV_CHANNEL,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1],
                         lbl_.get_address()[2]);
      ok  = true;
    }
    if (!ok && lbl_.is('E', 1)) {
      *this = calo_hv_id(CALOHV_EXTHARNESS,
                         lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('I', 1)) {
      *this = calo_hv_id(CALOHV_INTHARNESS,
                         lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('A', 2)) {
      *this = calo_hv_id(CALOHV_INTCABLE,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1]);
      ok  = true;
    }
    return ok;
  }

  // static
  int calo_hv_id::compare(const calo_hv_id & lhs_, const calo_hv_id & rhs_)
  {
    if (lhs_.get_type() < rhs_.get_type()) return -1;
    if (lhs_.get_type() > rhs_.get_type()) return +1;
    if (lhs_.get_crate() < rhs_.get_crate()) return -1;
    if (lhs_.get_crate() > rhs_.get_crate()) return +1;
    if (lhs_.get_board() < rhs_.get_board()) return -1;
    if (lhs_.get_board() > rhs_.get_board()) return +1;
    if (lhs_.get_channel() < rhs_.get_channel()) return -1;
    if (lhs_.get_channel() > rhs_.get_channel()) return +1;
    if (lhs_.get_harness() < rhs_.get_harness()) return -1;
    if (lhs_.get_harness() > rhs_.get_harness()) return +1;
    if (lhs_.get_cable() < rhs_.get_cable()) return -1;
    if (lhs_.get_cable() > rhs_.get_cable()) return +1;
    return 0;
  }

  bool calo_hv_id::operator<(const calo_hv_id & other_) const
  {
    return compare(*this, other_) == -1;
  }
 
  bool calo_hv_id::operator>(const calo_hv_id & other_) const
  {
    return compare(*this, other_) == +1;
  }
  
  bool calo_hv_id::operator==(const calo_hv_id & other_) const
  {
    return compare(*this, other_) == 0;
  }

  calo_hv_id calo_hv_id::get_crate_id() const
  {
    calo_hv_id cr(CALOHV_CRATE, _crate_);
    return cr;
  }
  
  calo_hv_id calo_hv_id::get_board_id() const
  {
    calo_hv_id cr(CALOHV_BOARD, _crate_, _board_);
    return cr;
  }
  
  calo_hv_id calo_hv_id::get_internal_harness_id() const
  {
    calo_hv_id cr(CALOHV_INTHARNESS, _harness_);
    return cr;
  }

} // namespace sncabling
