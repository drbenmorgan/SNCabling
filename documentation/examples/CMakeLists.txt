

add_executable(ex_calo_hv_cabling ex_calo_hv_cabling.cxx)
target_link_libraries(ex_calo_hv_cabling SNCabling)
set_target_properties(ex_calo_hv_cabling
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_examples
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_examples
  )

if (SNCABLING_WITH_SERVICE)
  add_executable(ex_cabling_service ex_cabling_service.cxx)
  target_link_libraries(ex_cabling_service SNCabling)
  set_target_properties(ex_cabling_service
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_examples
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sncabling_examples
    )
  
endif()
# - end
