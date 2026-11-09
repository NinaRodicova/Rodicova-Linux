SUBDIRS = po

bin_PROGRAMS = prog
prog_SOURCES = prog.c

prog_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

prog_LDADD = @LIBINTL@
