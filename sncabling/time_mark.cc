// sncabling/time_mark.cc - Implementation of the time mark data
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
#include <sncabling/time_mark.h>

// Standard Library:
#include <sstream>

// This project:
#include <sncabling/exception.h>

namespace sncabling {

  // static
  const time_mark & time_mark::invalid_time_mark()
  {
    static const time_mark _itm;
    return _itm;
  }
  
  time_mark::time_mark()
  {
    return;
  }

  bool time_mark::is_complete() const
  {
    if (_mode_ == TIME_MARK_UNDEF) {
      return false;
    } else if (_mode_ == TIME_MARK_PERIOD) {
      if (_period_id_ < 0) return false;
    } else if (_mode_ == TIME_MARK_TIMEPOINT) {
      if (_time_.is_not_a_date_time()) return false;
    }
    return true;
  }

  bool time_mark::is_period() const
  {
    return _mode_ == TIME_MARK_PERIOD;
  }

  bool time_mark::is_time_point() const
  {
    return _mode_ == TIME_MARK_TIMEPOINT;
  }

  void time_mark::make_period(const int32_t period_id_)
  {
    _mode_ = TIME_MARK_PERIOD;
    SN_THROW_IF(period_id_ < 0, std::logic_error, "Invalid period ID [" << period_id_ << "]!");
    _period_id_ = period_id_;
    _time_ = boost::posix_time::not_a_date_time;
    return;
  }

  void time_mark::make_time_point(const boost::posix_time::ptime & pt_)
  {
    _mode_ = TIME_MARK_TIMEPOINT;
    _period_id_ = INVALID_PERIOD;
    SN_THROW_IF(pt_.is_not_a_date_time(), std::logic_error, "Invalid time point!");
    _time_ = pt_;
    return;
  }

  void time_mark::make_time_point(const std::string & time_repr_)
  {
    _mode_ = TIME_MARK_TIMEPOINT;
    _period_id_ = INVALID_PERIOD;
    {
      bool success = false;
      if (!success) {
        try {
          boost::posix_time::ptime pt(boost::posix_time::time_from_string(time_repr_));
          if (!pt.is_not_a_date_time()) {
            success = true;
            _time_ = pt;
          }
        } catch (...) {
        }
      }
      if (!success) {
        try {
          boost::posix_time::ptime pt(boost::posix_time::from_iso_string(time_repr_));
          if (!pt.is_not_a_date_time()) {
            success = true;
            _time_ = pt;
          }
        } catch (...) {
        }
      }
      SN_THROW_IF(!success, std::logic_error, "Invalid time representation '" << time_repr_ << "'!");
    }
    return;
  }

  void time_mark::invalidate()
  {
    _mode_      = TIME_MARK_UNDEF;
    _period_id_ = INVALID_PERIOD;
    _time_      = boost::posix_time::not_a_date_time;
    return;
  }
 
  int32_t time_mark::get_period_id() const
  {
    return _period_id_;
  }
    
  const boost::posix_time::ptime & time_mark::get_time() const
  {
    return _time_;
  }

  // friend
  std::ostream & operator<<(std::ostream & out_, const time_mark & tm_)
  {
    std::ostringstream sout;
    if (tm_.is_period()) {
      sout << "[P:" << tm_._period_id_ << ']';
    } else if (tm_.is_time_point()) {
      sout << "[T:" << boost::posix_time::to_iso_string(tm_._time_) << ']';
    } else {
      sout << "[?]";  
    }
    out_ << sout.str();
    return out_;
  }

} // namespace sncabling
