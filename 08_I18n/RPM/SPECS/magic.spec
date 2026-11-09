Name:           magic
Version:        1.0
Release:        alt1
Group:	Other
License:	MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/08_I18n
Source:        %{name}-%{version}.tar.gz
Summary:	08 homework

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  gettext-tools
BuildRequires:  autoconf
BuildRequires:  automake

%description
Homework8

%prep
%setup

%build
%configure
%make_build

%install
make install DESTDIR=%{buildroot}
%find_lang %{name}

%files -f %{name}.lang
%{_bindir}/prog

%changelog
* Mon Nov 09 2026 Nina <nrodicova@gmail.com> 1.0-alt1
- Initial build
