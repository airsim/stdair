Standard Airline IT Library
===========================

# Summary

StdAir aims at providing a clean API, and the corresponding C++
implementation, for the basis of Airline IT and travel distribution
Business Object Model (BOM), that is, to be used by several other
open source projects, including all the components of the Travel
Market Simulator (http://www.travel-market-simulator.com), such as
AirRAC, RMOL, AirInv, AvlCal, AirTSP, SimFQT, SimLFS, SimCRS,
TravelCCM, SEvMgr, TraDemGen, and TvlSim.

StdAir is the fundamental brick of the Travel Market Simulator.
However, it may be used in a stand-alone mode.

# Installation

## On Fedora/CentOS/RedHat distribution
Just use DNF (or Yum on older distributions):
```bash
$ dnf -y install stdair-devel stdair-doc
```

You can also get the RPM packages (which may work on Linux
distributions like Novel Suse and Mandriva) from the Fedora repository
(_e.g._, for Fedora 32, 
https://fr2.rpmfind.net/linux/RPM/fedora/32/x86_64/)


## Building the library and test binary from Git repository
The Git repository may be cloned as following:
```bash
$ git clone git@github.com:airsim/stdair.git # through SSH
$ git clone https://github.com/airsim/stdair.git # if the firewall filters SSH
$ cd stdair
```

Then, you need the following packages (Fedora/RedHat/CentOS names here, 
but names may vary according to distributions):
* cmake
* gcc-c++
* boost-devel / libboost-dev
* python-devel / python-dev
* gettext-devel / gettext
* sqlite3-devel / libsqlite3-dev
* readline-devel / libreadline-dev
* libncurses5-devel
* soci-mysql-devel, soci-sqlite3-devel
* stdair-devel / libstdair-dev
* sevmgr-devel / libsevmgr-dev
* doxygen / doxygen-latex, ghostscript, graphviz
* tetex-latex (optional)
* rpm-build (optional)


# Building the library and test binary from the tarball
The latest stable source tarball (`stdair*.tar.gz` or `.bz2`) can be
found on GitHub: http://github.com/airsim/stdair/releases, _e.g._,
https://github.com/airsim/stdair/archive/stdair-1.00.9.tar.gz

To customise the following to your environment, you can alter the path
to the installation directory:
```bash
export INSTALL_BASEDIR="${HOME}/dev/deliveries"
export STDAIR_VER="1.00.9"
if [ -d /usr/lib64 ]; then LIBSUFFIX="64"; fi
export LIBSUFFIX_4_CMAKE="-DLIB_SUFFIX=$LIBSUFFIX"
```

Then, as usual:
* To configure the project, type something like:
```bash
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/stdair-$STDAIR_VER \
	-DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON \
	-DINSTALL_DOC:BOOL=ON -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
```
* With a specific version of Boost, say Boost 1.69 installed in a parallel way
  (for instance, as an optional module):
```bash
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/stdair-$STDAIR_VER \
        -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON \
        -DBOOST_LIBRARYDIR=/usr/lib64/boost169 -DBOOST_INCLUDEDIR=/usr/include/boost169 \
        -DBoost_ADDITIONAL_VERSIONS="1.69 1.69.0" \
        -DINSTALL_DOC:BOOL=ON -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
```
* To build the project, type:
```bash
$ make
```
* To test the project, type:
```bash
$ make check
```
* To install the library (`libstdair*.so*`) and the binary (`stdair`), just type:
```bash
  make install
  pushd /home/user/dev/deliveries
  rm -f stdair-stable && ln -s stdair-$STDAIR_VER stdair-stable
  popd -
```
* To package the source files, type:
```bash
$ make dist
```
* To package the binary and the (HTML and PDF) documentation:
```bash
$ make package
```
* To browse the (just installed, if enabled) HTML documentation:
```bash
$ midori file://${INSTALL_BASEDIR}/stdair-$STDAIR_VER/share/doc/stdair/html/index.html
```
* To browse the (just installed, if enabled) PDF documentation:
```bash
$ evince ${INSTALL_BASEDIR}/stdair-$STDAIR_VER/share/doc/stdair/html/refman.pdf
```
* To run the local binary version:
```bash
$ ./stdair/stdair -b
```
* To run the installed version:
```bash
$ ${INSTALL_BASEDIR}/stdair-$STDAIR_VER/bin/stdair -b
```

Denis Arnaud (August 2015)

