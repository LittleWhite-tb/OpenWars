#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT(OpenAWars, 0.1, http://code.google.com/p/openawars/issues/list)
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([Sources/main.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_SEARCH_LIBS(SDL_Init, SDL, [], [
	AC_MSG_ERROR([SDL is needed for this project])
])

AC_SEARCH_LIBS(IMG_Init, SDL_image, [], [
	AC_MSG_ERROR([SDL_image is needed for this project])
])

#AC_SEARCH_LIBS(xmlParseFile, xml2, [], [
#	AC_MSG_ERROR([xml2 is needed for this project])
#])

PKG_CHECK_MODULES(LIBXML, [libxml-2.0 >= 2.6.0], , [
	AC_MSG_RESULT(no)
	AC_MSG_ERROR([
You must have libxml2 >= 2.6.0 development headers installed to build.
])])

AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

CPPFLAGS="$CPPFLAGS $LIBXML_CFLAGS"
LIBS="$LIBS $LIBXML_LIBS"

# Checks for header files.
AC_PATH_X
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h malloc.h memory.h stddef.h stdint.h stdlib.h string.h strings.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC

CPPFLAGS="$CPPFLAGS -Wall -Wextra"

AC_CONFIG_FILES([
        Makefile
        Sources/Makefile
        ])


AC_OUTPUT
