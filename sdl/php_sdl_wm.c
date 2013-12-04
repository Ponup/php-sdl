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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sdl.h"

#include <SDL.h>

/* {{{ proto void sdl_wm_setcaption(string title, string icon)
 */
PHP_FUNCTION(sdl_wm_setcaption)
{
	char *title_arg = NULL, *icon_arg = NULL;
	int title_arg_len = 0, icon_arg_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &title_arg, &title_arg_len, &icon_arg, &icon_arg_len) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	SDL_WM_SetCaption( title_arg, icon_arg );
}
/* }}} */

/* {{{ proto void sdl_wm_getcaption(string &title, string &icon)
 */
PHP_FUNCTION(sdl_wm_getcaption)
{
	zval *title_arg, *icon_arg;
	char *title, *icon;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &title_arg, &icon_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	/* check for parameter being passed by reference */
	if (!PZVAL_IS_REF(title_arg)) {
		php_error(E_WARNING, "%s() parameter title needs to be passed by reference",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (!PZVAL_IS_REF(icon_arg)) {
		php_error(E_WARNING, "%s() parameter icon needs to be passed by reference",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	convert_to_string_ex( &title_arg );
	convert_to_string_ex( &icon_arg );

	SDL_WM_GetCaption( &title, &icon );

	ZVAL_STRING( title_arg, title, 1 );
	ZVAL_STRING( icon_arg, icon, 1 );
}
/* }}} */

/* {{{ proto void sdl_wm_seticon(array surface, array mask)
 */
PHP_FUNCTION(sdl_wm_seticon)
{
	zval *surface_arg, *mask_arg, **handle_resource, **mask_value;
	int mask_arg_null;
	ulong mask_count, i;
	Uint8 *mask = NULL;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "az", &surface_arg, &mask_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (Z_TYPE_PP(&mask_arg) != IS_ARRAY) {
		mask_arg_null = 1;
	} else {
		mask_arg_null = 0;
		mask_count = 0;
		mask_count = zend_hash_next_free_element(Z_ARRVAL_PP(&mask_arg));

		if (mask_count == 0) {
			php_error(E_WARNING, "%s() array mask is empty!",
				  get_active_function_name(TSRMLS_C));
			RETURN_FALSE;
		}

		mask = (Uint8 *)emalloc(mask_count*sizeof(Uint8));

		for(i = 0; i < mask_count; i++) {

			if (zend_hash_index_find(Z_ARRVAL_PP(&mask_arg), i, (void **)&mask_value) == FAILURE) {
				php_error(E_WARNING, "%s() unable to find mask[%lu]",
				  get_active_function_name(TSRMLS_C), i );
			}

			mask[i] = (Uint8) Z_LVAL_PP(mask_value);
		}
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	SDL_WM_SetIcon(surface, (mask_arg_null) ? NULL : mask);

	efree(mask);
}
/* }}} */

/* {{{ proto void sdl_wm_iconifywindow(void)
 */
PHP_FUNCTION(sdl_wm_iconifywindow)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_BOOL( SDL_WM_IconifyWindow() );
}
/* }}} */

/* {{{ proto int sdl_wm_togglefullscreen(array surface)
 */
PHP_FUNCTION(sdl_wm_togglefullscreen)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_BOOL( SDL_WM_ToggleFullScreen( surface ) );
}
/* }}} */

/* {{{ proto int sdl_wm_grabinput(int mode)
 */
PHP_FUNCTION(sdl_wm_grabinput)
{
	long mode;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mode) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG( SDL_WM_GrabInput( mode ) );
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
