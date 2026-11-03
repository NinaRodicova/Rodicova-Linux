Name:           rhasher
Version:        0.0.1
Release:        alt1
Group:          Text tools
License:        MIT
Summary:        07 Homework
Source:         %name-%version.tar.gz

BuildRequires: gcc make autoconf automake libtool
BuildRequires: librhash-devel
BuildRequires: libreadline-devel

%description
07_homeword

%prep
%setup

%build
%autoreconf -fi
%configure
%make_build

%install
%makeinstall_std

%files
%_bindir/%name

%changelog
* Mon Nov 03 2025 Nina <nrodicova@gmail.com> 0.0.1-alt1
- Initial build
