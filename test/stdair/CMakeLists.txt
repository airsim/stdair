#
# StdAir Tests
#
if (Boost_FOUND)

  # CMake macro (defined in config/add_test_suite.cmake)
  include (add_test_suite)

  enable_testing() 

  # * StdAir Test Suite
  file (GLOB stdairtest_SOURCES *.cpp)
  add_test_suite (StdAirTest "${stdairtest_SOURCES}" ${STDAIR_LIB_TARGET} ${BOOST_LIBS_FOR_TEST})

  # * Next test suite
  # ...

  # Don't forget to add the test suite to the DEPENDS argument list
  add_custom_target (
	check
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS StdAirTest)

endif()
