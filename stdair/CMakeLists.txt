##
# StdAir module
module_set_name (stdair)

##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
module_generate_config_helpers ()

##
# Source directories for the standard library.
# All the sources within each of the directories/layers will be used and
# assembled, in order to form a single library, named here the
# "standard library".
module_define_sources (basic bom factory dbadaptor command service)

##
# Assembling
# The additional parameters, if given, correspond to the names of the
# modules this current module depends upon. Dependencies on the
# external libraries (e.g., Boost, SOCI, StdAir) are automatically
# appended, thanks to the get_external_libs() macro.
module_library_add_standard ()

# Specification of the additional libraries: target, headers and sources
#file (GLOB ${PROJECT_NAME}uicl_HEADERS ui/cmdline/SReadline.hpp)
module_library_add_specific (${PROJECT_NAME}uicl 
  "ui/cmdline/SReadline.hpp" "ui/cmdline/SReadline.hpp")

##
# Library installation
# The parameters correspond to additional libraries to be installed.
# When no parameter is given, only the standard library is installed.
module_library_install_all (${PROJECT_NAME}uicl)


##
# Header installation for the non-root layers
module_header_install_standard ()

##
# Assembling: specify the standard binary target for the current module.
module_binary_add_standard (../batches)

##
# Binary installation
# The parameters correspond to additional binaries to be installed.
# When no parameter is given, only the standard binary is installed.
module_binary_install_all ()

##
# Install the CMake import helper, so that third party projects can refer to it
# (for libraries, header files and binaries)
module_export_install ()
