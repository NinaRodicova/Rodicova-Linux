Name:	tracing
Version:	0.0.1
Release:	alt1
Group:	Other
License:	MIT
URL:	https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/06_Tracing
Source:	%name-%version.tar.gz
Summary:	homework 06

%description
tracing program move

%prep
%setup

%build
make move

%install
make DESTDIR=%buildroot install

%files
%{_bindir}/move
%{_bindir}/my_remove.so
%{_bindir}/safemove
%doc %{_docdir}/%{name}/README

%changelog
* Sat Oct 31 2026 Initial package - 0.0.1-alt1
- Initial package
