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

#
ARG_DOC=${1}
DOC_OPTION=""
if [ "${ARG_DOC}" = "off" -o "${ARG_DOC}" = "OFF" ]
then
    DOC_OPTION="-DINSTALL_DOC:BOOL=OFF"
fi

#
VERSION_MAJOR=0
VERSION_MINOR=36
VERSION_PATCH=0
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
LIB_OPTION=""
if [ -d /usr/lib64 ]
then
    LIB_OPTION="-DLIB_SUFFIX=64"
fi

#
CMAKE_CMD="cmake -DCMAKE_INSTALL_PREFIX=${PREFIX} ${LIB_OPTION} -DCMAKE_BUILD_TYPE:STRING=Debug ${DOC_OPTION} .."

#
cat > configure << _EOF
#!/bin/sh -x

# Clean potential former builds
rm -rf build
mkdir build

# Configuration
cd build
${CMAKE_CMD}
cd -

# Trace back off
set +x

# Tell how to build, test and install
echo ""
echo "--------------------"
echo "To build, test and install:"
echo "cd build && make && make check && make install && cd -"
echo "--------------------"
echo ""
_EOF

#
chmod 755 configure

#
echo "You can now just run ./configure"
