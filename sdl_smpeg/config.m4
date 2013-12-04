dnl $Id$
dnl config.m4 for extension sdl_smpeg

PHP_ARG_WITH(sdl_smpeg, for sdl_smpeg support, [  --with-sdl_smpeg=DIR    Include sdl_smpeg support ])

if test "$PHP_SDL_SMPEG" != "no"; then

	SMPEG_CONFIG_BIN="smpeg-config"
	AC_MSG_CHECKING(for $SMPEG_CONFIG_BIN)

	SMPEG_SEARCH_PATHS="/usr/local /usr"
	if test "$PHP_SDL_SMPEG" != "yes"; then
		SMPEG_SEARCH_PATHS="$PHP_SDL_SMPEG $SMPEG_SEARCH_PATHS"
	fi
	
	SMPEG_CONFIG=""
	for SMPEG_SEARCH_PATH in $SMPEG_SEARCH_PATHS; do
		SMPEG_CONFIG="$SMPEG_SEARCH_PATH/bin/$SMPEG_CONFIG_BIN"
		if test -x "$SMPEG_CONFIG"; then
			break
		fi
	done

	if test -x "$SMPEG_CONFIG"; then
		AC_MSG_RESULT(found in $SMPEG_CONFIG)

		PHP_EVAL_INCLINE(`$SMPEG_CONFIG --cflags`)
		PHP_EVAL_LIBLINE(`$SMPEG_CONFIG --libs`, SDL_SMPEG_SHARED_LIBADD)
	else
		AC_MSG_RESULT(not found)

		AC_MSG_ERROR($SMPEG_CONFIG_BIN not found in $SMPEG_SEARCH_PATHS. Please check your smpeg installation.)
	fi

	PHP_NEW_EXTENSION(sdl_smpeg, sdl_smpeg.c, $ext_shared)
	ifdef([PHP_ADD_EXTENSION_DEP], [ PHP_ADD_EXTENSION_DEP(sdl_smpeg, sdl) ] )
	PHP_SUBST(SDL_SMPEG_SHARED_LIBADD)
	
	AC_DEFINE(HAVE_SDL_SMPEG, 1, [ ])
fi

