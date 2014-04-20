dnl $Id$
dnl config.m4 for extension sdl_mixer

PHP_ARG_WITH(sdl_mixer, for sdl_mixer support, [  --with-sdl_mixer=DIR    Include sdl_mixer support ])

if test "$PHP_SDL_MIXER" != "no"; then
	PHP_ADD_LIBRARY(SDL_mixer, 1, SDL_SHARED_LIBADD)

	PHP_NEW_EXTENSION(sdl_mixer, sdl_mixer.c, $ext_shared)
	ifdef([PHP_ADD_EXTENSION_DEP], [ PHP_ADD_EXTENSION_DEP(sdl_mixer, sdl) ] )
	
	PHP_ADD_LIBRARY_WITH_PATH(SDL_mixer, $SDL_MIXER_DIR/$PHP_LIBDIR, SDL_MIXER_SHARED_LIBADD)
	PHP_SUBST(SDL_MIXER_SHARED_LIBADD)

	AC_DEFINE(HAVE_SDL_MIXER, 1, [ ])
fi

