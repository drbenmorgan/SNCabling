# - CMake build script for sncablingquery application

#-----------------------------------------------------------------------
# Copyright 2018 François Mauger <mauger@lpccaen.in2p3.fr>
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
message (STATUS "[info] Begin of 'source/sncablingquery/CMakeLists.txt'.")

#-----------------------------------------------------------------------
# Build utility script
#
message (STATUS "[info] Generating the 'sncablingquery' utility script...")
configure_file(sncablingquery.in ${CMAKE_CURRENT_BINARY_DIR}/sncablingquery @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sncablingquery
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  PERMISSIONS
  OWNER_READ OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  # COMPONENT Development
  )

message (STATUS "[info] End of 'source/sncablingquery/CMakeLists.txt'.")
