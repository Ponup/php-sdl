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
#include "surface.h"

#define SDL_RENDERER_RES_NAME "SDL Renderer"
int le_sdl_renderer;

#define SDL_TEXTURE_RES_NAME "SDL Texture"
int le_sdl_texture;

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderDrawColor, 0, 0, 5)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
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

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderClear, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderClear)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderClear(renderer));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyRenderer, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_DestroyRenderer)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_DestroyRenderer(renderer);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyTexture, 0, 0, 1)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_DestroyTexture)
{
	zval *z_texture;
	SDL_Texture *texture;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_texture) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	SDL_DestroyTexture(texture);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderFillRect, 0, 0, 2)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
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

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderFillRect(renderer, &rect));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPresent, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderPresent)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_RenderPresent(renderer);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTextureFromSurface, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_CreateTextureFromSurface)
{
	zval *z_renderer, *z_surface;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *surface = NULL;
	
	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zO", &z_renderer, &z_surface, get_php_sdl_surface_ce() ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	surface = zval_to_sdl_surface(z_surface TSRMLS_CC);

	if( renderer && surface ) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		RETURN_RES(zend_register_resource(texture, le_sdl_texture));
	}
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
	RETURN_RES(zend_register_resource(renderer, le_sdl_renderer));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderCopy, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RenderCopy)
{
	zval *z_renderer, *z_texture;
	zval *z_srcrect, *z_dstrect;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect *srcrect = NULL, *dstrect = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzO!O!", &z_renderer, &z_texture, &z_srcrect, get_php_sdl_rect_ce(), &z_dstrect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);
	
	if(z_srcrect != NULL && Z_TYPE_P(z_srcrect) != IS_NULL) {
		srcrect = (SDL_Rect*)emalloc(sizeof(SDL_Rect));
		zval_to_sdl_rect(z_srcrect, srcrect TSRMLS_CC);
	}
	if(z_dstrect != NULL && Z_TYPE_P(z_dstrect) != IS_NULL) {
		dstrect = (SDL_Rect*)emalloc(sizeof(SDL_Rect));
		zval_to_sdl_rect(z_dstrect, dstrect TSRMLS_CC);
	}

	RETURN_LONG(SDL_RenderCopy(renderer, texture, srcrect, dstrect));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ sdl_render_functions[] */
zend_function_entry sdl_render_functions[] = {
	ZEND_FE(SDL_CreateRenderer, arginfo_SDL_CreateRenderer)
	ZEND_FE(SDL_DestroyRenderer, arginfo_SDL_DestroyRenderer)
	ZEND_FE(SDL_DestroyTexture, arginfo_SDL_DestroyTexture)
	ZEND_FE(SDL_SetRenderDrawColor, arginfo_SDL_SetRenderDrawColor)
	ZEND_FE(SDL_RenderClear, arginfo_SDL_RenderClear)
	ZEND_FE(SDL_RenderCopy, arginfo_SDL_RenderCopy)
	ZEND_FE(SDL_RenderFillRect, arginfo_SDL_RenderFillRect)
	ZEND_FE(SDL_RenderPresent, arginfo_SDL_RenderPresent)
	ZEND_FE(SDL_CreateTextureFromSurface, arginfo_SDL_CreateTextureFromSurface)
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
	le_sdl_texture = zend_register_list_destructors_ex(NULL, NULL, SDL_TEXTURE_RES_NAME, module_number);

	return (zend_register_functions(NULL, sdl_render_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */
