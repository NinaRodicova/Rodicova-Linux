AC_INIT([growable-buf-lib], [1.0], [nrodicova@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT

PKG_CHECK_MODULES([CHECK], [check >= 0.8.2],
    [have_check="yes"],
    [AC_MSG_WARN(['Check' not found.])
     have_check="no"])
AM_CONDITIONAL([HAVE_CHECK], [test x$have_check = xyes])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
