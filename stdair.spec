#
%global mydocs __tmp_docdir
#
Name:           stdair
Version:        0.44.2
Release:        1%{?dist}

Summary:        C++ Standard Airline IT Object Library

Group:          System Environment/Libraries 
License:        LGPLv2+
URL:            http://%{name}.sourceforge.net
Source0:        http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.bz2
BuildRoot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:  cmake, python-devel
BuildRequires:  boost-devel, soci-mysql-devel, zeromq-devel, readline-devel


%description
%{name} aims at providing a clean API, and the corresponding C++
implementation, for the basis of Airline IT and travel distribution
Business Object Model (BOM), that is, to be used by several other open
source projects, such as AirRAC, RMOL, AirInv, AvlCal, AirSched, SimFQT,
SimLFS, SimCRS, TravelCCM, SEvMgr, TraDemGen, DSim, OpenTREP, etc.

Install the %{name} package if you need a library of basic C++ objects
for Airline IT (e.g., schedule management, inventory, revenue management,
revenue accounting), travel distribution, demand generation and customer choice
modeling, mainly for simulation purpose.

%package        devel
Summary:        Header files, libraries and development helper tools for %{name}
Group:          Development/Libraries
Requires:       %{name}%{?_isa} = %{version}-%{release}
Requires:       pkgconfig

%description    devel
This package contains the header files, shared libraries and
development helper tools for %{name}. If you would like to develop
programs using %{name}, you will need to install %{name}-devel.

%package        doc
Summary:        HTML documentation for the %{name} library
Group:          Documentation
%if 0%{?fedora} || 0%{?rhel} > 5
BuildArch:      noarch
%endif
BuildRequires:  tex(latex)
BuildRequires:  doxygen, ghostscript

%description    doc
This package contains HTML pages, as well as a PDF reference manual,
for %{name}. All that documentation is generated thanks to Doxygen
(http://doxygen.org). The content is the same as what can be browsed
online (http://%{name}.org).


%prep
%setup -q


%build
%cmake .
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

# Fix some permissions
find $RPM_BUILD_ROOT%{_libexecdir}/%{name} -type f -name '*.sh' -exec chmod +x {} \;

mkdir -p %{mydocs}
mv $RPM_BUILD_ROOT%{_docdir}/%{name}-%{version}/html %{mydocs}
rm -f %{mydocs}/html/installdox

%check
ctest

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING NEWS README
%{_bindir}/%{name}
%{_libdir}/lib%{name}.so.*
%{_libdir}/lib%{name}uicl.so.*
%{_mandir}/man1/%{name}.1.*
%dir %{_libexecdir}/%{name}
%{_libexecdir}/%{name}/*.sh
%dir %{_datadir}/%{name}
%dir %{_datadir}/%{name}/db
%dir %{_datadir}/%{name}/db/data
%dir %{_datadir}/%{name}/samples
%dir %{_datadir}/%{name}/samples/rds01
%{_datadir}/%{name}/db/data/*.sql
%{_datadir}/%{name}/db/data/*.csv
%{_datadir}/%{name}/samples/*.csv
%{_datadir}/%{name}/samples/rds01/*.csv

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}
%{_bindir}/%{name}-config
%{_libdir}/lib%{name}.so
%{_libdir}/lib%{name}uicl.so
%{_libdir}/pkgconfig/%{name}.pc
%{_datadir}/aclocal/%{name}.m4
%{_datadir}/%{name}/CMake
%{_mandir}/man1/%{name}-config.1.*
%{_mandir}/man3/%{name}-library.3.*

%files doc
%defattr(-,root,root,-)
%doc %{mydocs}/html
%doc COPYING


%changelog
* Sat Nov 12 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.44.1-1
- Upstream update

* Sat Nov 05 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.44.1-1
- Upstream update

* Tue Nov 02 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.44.0-1
- Upstream update

* Tue Oct 18 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.43.1-1
- The build framework is now compatible with CMake 2.6 (the exclusive
  dependency on CMake 2.8 has been removed).

* Sat Oct 15 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.43.0-2
- Improved a little the package descriptions

* Sat Oct 15 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.43.0-1
- Upstream update

* Mon Aug 15 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.38.0-1
- Upstream update

* Fri Aug 12 2011 Adam Jackson <ajax@redhat.com> 0.36.2-2
- Rebuild for new boost
 
* Mon Aug 01 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.36.2-1
- The CMake framework now takes into account compilation flags

* Sun Jul 31 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.36.1-1
- Upstream update

* Sun Jul 31 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.36.0-2
- Took into account review elements (#702987)

* Tue Jul 26 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.36.0-1
- Upstream update

* Thu Jul 07 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.35.0-1
- Upstream update

* Wed Jun 15 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.34.0-1
- Upstream update
- The build system is now CMake (instead of the GNU Autotools)

* Tue Jun  7 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.33.0-1
- Upstream update

* Sun May 22 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.32.0-1
- Upstream update

* Mon May 16 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.31.0-1
- Upstream update

* Fri Apr 29 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.30.0-1
- Upstream update

* Wed Apr 20 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.29.0-1
- Upstream update

* Sun Apr 17 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.28.0-1
- Upstream update

* Tue Apr 12 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.27.0-1
- Upstream update

* Fri Apr 08 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.26.0-1
- Upstream update

* Tue Apr 05 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.25.0-1
- Upstream update

* Fri Apr 01 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.24.0-1
- Upstream update

* Thu Mar 24 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.23.0-1
- Upstream update

* Thu Mar 17 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.22.0-1
- Upstream update

* Sun Mar 13 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.21.0-1
- Upstream update

* Fri Mar  4 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.20.0-1
- Upstream update

* Thu Mar  3 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.19.0-1
- Upstream update

* Thu Mar  3 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.18.0-1
- Upstream update

* Wed Mar  2 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.17.0-1
- Upstream update

* Fri Feb 25 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.16.0-1
- Upstream update

* Tue Feb 22 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.15.0-1
- Upstream update

* Sat Feb 19 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.14.0-1
- Upstream update

* Wed Feb 16 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.13.0-1
- Upstream update

* Sat Feb 12 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.12.0-1
- Upstream update

* Tue Jan 18 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.11.0-1
- Upstream update

* Thu Dec 29 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.10.0-1
- Upstream update

* Fri Dec 03 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.9.0-1
- Upstream update

* Sat Nov 06 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.8.0-1
- Upstream update

* Thu Oct 14 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.7.0-1
- Upstream update

* Thu Oct 14 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.6.0-1
- Upstream update

* Thu Sep 16 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.5.0-1
- Upstream update

* Fri Sep 03 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.4.0-1
- Replace extracc external ref to dependency

* Sun Aug 29 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.3.0-1
- Upstream update

* Wed Jul 13 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.1.0-1
- First RPM release

