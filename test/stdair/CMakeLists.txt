#
# StdAir Tests
#
module_set_name (stdair)


##
# Specify each test suite configuration

# * StdAir Test Suite
file (GLOB stdairtest_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
module_test_add_suite (StdAirTest "${stdairtest_SOURCES}" stdair)


##
# Register all the test suites to be built and performed
module_test_build_all ()
