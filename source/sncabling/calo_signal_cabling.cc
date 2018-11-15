// sncabling/calo_signal_cabling.cc - Implementation of signal readout cabling table
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
#include <sncabling/calo_signal_cabling.h>

// Standard Library:
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

// Third Party:
#include <boost/algorithm/string.hpp>
#include <bayeux/datatools/exception.h>
#include <bayeux/datatools/logger.h>
#include <bayeux/datatools/utils.h>

// This project:
#include <sncabling/label.h>

namespace sncabling {

  calo_signal_cabling::calo_signal_cabling()
  {
    return;
  }

  bool calo_signal_cabling::has_om(const om_id & om_) const
  {
    if (_table_.find(om_) != _table_.end()) return true;
    return false;
  }

  bool calo_signal_cabling::has_channel(const calo_signal_id & channel_) const
  {
    if (_reverse_table_.find(channel_) != _reverse_table_.end()) return true;
    return false;
  }

  void calo_signal_cabling::add(const om_id & om_,
                            const calo_signal_id & channel_,
                            const calo_signal_id & extcable_,
                            const calo_signal_id & intcable_)
  {
    DT_THROW_IF(!om_.is_valid(), std::logic_error,
                "Not an optical module ID!");
    DT_THROW_IF(!channel_.is_channel(), std::logic_error,
                "Not a calorimeter signal readout channel ID!");
    DT_THROW_IF(!extcable_.is_external_cable(), std::logic_error,
                "Not a calorimeter signal readout cable ID!");
    DT_THROW_IF(!intcable_.is_internal_cable(), std::logic_error,
                "Not a calorimeter signal readout cable ID!");
    signal_connections conn;
    conn.channel = channel_;
    conn.extcable = extcable_;
    conn.intcable = intcable_;
    _table_[om_] = conn;
    _reverse_table_[channel_] = om_;
    return;
  }
 
  const calo_signal_id & calo_signal_cabling::get_channel(const om_id & om_) const
  {
    const auto & found = _table_.find(om_);
    DT_THROW_IF(found == _table_.end(), std::logic_error,
                "Missing OM!");
    return found->second.channel;
  }
 
  const calo_signal_id & calo_signal_cabling::get_int_cable(const om_id & om_) const
  {
    const auto & found = _table_.find(om_);
    DT_THROW_IF(found == _table_.end(), std::logic_error,
                "Missing OM!");
    return found->second.intcable;
  }
       
  const om_id & calo_signal_cabling::get_om(const calo_signal_id & channel_) const
  {
    const auto & found = _reverse_table_.find(channel_);
    DT_THROW_IF(found == _reverse_table_.end(), std::logic_error,
                "Missing signal readout channel!");
    return found->second;
  }

  const calo_signal_cabling::signal_cabling_map_type &
  calo_signal_cabling::get_table() const
  {
    return _table_;
  }

  const calo_signal_cabling::reverse_signal_cabling_map_type &
  calo_signal_cabling::get_reverse_table() const
  {
    return _reverse_table_;
  }
 
  void calo_signal_cabling::build_om_from_board(const calo_signal_id & board_,
                                            std::vector<om_id> & list_) const
  {
    DT_THROW_IF(!board_.is_board(), std::logic_error,
                "Not a calorimeter signal readout board ID!");
    list_.clear();
    for (const auto & p : _table_) {
      calo_signal_id board_id = p.second.channel.get_board_id();
      if (board_id == board_) {
        list_.push_back(p.first);
      }
    }
    return;
  }
 
  void calo_signal_cabling::build_om_from_crate(const calo_signal_id & crate_,
                                            std::vector<om_id> & list_) const
  {
    DT_THROW_IF(!crate_.is_crate(), std::logic_error,
                "Not a calorimeter signal readout crate ID!");
    list_.clear();
    for (const auto & p : _table_) {
      calo_signal_id crate_id = p.second.channel.get_crate_id();
      if (crate_id == crate_) {
        list_.push_back(p.first);
      }
    }
    return;
  }

  void calo_signal_cabling::print(std::ostream & out_) const
  {
    out_ << "channel" << " " << "external_cable" << " " << "internal_cable" << " " << "OM" << std::endl;
    for (const auto & p : _table_) {
      sncabling::label lbl_to_om = p.first.to_label();
      sncabling::label lbl_from_channel = p.second.channel.to_label();
      sncabling::label lbl_ext_cable  = p.second.extcable.to_label();
      sncabling::label lbl_int_cable  = p.second.intcable.to_label();
      out_ << std::setw(9) << std::left << lbl_from_channel.to_string()
           << " " << std::setw(7) << std::left << lbl_ext_cable.to_string()
           << " " << std::setw(7) << std::left << lbl_int_cable.to_string()
           << " " << std::left << lbl_to_om.to_string()  << std::endl;
    }
    return;
  }
 
  void calo_signal_cabling::clear()
  {
    _reverse_table_.clear();
    _table_.clear();
    return;
  }
 
  void calo_signal_cabling::load(const std::string & filename_, const unsigned int tags_)
  {
    datatools::logger::priority logging = datatools::logger::PRIO_FATAL;
    // bool led_cable_match = false;
    if (tags_ & LOAD_DEBUG) {
      logging = datatools::logger::PRIO_DEBUG;
    }
    // if (tags_ & LOAD_LED_CABLE_MATCH) {
    //   led_cable_match = true;
    // }
    if (datatools::logger::is_debug(logging)) {
      DT_LOG_DEBUG(logging,"Loading file '" << filename_ << "'...");
    }
    std::string filename = filename_;
    datatools::fetch_path_with_env(filename);
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
      if (datatools::logger::is_debug(logging)) {
        std::cerr << "[debug] Raw line: '" << raw_line << "'" << std::endl;
      }
      std::vector<std::string> tokens;
      
      boost::split(tokens, raw_line, boost::is_any_of(";"));
      DT_THROW_IF(tokens.size() != 4, std::logic_error,
                  "Invalid format!")
      for (int i = 0; i < 4; i++) {
        boost::trim(tokens[i]);
      }
      std::string channel_repr = tokens[0];
      std::string extcable_repr = tokens[1];
      std::string intcable_repr = tokens[2];
      std::string om_repr = tokens[3];
     
      label channel_lbl;
      DT_THROW_IF(!channel_lbl.parse_from(channel_repr, 'H', 3),
                  std::logic_error,
                  "Invalid CaloSignal label format '" << channel_repr << "'!");
      if (datatools::logger::is_debug(logging)) {
        std::cerr << "[debug] CaloSignal channel label: '" << channel_lbl << "'" << std::endl;
      }
     
      label extcable_lbl;
      DT_THROW_IF(!extcable_lbl.parse_from(extcable_repr, 'L', 2),
                  std::logic_error,
                  "Invalid CaloSignal label format '" << extcable_repr << "'!");
      if (datatools::logger::is_debug(logging)) {
        std::cerr << "[debug] CaloSignal external cable label: '" << extcable_lbl << "'" << std::endl;
      }
     
      label intcable_lbl;
      DT_THROW_IF(!intcable_lbl.parse_from(intcable_repr, 'A', 2),
                  std::logic_error,
                  "Invalid CaloSignal label format '" << intcable_repr << "'!");
      if (datatools::logger::is_debug(logging)) {
        std::cerr << "[debug] CaloSignal internal cable label: '" << intcable_lbl << "'" << std::endl;
      }
      
      label om_lbl;
      DT_THROW_IF(!om_lbl.parse_from(om_repr),
                  std::logic_error,
                  "Invalid OM label format '" << om_repr << "'!");
      if (datatools::logger::is_debug(logging)) {
        std::cerr << "[debug] OM label: '" << om_lbl << "'" << std::endl;
      }

      calo_signal_id channel;
      DT_THROW_IF(!channel.from_label(channel_lbl),
                  std::logic_error,
                  "Invalid CaloSignal channel identifier '" << channel_lbl << "'!");
      DT_THROW_IF(!channel.is_channel(),
                  std::logic_error,
                  "Not a CaloSignal channel identifier '" << channel_lbl << "'!");

      calo_signal_id extcable;
      DT_THROW_IF(!extcable.from_label(extcable_lbl),
                  std::logic_error,
                  "Invalid CaloSignal external cable identifier '" << extcable_lbl << "'!");
      DT_THROW_IF(!extcable.is_external_cable(),
                  std::logic_error,
                  "Not a CaloSignal external cable identifier '" << extcable_lbl << "'!");

      calo_signal_id intcable;
      DT_THROW_IF(!intcable.from_label(intcable_lbl),
                  std::logic_error,
                  "Invalid CaloSignal internal cable identifier '" << intcable_lbl << "'!");
      DT_THROW_IF(!intcable.is_internal_cable(),
                  std::logic_error,
                  "Not a CaloSignal internal cable identifier '" << extcable_lbl << "'!");
      
      om_id om;
      DT_THROW_IF(!om.from_label(om_lbl),
                  std::logic_error,
                  "Invalid OM identifier '" << om_lbl << "'!");
      add(om, channel, extcable, intcable);
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
