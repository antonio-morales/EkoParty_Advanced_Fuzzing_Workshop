#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([unrtf], [0.21.10], [bug-unrtf@gnu.org])
AC_CONFIG_SRCDIR([src/attr.c])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADER([config.h])

# Initialize automake

AM_INIT_AUTOMAKE

# AM_MAINTAINER_MODE is a controversial macro.
# I suggest you read this to understand what is going on:
#
# http://www.gnu.org/software/automake/manual/html_mono/automake.html#maintainer-mode
#
# when acting as a maintainer (writing code, preparing distributions, ...),
# turn the maintainer mode on by using ./configure --enable-maintainer-mode
#
# your users will not see maintainer rules, and so their (potentially
# incompatible) autotools do not have any chance to trigger and mess up things.

AM_MAINTAINER_MODE

# Checks for programs (compiler and installation program)
AC_PROG_CC
AC_PROG_INSTALL

# Checks for header files.
AC_HEADER_STDC

# following is not really necessary, since it is already done by preceding
# macro, but it shows how to extend HAVE_ macros to other headers.
AC_CHECK_HEADERS([stdlib.h stdio.h ctype.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strchr strstr])

AC_CANONICAL_HOST
case $host in
    *-*-cygwin*)	AC_SUBST(LIBS, ["-liconv"]);;
    *aix*)		AC_SUBST(LIBS, ["-liconv"]);;
    *-*-darwin*)	AC_SUBST(LIBS, ["-liconv"]);;
    *-*-solaris*)	AC_SUBST(LIBS, ["-liconv"]);;
esac

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 outputs/Makefile
                 patches/Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT

