dnl config.m4 for the PHP SDL extension

PHP_ARG_WITH(sdl, whether to enable SDL functions,
[  --with-sdl[=SDLCONFIG_PATH]         Enable SDL support])

PHP_ARG_ENABLE(sdl-debug, whether to enable PHP-SDL debug support,
[  --enable-sdl-debug     Enable SDL debug support], no, no)

if test "$PHP_SDL" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_SDL2 -Wall -Wfatal-errors"

  REQ_PHP_VERSION="8.0.0"
  REQ_PHP_VERSION_ID=80000
  if test -z "$PHP_VERSION_ID"; then
    AC_MSG_CHECKING(PHP version)
    AC_TRY_COMPILE([#include <php_version.h>], [
    #if PHP_VERSION_ID < $REQ_PHP_VERSION_ID
    #error  this extension requires at least PHP version $REQ_PHP_VERSION
    #endif
    ],
    [AC_MSG_RESULT(ok)],
    [AC_MSG_ERROR([need at least PHP v$REQ_PHP_VERSION])])
  else
    if test "$PHP_VERSION_ID" -lt "$REQ_PHP_VERSION_ID"; then
      AC_MSG_ERROR([SDL needs at least PHP v$REQ_PHP_VERSION])
    fi
  fi
  PHP_SDL_CFLAGS="$CPPFLAGS"

  export CPPFLAGS="$OLD_CPPFLAGS"

  dnl {{{ --enable-sdl-debug
  if test "$PHP_SDL_DEBUG" != "no"; then
    CFLAGS="$CFLAGS -Wall -Wpedantic -g -ggdb -O0"
  fi
  dnl }}}

  if test "$PHP_SDL" == "yes"; then
    AC_PATH_PROG(SDL2_CONFIG, sdl2-config, no)
  else
    SDL2_CONFIG="$PHP_SDL"
  fi

  AC_MSG_CHECKING(for SDL2 library)
  if test -x "$SDL2_CONFIG" ; then
    SDL2_VERSION=`$SDL2_CONFIG --version`
    AC_MSG_RESULT(using SDL2 version $SDL2_VERSION)
    PHP_EVAL_INCLINE(`$SDL2_CONFIG --cflags`)
    PHP_EVAL_LIBLINE(`$SDL2_CONFIG --libs`, SDL_SHARED_LIBADD)
  else
    AC_MSG_ERROR(Cannot find sdl2-config)
  fi

  PHP_SUBST(SDL_SHARED_LIBADD)
  AC_DEFINE(HAVE_SDL2, 1, [ ])

  SDL_SOURCE_FILES="`find src -name "*.c"`"
  PHP_NEW_EXTENSION(sdl, $SDL_SOURCE_FILES, $ext_shared,, $PHP_SDL_CFLAGS)
fi
