# -----------------------------------------------------
message( STATUS "[info] Define SNCabling dependencies")

if (SNCABLING_WITH_SERVICE)
  set(SNCABLING_WITH_BAYEUX_DEPENDENCY 1)
endif()

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
  endif()
endif()

  # -------------------------------------------------------
  # - Boost:
  # Boost is also important with specific libs
  message( STATUS "[info] Searching special Boost material for SNCabling...")
  set(SNCABLING_BOOST_MIN_VERSION ${BAYEUX_BOOST_VERSION})
  set(Boost_NO_BOOST_CMAKE ON)
  set(SNCABLING_BOOST_COMPONENTS
    ${BAYEUX_BOOST_COMPONENTS}
    )
  list(APPEND SNCABLING_BOOST_COMPONENTS log)
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
  # Qt5 support
  #
  # if (SNCABLING_WITH_QT_GUI)
  #   set(SNCablingLibrary_HEADERS_QT_TO_BE_MOCCED)
  #   find_package(Qt5Core    ${SNCABLING_QT5_VERSION} REQUIRED)
  #   find_package(Qt5Gui     ${SNCABLING_QT5_VERSION} REQUIRED)
  #   find_package(Qt5Widgets ${SNCABLING_QT5_VERSION} REQUIRED)
  #   find_package(Qt5Svg     ${SNCABLING_QT5_VERSION} REQUIRED)
  #   message (STATUS "[info] Include dirs         = ${Qt5Core_INCLUDE_DIRS}")
  #   message (STATUS "[info] Include private dirs = ${Qt5Core_PRIVATE_INCLUDE_DIRS}")
  #   message (STATUS "[info] Include dirs         = ${Qt5Gui_INCLUDE_DIRS}")
  #   message (STATUS "[info] Include private dirs = ${Qt5Gui_PRIVATE_INCLUDE_DIRS}")
  #   message (STATUS "[info] Include dirs         = ${Qt5Widgets_INCLUDE_DIRS}")
  #   message (STATUS "[info] Include private dirs = ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}")
  #   include_directories(
  #     ${Qt5Core_INCLUDE_DIRS}
  #     ${Qt5Core_PRIVATE_INCLUDE_DIRS}
  #     ${Qt5Gui_INCLUDE_DIRS}
  #     ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
  #     ${Qt5Widgets_INCLUDE_DIRS}
  #     ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
  #     )
  # endif()


  #-----------------------------------------------------------------------
  message( STATUS "[info] End of SNCabling dependencies")

  # end
