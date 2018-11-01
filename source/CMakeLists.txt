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
message (STATUS "[info] Begin of 'source/CMakeLists.txt'.")

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
message( STATUS "[info] Adding subdirectory 'sncabling'...")
add_subdirectory(sncabling)

#-----------------------------------------------------------------------
# Apps
message( STATUS "[info] Adding subdirectory 'sncablingquery'...")
add_subdirectory(sncablingquery)

#-----------------------------------------------------------------------
# Manual
#
if(Pandoc_FOUND)
  set(SNCABLING_MANPAGE_IN  ${CMAKE_CURRENT_SOURCE_DIR}/SNCabling.1.md)
  set(SNCABLING_MANPAGE_OUT ${SNCABLING_BUILD_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${SNCABLING_TAG}/man/man1/SNCabling.1)

  add_custom_command(OUTPUT ${SNCABLING_MANPAGE_OUT}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SNCABLING_BUILD_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${SNCABLING_TAG}/man/man1
    COMMAND ${Pandoc_EXECUTABLE} -s -w man ${SNCABLING_MANPAGE_IN} -o ${SNCABLING_MANPAGE_OUT}
    COMMENT "Generating SNCabling.1 man page"
    DEPENDS ${SNCABLING_MANPAGE_IN}
    )
  add_custom_target(vire_man ALL DEPENDS ${SNCABLING_MANPAGE_OUT})
endif()

message (STATUS "[info] End of 'source/CMakeLists.txt'.")

#- end
