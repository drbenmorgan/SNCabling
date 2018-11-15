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
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(SNCablingClient VERSION 1.0.0)

find_package(SNCabling 1.0.0 REQUIRED NO_MODULE)

add_executable(sncablingclient sncablingclient.cxx)
target_link_libraries(sncablingclient SNCabling::SNCabling)

# - end

