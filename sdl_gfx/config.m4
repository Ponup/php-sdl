dnl $Id$
dnl config.m4 for extension sdl_gfx

PHP_ARG_WITH(sdl_gfx, for sdl_gfx support, [  --with-sdl_gfx=DIR      Include sdl_gfx support ])

if test "$PHP_SDL_GFX" != "no"; then
	PHP_ADD_LIBRARY( SDL_gfx, 1, SDL_SHARED_LIBADD )

	PHP_NEW_EXTENSION(sdl_gfx, sdl_gfx.c, $ext_shared)
	ifdef([PHP_ADD_EXTENSION_DEP], [ PHP_ADD_EXTENSION_DEP(sdl_gfx, sdl) ] )

	PHP_ADD_LIBRARY_WITH_PATH(SDL_gfx, $SDL_GFX_DIR/lib, SDL_GFX_SHARED_LIBADD)
	PHP_SUBST(SDL_GFX_SHARED_LIBADD)

	AC_DEFINE(HAVE_SDL_GFX, 1, [ ])
fi

