list(APPEND SNCabling_TESTS
  test-utils.cxx
  test-time_mark.cxx
  test-label.cxx
  test-om_id.cxx
  test-lis_id.cxx
  test-calo_hv_id.cxx
  test-calo_signal_id.cxx
  test-lis_cabling.cxx
  test-calo_hv_cabling.cxx
  test-calo_signal_cabling.cxx
  test-service.cxx
  )

if (SNCABLING_ENABLE_TESTING)
  foreach(_testsource ${SNCabling_TESTS})
    set(_sncabling_TEST_ENVIRONMENT "SNCABLING_RESOURCE_FILES_DIR=${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG}/resources")
    get_filename_component(_testname "${_testsource}" NAME_WE)
    string(REPLACE "-" ";" _testname_splitted ${_testname})
    list(APPEND _sncabling_TEST_ENVIRONMENT
      "SNCABLING_TESTING_DIR=${CMAKE_CURRENT_SOURCE_DIR}/testing")
    set(_testname "sncabling-${_testname}")
    add_executable(${_testname} ${_testsource})
    target_link_libraries(${_testname} SNCabling)
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_tests
      )
  endforeach()
endif()

# - end
