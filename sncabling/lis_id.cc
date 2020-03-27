// sncabling/lis_id.cc - Implementation of OM ID
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
#include <sncabling/lis_id.h>

// Standard Library:
#include <string>
#include <sstream>

// This Project:
#include <sncabling/label.h>

namespace sncabling {

  lis_id::lis_id(const lis_type type_,
                 const int addr0_,
                 const int addr1_,
                 const bool secondary_)
  {
    _type_ = type_;
    if (_type_ == LIS_LED) {
      _led_ = addr0_ < 0 ? -1 : addr0_;
    }
    if (_type_ == LIS_BUNDLE) {
      _bundle_ = addr0_ < 0 ? -1 : addr0_;
    }
    if (_type_ == LIS_FIBER) {
      _bundle_ = addr0_ < 0 ? -1 : addr0_;
      _fiber_ = addr1_ < 0 ? -1 : addr1_;
      _secondary_ = secondary_;
    }
  }

  bool lis_id::is_valid() const
  {
    if (_type_ == LIS_UNDEF) {
      return false;
    }
    if (_type_ == LIS_LED) {
      if (_led_ < 0) {
        return false;
      }
    }
    if (_type_ == LIS_BUNDLE) {
      if (_bundle_ < 0) {
        return false;
      }
    }
    if (_type_ == LIS_FIBER) {
      if (_bundle_ < 0) {
        return false;
      }
      if (_fiber_ < 0) {
        return false;
      }
    }
    return true;
  }

  void lis_id::invalidate()
  {
    _type_ = LIS_UNDEF;
    _secondary_ = false;
    _led_     = -1;
    _bundle_  = -1;
    _fiber_   = -1;
  }

  int lis_id::get_type() const
  {
    return _type_;
  }

  std::string lis_id::what() const
  {
    switch(_type_) {
    case LIS_LED :
      return "lis_led";
    case LIS_BUNDLE :
      return "lis_bundle";
    case LIS_FIBER :
      return "lis_fiber";
    }
    return "";
  }

  bool lis_id::is_led() const
  {
    return _type_== LIS_LED;
  }

  bool lis_id::is_bundle() const
  {
    return _type_== LIS_BUNDLE;
  }

  bool lis_id::is_fiber() const
  {
    return _type_== LIS_FIBER;
  }

  bool lis_id::is_primary() const
  {
    return !_secondary_;
  }

  bool lis_id::is_secondary() const
  {
    return _secondary_;
  }

  int lis_id::get_led() const
  {
    return _led_;
  }

  int lis_id::get_bundle() const
  {
    return _bundle_;
  }

  int lis_id::get_fiber() const
  {
    return _fiber_;
  }

  label lis_id::to_label() const
  {
    label lbl;
    switch(_type_) {
    case LIS_LED :
      lbl.set_symbol('L');
      lbl.append_address(_led_);
      break;
    case LIS_BUNDLE :
      lbl.set_symbol('B');
      lbl.append_address(_bundle_);
      break;
    case LIS_FIBER :
      if (is_secondary()) {
        lbl.set_symbol('S');
      } else {
        lbl.set_symbol('P');
      }
      lbl.append_address(_bundle_);
      lbl.append_address(_fiber_);
      break;
    }
    return lbl;
  }

  bool lis_id::from_label(const label & lbl_)
  {
    bool ok = false;
    if (!ok && lbl_.is('L', 1)) {
      *this = lis_id(LIS_LED,
                    lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('B', 1)) {
      *this = lis_id(LIS_BUNDLE,
                    lbl_.get_address()[0]);
      ok  = true;
    }
    if (!ok && lbl_.is('P', 2)) {
      *this = lis_id(LIS_FIBER,
                    lbl_.get_address()[0],
                    lbl_.get_address()[1]);
      this->_secondary_ = false;
      ok  = true;
    }
    if (!ok && lbl_.is('S', 2)) {
      *this = lis_id(LIS_FIBER,
                    lbl_.get_address()[0],
                    lbl_.get_address()[1]);
      this->_secondary_ = true;
      ok  = true;
    }
    return ok;
  }

  // static
  int lis_id::compare(const lis_id & lhs_, const lis_id & rhs_)
  {
    if (lhs_.get_type() < rhs_.get_type()) {
      return -1;
    }
    if (lhs_.get_type() > rhs_.get_type()) {
      return +1;
    }
    if (lhs_.get_led() < rhs_.get_led()) {
      return -1;
    }
    if (lhs_.get_led() > rhs_.get_led()) {
      return +1;
    }
    if (lhs_.get_bundle() < rhs_.get_bundle()) {
      return -1;
    }
    if (lhs_.get_bundle() > rhs_.get_bundle()) {
      return +1;
    }
    if (lhs_.get_fiber() < rhs_.get_fiber()) {
      return -1;
    }
    if (lhs_.get_fiber() > rhs_.get_fiber()) {
      return +1;
    }
    return 0;
  }

  bool lis_id::operator<(const lis_id & other_) const
  {
    return compare(*this, other_) == -1;
  }

  bool lis_id::operator>(const lis_id & other_) const
  {
    return compare(*this, other_) == +1;
  }

  bool lis_id::operator==(const lis_id & other_) const
  {
    return compare(*this, other_) == 0;
  }

} // namespace sncabling
