// sncabling/calo_signal_id.cc - Implementation of Calorimeter signal cabling ID
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
#include <sncabling/calo_signal_id.h>

// Standard Library:
#include <string>
#include <sstream>

// This Project:
#include <sncabling/label.h>

namespace sncabling {

  calo_signal_id::calo_signal_id(const calosignal_type type_,
                                 const int addr0_,
                                 const int addr1_,
                                 const int addr2_)
  {
    _type_ = type_;
    if (_type_ == CALOSIGNAL_CRATE) {
      _crate_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOSIGNAL_BOARD) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
    }
    if (_type_ == CALOSIGNAL_CHANNEL) {
      _crate_ = addr0_ < 0 ? -1 : addr0_;
      _board_ = addr1_ < 0 ? -1 : addr1_;
      _channel_ = addr2_ < 0 ? -1 : addr2_;
    }
    if (_type_ == CALOSIGNAL_EXTHARNESS) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOSIGNAL_INTHARNESS) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
    }
    if (_type_ == CALOSIGNAL_EXTCABLE) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
      _cable_ = addr1_ < 0 ? -1 : addr1_  ;
    }
    if (_type_ == CALOSIGNAL_INTCABLE) {
      _harness_ = addr0_ < 0 ? -1 : addr0_  ;
      _cable_ = addr1_ < 0 ? -1 : addr1_  ;
    }
  }

  bool calo_signal_id::is_valid() const
  {
    if (_type_ == CALOSIGNAL_UNDEF) {
      return false;
    }
    if (_type_ == CALOSIGNAL_CRATE) {
      if (_crate_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_BOARD) {
      if (_crate_ < 0) {
        return false;
      }
      if (_board_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_CHANNEL) {
      if (_crate_ < 0) {
        return false;
      }
      if (_board_ < 0) {
        return false;
      }
      if (_channel_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_EXTHARNESS) {
      if (_harness_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_INTHARNESS) {
      if (_harness_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_EXTCABLE) {
      if (_harness_ < 0) {
        return false;
      }
      if (_cable_ < 0) {
        return false;
      }
    }
    if (_type_ == CALOSIGNAL_INTCABLE) {
      if (_harness_ < 0) {
        return false;
      }
      if (_cable_ < 0) {
        return false;
      }
    }
    return true;
  }

  std::string calo_signal_id::what() const
  {
    switch(_type_) {
    case CALOSIGNAL_CRATE :
      return "calo_signal_crate";
    case CALOSIGNAL_BOARD :
      return "calo_signal_board";
    case CALOSIGNAL_CHANNEL :
      return "calo_signal_channel";
    case CALOSIGNAL_EXTHARNESS :
      return "calo_signal_external_harness";
    case CALOSIGNAL_INTHARNESS :
      return "calo_signal_internal_harness";
    case CALOSIGNAL_INTCABLE :
      return "calo_signal_internal_cable";
    case CALOSIGNAL_EXTCABLE :
      return "calo_signal_external_cable";
    }
    return "";
  }

  void calo_signal_id::invalidate()
  {
    _type_ = CALOSIGNAL_UNDEF;
    _crate_    = -1;
    _board_    = -1;
    _channel_  = -1;
    _harness_  = -1;
    _cable_    = -1;
  }

  int calo_signal_id::get_type() const
  {
    return _type_;
  }

  bool calo_signal_id::is_crate() const
  {
    return _type_== CALOSIGNAL_CRATE;
  }

  bool calo_signal_id::is_board() const
  {
    return _type_== CALOSIGNAL_BOARD;
  }

  bool calo_signal_id::is_channel() const
  {
    return _type_== CALOSIGNAL_CHANNEL;
  }

  bool calo_signal_id::is_external_harness() const
  {
    return _type_ == CALOSIGNAL_EXTHARNESS;
  }

  bool calo_signal_id::is_internal_harness() const
  {
    return _type_ == CALOSIGNAL_INTHARNESS;
  }

  bool calo_signal_id::is_internal_cable() const
  {
    return _type_ == CALOSIGNAL_INTCABLE;
  }

  bool calo_signal_id::is_external_cable() const
  {
    return _type_ == CALOSIGNAL_EXTCABLE;
  }

  int calo_signal_id::get_crate() const
  {
    return _crate_;
  }

  int calo_signal_id::get_board() const
  {
    return _board_;
  }

  int calo_signal_id::get_channel() const
  {
    return _channel_;
  }

  int calo_signal_id::get_harness() const
  {
    return _harness_;
  }

  int calo_signal_id::get_cable() const
  {
    return _cable_;
  }

  label calo_signal_id::to_label() const
  {
    label lbl;
    switch(_type_) {
    case CALOSIGNAL_CRATE :
      lbl.set_symbol('C');
      lbl.append_address(_crate_);
      break;
    case CALOSIGNAL_BOARD :
      lbl.set_symbol('B');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      break;
    case CALOSIGNAL_CHANNEL :
      lbl.set_symbol('H');
      lbl.append_address(_crate_);
      lbl.append_address(_board_);
      lbl.append_address(_channel_);
      break;
    case CALOSIGNAL_EXTHARNESS :
      lbl.set_symbol('E');
      lbl.append_address(_harness_);
      break;
    case CALOSIGNAL_INTHARNESS :
      lbl.set_symbol('I');
      lbl.append_address(_harness_);
      break;
    case CALOSIGNAL_INTCABLE :
      lbl.set_symbol('A');
      lbl.append_address(_harness_);
      lbl.append_address(_cable_);
      break;
    case CALOSIGNAL_EXTCABLE :
      lbl.set_symbol('L');
      lbl.append_address(_harness_);
      lbl.append_address(_cable_);
      break;
    }
    return lbl;
  }

  bool calo_signal_id::from_label(const label & lbl_)
  {
    bool ok = false;
    if (!ok && lbl_.is('C', 1)) {
      *this = calo_signal_id(CALOSIGNAL_CRATE,
                         lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('B', 2)) {
      *this = calo_signal_id(CALOSIGNAL_BOARD,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1]);
      ok  = true;
    }
    if (!ok && lbl_.is('H', 3)) {
      *this = calo_signal_id(CALOSIGNAL_CHANNEL,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1],
                         lbl_.get_address()[2]);
      ok  = true;
    }
    if (!ok && lbl_.is('E', 1)) {
      *this = calo_signal_id(CALOSIGNAL_EXTHARNESS,
                         lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('I', 1)) {
      *this = calo_signal_id(CALOSIGNAL_INTHARNESS,
                         lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('A', 2)) {
      *this = calo_signal_id(CALOSIGNAL_INTCABLE,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1]);
      ok  = true;
    }
    if (!ok && lbl_.is('L', 2)) {
      *this = calo_signal_id(CALOSIGNAL_EXTCABLE,
                         lbl_.get_address()[0],
                         lbl_.get_address()[1]);
      ok  = true;
    }
    return ok;
  }

  // static
  int calo_signal_id::compare(const calo_signal_id & lhs_, const calo_signal_id & rhs_)
  {
    if (lhs_.get_type() < rhs_.get_type()) {
      return -1;
    }
    if (lhs_.get_type() > rhs_.get_type()) {
      return +1;
    }
    if (lhs_.get_crate() < rhs_.get_crate()) {
      return -1;
    }
    if (lhs_.get_crate() > rhs_.get_crate()) {
      return +1;
    }
    if (lhs_.get_board() < rhs_.get_board()) {
      return -1;
    }
    if (lhs_.get_board() > rhs_.get_board()) {
      return +1;
    }
    if (lhs_.get_channel() < rhs_.get_channel()) {
      return -1;
    }
    if (lhs_.get_channel() > rhs_.get_channel()) {
      return +1;
    }
    if (lhs_.get_harness() < rhs_.get_harness()) {
      return -1;
    }
    if (lhs_.get_harness() > rhs_.get_harness()) {
      return +1;
    }
    if (lhs_.get_cable() < rhs_.get_cable()) {
      return -1;
    }
    if (lhs_.get_cable() > rhs_.get_cable()) {
      return +1;
    }
    return 0;
  }

  bool calo_signal_id::operator<(const calo_signal_id & other_) const
  {
    return compare(*this, other_) == -1;
  }

  bool calo_signal_id::operator>(const calo_signal_id & other_) const
  {
    return compare(*this, other_) == +1;
  }

  bool calo_signal_id::operator==(const calo_signal_id & other_) const
  {
    return compare(*this, other_) == 0;
  }

  calo_signal_id calo_signal_id::get_crate_id() const
  {
    calo_signal_id cr(CALOSIGNAL_CRATE, _crate_);
    return cr;
  }

  calo_signal_id calo_signal_id::get_board_id() const
  {
    calo_signal_id cr(CALOSIGNAL_BOARD, _crate_, _board_);
    return cr;
  }

  calo_signal_id calo_signal_id::get_internal_harness_id() const
  {
    calo_signal_id cr(CALOSIGNAL_INTHARNESS, _harness_);
    return cr;
  }

  calo_signal_id calo_signal_id::get_external_harness_id() const
  {
    calo_signal_id cr(CALOSIGNAL_EXTHARNESS, _harness_);
    return cr;
  }

} // namespace sncabling
