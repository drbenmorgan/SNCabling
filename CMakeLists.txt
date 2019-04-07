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
message (STATUS "[info] Begin of 'CMakeLists.txt'.")

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
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(SNCabling)

# - Load custom modules
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

# - Version number management utilities:
include(BxVersionManager)

# - Versioning only giving major and minor. Patch number is
#   automatically deduced from an external file.
bx_version_set(SNCabling 1 0)
message(STATUS "[info] Project version = '${PROJECT_VERSION}'")

#-----------------------------------------------------------------------
# Common LPC utilities
#
include(LPCCMakeSettings)

# - SVN revision number for dev builds
include(LPCSVNUtilities)
set(SNCabling_VERSION_REVISION 0)

Subversion_DIRECTORY_IS_WC(${PROJECT_SOURCE_DIR} SNCabling)
if(SNCabling_DIRECTORY_IS_WC)
  Subversion_WC_INFO(${PROJECT_SOURCE_DIR} SNCabling)
  set(SNCabling_VERSION_REVISION ${SNCabling_WC_REVISION})
endif()


message (STATUS "[info] SNCABLING_LIBDIR_TO_RESOURCEDIR = '${SNCABLING_LIBDIR_TO_RESOURCEDIR}'")
 
#-----------------------------------------------------------------------
# Useful variables
set(SNCABLING_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
set(SNCABLING_BINARY_DIR "${PROJECT_BINARY_DIR}")

#-----------------------------------------------------------------------
# Configure testing if required
#
option(SNCABLING_ENABLE_TESTING "Build unit testing system for SNCabling" ON)
if(SNCABLING_ENABLE_TESTING)
  enable_testing()
endif()

#-----------------------------------------------------------------------
# Configure/Build utilities as needed
#
option(SNCABLING_WITH_DEVELOPER_TOOLS "Build/install developer tools" ON)
mark_as_advanced(SNCABLING_WITH_DEVELOPER_TOOLS)

#-----------------------------------------------------------------------
# Optional build of documentation
#
option(SNCABLING_WITH_SERVICE "Build service support for SNCabling (depends on Bayeux)" OFF)

#-----------------------------------------------------------------------
# Optional build of documentation
#
option(SNCABLING_WITH_DOCS "Build documentation for SNCabling" ON)

#-----------------------------------------------------------------------
# Debug
message( STATUS "[info] SNCabling_VERSION              = '${SNCabling_VERSION}'")
message( STATUS "[info] SNCABLING_SOURCE_DIR           = '${SNCABLING_SOURCE_DIR}'")
message( STATUS "[info] SNCABLING_BINARY_DIR           = '${SNCABLING_BINARY_DIR}'")
message( STATUS "[info] SNCABLING_ENABLE_TESTING       = '${SNCABLING_ENABLE_TESTING}'")
message( STATUS "[info] SNCABLING_WITH_DEVELOPER_TOOLS = '${SNCABLING_WITH_DEVELOPER_TOOLS}'")
message( STATUS "[info] SNCABLING_WITH_DOCS            = '${SNCABLING_WITH_DOCS}'")

#-----------------------------------------------------------------------
include(SNCablingDependencies)

#-----------------------------------------------------------------------
# Build the subdirectories as required
#
message( STATUS "[info] Adding subdirectory 'source'...")
add_subdirectory(source)

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

message(STATUS "[debug] CMAKE_INSTALL_CMAKEDIR = '${CMAKE_INSTALL_CMAKEDIR}'")
message(STATUS "[debug] PROJECT_TAG            = '${PROJECT_TAG}'")

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

#-----------------------------------------------------------------------
# - Install published resources and documentation

#-----------------------------------------------------------------------
# Resource installation
add_subdirectory(resources)

message (STATUS "[info] End of 'CMakeLists.txt'.")

# - end