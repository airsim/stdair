# Process this file with autoconf to produce a configure script
#-------------------------------------------------------------------
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2007-2011  Denis Arnaud <denis_arnaud@users.sourceforge.net>])
AC_INIT([STDAIR],[0.40.0],[denis_arnaud@users.sourceforge.net],[stdair])
AC_CONFIG_HEADER([stdair/config.h])
AC_CONFIG_SRCDIR([stdair/bom/BomRoot.hpp])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE
AM_PATH_CPPUNIT(1.10)
AM_CONDITIONAL([HAVE_CPPUNIT], [test "x$CPPUNIT_LIBS" != x])

# Package name
PACKAGE_PRETTY_NAME="StdAir"
AC_SUBST(PACKAGE_PRETTY_NAME)

# Shared library versioning
GENERIC_LIBRARY_VERSION="0:40:0"
#                        | | |
#                 +------+ | +---+
#                 |        |     |
#              current:revision:age
#                 |        |     |
#                 |        |     +- increment if interfaces have been added;
#                 |        |        set to zero if interfaces have been 
#                 |        |        removed or changed
#                 |        +- increment if source code has changed;
#                 |           set to zero if current is incremented
#                 +- increment if interfaces have been added, removed
#                    or changed
AC_SUBST(GENERIC_LIBRARY_VERSION)

# Check for host and disable building a shared library in Windows
AC_CANONICAL_HOST
case $host in
  *-*-msdos* | *-*-go32* | *-*-mingw32* | *-*-cygwin* | *-*-windows*) 
    AC_DISABLE_SHARED
    AC_ENABLE_STATIC
    ;;
  *)  
    AC_ENABLE_SHARED
    AC_DISABLE_STATIC
    ;;
esac

# Set default language to C++
AC_LANG([C++])
AC_LANG_CPLUSPLUS

# Checks for programs
save_CFLAGS="$CFLAGS"
save_CXXFLAGS="$CXXFLAGS"
save_FFLAGS="$FFLAGS"
AC_PROG_CXX
AC_PROG_CXXCPP
CXXFLAGS="$save_CXXFLAGS"
CFLAGS="$save_CFLAGS"
FFLAGS="$save_FFLAGS"
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Check for exceptions switch
AC_ARG_ENABLE(exceptions,
              [AS_HELP_STRING([--enable-exceptions],
                              [enable exceptions handling mechanism])],
              [AC_DEFINE([STDAIR_EXCEPTIONS], [1],
                         [Define if you want exceptions handling])])
test "x$enable_exceptions" != "xno" && enable_exceptions=yes

# Set the LIB_SUFFIX variable, depending on the x86 architecture
# (either 32 or 64 bits)
#if test -d /usr/lib64; then
#  LIB_SUFFIX="64"
#else
  LIB_SUFFIX=""
#fi
AC_SUBST(LIB_SUFFIX)

# Set the data directory for StdAir
pkgdatadir="${datadir}/stdair"
AC_SUBST(pkgdatadir)
# Set the directory for data samples exported by StdAir
sampledir="${pkgdatadir}/samples"
AC_SUBST(sampledir)

# Set the database (DB) directory for StdAir
dbdir="${pkgdatadir}/db"
AC_SUBST(dbdir)

# Check for info pages
AC_ARG_ENABLE(info-doc, 
              [AS_HELP_STRING([--disable-info-doc],
                              [do not generate Info documentation])])
test "x$enable_info_doc" != xno && enable_info_doc=yes

# Check for html-doc switch
AC_ARG_ENABLE(html-doc, 
              [AS_HELP_STRING([--disable-html-doc],
                              [do not generate HTML documentation])])
test "x$enable_html_doc" != xno && enable_html_doc=yes


# Provide --with-docdir
AC_ARG_WITH(docdir,
            [AS_HELP_STRING([--with-docdir=DIR],
                            [set documentation directory to DIR])],
            [DOC_DIR="$withval"],
            [DOC_DIR=""])
if test "x$DOC_DIR" != x; then
  docdir="$DOC_DIR"
else
  docdir="${datadir}/doc/$PACKAGE-$VERSION"
fi
AC_SUBST(docdir)


# Default compilation flags
if test -z "${CFLAGS}"; then
   CFLAGS="-g -Wall"
fi

if test -z "${CXXFLAGS}"; then
   CXXFLAGS="-g -Wall"
fi

# -----------------------------------------------------------------
# Readline: http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html
# -----------------------------------------------------------------
AM_PATH_READLINE([6.0])
AC_SUBST(READLINE_VERSION)
AC_SUBST(READLINE_CFLAGS)
AC_SUBST(READLINE_LIBS)

# -----------------------------------------------------------------
# ZeroMQ: http://zeromq.org
# -----------------------------------------------------------------
AM_PATH_ZEROMQ([2.0])
AC_SUBST(READLINE_VERSION)
AC_SUBST(READLINE_CFLAGS)
AC_SUBST(READLINE_LIBS)

# -----------------------------------------------------------
# Python: http://www.python.org
# -----------------------------------------------------------
PGAC_CHECK_PYTHON_EMBED_SETUP
AC_SUBST(PYTHON_VERSION)
AC_SUBST(PYTHON_LIBS)
AC_SUBST(PYTHON_CFLAGS)
AC_SUBST(PYTHON_ADD_LIBS)


# --------------------------------------------------------
# Boost (STL Extensions: http://www.boost.org)
# --------------------------------------------------------
AX_BOOST([1.33])

# --------------------------------------------------------------------
# Support for MySQL (C client API): http://www.mysql.org
# --------------------------------------------------------------------
AX_MYSQL
AC_SUBST(MYSQL_VERSION)
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(MYSQL_LIBS)

# --------------------------------------------------------------------
# Support for SOCI http://soci.sourceforge.net
# --------------------------------------------------------------------
AX_SOCI
AC_SUBST(SOCI_VERSION)
AC_SUBST(SOCI_CFLAGS)
AC_SUBST(SOCI_LIBS)

# -------------------------------------------------------------------
# Support for documentation
# -------------------------------------------------------------------
# Checks for documentation build tools
#AC_CHECK_PROG([texinfo_ok], [texinfo], [yes], [no])
#if test "x$enable_info_doc" != xno; then
#  test "x$texinfo_ok" != xyes && enable_info_doc=no
#  AC_PATH_PROG([PERL], [perl], [])
#fi
AM_CONDITIONAL([INFO_DOC], [test "x$enable_info_doc" = xyes])

# Checks for documentation build tools
AC_CHECK_PROG([doxygen_ok], [doxygen], [yes], [no])
AC_CHECK_PROG([latex_ok], [latex], [yes], [no])
AC_CHECK_PROG([dvips_ok], [dvips], [yes], [no])
AC_CHECK_PROG([gs_ok], [gs], [yes], [no])
if test "x$enable_html_doc" != xno; then
  test "x$doxygen_ok" != xyes && enable_html_doc=no
  test "x$latex_ok" != xyes && enable_html_doc=no
  test "x$dvips_ok" != xyes && enable_html_doc=no
  test "x$gs_ok" != xyes && enable_html_doc=no
  AC_PATH_PROG([PERL], [perl], [])
fi
AM_CONDITIONAL([HTML_DOC], [test "x$enable_html_doc" = xyes])


# Check for diff program used for tests
AC_CHECK_PROG([diff_ok], [diff], [yes], [no])
AC_CHECK_PROG([sed_ok], [sed], [yes], [no])
enable_tests=yes
test "x$diff_ok" != xyes && enable_tests=no
test "x$sed_ok" != xyes && enable_tests=no
AM_CONDITIONAL([RUN_TESTS], [test "x$enable_tests" = xyes])


# Checks for header files
AC_HEADER_STDC
AC_HEADER_TIME
AC_CHECK_HEADERS([fstream iomanip iostream sstream limits list vector map \
  queue stdexcept string])


# config.h top and bottom
AH_TOP([
#ifndef CONFIG_H
#define CONFIG_H
])


# --------------------------------------------------------
# I18n (internationalisation) with GNU Gettext
# --------------------------------------------------------
#AM_GNU_GETTEXT([external], [need-formatstring-macros])
#AM_GNU_GETTEXT_VERSION([0.14])
# Force the usage of the i18n feature: on 64bit architecture,
# as gettext uses conversions from int to char*, there may be
# some issues. However, for regular translation (e.g., to German 
# or French), the PO files are correctly transformed into GMO.
#USE_NLS=yes


# Define configured files
AC_CONFIG_FILES(
	Makefile
	stdair-config
	stdair.pc
	stdair.m4
	stdair/Makefile
	stdair/basic/Makefile
	stdair/bom/Makefile
	stdair/dbadaptor/Makefile
	stdair/factory/Makefile
	stdair/command/Makefile
	stdair/config/Makefile
	stdair/config/stdair-paths.hpp
	stdair/service/Makefile	
	stdair/core/Makefile
	stdair/ui/Makefile
	stdair/ui/cmdline/Makefile
	batches/Makefile
	man/Makefile
	man/doxygen_man1.cfg
	man/doxygen_man3.cfg
	doc/Makefile
	doc/diagrams/Makefile
	doc/images/Makefile
	doc/tutorial/Makefile
	doc/tutorial/src/Makefile
	doc/local/Makefile
	doc/doxygen_html.cfg
	samples/Makefile
	samples/rds01/Makefile
	db/Makefile
	db/data/Makefile
	db/admin/Makefile
	db/admin/clean_all_tables.sh
	db/admin/clean_a_table.sh
	db/admin/count_all_tables.sh
	db/admin/count_a_table.sh
	db/admin/create_airinv_db.sh
	db/admin/create_airinv_user.sh
	db/admin/create_dsim_db.sh
	db/admin/create_dsim_user.sh
	db/admin/dump_airinv_db_structure.sh
	db/admin/dump_dsim_db_structure.sh
	db/admin/load_airinv_dsim_data.sh
	db/admin/load_dsim_data.sh
	test/Makefile
	test/inheritance/Makefile
	test/guillotine/Makefile
	test/archi_intru/Makefile
	test/archi_static_cast/Makefile
	test/mpl/Makefile
	test/mpl/contrib/Makefile
	test/stdair/Makefile
)
AC_OUTPUT

echo "
------------------------------------------------------------------------------
$PACKAGE-$VERSION library configuration:
------------------------------------------------------------------------------

Directories:
  - prefix ................. : ${prefix}
  - exec_prefix ............ : ${exec_prefix}
  - includedir ............. : ${includedir}
  - libdir ................. : ${libdir}
  - datarootdir ............ : ${datarootdir}
  - datadir ................ : ${datadir}
  - pkgdatadir ............. : ${pkgdatadir}
  - sampledir .............. : ${sampledir}
  - dbdir .................. : ${dbdir}
  - docdir ................. : ${docdir}
  - mandir ................. : ${mandir}
  - infodir ................ : ${infodir}

Switches:
  - exceptions ............. : ${enable_exceptions}
  - use-nls ................ : ${USE_NLS}
  - info-doc ............... : ${enable_info_doc}
  - html-doc ............... : ${enable_html_doc}
  - shared ................. : ${enable_shared}
  - static ................. : ${enable_static}

Documentation tools:
  - texinfo ................ : ${texinfo_ok}
  - doxygen ................ : ${doxygen_ok}
  - latex .................. : ${latex_ok}
  - dvips .................. : ${dvips_ok}
  - ghostscript ............ : ${gs_ok}

Testing tools:
  - diff ................... : ${diff_ok}
  - sed .................... : ${sed_ok}

Compiler/linker flags/libs/defs:
  - CXX .................... : ${CXX}
  - CFLAGS ................. : ${CFLAGS}
  - CXXFLAGS ............... : ${CXXFLAGS}
  - CPPFLAGS ............... : ${CPPFLAGS}
  - FFLAGS ................. : ${FFLAGS}
  - LDFLAGS ................ : ${LDFLAGS}
  - LIBS ................... : ${LIBS}

External libraries:
  - Readline ............... :
    o READLINE_VERSION ..... : ${READLINE_VERSION}
    o READLINE_CFLAGS ...... : ${READLINE_CFLAGS}
    o READLINE_LIBS ........ : ${READLINE_LIBS} 

  - ZeroMQ ................. :
    o ZEROMQ_VERSION ....... : ${ZEROMQ_VERSION}
    o ZEROMQ_CFLAGS ........ : ${ZEROMQ_CFLAGS}
    o ZEROMQ_LIBS .......... : ${ZEROMQ_LIBS} 

  - Python ................. :
    o PYTHON_VERSION ....... : ${PYTHON_VERSION}
    o PYTHON_CFLAGS ........ : ${PYTHON_CFLAGS}
    o PYTHON_LIBS .......... : ${PYTHON_LIBS} 
    o PYTHON_ADD_LIBS ...... : ${PYTHON_ADD_LIBS} 

  - Boost .................. :
    o BOOST_VERSION ........ : ${BOOST_VERSION}
    o BOOST_CFLAGS ......... : ${BOOST_CFLAGS}
    o BOOST_LIBS ........... : ${BOOST_LIBS}
    o BOOST_UTF_LIB ........ : ${BOOST_UNIT_TEST_FRAMEWORK_LIB}
    o BOOST_DATE_TIME_LIB .. : ${BOOST_DATE_TIME_LIB}
    o BOOST_PO_LIB ......... : ${BOOST_PROGRAM_OPTIONS_LIB}
    o BOOST_SYSTEM_LIB ..... : ${BOOST_SYSTEM_LIB}
    o BOOST_FILESYSTEM_LIB . : ${BOOST_FILESYSTEM_LIB}
    o BOOST_THREAD_LIB ..... : ${BOOST_THREAD_LIB}
    o BOOST_PYTHON_LIB ..... : ${BOOST_PYTHON_LIB}
    o BOOST_ASIO_LIB ....... : ${BOOST_ASIO_LIB}
    o BOOST_MPI_LIB ........ : ${BOOST_MPI_LIB}
    o BOOST_MPI_PYTHON_LIB . : ${BOOST_MPI_PYTHON_LIB}
    o BOOST_IOSTREAMS_LIB .. : ${BOOST_IOSTREAMS_LIB}
    o BOOST_SIGNALS_LIB .... : ${BOOST_SIGNALS_LIB}
    o BOOST_SERIAL_LIB ..... : ${BOOST_SERIALIZATION_LIB}
    o BOOST_WSERIAL_LIB .... : ${BOOST_WSERIALIZATION_LIB}
    o BOOST_REGEX_LIB ...... : ${BOOST_REGEX_LIB}

  - MySQL .................. :
    o MYSQL_VERSION ........ : ${MYSQL_VERSION}
    o MYSQL_CFLAGS ......... : ${MYSQL_CFLAGS}
    o MYSQL_LIBS ........... : ${MYSQL_LIBS} 

  - SOCI ................... :	
    o SOCI_VERSION ......... : ${SOCI_VERSION}
    o SOCI_CFLAGS .......... : ${SOCI_CFLAGS}
    o SOCI_LIBS ............ : ${SOCI_LIBS}

------------------------------------------------------------------------------
Now type 'make && make install' to build and install $PACKAGE-$VERSION library
------------------------------------------------------------------------------
"
