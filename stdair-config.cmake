#
# Config file for the StdAir package. It defines the following variables:
#  STDAIR_VERSION      - version of StdAir
#  STDAIR_BINARY_DIRS  - binary directories for StdAir
#  STDAIR_INCLUDE_DIRS - include directories for StdAir
#  STDAIR_LIBRARY_DIRS - library directories for StdAir (normally not used!)
#  STDAIR_LIBRARIES    - libraries to link against
#  STDAIR_EXECUTABLES  - the stdair binaries/executables
#  STDAIR_SAMPLE_DIR   - the stdair (CSV) sample files

# Tell the user project where to find the headers, libraries and sample files
set (STDAIR_VERSION "99.99.99")
set (STDAIR_BINARY_DIRS "/usr/bin")
set (STDAIR_INCLUDE_DIRS "/usr/include")
set (STDAIR_LIBRARY_DIRS "/usr/lib")
set (STDAIR_SAMPLE_DIR "/usr/share/stdair/samples")

# Our library dependencies (contains definitions for IMPORTED targets)
include ("/usr/share/stdair/CMake/stdair-library-depends.cmake")

# These are IMPORTED targets created by stdair-library-depends.cmake
set (STDAIR_LIBRARIES stdairlib stdairuicllib)
set (STDAIR_EXECUTABLES stdair)
