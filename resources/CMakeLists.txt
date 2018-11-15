# - installation of resource files and dirs:

message (STATUS "[info]   CMAKE_INSTALL_DATAROOTDIR = '${CMAKE_INSTALL_DATAROOTDIR}'")
message (STATUS "[info]   CMAKE_CURRENT_SOURCE_DIR  = '${CMAKE_CURRENT_SOURCE_DIR}'")
message (STATUS "[info]   PROJECT_BUILD_DATAROOTDIR = '${PROJECT_BUILD_DATAROOTDIR}'")
message (STATUS "[info]   SNCABLING_TAG             = '${SNCABLING_TAG}'")

# - Copy resource files from the source dir to the build dir:
add_custom_target(SNCablingResources ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/config
  ${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG}/resources/config
  )

add_custom_target(SNCablingExamples ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/examples
  ${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG}/resources/examples
  )

message (STATUS "[info] Configuration resource files installation directive.")
install(DIRECTORY ${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG}/resources/config/		       
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${SNCABLING_TAG}/resources/config
  FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
  DIRECTORY_PERMISSIONS
  OWNER_READ GROUP_READ WORLD_READ
  OWNER_WRITE  
  OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
  PATTERN "*~" EXCLUDE PATTERN "_*" EXCLUDE
  )

message (STATUS "[info] Example resource files installation directive.")
install(DIRECTORY ${PROJECT_BUILD_DATAROOTDIR}/${SNCABLING_TAG}/resources/examples/
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${SNCABLING_TAG}/resources/examples
  FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
  DIRECTORY_PERMISSIONS
  OWNER_READ GROUP_READ WORLD_READ
  OWNER_WRITE  
  OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
  PATTERN "*~" EXCLUDE PATTERN "_*" EXCLUDE
  )

# - end