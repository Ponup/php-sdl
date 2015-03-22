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
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "render.h"
#include "window.h"

#define SDL_RENDERER_RES_NAME "SDL Renderer"

int le_sdl_renderer;

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderDrawColor, 0, 0, 5)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_SetRenderDrawColor)
{
	zval *z_renderer;
	long r, g, b, a;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zllll", &z_renderer, &r, &g, &b, &a) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(renderer, SDL_Renderer*, &z_renderer, -1, SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderClear, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderClear)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(renderer, SDL_Renderer*, &z_renderer, -1, SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderClear(renderer));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderFillRect, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderFillRect)
{
	zval *z_renderer;
	zval *z_rect;
	SDL_Rect rect;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zO", &z_renderer, &z_rect, get_php_sdl_rect_ce() ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	zval_to_sdl_rect(z_rect, &rect TSRMLS_CC);

	ZEND_FETCH_RESOURCE(renderer, SDL_Renderer*, &z_renderer, -1, SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderFillRect(renderer, &rect));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPresent, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderPresent)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(renderer, SDL_Renderer*, &z_renderer, -1, SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_RenderPresent(renderer);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateRenderer, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_CreateRenderer)
{
	long index, flags;
	zval *z_window;
	SDL_Window *window;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oll", &z_window, get_php_sdl_window_ce(), &index, &flags) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	if( z_window != NULL ) {
		window = zval_to_sdl_window(z_window TSRMLS_CC);
	}

	renderer = SDL_CreateRenderer(window, index, flags);
	ZEND_REGISTER_RESOURCE(return_value, renderer, le_sdl_renderer);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ sdl_render_functions[] */
zend_function_entry sdl_render_functions[] = {
	ZEND_FE(SDL_CreateRenderer, arginfo_SDL_CreateRenderer)
	ZEND_FE(SDL_SetRenderDrawColor, arginfo_SDL_SetRenderDrawColor)
	ZEND_FE(SDL_RenderClear, arginfo_SDL_RenderClear)
	ZEND_FE(SDL_RenderFillRect, arginfo_SDL_RenderFillRect)
	ZEND_FE(SDL_RenderPresent, arginfo_SDL_RenderPresent)
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_render)
{
	REGISTER_LONG_CONSTANT("SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE, CONST_CS | CONST_PERSISTENT);

	le_sdl_renderer = zend_register_list_destructors_ex(NULL, NULL, SDL_RENDERER_RES_NAME, module_number);

	return (zend_register_functions(NULL, sdl_render_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */
