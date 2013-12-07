dnl
dnl $ Id: $
dnl

PHP_ARG_ENABLE(sdl, whether to enable SDL functions,
[  --enable-sdl         Enable SDL support])

if test "$PHP_SDL" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_SDL2"

	echo $PHP_VERSION
	echo $PHP_VERSION_ID


  AC_MSG_CHECKING(PHP version)

  export CPPFLAGS="$OLD_CPPFLAGS"

  AC_PATH_PROG(SDL2_CONFIG, sdl2-config, no)

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

  sources="
cpuinfo.c
error.c
pixels.c
rect.c
surface.c
video.c
window.c
version.c
"
  PHP_NEW_EXTENSION(sdl, sdl.c $sources, $ext_shared)
fi
