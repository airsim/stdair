# StdAir project batches
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
# Binaries (batches)
bin_PROGRAMS = stdair

##
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = ${bin_PROGRAMS:%=%.log}

##
#
stdair_SOURCES = $(stdair_batches_h_sources) $(stdair_batches_cc_sources)
stdair_CXXFLAGS = $(BOOST_CFLAGS)
stdair_LDADD = 
stdair_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/libstdair.la
