dnl $Id$
dnl config.m4 for extension sdl

PHP_ARG_WITH(sdl, for sdl support, [  --with-sdl=DIR          Include sdl support ])

if test "$PHP_SDL" != "no"; then

	SDL_CONFIG_BIN="sdl-config"
	AC_MSG_CHECKING(for $SDL_CONFIG_BIN)

	SDL_SEARCH_PATHS="/usr/local /usr"
	if test "$PHP_SDL" != "yes"; then
		SDL_SEARCH_PATHS="$PHP_SDL $SDL_SEARCH_PATHS"
	fi

	SDL_CONFIG=""
	for SDL_SEARCH_PATH in $SDL_SEARCH_PATHS; do
		SDL_CONFIG="$SDL_SEARCH_PATH/bin/$SDL_CONFIG_BIN"
		if test -x "$SDL_CONFIG"; then
			break
		fi
	done

	if test -n "$SDL_CONFIG"; then
		AC_MSG_RESULT(found in $SDL_CONFIG)

		PHP_EVAL_INCLINE(`$SDL_CONFIG --cflags`)
		PHP_EVAL_LIBLINE(`$SDL_CONFIG --libs`, SDL_SHARED_LIBADD)
	else
		AC_MSG_RESULT([not found, trying manual way])

		AC_MSG_CHECKING(for SDL/SDL.h)

		SDL_DIR=""
		for i in $SDL_SEARCH_PATHS; do
			if test -f "$i/include/SDL/SDL.h"; then
				SDL_DIR=$i
			fi
			if test -n "$SDL_DIR"; then
				break
			fi
		done

		if test -z "$SDL_DIR"; then
			AC_MSG_ERROR(not found in $SDL_SEARCH_PATHS)
		else
			AC_MSG_RESULT(found below $SDL_DIR/include)
		fi

		if test ! -f "$SDL_DIR/$PHP_LIBDIR/libSDL.$SHLIB_SUFFIX_NAME"; then
			AC_MSG_ERROR(Cannot find $PHP_LIBDIR/libSDL.$SHLIB_SUFFIX_NAME below $i)
		fi

		PHP_ADD_INCLUDE($SDL_DIR/include/SDL)
		PHP_ADD_LIBRARY_WITH_PATH(SDL, $SDL_DIR/$PHP_LIBDIR, SDL_SHARED_LIBADD)
	fi

	PHP_NEW_EXTENSION(sdl, php_sdl.c php_sdl_audio.c php_sdl_event.c php_sdl_thread.c php_sdl_wm.c php_sdl_cdrom.c php_sdl_joystick.c php_sdl_time.c, $ext_shared)
	PHP_SUBST(SDL_SHARED_LIBADD)
	
	AC_DEFINE(HAVE_SDL, 1, [ ])
fi

