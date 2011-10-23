## test/stdair sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
SUBDIRS =

EXTRA_DIST =

##
# Test library
noinst_LTLIBRARIES = libstdairtest.la

libstdairtest_la_SOURCES = \
	$(stdair_test_lib_h_sources) $(stdair_test_lib_cc_sources)
libstdairtest_la_CXXFLAGS =
libstdairtest_la_LDFLAGS = \
	$(top_builddir)/stdair/core/libstdair.la


##
# Test binaries
#
nofail_PRG = StandardAirlineITTestSuite
fail_PRG =

#
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = ${nofail_PRG:%=%_utfresults.xml} ${nofail_PRG:%=%.log} \
	StandardAirlineITTestSuite_*.log StandardAirlineITTestSuite_serial.txt

#
check_PROGRAMS = $(nofail_PRG) $(fail_PRG)
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = $(fail_PRG)

#
StandardAirlineITTestSuite_SOURCES = \
	$(stdair_test_bin_h_sources) $(stdair_test_bin_cc_sources)
StandardAirlineITTestSuite_CXXFLAGS = $(BOOST_CFLAGS)
StandardAirlineITTestSuite_LDADD = 
StandardAirlineITTestSuite_LDFLAGS = \
	$(BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB) \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/test/stdair/libstdairtest.la
