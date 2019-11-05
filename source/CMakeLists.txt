# - CMake script for SNCabling Library and Apps
#
#-----------------------------------------------------------------------
# Copyright 2018, François Mauger <mauger@lpccaen.in2p3.fr>
#
# This file is part of SNCabling.
#
# SNCabling is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SNCabling is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SNCabling. If not, see <http://www.gnu.org/licenses/>.
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Core configuration
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SNCABLING_BUILD_PREFIX}/include)
include_directories(${SNCABLING_BUILD_PREFIX}/include/sncabling)
#
#-----------------------------------------------------------------------
# Libraries and apps
#

#-----------------------------------------------------------------------
# Main SNCabling library + protobuf support:
add_subdirectory(sncabling)

#-----------------------------------------------------------------------
# Apps
add_subdirectory(sncablingquery)

