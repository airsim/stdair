#
%global mydocs __tmp_docdir
#
Name:           stdair
Version:        0.34.0
Release:        1%{?dist}

Summary:        C++ Standard Airline IT Object Library

Group:          System Environment/Libraries 
License:        LGPLv2+
URL:            http://sourceforge.net/projects/%{name}/
Source0:        http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.bz2
%{?el5:BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)}

BuildRequires:  cmake
BuildRequires:  boost-devel, soci-mysql-devel, zeromq-devel


%description
%{name} aims at providing a clean API, and the corresponding C++
implementation, for the basis of Airline IT Business Object Model (BOM),
that is, to be used by several other open source projects, such as RMOL, 
Air-Sched, Travel-CCM, OpenTREP, etc.

Install the %{name} package if you need a Standard Airline IT C++ objects.

%package        devel
Summary:        Header files, libraries and development documentation for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       pkgconfig
# for %%_datadir/cmake ownership, can consider making cmake-filesystem
# if this dep is a problem
Requires: cmake

%description    devel
This package contains the header files, static libraries and
development documentation for %{name}. If you would like to develop
programs using %{name}, you will need to install %{name}-devel.

%package doc
Summary:        HTML documentation for the %{name} library
Group:          Documentation
%{?fedora:BuildArch:      noarch}
BuildRequires:  tex(latex)
BuildRequires:  doxygen, ghostscript

%description doc
This package contains the documentation in the HTML format of the %{name}
library. The documentation is the same as at the %{name} web page.


%prep
%setup -q
# Fix some permissions and formats
%{__chmod} -x AUTHORS ChangeLog COPYING NEWS README
find . -type f -name '*.[hc]pp' -exec chmod 644 {} \;


%build
%cmake .
make %{?_smp_mflags}

%install
%{__rm} -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%check
ctest

# The INSTALL package is not relevant for RPM package users
# (e.g., see https://bugzilla.redhat.com/show_bug.cgi?id=489233#c4)
%{__rm} -f $RPM_BUILD_ROOT/INSTALL

# Fix some permissions
find $RPM_BUILD_ROOT%{_libexecdir}/%{name} -type f -name '*.sh' -exec chmod 755 {} \;

%{__mkdir_p} %{mydocs}
%{__mv} $RPM_BUILD_ROOT%{_docdir}/%{name}-%{version}/html %{mydocs}
%{__rm} -f %{mydocs}/html/installdox

%clean
%{__rm} -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING NEWS README
%{_bindir}/%{name}
%{_libdir}/lib*.so.*
%{_mandir}/man1/%{name}.1.*
%dir %{_libexecdir}/%{name}
%{_libexecdir}/%{name}/*.sh
%dir %{_datadir}/%{name}
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

