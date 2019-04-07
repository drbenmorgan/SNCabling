// sncabling/lis_cabling.cc - Implementation of LIS cabling table
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
#include <sncabling/lis_cabling.h>

// Standard Library:
#include <string>
#include <sstream>
#include <fstream>

// Third Party:
#include <boost/algorithm/string.hpp>
// #include <bayeux/datatools/utils.h>

// This project:
#include <sncabling/label.h>
#include <sncabling/exception.h>
#include <sncabling/logger.h>
#include <sncabling/utils.h>

namespace sncabling {

  lis_cabling::lis_cabling()
  {
    return;
  }

  bool lis_cabling::has_fiber(const lis_id & fiber_) const
  {
    if (_table_.find(fiber_) != _table_.end()) return true;
    return false;
  }
  
  void lis_cabling::add_fiber(const lis_id & fiber_,
                              const lis_id & from_led_,
                              const om_id & to_om_)
  {
    const auto & found = _table_.find(fiber_);
    SN_THROW_IF(found != _table_.end(), std::logic_error,
                "Fiber '" << fiber_.to_label() << "' already connected!");
    fiber_connections conn;
    conn.om = to_om_;
    conn.led = from_led_;
    _table_[fiber_] = conn;
    return;
  }
  
  const om_id & lis_cabling::get_om(const lis_id & fiber_) const
  {
    const auto & found = _table_.find(fiber_);
    SN_THROW_IF(found == _table_.end(), std::logic_error,
                "Missing fiber!");
    return found->second.om;
  }
  
  const lis_id & lis_cabling::get_led(const lis_id & fiber_) const
  {
    const auto & found = _table_.find(fiber_);
    SN_THROW_IF(found == _table_.end(), std::logic_error,
                "Missing fiber!");
    return found->second.led;
  }
  
  const lis_cabling::fiber_cabling_map_type & lis_cabling::get_table() const
  {
    return _table_;
  }
 
  void lis_cabling::print(std::ostream & out_) const
  {
    out_ << "LED" << " " << "Fiber"  << " " << "OM" << std::endl;
    for (const auto & p : _table_) {
      sncabling::label lbl_link = p.first.to_label();
      sncabling::label lbl_from = p.second.led.to_label();
      sncabling::label lbl_to   = p.second.om.to_label();
      out_ << lbl_from << " <- " << lbl_link  << " -> " << lbl_to  << std::endl;
    }
    return;
  }

  bool lis_cabling::om_has_fiber(const om_id & om_, const bool secondary_) const
  {
    for (const auto & p : _table_) {
      if (p.second.om == om_) {
        if (secondary_) {
          if (p.first.is_secondary()) {
            return true;
          }
        } else {
          if (p.first.is_primary()) {
            return true;
          }
        }
      }
    }
    return false;
  }

  void lis_cabling::build_om_from_led(const lis_id & led_,
                                      std::vector<om_id> & list_,
                                      const bool secondary_) const
  {
    list_.clear();
    for (const auto & p : _table_) {
      if (p.second.led == led_) {
        if (secondary_) {
          if (p.first.is_secondary()) {
            list_.push_back(p.second.om);
          }
        } else {
          if (p.first.is_primary()) {
            list_.push_back(p.second.om);
          }
        }
      }
    }
    return;
  }

  bool lis_cabling::build_led_from_om(const om_id & om_,
                                      lis_id & led_,
                                      const bool secondary_) const
  {
    led_.invalidate();
    for (const auto & p : _table_) {
      if (p.second.om == om_) {
        if (secondary_) {
          if (p.first.is_secondary()) {
            led_ = p.second.led;
          }
        } else {
          if (p.first.is_primary()) {
            led_ = p.second.led;
          }
        }
      }
    }
    return led_.is_valid();
  }

  void lis_cabling::load(const std::string & filename_, const unsigned int tags_)
  {
    bool debug = false;
    bool led_bundle_match = false;
    if (tags_ & LOAD_DEBUG) {
      debug = true;
    }
    if (tags_ & LOAD_LED_BUNDLE_MATCH) {
      led_bundle_match = true;
    }
    SN_LOG_DEBUG(debug, "Loading file '" << filename_ << "'...");
    std::string filename = filename_;
    // datatools::fetch_path_with_env(filename);
    filename = resolve_path(filename_);
    std::ifstream fin(filename.c_str());
    std::size_t line_counter = 0;
    while (fin) {
      std::string raw_line;
      std::getline(fin, raw_line);
      boost::trim(raw_line);
      line_counter++;
      if (raw_line.size() == 0 || raw_line[0] == '#') {
        continue;
      }
      SN_LOG_DEBUG(debug,"Raw line: '" << raw_line << "'");
      std::vector<std::string> tokens;
      
      boost::split(tokens, raw_line, boost::is_any_of(";"));
      SN_THROW_IF(tokens.size() != 2, std::logic_error,
                  "Invalid format!");
      std::string fiber_repr = tokens[0];
      std::string om_repr = tokens[1];
     
      label fiber_lbl;
      SN_THROW_IF(!fiber_lbl.parse_from(fiber_repr),
                  std::logic_error,
                  "Invalid LIS label format '" << fiber_repr << "'!");
      SN_LOG_DEBUG(debug, "LIS fiber label: '" << fiber_lbl << "'");
      label om_lbl;
      SN_THROW_IF(!om_lbl.parse_from(om_repr),
                  std::logic_error,
                  "Invalid OM label format '" << om_repr << "'!");
      SN_LOG_DEBUG(debug, "OM label: '" << om_lbl << "'");

      lis_id fiber;
      SN_THROW_IF(!fiber.from_label(fiber_lbl),
                  std::logic_error,
                  "Invalid LIS fiber identifier '" << fiber_lbl << "'!");
      om_id om;
      SN_THROW_IF(!om.from_label(om_lbl),
                  std::logic_error,
                  "Invalid OM identifier '" << om_lbl << "'!");

      lis_id led(sncabling::LIS_LED, fiber.get_bundle(), -1, fiber.is_secondary());
      if (led_bundle_match) {
        
      }
      add_fiber(fiber, led, om);
      fin >> std::ws;
      if (!fin) {
        break;
      }
      if (fin.eof()) {
        break;
      }
    }
    return;
  }
 
} // namespace sncabling
