## stdair/ui/cmdline sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libstdairui.la

libstdairui_la_SOURCES = $(stdair_cmd_h_sources) $(stdair_cmd_cc_sources) 
libstdairui_la_CXXFLAGS = $(BOOST_CFLAGS) 
libstdairui_la_LDFLAGS =


# Header files
pkgincludedir = $(includedir)/stdair/ui/cmdline
pkginclude_HEADERS = $(stdair_cmd_h_sources)

