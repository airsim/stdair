## stdair/ui/cmdline sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
# User Interface (UI) library for StdAir
lib_LTLIBRARIES = libstdairuicl.la

##
#
MAINTAINERCLEANFILES = Makefile.in

libstdairuicl_la_SOURCES = $(stdair_cmd_h_sources) $(stdair_cmd_cc_sources) 
libstdairuicl_la_CXXFLAGS = $(BOOST_CFLAGS)
libstdairuicl_la_LIBADD =
libstdairuicl_la_LDFLAGS = \
	$(READLINE_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/core/libstdair.la \
	-version-info $(GENERIC_LIBRARY_VERSION)

# Header files
pkgincludedir = $(includedir)/stdair/ui/cmdline
pkginclude_HEADERS = $(stdair_cmd_h_sources)
