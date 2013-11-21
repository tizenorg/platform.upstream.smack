Name:       smack
Version:    1.0.4
Release:    1
Summary:    Selection of tools for developers working with Smack
Group:      Security/Access Control
License:    LGPL-2.1
URL:        https://github.com/smack-team/smack
Source0:    %{name}-%{version}.tar.gz
Source1001: 	smack.manifest
BuildRequires: automake
BuildRequires: autoconf
BuildRequires: libtool
BuildRequires: pkg-config

%description
Tools provided to load and unload rules from the kernel and query the policy

%package devel
Summary:    Development headers and libs for libsmack
Group:      Development/Libraries
Requires:   libsmack = %{version}

%description devel
Standard header files for use when developing Smack enabled applications

%package -n libsmack
Summary:    Library allows applications to work with Smack
Group:      Security/Access Control

%description -n libsmack
Library allows applications to work with Smack.

%prep
%setup -q
cp %{SOURCE1001} .

%build
autoreconf --install --symlink
%configure --with-systemdsystemunitdir=%{_prefix}/lib/systemd/system

make %{?_smp_mflags}

%install
%make_install

install -d %{buildroot}/etc/smack/accesses.d
install -d %{buildroot}/etc/smack/cipso.d
install -d %{buildroot}/etc/smack/netlabel.d
install -d %{buildroot}/smack


%post -p /sbin/ldconfig -n libsmack

%postun -p /sbin/ldconfig -n libsmack


%docs_package

%files -n libsmack
%manifest %{name}.manifest
%defattr(644,root,root,755)
%license COPYING
%{_libdir}/libsmack.so.*

%files devel
%manifest %{name}.manifest
%defattr(644,root,root,755)
%{_includedir}/sys/smack.h
%{_libdir}/libsmack.so
%{_libdir}/pkgconfig/libsmack.pc

%files 
%manifest %{name}.manifest
%defattr(644,root,root,755)
%{_sysconfdir}/smack
%{_sysconfdir}/smack/accesses.d
%{_sysconfdir}/smack/cipso.d
%{_sysconfdir}/smack/netlabel.d
%attr(755,root,root) %{_bindir}/*
