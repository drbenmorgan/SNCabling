// sncabling/label.cc - Implementation of SNCabling label
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

// Ourselves
#include <sncabling/label.h>

// Standard Library:
#include <string>
#include <sstream>

// Third party Library:
#include <boost/algorithm/string.hpp>

// This Project
#include <sncabling/logger.h>

namespace sncabling {

  label::label(const char symbol_,
               const int addr0_,
               const int addr1_,
               const int addr2_,
               const int addr3_,
               const int addr4_)
  {
    if (symbol_ == '?') {
      return;
    }
    _symbol_ = symbol_;
    if (addr0_ == -1) {
      return;
    }
    _address_.push_back(addr0_);
    if (addr1_ == -1) {
      return;
    }
    _address_.push_back(addr1_);
    if (addr2_ == -1) {
      return;
    }
    _address_.push_back(addr2_);
    if (addr3_ == -1) {
      return;
    }
    _address_.push_back(addr3_);
    if (addr4_ == -1) {
      return;
    }
    _address_.push_back(addr4_);
  }

  void label::set_symbol(const char symbol_)
  {
    _symbol_ = symbol_;
  }

  char label::get_symbol() const
  {
    return _symbol_;
  }

  bool label::is_symbol(const char symbol_) const
  {
    return _symbol_ == symbol_;
  }

  bool label::is(const char symbol_, const std::size_t depth_) const
  {
    if (! is_symbol(symbol_)) {
      return false;
    }
    if (_address_.size() != depth_) {
      return false;
    }
    return true;
  }

  void label::set_address(const std::vector<int> & addr_)
  {
    _address_ = addr_;
  }

  void label::append_address(const int addr_)
  {
    _address_.push_back(addr_);
  }

  const std::vector<int> & label::get_address() const
  {
    return _address_;
  }

  bool label::parse_from(const std::string & word_,
                         const char symbol_,
                         const std::size_t & depth_)
  {
    std::istringstream in(word_);
    std::string token;
    in >> token;
    if (token.empty()) {
      SN_LOG_ERROR("Zero length string!");
      return false;
    }
    std::size_t nsemicolon = token.find(':');
    if (nsemicolon != 1) {
      SN_LOG_ERROR("Missing semicolon in '" << token << "!");
      return false;
    }
    // Extract symbol:
    char symbol = token[0];
    // Check mandatory symbol:
    if (symbol_ != '\0' && symbol_ != symbol) {
      SN_LOG_ERROR("Symbol '" << symbol << "' does not match the expected '" << symbol_ << "'!");
      return false;
    }
    // Extract address:
    std::vector<std::string> saddr;
    std::string addr_repr = token.substr(2);
    boost::split(saddr, addr_repr, boost::is_any_of("."));
    std::vector<int> address;
    for (const auto& i : saddr) {
      int addr;
      std::istringstream ss(i);
      ss >> addr;
      if (!ss) {
        SN_LOG_ERROR("Cannot parse an address segment from '" << i << "!");
        return false;
      }
      if (addr < 0) {
        SN_LOG_ERROR("Invalid (<0) address segment [" << addr << "]!");
        return false;
      }
      address.push_back(addr);
    }
    if (depth_ != 0U && address.size() != depth_) {
      SN_LOG_ERROR("Address depth [" << address.size() << "] does not match the expected [" << depth_ << "]!");
      return false;
    }
    set_symbol(symbol);
    set_address(address);
    return true;
  }

  std::string label::to_string() const
  {
    std::ostringstream sout;
    sout << *this;
    return sout.str();
  }

  // friend
  std::ostream & operator<<(std::ostream & out_, const label & label_)
  {
    std::ostringstream strout;
    strout << label_._symbol_ << ':';
    for (std::size_t i = 0; i < label_._address_.size(); i++) {
      if (i > 0) {
        strout << '.';
      }
      strout << label_._address_[i];
    }
    out_ << strout.str();
    return out_;
  }

} // namespace sncabling
