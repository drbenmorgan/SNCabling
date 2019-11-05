if (SNCABLING_WITH_SERVICE)
  set(SNCABLING_WITH_BAYEUX_DEPENDENCY 1)
endif()

# Default Boost version:
set(SNCABLING_BOOST_MIN_VERSION "1.53")
set(SNCABLING_BOOST_COMPONENTS "filesystem" "date_time" "system")

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
  find_package(Bayeux ${SNCABLING_BAYEUX_MIN_VERSION} REQUIRED NO_MODULE)
  if (Bayeux_FOUND)
    set(SNCabling_BAYEUX_VERSION ${Bayeux_VERSION})
    set(SNCABLING_BOOST_MIN_VERSION ${BAYEUX_BOOST_VERSION})
    list(APPEND SNCABLING_BOOST_COMPONENTS
      ${BAYEUX_BOOST_COMPONENTS}
      )
  endif()
endif()

# -------------------------------------------------------
# - Boost:
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${SNCABLING_BOOST_MIN_VERSION} REQUIRED
  COMPONENTS ${SNCABLING_BOOST_COMPONENTS}
  )
set(SNCabling_Boost_VERSION ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION})
set(SNCabling_Boost_LIBRARIES)
foreach(_sncabling_boost_lib ${SNCABLING_BOOST_COMPONENTS})
  list(APPEND SNCabling_Boost_LIBRARIES Boost::${_sncabling_boost_lib})
endforeach()
