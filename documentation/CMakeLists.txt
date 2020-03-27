
# Minimal Doxygen build (requires CMake 3.9 or newer)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_EXCLUDE_PATTERNS "*.cc" "${PROJECT_BINARY_DIR}/*")
  set(DOXYGEN_STRIP_FROM_INC_PATH "${PROJECT_SOURCE_DIR}")
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")

  doxygen_add_docs(sncabling-doxygen
    README.md sncabling
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Doxygenating SNCabling"
  )
endif()

