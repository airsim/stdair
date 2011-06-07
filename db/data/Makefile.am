## db/data sub-directory of the StdAir project
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
SUBDIRS =

MAINTAINERCLEANFILES = Makefile.in Makefile

##
datadir = @datadir@
pkgdatadir = @pkgdatadir@
dbdir = @dbdir@/data

#
noinst_DATA = $(db_data_csv_sources)

EXTRA_DIST = $(noinst_DATA)

# Targets
install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(dbdir); \
	for f in $(db_data_csv_sources); do \
		$(INSTALL_DATA) $$f $(DESTDIR)$(dbdir); \
	done

uninstall-local:
	rm -rf $(DESTDIR)$(dbdir)

clean-local:
	rm -rf *.log *.tag
