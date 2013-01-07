Name:       smack
Version:    1.0
Release:    1
Summary:    Package to interact with Smack
Group:      System/Kernel
License:    LGPL-2.1
URL:        https://github.com/smack-team/smack
Source0:    %{name}-%{version}.tar.gz
BuildRequires: automake
BuildRequires: autoconf
BuildRequires: libtool

%description
Library allows applications to work with Smack

%package devel
Summary:    Development headers and libs for libsmack
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Standard header files for use when developing Smack enabled applications

%package utils
Summary:    Selection of tools for developers working with Smack
Group:      System/Kernel
Requires:   %{name} = %{version}-%{release}

%description utils
Tools provided to load and unload rules from the kernel and query the policy

%prep
%setup -q

%build
autoreconf --install --symlink
%configure --with-systemdsystemunitdir=%{_prefix}/lib/systemd/system

make %{?_smp_mflags}

%install
%make_install

install -d %{buildroot}/etc/smack/accesses.d
install -d %{buildroot}/etc/smack/cipso.d
install -d %{buildroot}/smack

install -d %{buildroot}%{_prefix}/lib/systemd/system/basic.target.wants
install -d %{buildroot}%{_prefix}/lib/systemd/system/local-fs.target.wants
ln -s ../smack.service %{buildroot}%{_prefix}/lib/systemd/system/basic.target.wants/smack.service
ln -s ../smack.mount %{buildroot}%{_prefix}/lib/systemd/system/local-fs.target.wants/smack.mount


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%docs_package

%files
%defattr(644,root,root,755)
%{_libdir}/libsmack.so.*

%files devel
%defattr(644,root,root,755)
%{_includedir}/sys/smack.h
%{_libdir}/libsmack.so
%{_libdir}/pkgconfig/libsmack.pc

%files utils
%defattr(644,root,root,755)
%{_sysconfdir}/smack
%{_sysconfdir}/smack/accesses.d
%{_sysconfdir}/smack/cipso.d
/smack
%attr(755,root,root) %{_bindir}/*
%{_prefix}/lib/systemd/system/smack.mount
%{_prefix}/lib/systemd/system/local-fs.target.wants/smack.mount
%{_prefix}/lib/systemd/system/smack.service
%{_prefix}/lib/systemd/system/basic.target.wants/smack.service
