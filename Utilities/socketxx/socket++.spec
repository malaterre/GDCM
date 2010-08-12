Name: socket++
Summary: A C++ interface for sockets.
Version: 1.12.10
Release: 1
Copyright: Freely Distributable
Group: Development/Libraries
Source: http://www.hstraub.at/linux/downloads/src/%{name}-%{version}.tar.gz
Vendor: Gnanasekaran Swaminathan
URL: http://members.aon.at/hstraub/linux/socket++/
Packager: Herbert Straub <h.straub@aon.at>
BuildRequires: autoconf automake texinfo libtool info
BuildRoot: %{_tmppath}/%{name}-root

%description
Socket++ library defines a family of C++ classes that can be used
more effectively than directly calling the underlying low-level
system functions. One distinct advantage of the socket++ is that
it has the same interface as that of the iostream so that
the users can perform type-safe input output.

This is a modified version of the original socket++ 1.11 Library

%prep
%setup
%build
./autogen
%configure
make

%install
[ "$RPM_BUILD_ROOT" != "" ] && rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install
rm -f $RPM_BUILD_ROOT%{_infodir}/dir

%clean
[ "$RPM_BUILD_ROOT" != "" ] && rm -rf $RPM_BUILD_ROOT

%post
/sbin/ldconfig
/sbin/install-info %{_infodir}/socket++.info.gz %{_infodir}/dir

%preun
if [ "$1" = 0 ]; then
  /sbin/install-info --delete %{_infodir}/socket++.info.gz %{_infodir}/dir
fi

%postun
/sbin/ldconfig

%files
%{_includedir}/socket++/*
%{_libdir}/*
%{_infodir}/*
%doc COPYING README* ChangeLog AUTHORS THANKS NEWS

%changelog

* Sat Apr 26 2003 Herbert Straub <h.straub@aonat>
- new upstream version
- version 1.12.10-1 RPM

* Fri Mar 13 2003 Herbert Straub <h.straub@aon.at>
- new upstream version
- version 1.12.9-1 RPM

* Fri Dec 06 2002 Herbert Straub <h.straub@aon.at>
- new upstream version, new fixed up spec file from Carles Arjona
- version 1.12.8-1 RPM

* Wed Nov 27 2002 Carles Arjona <nospammer@bigfoot.com>
- fixed up spec file
- version 1.12.7-1 RPM

* Sat Nov 23 2002 Herbert Straub <herbert.straub@aon.at>
- new upstream version
- version 1.12.6-1 RPM

* Sun Nov 15 2002 Herbert Straub <herbert.straub@aon.at>
- new upstream version
- version 1.12.5-1 RPM

* Sun Nov 10 2002 Carles Arjona <nospammer@bigfoot.com>
- added BuildRoot support
- version 1.12.4-1 RPM

* Thu Oct 08 2002 Herbert Straub <h.straub@aon.at>
- version 1.12.3 RPM

* Fri Jul 06 2001 Lauri Nurmi <lanurmi@iki.fi>
- version 1.11ln3 RPM





