AC_PREREQ([2.69])
AC_INIT([rhasher], [0.00], [nrodicova@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADER([rhash.h], [], [
  AC_MSG_ERROR([Unable to find rhash.h])
])

AC_CHECK_LIB([rhash], [rhash_library_init], [], [
  AC_MSG_ERROR([Unable to find rhash])
])

AC_CHECK_LIB([readline], [readline], [rreadline=yes LIBS="-lreadline $LIBS"], [rreadline=no])

AC_ARG_ENABLE([readline],
  AS_HELP_STRING([--enable-readline], [Force build with readline support]),
  [],
  [enable_readline=$rreadline]
)

AM_CONDITIONAL([USE_READLINE], [test "x$enable_readline" = "xyes"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
