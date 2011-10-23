## test/guillotine sub-directory
include $(top_srcdir)/Makefile.common

#
MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

#
check_PROGRAMS = guillotine

guillotine_SOURCES = guillotine.cpp
guillotine_CXXFLAGS = $(BOOST_CFLAGS)
guillotine_LDADD = $(BOOST_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB)
guillotine_LDFLAGS = $(top_builddir)/stdair/libstdair.la
