AC_PREREQ(2.61)

# Package version
m4_define(helloworld_version_major, 0)
m4_define(helloworld_version_minor, 1)
m4_define(helloworld_version_micro, 0)

m4_define([helloworld_version],
          [helloworld_version_major.helloworld_version_minor.helloworld_version_micro])
m4_define([helloworld_api_version],
          [helloworld_version_major.helloworld_version_minor])

AC_ARG_ENABLE([dev],
  [AS_HELP_STRING([--disable-dev], [Turn on helloworld Development])],
  [:],
  [enable_dev=check])

AC_ARG_ENABLE([utest],
  [AS_HELP_STRING([--disable-utest], [Configuration for helloworld Unit Testing])],
  [:],
  [enable_utest=check])

AC_INIT(helloworld, helloworld_version)
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS(config.h)

if test "$enable_utest" = "yes"; then
    AC_DEFINE([UTEST],1,[Define to 1 for unit tests testing])
    AC_MSG_NOTICE([Configuration for helloworld Unit Testing])
    
else
    AC_DEFINE([DEVELOPMENT],1,[Define to 1 for development code])
    AC_MSG_NOTICE([Configuration for helloworld Development])
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
echo "   helloworld $VERSION"
echo "   ====================="
echo ""
echo "   To build the project, run \"make\" in build directory"
echo ""
