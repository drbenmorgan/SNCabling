# - Top level CMake script for SNCabling

#-----------------------------------------------------------------------
# Copyright (C) 2018 François Mauger <mauger@lpccaen.in2p3.fr>
# Copyright (C) 2018 Yves Lemière <lemiere@lpccaen.in2p3.fr>
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SNCabling.  If not, see <http://www.gnu.org/licenses/>.
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Enforce an out-of-source build.
#
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "SNCabling requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

#-----------------------------------------------------------------------
# CMake/project requirements and configuration
#
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(SNCabling
  VERSION 1.0.0
  DESCRIPTION "SuperNEMO Demonstrator Cabling Conditions Database"
  )

# - Load custom modules
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

#-----------------------------------------------------------------------
# Common LPC utilities
#
include(LPCCMakeSettings)

#-----------------------------------------------------------------------
# Primary dependencies
#
find_package(Boost 1.64 REQUIRED filesystem date_time system)

#-----------------------------------------------------------------------
# Useful variables
set(SNCABLING_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
set(SNCABLING_BINARY_DIR "${PROJECT_BINARY_DIR}")

#-----------------------------------------------------------------------
# Set up testing (CTest provides the "BUILD_TESTING" option)
#
include(CTest)

#-----------------------------------------------------------------------
# Configure/Build optional components
#
option(SNCABLING_WITH_DEVELOPER_TOOLS "Build/install developer tools" ON)
mark_as_advanced(SNCABLING_WITH_DEVELOPER_TOOLS)

option(SNCABLING_WITH_SERVICE "Build Bayeux service support for SNCabling" OFF)
if(SNCABLING_WITH_SERVICE)
  find_package(Bayeux 3.4.0 REQUIRED)
endif()

option(SNCABLING_WITH_DOCS "Build documentation for SNCabling" ON)

#-----------------------------------------------------------------------
# Build the subdirectories as required
#
add_subdirectory(sncabling)
add_subdirectory(programs)
add_subdirectory(resources)
if(SNCABLING_WITH_DOCS)
  add_subdirectory(documentation)
endif()

#-----------------------------------------------------------------------
# - CMake Support files
include(CMakePackageConfigHelpers)

# - Versioning file is the same for the build and install trees
write_basic_package_version_file(
  ${SNCABLING_BUILD_CMAKEDIR}/${SNCABLING_TAG}/SNCablingConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
  )

# - Config file is also the same in build/install trees as we use same layout
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/SNCablingConfig.cmake.in
  ${SNCABLING_BUILD_CMAKEDIR}/${SNCABLING_TAG}/SNCablingConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${PROJECT_TAG}
  PATH_VARS
    CMAKE_INSTALL_BINDIR
    CMAKE_INSTALL_LIBDIR
    CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_DATAROOTDIR
    )

# - Targets (build tree)
export(EXPORT SNCablingTargets
  NAMESPACE SNCabling::
  FILE ${SNCABLING_BUILD_CMAKEDIR}/${SNCABLING_TAG}/SNCablingTargets.cmake
  )

# - Targets (install tree)
install(EXPORT SNCablingTargets
  NAMESPACE SNCabling::
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${SNCABLING_TAG}
  )

# - Installation of, well, install tree files
install(
  FILES
    ${PROJECT_BUILD_CMAKEDIR}/${SNCABLING_TAG}/SNCablingConfigVersion.cmake
    ${PROJECT_BUILD_CMAKEDIR}/${SNCABLING_TAG}/SNCablingConfig.cmake
  DESTINATION
    ${CMAKE_INSTALL_CMAKEDIR}/${SNCABLING_TAG}
  )

