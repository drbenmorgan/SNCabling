//! \file    sncabling/time_mark.h
//! \brief   SuperNEMO Cabling utilities
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

#ifndef SNCABLING_TIME_MARK_H
#define SNCABLING_TIME_MARK_H

// Standard Library:
#include <string>
#include <iostream>

// Third party:
#include <boost/date_time/posix_time/posix_time.hpp>

namespace sncabling {

  /// \brief Time mark
  ///
  /// A time_mark object represents a mark in time. It may be
  /// implemented as the unique identifier of a given period
  /// or an effective time point (presumably UTC).
  class time_mark
  {
  public:
    
    enum time_mark_mode {
      TIME_MARK_UNDEF     = 0,
      TIME_MARK_PERIOD    = 1,
      TIME_MARK_TIMEPOINT = 2
    };

    static const int32_t INVALID_PERIOD = -1;

    /// Constructor
    time_mark();

    void make_period(const int32_t);

    void make_time_point(const boost::posix_time::ptime &);

    void make_time_point(const std::string &);

    void invalidate();

    bool is_complete() const;

    bool is_period() const;

    bool is_time_point() const;

    int32_t get_period_id() const;
    
    const boost::posix_time::ptime & get_time() const;

    friend std::ostream & operator<<(std::ostream & out_, const time_mark & tm_);

    static const time_mark & invalid_time_mark();
    
  private:
                
    time_mark_mode           _mode_      = TIME_MARK_UNDEF;
    int32_t                  _period_id_ = INVALID_PERIOD;
    boost::posix_time::ptime _time_      = boost::posix_time::not_a_date_time;
                
  };

} // namespace sncabling

#endif // SNCABLING_TIME_MARK_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --

