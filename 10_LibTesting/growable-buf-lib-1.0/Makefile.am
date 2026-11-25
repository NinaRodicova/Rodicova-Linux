ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I$(srcdir)/src

lib_LTLIBRARIES = libgrowablebuf.la
libgrowablebuf_la_SOURCES = src/growable_buf.c src/growable_buf.h
libgrowablebuf_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = src/growable_buf.h

if HAVE_CHECK
check_PROGRAMS = tests/test_growable_buf

tests_test_growable_buf_SOURCES = tests/test_growable_buf.c
tests_test_growable_buf_CFLAGS = @CHECK_CFLAGS@
tests_test_growable_buf_LDADD = libgrowablebuf.la @CHECK_LIBS@

TESTS = tests/test_growable_buf
TESTS_ENVIRONMENT = CK_FORK=yes
CK_VERBOSITY = verbose
endif

coverage:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage" check
	gcov -o src/.libs src/growable_buf.c
	@echo "---- coverage summary ----"
	@gcov src/growable_buf.c | grep -A1 "File 'src/growable_buf.c'"

CLEANFILES = *.gcda *.gcno *.gcov
