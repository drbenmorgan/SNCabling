//! \file    sncabling/logger.h
//! \brief   Logging handling macros
//! \details
//
// Copyright (c) 2019 by Francois Mauger <mauger@lpccaen.in2p3.fr>
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

#ifndef SNCABLING_LOGGER_H
#define SNCABLING_LOGGER_H

// Standard Library:
#include <string>
#include <iostream>
#include <sstream>

// - Boost:
#include <boost/current_function.hpp>

#define SN_LOG_DEBUG(Debug, Message)					\
  {									\
  if (Debug) { \
    std::stringstream sSN_LOG;						\
    sSN_LOG << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ":debug:" << Message << "]"; \
    std::cerr << sSN_LOG.str() << std::endl;				\
  } \
}

#define SN_LOG_ERROR(Message)						\
  {									\
  std::stringstream sSN_LOG;						\
  sSN_LOG << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ":error:" << Message << "]"; \
  std::cerr << sSN_LOG.str() << std::endl;				\
}

#endif // SNCABLING_LOGGER_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
