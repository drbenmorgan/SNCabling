//! \file    sncabling/om_id.h
//! \brief   Optical module ID
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

#ifndef SNCABLING_OM_ID_H
#define SNCABLING_OM_ID_H

// Standard library:
#include <string>
// #include <functional>

namespace sncabling {

  class label;
  
  enum om_type {
    OM_UNDEF = -1,
    OM_MAIN  =  0,
    OM_XWALL =  1,
    OM_GVETO =  2,
    OM_REF   =  3
  };

  class om_id
  {
  public:

    om_id(const om_type = OM_UNDEF,
          const int addr0_ = -1,
          const int addr1_ = -1,
          const int addr2_ = -1,
          const int addr3_ = -1);
    void invalidate();
    bool is_valid() const;
    int get_type() const;
    std::string what() const;
    bool is_main() const;
    bool is_xwall() const;
    bool is_gveto() const;
    bool is_ref() const;
    int get_side() const;
    int get_wall() const;
    int get_column() const;
    int get_row() const;
    int get_ref() const;
    static int compare(const om_id & lhs_, const om_id & rhs_);
    bool operator<(const om_id & other_) const;
    bool operator>(const om_id & other_) const;
    bool operator==(const om_id & other_) const;
    bool from_label(const label & lbl_);
    label to_label() const;
   
  private:
      
    om_type _type_ = OM_UNDEF; //!< Type of optical module
    int  _side_    = -1; //!< Side number
    int  _wall_    = -1; //!< Wall number
    int  _column_  = -1; //!< Column number
    int  _row_     = -1; //!< Row number
    int  _ref_     = -1; //!< Reference OM number
    
  };

} // namespace sncabling 

// namespace std {
//   template<>
//   bool less<typename sncabling::om_id>::operator()(const sncabling::om_id & lhs_,
//                                                    const sncabling::om_id & rhs_) const;
// } // namespace std 

#endif // SNCABLING_OM_ID_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
