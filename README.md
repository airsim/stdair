
Summary:
--------
StdAir aims at providing a clean API, and the corresponding C++
implementation, for the basis of Airline IT and travel distribution
Business Object Model (BOM), that is, to be used by several other
open source projects, including all the components of the Travel
Market Simulator (http://www.travel-market-simulator.com), such as
AirRAC, RMOL, AirInv, AvlCal, AirTSP, SimFQT, SimLFS, SimCRS,
TravelCCM, SEvMgr, TraDemGen, and TvlSim.

StdAir is the fundamental brick of the Travel Market Simulator.
However, it may be used in a stand-alone mode.

Getting and installing from the Fedora/CentOS/RedHat distribution:
------------------------------------------------------------------
Just use Yum:
yum -y install stdair-devel stdair-doc

You can also get the RPM packages (which may work on Linux
distributions like Novel Suse and Mandriva) from the Fedora repository
(e.g., for Fedora 22, 
http://fr2.rpmfind.net/linux/fedora/releases/22/Everything/)


Building the library and test binary from Git repository:
----------------------------------------------------------------
The Git repository may be cloned as following:
$ git clone git@github.com:airsim/stdair.git airtspgit # through SSH
$ git clone https://github.com/airsim/stdair.git # if the firewall filters SSH
cd stdairgit
git checkout trunk

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


Building the library and test binary from the tarball:
------------------------------------------------------
The latest stable source tarball (stdair*.tar.gz or .bz2) can be
found on GitHub: http://github.com/airsim/stdair/releases, e.g.,
http://github.com/airsim/stdair/archive/stdair-1.00.7.tar.gz

To customise the following to your environment, you can alter the path
to the installation directory:
export INSTALL_BASEDIR=/home/user/dev/deliveries
export STDAIR_VER=1.00.7
if [ -d /usr/lib64 ]; then LIBSUFFIX=64; fi
export LIBSUFFIX_4_CMAKE="-DLIB_SUFFIX=$LIBSUFFIX"

Then, as usual:
* To configure the project, type something like:
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/stdair-$STDAIR_VER \
	-DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON \
	-DINSTALL_DOC:BOOL=ON -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
* To build the project, type:
  make
* To test the project, type:
  make check
* To install the library (libstdair*.so*) and the binary (stdair), just type:
  make install
  cd /home/user/dev/deliveries
  rm -f stdair-stable && ln -s stdair-$STDAIR_VER stdair-stable
  cd -
* To package the source files, type:
  make dist
* To package the binary and the (HTML and PDF) documentation:
  make package
* To browse the (just installed, if enabled) HTML documentation:
  midori file://${INSTALL_BASEDIR}/stdair-$STDAIR_VER/share/doc/stdair/html/index.html
* To browse the (just installed, if enabled) PDF documentation:
  evince ${INSTALL_BASEDIR}/stdair-$STDAIR_VER/share/doc/stdair/html/refman.pdf
* To run the local binary version:
  ./stdair/stdair -b
* To run the installed version:
  ${INSTALL_BASEDIR}/stdair-$STDAIR_VER/bin/stdair -b

Denis Arnaud (August 2015)

