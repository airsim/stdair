## db/admin sub-directory of the StdAir project
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
SUBDIRS =

MAINTAINERCLEANFILES = Makefile.in Makefile

##
libexecdir = @libexecdir@/@PACKAGE@

#
noinst_DATA = $(db_admin_sh_in_sources)

EXTRA_DIST = $(noinst_DATA)

# Targets
install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(libexecdir); \
	for f in $(db_admin_sh_sources); do \
		$(INSTALL_DATA) $$f $(DESTDIR)$(libexecdir); \
	done

uninstall-local:
	rm -rf $(DESTDIR)$(libexecdir)

clean-local:
	rm -rf *.log *.tag
