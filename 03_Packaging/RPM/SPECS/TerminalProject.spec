Name:	TerminalProject
Version:	0.0.1
Release:	alt1
Group:	Other
License:	MIT
URL:	https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Source:	%name-%version.tar.gz
Summary:	homework 01

BuildRequires: libncursesw-devel

%description
File viewing program.

%prep
%setup -c

%build
make Show

%install
make DESTDIR=%buildroot install

%files
%_bindir/Show
