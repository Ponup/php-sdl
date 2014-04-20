dnl $Id$
dnl config.m4 for extension sdl_image

PHP_ARG_WITH(sdl_image, for sdl_image support, [  --with-sdl_image=DIR    Include sdl_image support ])

if test "$PHP_SDL_IMAGE" != "no"; then
	AC_MSG_CHECKING(for SDL/SDL_image.h and lib/libSDL_image.$SHLIB_SUFFIX_NAME)
	if test -f "$SDL_DIR/include/SDL/SDL_image.h" -a -f "$SDL_DIR/lib/libSDL_image.$SHLIB_SUFFIX_NAME"; then
		AC_DEFINE(HAVE_SDL_IMAGE, 1, [ ])
		SDL_IMAGE=yes
		AC_MSG_RESULT(found below $SDL_DIR/include and $SDL_DIR)
	else
		AC_MSG_RESULT(not found)
	fi

	SDL_LIST="/usr/local /usr"
	if test "$PHP_SDL_IMAGE" != "yes"; then
		SDL_LIST="$PHP_SDL_IMAGE $SDL_LIST"
	fi
	SDL_CONFIG=""

	AC_MSG_CHECKING(for sdl-config)
	for i in $SDL_LIST; do
		if test -x "$i/bin/sdl-config"; then
			SDL_CONFIG="$i/bin/sdl-config"
			break
		fi
	done

	if test -n "$SDL_CONFIG"; then
		AC_MSG_RESULT(found in $SDL_CONFIG)

		PHP_EVAL_INCLINE(`$SDL_CONFIG --cflags`)

		dnl Try to extract SDL_DIR to find SDL_Image
		SDL_CFLAGS=`$SDL_CONFIG --cflags`
		SDL_DIR=""
		for i in $SDL_CFLAGS; do
			case $i in
				-I*SDL*)
					SDL_INCDIR=`echo $i | cut -c 3-`
					AC_MSG_CHECKING(for SDL_image.h in $SDL_INCDIR)
					if test -f "$SDL_INCDIR/SDL_image.h"; then
						AC_DEFINE(HAVE_SDL_IMAGE, 1, [ ])
						SDL_IMAGE=yes
						AC_MSG_RESULT(found)
						PHP_ADD_LIBRARY(SDL_image, 1, SDL_SHARED_LIBADD)
					else
						AC_MSG_RESULT(not found)
					fi
					;;
			esac
		done
	fi
		
	PHP_ADD_LIBRARY_WITH_PATH(SDL_image, $SDL_IMAGE_DIR/lib, SDL_IMAGE_SHARED_LIBADD)

	if test "$ext_shared" = "yes"; then
		PHP_ADD_LIBRARY_WITH_PATH(SDL, $SDL_DIR/lib, SDL_SHARED_LIBADD)
		if test "$SDL_IMAGE" = "yes"; then
			PHP_ADD_LIBRARY_WITH_PATH(SDL_image, $SDL_DIR/lib, SDL_SHARED_LIBADD)
		fi
	else
		PHP_ADD_LIBRARY_DEFER_WITH_PATH(SDL, $SDL_DIR/lib)
		if test "$SDL_IMAGE" = "yes"; then
			PHP_ADD_LIBRARY_DEFER_WITH_PATH(SDL_image, $SDL_DIR/lib)
		fi
	fi
	
	PHP_NEW_EXTENSION(sdl_image, sdl_image.c, $ext_shared)
	ifdef([PHP_ADD_EXTENSION_DEP], [ PHP_ADD_EXTENSION_DEP(sdl_image, sdl) ] )

	PHP_SUBST(SDL_SHARED_LIBADD)
	PHP_SUBST(SDL_IMAGE_SHARED_LIBADD)

	AC_DEFINE(HAVE_SDL_IMAGE, 1, [ ])
fi

