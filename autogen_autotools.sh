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
rm -f config.cache acconfig.h

#
echo "- autoreconf."            && \
autoreconf -fvi                 && \
echo "" && \
echo "Now, the configuration script has to be run. For instance:" && \
echo "mkdir -p tmp && cd tmp && \\" && \
echo " ../configure --prefix=/home/user/dev/deliveries/stdair-0.37.1 --srcdir=.." && \
echo "" && \
echo "Alternatively" && \
echo "mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=/home/user/dev/deliveries/stdair-0.37.1 \\" \
echo " -DLIB_SUFFIX=64 -DCMAKE_BUILD_TYPE:STRING=Debug -DINSTALL_DOC:BOOL=OFF .." && \
echo "" && \
echo "Then:" && \
echo "make && make doc && make install" && \
echo "" && \
exit 0

#echo "- configure."     && ./configure "$@" && exit 0
