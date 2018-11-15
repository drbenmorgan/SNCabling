message(STATUS "[info] Begin of 'source/sncabling/CMakeLists.txt'")


#-----------------------------------------------------------------------
# Configure Sncabling library
#

message(STATUS "[debug] SNCABLING_LIBDIR_TO_RESOURCEDIR = '${SNCABLING_LIBDIR_TO_RESOURCEDIR}'")
message(STATUS "[debug] SNCABLING_LIBDIR_TO_PLUGINDIR   = '${SNCABLING_LIBDIR_TO_PLUGINDIR}'")
# set(SNCABLING_DATAROOTDIR ${SNCABLING_BUILD_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${SNCABLING_TAG})
# set(SNCABLING_DATAROOTDIR ${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG})
# message(STATUS "[debug] SNCABLING_DATAROOTDIR           = '${SNCABLING_DATAROOTDIR}'")


# -- RPATH settings --
# From: https://cmake.org/Wiki/CMake_RPATH_handling
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

set(SNCablingLibrary_DEFINITIONS
  -std=c++11
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS ${SNCablingLibrary_DEFINITIONS})
endif()

set(SNCablingLibrary_HEADERS
  sncabling_config.h.in
  resource_files.h
  version.h.in
  label.h
  sncabling_library.h
  om_id.h
  lis_id.h
  calo_hv_id.h
  calo_signal_id.h
  lis_cabling.h
  calo_hv_cabling.h
  calo_signal_cabling.h
  service.h
  utils.h
  time_mark.h
  )

#-----------------------------------------------------------------------
# Declare sources
#
configure_file(sncabling.cc.in      sncabling.cc      @ONLY)
configure_file(resource_files.cc.in resource_files.cc @ONLY)

string(RANDOM LENGTH 18 MANGLE_BINRELOC_MAIN)
set(MANGLE_BINRELOC "SNCABLINGMB${MANGLE_BINRELOC_MAIN}")
configure_file(sncabling_binreloc.h.in sncabling_binreloc.h @ONLY)

set(SNCablingLibrary_SOURCES
  service.cc
  version.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sncabling.cc
  ${CMAKE_CURRENT_BINARY_DIR}/resource_files.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sncabling_binreloc.h
  sncabling_binreloc.c
  sncabling_library.cc
  label.cc
  om_id.cc
  lis_id.cc
  lis_cabling.cc
  calo_hv_id.cc
  calo_signal_id.cc
  calo_hv_cabling.cc
  calo_signal_cabling.cc
  utils.cc
  time_mark.cc
  )

# - Publish headers
foreach(_hdrin ${SNCablingLibrary_HEADERS})
  string(REGEX REPLACE "\\.in$" "" _hdrout "${_hdrin}")
  configure_file(${_hdrin} ${SNCABLING_BUILD_PREFIX}/include/sncabling/${_hdrout} @ONLY)
endforeach()

#-----------------------------------------------------------------------
# Build/Link Library
#
include_directories(${SNCABLING_BUILD_PREFIX}/include)

#-----------------------------------------------------------------------
# Build/Link the library
#
add_library(SNCabling SHARED
  ${SNCablingLibrary_HEADERS}
  ${SNCablingLibrary_PRIVATE_HEADERS}
  ${SNCablingLibrary_SOURCES}
  ${_SNCablingProtobufLibrary_cpp_HEADERS}
  ${_SNCablingProtobufLibrary_cpp_SOURCES}
  )
# Doc: https://cmake.org/Wiki/CMake_FAQ#How_can_I_add_a_dependency_to_a_source_file_which_is_generated_in_a_subdirectory.3F
# Tell CMake the source won't be available until build time.
set_source_files_properties(${_SNCablingProtobufLibrary_cpp_HEADERS} PROPERTIES GENERATED 1)
set_source_files_properties(${_SNCablingProtobufLibrary_cpp_SOURCES} PROPERTIES GENERATED 1)
set_target_properties(SNCabling PROPERTIES LINKER_LANGUAGE CXX)
foreach(_pb_target ${_SNCablingProtobufLibrary_cpp_TARGETS})
  message( STATUS "[info] ##### Adding new dependency from target='${_pb_target}'")
  add_dependencies(SNCabling ${_pb_target})
endforeach()

target_compile_definitions(SNCabling PRIVATE ENABLE_BINRELOC)
message( STATUS "[debug] SNCABLING_CXX_COMPILE_FEATURES = '${SNCABLING_CXX_COMPILE_FEATURES}'")
target_compile_features(SNCabling PUBLIC ${SNCABLING_CXX_COMPILE_FEATURES})
# set_property(TARGET SNCabling APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include/sncabling>  # <prefix>/include/sncabling
#   )
message( STATUS "[debug] SNCABLING_BUILD_PREFIX   = '${SNCABLING_BUILD_PREFIX}'")
message( STATUS "[debug] CMAKE_CURRENT_BINARY_DIR = '${CMAKE_CURRENT_BINARY_DIR}'")
message( STATUS "[debug] CMAKE_INSTALL_INCLUDEDIR = '${CMAKE_INSTALL_INCLUDEDIR}'")
# - Use BinReloc
set_target_properties(SNCabling PROPERTIES COMPILE_DEFINITIONS ENABLE_BINRELOC)
# target_compile_definitions(SNCabling PRIVATE ENABLE_BINRELOC)

target_include_directories(SNCabling
  PUBLIC
  $<BUILD_INTERFACE:${SNCABLING_BUILD_PREFIX}/include>
  $<BUILD_INTERFACE:${SNCABLING_BUILD_PREFIX}/include/sncabling>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sncabling>
  )

message( STATUS "[debug] SNCabling_Boost_LIBRARIES    = '${SNCabling_Boost_LIBRARIES}'")
target_link_libraries(SNCabling PUBLIC
  Bayeux::Bayeux
  ${SNCabling_Boost_LIBRARIES}
  )

# - Install it
install(TARGETS SNCabling
  EXPORT  SNCablingTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

# - Install public headers (preliminary)
install(DIRECTORY ${SNCABLING_BUILD_PREFIX}/include/sncabling
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
  FILES_MATCHING PATTERN "*.h"
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
  )

add_subdirectory(testing)

message(STATUS "[info] End of 'source/sncabling/CMakeLists.txt'.")

# - end