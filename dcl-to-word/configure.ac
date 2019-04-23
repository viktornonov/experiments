AC_INIT([dcl],[0.1])
AM_INIT_AUTOMAKE([-Wall foreign])
#??? needed for the check??
AM_PROG_AR


AC_PROG_CC
LT_INIT

# maybe I don;t need this???
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])
AC_OUTPUT
