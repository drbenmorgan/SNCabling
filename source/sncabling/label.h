//! \file    sncabling/label.h
//! \brief   Label
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

#ifndef SNCABLING_LABEL_H
#define SNCABLING_LABEL_H

// Standard Library:
#include <iostream>
#include <vector>

namespace sncabling {

  struct label
  {
  public:
    
    label(const char symbol_ = '?',
          const int addr0_ = -1,
          const int addr1_ = -1,
          const int addr2_ = -1,
          const int addr3_ = -1,
          const int addr4_ = -1);

    void set_symbol(const char symbol_);

    bool is_symbol(const char symbol_) const;

    char get_symbol() const;

    bool is(const char symbol_, const std::size_t depth_) const;

    void set_address(const std::vector<int> & addr_);

    void append_address(const int);
    
    const std::vector<int> & get_address() const;
    
    friend std::ostream & operator<<(std::ostream & out_, const label & label_);

    bool parse_from(const std::string & token_,
                    const char symbol_ = '\0',
                    const std::size_t & depth_ = 0);

    std::string to_string() const;
    
  private:
    
    char             _symbol_ = '?';
    std::vector<int> _address_;
    
  };
    
} // namespace sncabling

#endif // SNCABLING_LABEL_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
