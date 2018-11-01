// sncabling/om_id.cc - Implementation of OM ID
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
#include <sncabling/om_id.h>

// Standard Library:
#include <string>
#include <sstream>

// This Project:
#include <sncabling/label.h>

namespace sncabling {
  
  om_id::om_id(const om_type type_,
               const int addr0_,
               const int addr1_,
               const int addr2_,
               const int addr3_)
  {
    _type_ = type_;
    if (_type_ == OM_REF) {
      _ref_ = addr0_;
      return;
    }
    _side_ = addr0_;
    _wall_ = -1;
    if (_type_ == OM_MAIN) {
      _column_ = addr1_;
      _row_ = addr2_;
    }
    if (_type_ == OM_XWALL) {
      _wall_ = addr1_;
      _column_ = addr2_;
      _row_ = addr3_;
    }
    if (_type_ == OM_GVETO) {
      _wall_ = addr1_;
      _column_ = addr2_;
    }
    return;
  }

  bool om_id::is_valid() const
  {
    if (_type_ == OM_UNDEF) return false;
    if (_type_ == OM_REF) {
      if (_ref_ < 0) return false;
    }
    if (_type_ == OM_MAIN) {
      if (_side_ < 0) return false;
      if (_column_ < 0) return false;
      if (_row_ < 0) return false;
    }
    if (_type_ == OM_XWALL) {
      if (_side_ < 0) return false;
      if (_wall_ < 0) return false;
      if (_column_ < 0) return false;
      if (_row_ < 0) return false;
    }
    if (_type_ == OM_GVETO) {
      if (_side_ < 0) return false;
      if (_wall_ < 0) return false;
      if (_column_ < 0) return false;
    }
    return true;
  }

  void om_id::invalidate()
  {
    _type_ = OM_UNDEF;
    _side_    = -1;
    _wall_    = -1;
    _column_  = -1;
    _row_    = -1;
    _ref_    = -1;
    return;
  }

  int om_id::get_type() const
  {
    return _type_;
  }

  std::string om_id::what() const
  {
    switch(_type_) {
    case OM_MAIN :
      return "om_main_wall";
    case OM_XWALL :
      return "om_xwall";
    case OM_GVETO :
      return "om_gveto";
    case OM_REF :
      return "om_reference";
    }
    return "";
  }

  bool om_id::is_main() const
  {
    return _type_== OM_MAIN;
  }
  
  bool om_id::is_xwall() const
  {
    return _type_== OM_XWALL;
  }
  
  bool om_id::is_gveto() const
  {
    return _type_== OM_GVETO;
  }
  
  bool om_id::is_ref() const
  {
    return _type_== OM_REF;
  }

  int om_id::get_side() const
  {
    return _side_;
  }
  
  int om_id::get_wall() const
  {
    return _wall_;
  }
  
  int om_id::get_column() const
  {
    return _column_;
  }
  
  int om_id::get_row() const
  {
    return _row_;
  }
  
  int om_id::get_ref() const
  {
    return _ref_;
  }

  label om_id::to_label() const
  {
    label lbl;
    switch(_type_) {
    case OM_REF :
      lbl.set_symbol('R');
      lbl.append_address(_ref_);
      break;
    case OM_MAIN :
      lbl.set_symbol('M');
      lbl.append_address(_side_);
      lbl.append_address(_column_);
      lbl.append_address(_row_);
      break;
    case OM_XWALL :
      lbl.set_symbol('X');
      lbl.append_address(_side_);
      lbl.append_address(_wall_);
      lbl.append_address(_column_);
      lbl.append_address(_row_);
      break;
    case OM_GVETO :
      lbl.set_symbol('G');
      lbl.append_address(_side_);
      lbl.append_address(_wall_);
      lbl.append_address(_column_);
      break;
    }
    return lbl;
  }
  
  bool om_id::from_label(const label & lbl_)
  {
    bool ok = false;
    if (!ok && lbl_.is('M', 3)) {
      *this = om_id(OM_MAIN,
                    lbl_.get_address()[0],
                    lbl_.get_address()[1],
                    lbl_.get_address()[2]);
      ok  = true;
    } 
    if (!ok && lbl_.is('X', 4)) {
      *this = om_id(OM_XWALL,
                    lbl_.get_address()[0],
                    lbl_.get_address()[1],
                    lbl_.get_address()[2],
                    lbl_.get_address()[3]);
      ok  = true;
    } 
    if (!ok && lbl_.is('G', 3)) {
      *this = om_id(OM_GVETO,
                    lbl_.get_address()[0],
                    lbl_.get_address()[1],
                    lbl_.get_address()[2]);
      ok  = true;
    }
    if (!ok && lbl_.is('R', 1)) {
      *this = om_id(OM_REF,
                    lbl_.get_address()[0]);
      ok  = true;
    } 
    return ok;
  }

  // static
  int om_id::compare(const om_id & lhs_, const om_id & rhs_)
  {
    if (lhs_.get_type() < rhs_.get_type()) return -1;
    if (lhs_.get_type() > rhs_.get_type()) return +1;
    if (lhs_.get_side() < rhs_.get_side()) return -1;
    if (lhs_.get_side() > rhs_.get_side()) return +1;
    if (lhs_.get_wall() < rhs_.get_wall()) return -1;
    if (lhs_.get_wall() > rhs_.get_wall()) return +1;
    if (lhs_.get_column() < rhs_.get_column()) return -1;
    if (lhs_.get_column() > rhs_.get_column()) return +1;
    if (lhs_.get_row() < rhs_.get_row()) return -1;
    if (lhs_.get_row() > rhs_.get_row()) return +1;
    if (lhs_.get_ref() < rhs_.get_ref()) return -1;
    if (lhs_.get_ref() > rhs_.get_ref()) return +1;
    return 0;
  }

  bool om_id::operator<(const om_id & other_) const
  {
    return compare(*this, other_) == -1;
  }
 
  bool om_id::operator>(const om_id & other_) const
  {
    return compare(*this, other_) == +1;
  }
  
  bool om_id::operator==(const om_id & other_) const
  {
    return compare(*this, other_) == 0;
  }

} // namespace sncabling

// namespace std {

//   template<>
//   bool less<sncabling::om_id>::operator()(const sncabling::om_id & lhs_,
//                                           const sncabling::om_id & rhs_) const
//   {
//     if (lhs_.get_type() < rhs_.get_type()) return true;
//     if (lhs_.get_type() > rhs_.get_type()) return false;
//     if (lhs_.get_side() < rhs_.get_side()) return true;
//     if (lhs_.get_side() > rhs_.get_side()) return false;
//     if (lhs_.get_wall() < rhs_.get_wall()) return true;
//     if (lhs_.get_wall() > rhs_.get_wall()) return false;
//     if (lhs_.get_column() < rhs_.get_column()) return true;
//     if (lhs_.get_column() > rhs_.get_column()) return false;
//     if (lhs_.get_row() < rhs_.get_row()) return true;
//       return false;
//   }
  
// } // namespace std 
