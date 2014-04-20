dnl $Id$
dnl config.m4 for extension sdl_ttf

PHP_ARG_WITH(sdl_ttf, for sdl_ttf support, [  --with-sdl_ttf=DIR      Include sdl_ttf support ])

if test "$PHP_SDL_TTF" != "no"; then
	PHP_ADD_LIBRARY(SDL_ttf, 1, SDL_SHARED_LIBADD)

	PHP_NEW_EXTENSION(sdl_ttf, sdl_ttf.c, $ext_shared)
	ifdef([PHP_ADD_EXTENSION_DEP], [ PHP_ADD_EXTENSION_DEP(sdl_ttf, sdl) ] )
	
	PHP_ADD_LIBRARY_WITH_PATH(SDL_ttf, $SDL_TTF_DIR/$PHP_LIBDIR, SDL_TTF_SHARED_LIBADD)
	PHP_SUBST(SDL_TTF_SHARED_LIBADD)
	
	AC_DEFINE(HAVE_SDL_TTF, 1, [ ])
fi

