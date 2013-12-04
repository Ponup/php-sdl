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
#include "php_sdl_ttf.h"

#include <SDL_ttf.h>

/* True global resources - no need for thread safety here */
static int le_sdl_ttf;

static int le_ttf_font;

static zend_module_dep sdl_ttf_deps[] = { 
	ZEND_MOD_REQUIRED("sdl")
	ZEND_MOD_END
};

/* {{{ sdl_ttf_functions[]
 *
 * Every user visible function must have an entry in sdl_ttf_functions[].
 */
const zend_function_entry sdl_ttf_functions[] = {
	ZEND_FE(ttf_init, NULL)
	ZEND_FE(ttf_openfont, NULL)
	ZEND_FE(ttf_closefont, NULL)
	ZEND_FE(ttf_rendertext_solid, NULL)
	ZEND_FE(ttf_rendertext_blended, NULL)
	ZEND_FE(ttf_renderutf8_solid, NULL)
	ZEND_FE(ttf_renderutf8_blended, NULL)
	ZEND_FE(ttf_renderunicode_solid, NULL)
	ZEND_FE(ttf_fontlineskip, NULL)
	ZEND_FE(ttf_quit, NULL)

	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_ttf_module_entry
 */
zend_module_entry sdl_ttf_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	sdl_ttf_deps,
	"SDL_ttf",
	sdl_ttf_functions,
	PHP_MINIT(sdl_ttf),
	PHP_MSHUTDOWN(sdl_ttf),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl_ttf),
	PHP_SDL_TTF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL_TTF
ZEND_GET_MODULE(sdl_ttf)
#endif

static void _ttf_destructor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl_ttf)
{
	le_ttf_font = zend_register_list_destructors_ex(_ttf_destructor, NULL, le_ttf_font_name, module_number);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl_ttf)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl_ttf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_ttf support", "enabled");
	php_info_print_table_row(2, "SDL_ttf module version", PHP_SDL_TTF_VERSION);
	php_info_print_table_end();
}
/* }}} */

PHP_FUNCTION(ttf_init)
{
	TTF_Init();
	RETURN_TRUE;
}

PHP_FUNCTION(ttf_openfont)
{
	char *fontPath = NULL;
	long fontPathLen, fontSize;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &fontPath, &fontPathLen, &fontSize) == FAILURE) {
		RETURN_FALSE;
	}

	TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
        ZEND_REGISTER_RESOURCE(return_value, font, le_ttf_font);
}

PHP_FUNCTION(ttf_rendertext_solid)
{
	zval *fontRes;
	zval *colorArray;
	char *text = NULL;
	int textLen = -1;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsa", &fontRes, &text, &textLen, &colorArray) == FAILURE)
	{
		RETURN_FALSE;
	}

	TTF_Font *font;
        ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	SDL_Color color;
	php_array_to_sdl_color(&colorArray, &color);

	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

PHP_FUNCTION(ttf_rendertext_blended)
{
	zval *fontRes;
	zval *colorArray;
	char *text = NULL;
	int textLen = -1;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsa", &fontRes, &text, &textLen, &colorArray) == FAILURE)
	{
		RETURN_FALSE;
	}

	TTF_Font *font;
        ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	SDL_Color color = { 100, 200, 0 };
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

PHP_FUNCTION(ttf_renderunicode_solid)
{
	zval *fontRes;
	zval *colorArray;
	char *text = NULL;
	int textLen = -1;
	TTF_Font *font = NULL;
	SDL_Color color = { 100, 200, 0 };

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsa", &fontRes, &text, &textLen, &colorArray) == FAILURE)
	{
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	SDL_Surface *surface = TTF_RenderUNICODE_Solid(font, text, color);

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

PHP_FUNCTION(ttf_renderutf8_solid)
{
	zval *fontRes;
	zval *colorArray;
	char *text = NULL;
	int textLen = -1;
	TTF_Font *font = NULL;
	SDL_Color color;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsa", &fontRes, &text, &textLen, &colorArray) == FAILURE)
	{
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	php_array_to_sdl_color(&colorArray, &color);

	SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

PHP_FUNCTION(ttf_renderutf8_blended)
{
	zval *fontRes;
	zval *colorArray;
	char *text = NULL;
	int textLen = -1;
	SDL_Color color;
	TTF_Font *font = NULL;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsa", &fontRes, &text, &textLen, &colorArray) == FAILURE)
	{
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	php_array_to_sdl_color(&colorArray, &color);

	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

PHP_FUNCTION(ttf_closefont)
{
	zval *fontRes = NULL;
	TTF_Font *font = NULL;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &fontRes) == FAILURE)
	{
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);
	TTF_CloseFont(font);

	RETURN_TRUE;
}

PHP_FUNCTION(ttf_fontlineskip)
{
	zval *fontRes = NULL;
	TTF_Font *font = NULL;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &fontRes) == FAILURE)
	{
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(font, TTF_Font*, &fontRes, -1, le_ttf_font_name, le_ttf_font);

	RETURN_LONG(TTF_FontLineSkip(font));
}

PHP_FUNCTION(ttf_quit)
{
	TTF_Quit();
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
