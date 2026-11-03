bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c

if USE_READLINE
rhasher_CPPFLAGS = -DUSE_READLINE
rhasher_LDADD = -lreadline
endif

TESTS = test_sha1.sh test_md5.sh
EXTRA_DIST = $(TESTS)

clean-local:
	rm -f test-suite.log *.log
