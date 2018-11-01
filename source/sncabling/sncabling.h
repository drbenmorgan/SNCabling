//! \file    sncabling/sncabling.h
//! \brief   Provide system init for SNCabling internals
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

#ifndef SNCABLING_SNCABLING_H
#define SNCABLING_SNCABLING_H

// Standard Library:
#include <string>

//! Main namespace for the SNCabling library
namespace sncabling {

  //! Check if the SNCabling library is initialized
  bool is_initialized();

  //! Initialize special resources of the SNCabling library
  void initialize(int argc_ = 0, char * argv_[] = 0, uint32_t flags_ = 0);

  //! Terminate special resources of the SNCabling library
  void terminate();

} // namespace sncabling

#endif // SNCABLING_SNCABLING_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
