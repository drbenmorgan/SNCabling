// sncabling/calo_feb_id.cc - Implementation of Calorimeter FEB ID
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
#include <sncabling/calo_feb_id.h>

// Standard Library:
#include <string>
#include <sstream>

// This Project:
#include <sncabling/label.h>

namespace sncabling {
  
  calo_feb_id::calo_feb_id(const calofeb_type type_,
                           const int addr0_,
                           const int addr1_,
                           const int addr2_)
  {
    _type_ = type_;
    if (_type_ == CALOFEB_CRATE) {
      _crate_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOFEB_BOARD) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
    }
    if (_type_ == CALOFEB_CHANNEL) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
      _channel_ = addr2_ < 0 ? -1 : addr2_;
    }
    return;
  }

  bool calo_feb_id::is_valid() const
  {
    if (_type_ == CALOFEB_UNDEF) return false;
    if (_type_ == CALOFEB_CRATE) {
      if (_crate_ < 0) return false;
    }
    if (_type_ == CALOFEB_BOARD) {
      if (_crate_ < 0) return false;
      if (_board_ < 0) return false;
    }
    if (_type_ == CALOFEB_CHANNEL) {
      if (_crate_ < 0) return false;
      if (_board_ < 0) return false;
      if (_channel_ < 0) return false;
    }
    return true;
  }

  std::string calo_feb_id::what() const
  {
    switch(_type_) {
    case CALOFEB_CRATE :
      return "calo_feb_crate";
    case CALOFEB_BOARD :
      return "calo_feb_board";
    case CALOFEB_CHANNEL :
      return "calo_feb_channel";
    }
    return "";
  }

  void calo_feb_id::invalidate()
  {
    _type_ = CALOFEB_UNDEF;
    _crate_    = -1;
    _board_    = -1;
    _channel_  = -1;
    return;
  }

  int calo_feb_id::get_type() const
  {
    return _type_;
  }

  bool calo_feb_id::is_crate() const
  {
    return _type_== CALOFEB_CRATE;
  }
  
  bool calo_feb_id::is_board() const
  {
    return _type_== CALOFEB_BOARD;
  }
  
  bool calo_feb_id::is_channel() const
  {
    return _type_== CALOFEB_CHANNEL;
  }

  int calo_feb_id::get_crate() const
  {
    return _crate_;
  }
  
  int calo_feb_id::get_board() const
  {
    return _board_;
  }
  
  int calo_feb_id::get_channel() const
  {
    return _channel_;
  }
  
  label calo_feb_id::to_label() const
  {
    label lbl;
    switch(_type_) {
    case CALOFEB_CRATE :
      lbl.set_symbol('C');
      lbl.append_address(_crate_);
      break;
    case CALOFEB_BOARD :
      lbl.set_symbol('B');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      break;
    case CALOFEB_CHANNEL :
      lbl.set_symbol('H');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      lbl.append_address(_channel_);
      break;
    }
    return lbl;
  }
  
  bool calo_feb_id::from_label(const label & lbl_)
  {
    bool ok = false;
    if (!ok && lbl_.is('C', 1)) {
      *this = calo_feb_id(CALOFEB_CRATE,
                          lbl_.get_address()[0]);
      ok  = true;
    } 
    if (!ok && lbl_.is('B', 2)) {
      *this = calo_feb_id(CALOFEB_BOARD,
                          lbl_.get_address()[0],
                          lbl_.get_address()[1]);
      ok  = true;
    } 
    if (!ok && lbl_.is('H', 3)) {
      *this = calo_feb_id(CALOFEB_CHANNEL,
                          lbl_.get_address()[0],
                          lbl_.get_address()[1],
                          lbl_.get_address()[2]);
      ok  = true;
    }
    return ok;
  }

  // static
  int calo_feb_id::compare(const calo_feb_id & lhs_, const calo_feb_id & rhs_)
  {
    if (lhs_.get_type() < rhs_.get_type()) return -1;
    if (lhs_.get_type() > rhs_.get_type()) return +1;
    if (lhs_.get_crate() < rhs_.get_crate()) return -1;
    if (lhs_.get_crate() > rhs_.get_crate()) return +1;
    if (lhs_.get_board() < rhs_.get_board()) return -1;
    if (lhs_.get_board() > rhs_.get_board()) return +1;
    if (lhs_.get_channel() < rhs_.get_channel()) return -1;
    if (lhs_.get_channel() > rhs_.get_channel()) return +1;
    return 0;
  }

  bool calo_feb_id::operator<(const calo_feb_id & other_) const
  {
    return compare(*this, other_) == -1;
  }
 
  bool calo_feb_id::operator>(const calo_feb_id & other_) const
  {
    return compare(*this, other_) == +1;
  }
  
  bool calo_feb_id::operator==(const calo_feb_id & other_) const
  {
    return compare(*this, other_) == 0;
  }

  calo_feb_id calo_feb_id::get_crate_id() const
  {
    calo_feb_id cr(CALOFEB_CRATE, _crate_);
    return cr;
  }
  
  calo_feb_id calo_feb_id::get_board_id() const
  {
    calo_feb_id cr(CALOFEB_BOARD, _crate_, _board_);
    return cr;
  }

} // namespace sncabling
