AC_PREREQ(2.61)

# Package version
m4_define(diff_app_version_major, 0)
m4_define(diff_app_version_minor, 1)
m4_define(diff_app_version_micro, 0)

m4_define([diff_app_version],
          [diff_app_version_major.diff_app_version_minor.diff_app_version_micro])
m4_define([diff_app_api_version],
          [diff_app_version_major.diff_app_version_minor])

AC_ARG_ENABLE([dev],
  [AS_HELP_STRING([--disable-dev], [Turn on diff_app Development])],
  [:],
  [enable_dev=check])

AC_ARG_ENABLE([utest],
  [AS_HELP_STRING([--disable-utest], [Configuration for diff_app Unit Testing])],
  [:],
  [enable_utest=check])

AC_INIT(diff_app, diff_app_version)
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS(config.h)

if test "$enable_utest" = "yes"; then
    AC_DEFINE([TEST],1,[Define to 1 for unit tests testing])
    AC_MSG_NOTICE([Configuration for diff_app Unit Testing])
    
else
    AC_DEFINE([DEV],1,[Define to 1 for development code])
    AC_MSG_NOTICE([Configuration for diff_app Development])
fi

LDFLAGS="$LDFLAGS -lpthread"
CFLAGS="-std=gnu99 -O2"
CXXFLAGS="-std=c++11 -O2"
CPPFLAGS="$CPPFLAGS"

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_INSTALL

# enable pkg-config
PKG_PROG_PKG_CONFIG

# Checks for library functions.
#AC_CHECK_FUNCS([memset])

AC_OUTPUT([
Makefile
src/Makefile
])

echo ""
echo "   diff_app $VERSION"
echo "   ====================="
echo ""
echo "   To build the project, run \"make\" in build directory"
echo ""
