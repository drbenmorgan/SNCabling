#-----------------------------------------------------------------------
# Configure Sncabling library
#
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

# Configured sources
configure_file(sncabling_config.h.in sncabling_config.h @ONLY)
configure_file(sncabling.cc.in      sncabling.cc      @ONLY)
configure_file(resource_files.cc.in resource_files.cc @ONLY)
configure_file(version.h.in version.h @ONLY)

string(RANDOM LENGTH 18 MANGLE_BINRELOC_MAIN)
set(MANGLE_BINRELOC "SNCABLINGMB${MANGLE_BINRELOC_MAIN}")
configure_file(sncabling_binreloc.h.in sncabling_binreloc.h @ONLY)


# Build and link the library
add_library(SNCabling SHARED
  ${CMAKE_CURRENT_BINARY_DIR}/sncabling_config.h
  ${CMAKE_CURRENT_BINARY_DIR}/version.h
  version.cc
  ${CMAKE_CURRENT_BINARY_DIR}/sncabling.cc
  sncabling.h
  ${CMAKE_CURRENT_BINARY_DIR}/resource_files.cc
  resource_files.h
  ${CMAKE_CURRENT_BINARY_DIR}/sncabling_binreloc.h
  sncabling_binreloc.c
  calo_hv_cabling.cc
  calo_hv_cabling.h
  calo_hv_id.cc
  calo_hv_id.h
  calo_signal_cabling.cc
  calo_signal_cabling.h
  calo_signal_id.cc
  calo_signal_id.h
  exception.h
  label.cc
  label.h
  lis_cabling.cc
  lis_cabling.h
  lis_id.cc
  lis_id.h
  logger.h
  om_id.cc
  om_id.h
  sncabling_library.cc
  sncabling_library.h
  testing
  time_mark.cc
  time_mark.h
  utils.cc
  utils.h
  )

if(SNCABLING_WITH_SERVICE)
  target_sources(SNCabling PRIVATE service.h service.cc)
endif()

target_compile_definitions(SNCabling PRIVATE ENABLE_BINRELOC)
target_compile_features(SNCabling PUBLIC ${SNCABLING_CXX_COMPILE_FEATURES})
target_include_directories(SNCabling
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
target_link_libraries(SNCabling PUBLIC Boost::filesystem Boost::date_time Boost::system)
if(SNCABLING_WITH_SERVICE)
  target_link_libraries(SNCabling PUBLIC Bayeux::Bayeux)
endif()

# Alias the library so that SNCabling can be used as a subproject
add_library(SNCabling::SNCabling ALIAS SNCabling)

# - Install the target and headers
install(TARGETS SNCabling
  EXPORT  SNCablingTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_BINARY_DIR}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sncabling
  FILES_MATCHING PATTERN "*.h"
  PATTERN "sncabling_binreloc.h" EXCLUDE
  PATTERN "testing" EXCLUDE
  PATTERN "CMakeFiles" EXCLUDE
  )

if(BUILD_TESTING)
  add_subdirectory(testing)
endif()

