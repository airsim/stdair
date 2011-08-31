#
cmake_minimum_required (VERSION 2.6)

##
# CMake macros for the project
include (config/project_config_embeddable.cmake)

##
# Project info
set_project_names (stdair StdAir)
set_project_brief ("C++ Standard Airline IT Library")
set_project_versions (99 99 99)

##
# Project options
# The parameters are:
#  * whether or not the documentation must be built and installed
set_project_options (on)


#####################################
##            Packaging            ##
#####################################
#
packaging_init (${PROJECT_NAME})
packaging_set_summary (
"${PROJECT_NAME} aims at providing a clean API, and the corresponding
C++ implementation, for the basis of Airline IT Business Object Model
(BOM), that is, to be used by several other open source projects, such
as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")
packaging_set_contact ("Denis Arnaud <denis_arnaud - at - users dot sourceforge dot net>")
packaging_set_vendor ("Denis Arnaud")

#
packaging_set_other_options (TBZ2 "TBZ2;TGZ")


########################################
##            Dependencies            ##
########################################
#
get_external_libs (git "python 2.7" "boost 1.41" "zeromq 2.0" "mysql 5.1"
  "soci 3.0" "doxygen 1.7")


##############################################
##           Build, Install, Export         ##
##############################################
##
# Initialise the building process
init_build ()

##
# Sub-modules
add_modules (${PROJECT_NAME})

##
# For other projects to use STDAIR, install a few helpers for standard
# build/packaging systems: CMake, GNU Autotools (M4), pkgconfig/pc, stdair-config
install_dev_helper_files ()

##
# Basic documentation (i.e., AUTHORS, NEWS, README, INSTALL)
install_basic_documentation ()


##########################################
##            Documentation             ##
##########################################
handle_html_doc ()

##
# Subdirs
add_subdirectory (db)
add_subdirectory (samples)
add_subdirectory (man)


#####################################
##              Tests              ##
#####################################
##
# Test suites
add_test_suites (${PROJECT_NAME})


#######################################
##          Overall Status           ##
#######################################
display_status ()


#######################################
##         CMake Cache Storage       ##
#######################################
store_in_cache ()
