//! \file    sncabling/calo_signal_cabling.h
//! \brief   Calorimeter signal readout system cabling table
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

#ifndef SNCABLING_CALO_SIGNAL_CABLING_H
#define SNCABLING_CALO_SIGNAL_CABLING_H

// Standard Library:
#include <map>
#include <vector>
#include <iostream>

// This project:
#include <sncabling/om_id.h>
#include <sncabling/calo_signal_id.h>

namespace sncabling {

  /// \brief Calorimeter signal readout system cabling
  ///
  ///
  class calo_signal_cabling
  {
  public:

    struct signal_connections {
      calo_signal_id channel;
      calo_signal_id extcable;
      calo_signal_id intcable;
    };

    typedef std::map<om_id, signal_connections> signal_cabling_map_type;
    typedef std::map<calo_signal_id, om_id>     reverse_signal_cabling_map_type;

    bool has_om(const om_id &) const;

    bool has_channel(const calo_signal_id &) const;

    void add(const om_id & om_,
             const calo_signal_id & channel_,
             const calo_signal_id & extcable_,
             const calo_signal_id & intcable_);

    const calo_signal_id & get_channel(const om_id & om_) const;

    const calo_signal_id & get_int_cable(const om_id & om_) const;

    const calo_signal_id & get_ext_cable(const om_id & om_) const;

    const om_id & get_om(const calo_signal_id & channel_) const;

    const signal_cabling_map_type & get_table() const;

    const reverse_signal_cabling_map_type & get_reverse_table() const;

    void build_om_from_board(const calo_signal_id & board_,
                             std::vector<om_id> & list_) const;

    void build_om_from_crate(const calo_signal_id & crate_,
                             std::vector<om_id> & list_) const;

    void print(std::ostream & out_ = std::clog) const;

    enum load_tag {
      LOAD_DEBUG = 0x0
    };

    void load(const std::string & filename_, const unsigned int tags_ = 0);

    void clear();

  private:

    signal_cabling_map_type         _table_;         ///< Main signal readout cabling map
    reverse_signal_cabling_map_type _reverse_table_; ///< Slave reverse signal readout cabling map

  };

} // namespace sncabling

#endif // SNCABLING_CALO_SIGNAL_CABLING_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --

