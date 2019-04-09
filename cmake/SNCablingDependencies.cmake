# -----------------------------------------------------
message( STATUS "[info] Define SNCabling dependencies")

if (SNCABLING_WITH_SERVICE)
  set(SNCABLING_WITH_BAYEUX_DEPENDENCY 1)
endif()

# Default Boost version:
set(SNCABLING_BOOST_MIN_VERSION "1.53")
set(SNCABLING_BOOST_COMPONENTS "filesystem" "date_time" )

if (SNCABLING_WITH_BAYEUX_DEPENDENCY)
  #-------------------------------------------------------
  # Bayeux
  #
  # Bayeux is the main external dependency, and we know it will additionally
  # search for and provide compatible versions of:
  #
  # - Boost
  # - GSL
  # - ROOT
  set(SNCABLING_BAYEUX_MIN_VERSION "3.4.0")
  message( STATUS "[info] Searching Bayeux ${SNCABLING_BAYEUX_MIN_VERSION}...")
  find_package(Bayeux ${SNCABLING_BAYEUX_MIN_VERSION} REQUIRED NO_MODULE)
  if (Bayeux_FOUND)
    message( STATUS "[info] Bayeux ${Bayeux_VERSION} found.")
    message( STATUS "[info] BAYEUX_BOOST_VERSION    = '${BAYEUX_BOOST_VERSION}'")
    # Trick because BayeuxConfig 3.2 does not provide the BAYEUX_BOOST_COMPONENTS variable:
    set(SNCabling_BAYEUX_VERSION ${Bayeux_VERSION})
    # # Trick because BayeuxConfig 3.2 does not provide the BAYEUX_BOOST_COMPONENTS variable:
    # set(BAYEUX_BOOST_COMPONENTS
    #   "filesystem;system;serialization;iostreams;program_options;regex;thread"
    #   )
    message( STATUS "[info] BAYEUX_BOOST_COMPONENTS = '${BAYEUX_BOOST_COMPONENTS}'")
    message( STATUS "[info] Bayeux_CMAKE_CONFIG_DIR = '${Bayeux_CMAKE_CONFIG_DIR}'")
    set(SNCABLING_BOOST_MIN_VERSION ${BAYEUX_BOOST_VERSION})
    list(APPEND SNCABLING_BOOST_COMPONENTS
      ${BAYEUX_BOOST_COMPONENTS}
      )
  endif()
endif()

# -------------------------------------------------------
# - Boost:
message( STATUS "[info] Searching Boost for SNCabling...")
set(Boost_NO_BOOST_CMAKE ON)
message( STATUS "[info] SNCABLING_BOOST_COMPONENTS   = '${SNCABLING_BOOST_COMPONENTS}'")
message( STATUS "[info] Finding Boost with specific libraries...")
find_package(Boost ${SNCABLING_BOOST_MIN_VERSION} REQUIRED
  ${SNCABLING_BOOST_COMPONENTS}
  )
set(SNCabling_Boost_VERSION ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION})
set(SNCabling_Boost_LIBRARIES)
foreach(_sncabling_boost_lib ${SNCABLING_BOOST_COMPONENTS})
  list(APPEND SNCabling_Boost_LIBRARIES Boost::${_sncabling_boost_lib})
endforeach()
message(STATUS "[info] SNCabling_Boost_VERSION   = '${SNCabling_Boost_VERSION}'")
message(STATUS "[info] SNCabling_Boost_LIBRARIES = '${SNCabling_Boost_LIBRARIES}'")
# message(STATUS "[info] Boost_LIBRARIES               = '${Boost_LIBRARIES}'")
# message(STATUS "[info] Boost_FILESYSTEM_LIBRARY      = '${Boost_FILESYSTEM_LIBRARY}'")
# message(STATUS "[info] Boost_SYSTEM_LIBRARY          = '${Boost_SYSTEM_LIBRARY}'")
# message(STATUS "[info] Boost_SERIALIZATION_LIBRARY   = '${Boost_SERIALIZATION_LIBRARY}'")
# message(STATUS "[info] Boost_IOSTREAMS_LIBRARY       = '${Boost_IOSTREAMS_LIBRARY}'")
# message(STATUS "[info] Boost_PROGRAM_OPTIONS_LIBRARY = '${Boost_PROGRAM_OPTIONS_LIBRARY}'")
# message(STATUS "[info] Boost_DATE_TIME_LIBRARY       = '${Boost_DATE_TIME_LIBRARY}'")
# message(STATUS "[info] Boost_THREAD_LIBRARY          = '${Boost_THREAD_LIBRARY}'")
# message(STATUS "[info] Boost_LOG_LIBRARY             = '${Boost_LOG_LIBRARY}'")
# message(STATUS "[info] Boost_LOG_SETUP_LIBRARY       = '${Boost_LOG_SETUP_LIBRARY}'")

#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
message( STATUS "[info] End of SNCabling dependencies")

# end
