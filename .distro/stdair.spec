Name:           stdair
Version:        0.0.0
Release:        %autorelease

Summary:        C++ Standard Airline IT Object Library

License:        LGPL-2.1-or-later
URL:            https://github.com/airsim/%{name}
Source0:        %{url}/archive/refs/tags/v%{version}.tar.gz#/%{name}-%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  cmake
BuildRequires:  boost-devel
BuildRequires:  soci-mysql-devel
BuildRequires:  soci-sqlite3-devel
BuildRequires:  pkgconfig(readline)

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
Requires:       %{name}%{?_isa} = %{version}-%{release}
Requires:       pkgconfig

%description    devel
This package contains the header files, shared libraries and
development helper tools for %{name}. If you would like to develop
programs using %{name}, you will need to install %{name}-devel.

%package        doc
Summary:        HTML documentation for the %{name} library
BuildRequires:  tex(latex)
BuildRequires:  doxygen
BuildRequires:  ghostscript
BuildRequires:  texlive-epstopdf

%description    doc
This package contains HTML pages, as well as a PDF reference manual,
for %{name}. All that documentation is generated thanks to Doxygen
(https://doxygen.org). The content is the same as what can be browsed
online (https://%{name}.org).


%prep
%autosetup

%build
%cmake
%cmake_build

%install
%cmake_install

# Fix some permissions
find %{buildroot}%{_libexecdir}/%{name} -type f -name '*.sh' -exec chmod +x {} \;

# Remove the Doxygen installer
rm -f %{buildroot}/%{_docdir}/%{name}/html/installdox

# Remove additional documentation files (those files are already available
# in the project top directory)
rm -f %{buildroot}%{_docdir}/%{name}/{NEWS,README.md,AUTHORS}

%check
%ctest

%files
%doc ChangeLog AUTHORS NEWS README.md
%license COPYING
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
%dir %{_datadir}/%{name}/samples/HybridForecasting
%dir %{_datadir}/%{name}/samples/IBP_study
%dir %{_datadir}/%{name}/samples/NewQFF
%dir %{_datadir}/%{name}/samples/NewQFF/instance01
%dir %{_datadir}/%{name}/samples/NewQFF/instance02
%dir %{_datadir}/%{name}/samples/OldQFF
%dir %{_datadir}/%{name}/samples/OldQFF/instance01
%dir %{_datadir}/%{name}/samples/OldQFF/instance02
%dir %{_datadir}/%{name}/samples/QForecasting
%{_datadir}/%{name}/db/data/*.sql
%{_datadir}/%{name}/db/data/*.csv
%{_datadir}/%{name}/samples/*.csv
%{_datadir}/%{name}/samples/rds01/*.csv
%{_datadir}/%{name}/samples/HybridForecasting/*.csv
%{_datadir}/%{name}/samples/IBP_study/*.csv
%{_datadir}/%{name}/samples/NewQFF/instance01/*.csv
%{_datadir}/%{name}/samples/NewQFF/instance02/*.csv
%{_datadir}/%{name}/samples/OldQFF/instance01/*.csv
%{_datadir}/%{name}/samples/OldQFF/instance02/*.csv
%{_datadir}/%{name}/samples/QForecasting/*.csv

%files devel
%{_includedir}/%{name}/
%{_bindir}/%{name}-config
%{_libdir}/lib%{name}.so
%{_libdir}/lib%{name}uicl.so
%{_libdir}/pkgconfig/%{name}.pc
%{_libdir}/cmake/%{name}/
%{_datadir}/aclocal/%{name}.m4
%{_mandir}/man1/%{name}-config.1.*
%{_mandir}/man3/%{name}-library.3.*

%files doc
%doc %{_docdir}/%{name}/
%license COPYING

%changelog
%autochangelog
