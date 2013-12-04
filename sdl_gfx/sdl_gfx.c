/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Santiago Lizardo <santiagolizardo@php.net>                   |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/sdl/php_sdl.h"
#include "php_sdl_gfx.h"

#include <SDL_gfxPrimitives.h>

/* True global resources - no need for thread safety here */
static int le_sdl_gfx;

static zend_module_dep sdl_gfx_deps[] = { 
	ZEND_MOD_REQUIRED("sdl")
	ZEND_MOD_END
};

/* {{{ sdl_gfx_functions[]
 *
 * Every user visible function must have an entry in sdl_gfx_functions[].
 */
const zend_function_entry sdl_gfx_functions[] = {
	ZEND_FE(gfx_rotozoomsurface, NULL)
	ZEND_FE(gfx_aacirclecolor, NULL)
	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_gfx_module_entry
 */
zend_module_entry sdl_gfx_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	sdl_gfx_deps,
	"SDL_gfx",
	sdl_gfx_functions,
	PHP_MINIT(sdl_gfx),
	PHP_MSHUTDOWN(sdl_gfx),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl_gfx),
	PHP_SDL_GFX_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL_GFX
ZEND_GET_MODULE(sdl_gfx)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl_gfx)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl_gfx)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl_gfx)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_gfx support", "enabled");
	php_info_print_table_row(2, "SDL_gfx module version", PHP_SDL_GFX_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* SDL_Surface * rotozoomSurface (SDL_Surface *src, double angle, double zoom, int smooth); */
PHP_FUNCTION(gfx_rotozoomsurface)
{
	zval *surfRes;
	long angle, smooth;
	double zoom;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zldl", &surfRes, &angle, &zoom, &smooth) == FAILURE)
	{
		RETURN_FALSE;
	}

	SDL_Surface *surf;
        ZEND_FETCH_RESOURCE(surf, SDL_Surface*, &surfRes, -1, le_surface_name, le_surface);

	SDL_Surface *newSurf = rotozoomSurface(surf, angle, zoom, smooth);

        php_sdl_surface_to_array(newSurf, return_value TSRMLS_CC);
}

/* int aacircleColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Uint32 color); */
PHP_FUNCTION(gfx_aacirclecolor)
{
	zval *surfRes;
	long x, y, r, color;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zllll", &surfRes, &x, &y, &r, &color) == FAILURE)
	{
		RETURN_FALSE;
	}

	SDL_Surface *surf;
        ZEND_FETCH_RESOURCE(surf, SDL_Surface*, &surfRes, -1, le_surface_name, le_surface);

	RETURN_LONG(aacircleColor(surf, x, y, r, color));
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
