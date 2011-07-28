#!/bin/sh

#
dir=`echo "$0" | sed 's,[^/]*$,,'`
test "x${dir}" = "x" && dir='.'

#
if test "x`cd "${dir}" 2>/dev/null && pwd`" != "x`pwd`"
then
    echo "This script must be executed directly from the source directory."
    exit 1
fi

##
# Parsing of command-line options
DOC_OPTION="-DINSTALL_DOC:BOOL=ON"
BUILD_DIR_OPTION="NO"
SOURCE_DIR="."
for opt_elem in $@
do
  if [ "${opt_elem}" = "-h" -o "${opt_elem}" = "-H" -o "${opt_elem}" = "--h" -o "${opt_elem}" = "--help" ]
  then
    echo ""
    echo " This script generates a 'configure' script for simulator-related projects."
    echo " That 'configure' script is compatible with some GNU Autotools options."
    echo " Run './configure', after its generation, to see its usage."
    echo " "
    echo "Usage:"
    echo "    \$0 [--nodoc]"
    echo ""
    exit 0
  fi
  if [ "${opt_elem}" = "-n" -o "${opt_elem}" = "-N" -o "${opt_elem}" = "--nodoc" ]
  then
      DOC_OPTION="-DINSTALL_DOC:BOOL=OFF"
  fi
  if [ "${opt_elem}" = "-b" -o "${opt_elem}" = "-B" -o "${opt_elem}" = "--builddir" ]
  then
      BUILD_DIR_OPTION="YES"
      SOURCE_DIR=".."
  fi
done

#
VERSION_MAJOR=99
VERSION_MINOR=99
VERSION_PATCH=99
VERSION_TMP_STRING=`grep "set_project_versions" CMakeLists.txt | sed -e "s/set_project_versions.*\([0-9]\+.\+[0-9]\+.\+[0-9]\+\).\+/\1/"`
VERSION_STRING=`echo "${VERSION_TMP_STRING}" | grep "^[0-9]\+.[0-9]\+.[0-9]\+$"`

if [ "x${VERSION_STRING}" != "x" ]
then
    VERSION_MAJOR=`echo ${VERSION_STRING} | cut -d\  -f1`
    VERSION_MINOR=`echo ${VERSION_STRING} | cut -d\  -f2`
    VERSION_PATCH=`echo ${VERSION_STRING} | cut -d\  -f3`
fi

#
LOCAL_USERNAME=`id | cut -d\( -f2 | cut -d\) -f1`
PREFIX=/home/${LOCAL_USERNAME}/dev/deliveries/stdair-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
if [ "${LOCAL_USERNAME}" = "build" ]
then
    PREFIX=/opt/stdair-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
fi

#
cat > configure << _EOF
#!/bin/sh

##
# Parsing of options
# Note: the build server:
#  * builds StdAir with the following option:
#    ./configure --prefix=/opt/stdair-0.36.0
#  * builds other simulator-related projects with the following option:
#    ./configure --with-stdair=/opt/stdair
#
PREFIX_OPTION=""
STDAIR_OPTION=""
DOC_OPTION="${DOC_OPTION}"
RM_OPTION="rm -rf build"
BUILD_DIR_OPTION="${BUILD_DIR_OPTION}"
SOURCE_DIR="${SOURCE_DIR}"
for opt_elem in \$@
do
  if [ "\${opt_elem}" = "-h" -o "\${opt_elem}" = "-H" -o "\${opt_elem}" = "--h" -o "\${opt_elem}" = "--help" ]
  then
    echo ""
    echo "Usage:"
    echo "    \$0 [--prefix=<install_dir>] [--with-stdair=<stdair_install_dir>] [--with-doc | --without-doc] [-n|-N|--norm] [-b|--buildir]"
    echo "      --with-doc/--without-doc : Force the (resp. non) generation of the documentation" 
    echo "      -n/-N/--norm             : Do not remove/clean older potential 'build' sub-directory" 
    echo "      -b/-B/--buildir          : Do the build in a dedicated 'build' sub-directory, rather than in-place" 
    echo ""
    exit 0
  fi
  IS_OPTION_PREFIX=\`echo "\${opt_elem}" | grep "^--prefix="\`
  if [ "\${IS_OPTION_PREFIX}" != "" ]
  then
    PREFIX_DIR=\`echo "\${opt_elem}" | sed -e "s/^--prefix=\(.*\)\$/\1/"\`
    PREFIX_OPTION="-DCMAKE_INSTALL_PREFIX=\${PREFIX_DIR}"
  fi
  IS_OPTION_STDAIR=\`echo "\${opt_elem}" | grep "^--with-stdair="\`
  if [ "\${IS_OPTION_STDAIR}" != "" ]
  then
    STDAIR_DIR=\`echo "\${opt_elem}" | sed -e "s/^--with-stdair=\(.*\)\$/\1/"\`
    STDAIR_OPTION="-DWITH_STDAIR_PREFIX=\${STDAIR_DIR}"
  fi
  IS_OPTION_W_DOC=\`echo "\${opt_elem}" | grep "^--with-doc"\`
  if [ "\${IS_OPTION_W_DOC}" != "" ]
  then
    DOC_OPTION="-DINSTALL_DOC:BOOL=ON"
  fi
  IS_OPTION_WO_DOC=\`echo "\${opt_elem}" | grep "^--without-doc"\`
  if [ "\${IS_OPTION_WO_DOC}" != "" ]
  then
    DOC_OPTION="-DINSTALL_DOC:BOOL=OFF"
  fi
  if [ "\${opt_elem}" = "-n" -o "\${opt_elem}" = "-N" -o "\${opt_elem}" = "--norm" ]
  then
    RM_OPTION=""
  fi
  if [ "\${opt_elem}" = "-b" -o "\${opt_elem}" = "-B" -o "\${opt_elem}" = "--builddir" ]
  then
    BUILD_DIR_OPTION="YES"
    SOURCE_DIR=".."
  fi
done

#
LIB_OPTION=""
if [ -d /usr/lib64 ]
then
    LIB_OPTION="-DLIB_SUFFIX=64"
fi

#
BUILD_OPTION="-DCMAKE_BUILD_TYPE:STRING=Debug"

#
CMAKE_CMD="cmake \${PREFIX_OPTION} \${STDAIR_OPTION} \${LIB_OPTION} \${BUILD_OPTION} \${DOC_OPTION} \${SOURCE_DIR}"

# Trace on
set -x

##
# Clean potential former builds
\${RM_OPTION}
mkdir -p build

##
# Configuration
if [ "\${BUILD_DIR_OPTION}" = "YES" ]
then
  cd build
fi
\${CMAKE_CMD}
if [ "\${BUILD_DIR_OPTION}" = "YES" ]
then
  cd -
fi

# Trace back off
set +x

##
# Tell how to build, test and install
echo ""
echo "--------------------"
echo "To build, test and install:"
if [ "\${BUILD_DIR_OPTION}" = "YES" ]
then
  echo "alias build_check_install='cd build && make && make check && make install && cd -'"
else
  echo "alias build_check_install='make && make check && make install'"
fi
echo "build_check_install"
echo "--------------------"
echo ""

_EOF

#
chmod 755 configure

#
echo "You can now just run ./configure"

