/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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

#include "render.h"
#include "window.h"
#include "surface.h"
#include "rect.h"

#define SDL_RENDERER_RES_NAME "SDL Renderer"
int le_sdl_renderer;

#define SDL_TEXTURE_RES_NAME "SDL Texture"
int le_sdl_texture;

PHP_FUNCTION(SDL_SetRenderDrawColor)
{
	zval *z_renderer;
	zend_long r, g, b, a;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zllll", &z_renderer, &r, &g, &b, &a) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

PHP_FUNCTION(SDL_RenderClear)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderClear(renderer));
}

PHP_FUNCTION(SDL_DestroyRenderer)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_DestroyRenderer(renderer);
}

PHP_FUNCTION(SDL_DestroyTexture)
{
	zval *z_texture;
	SDL_Texture *texture;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_texture) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	SDL_DestroyTexture(texture);
}

PHP_FUNCTION(SDL_RenderFillRect)
{
	zval *z_renderer = NULL;
	zval *z_rect = NULL;
	SDL_Rect rect;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_rect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	zval_to_sdl_rect(z_rect, &rect);

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderFillRect(renderer, &rect));
}

PHP_FUNCTION(SDL_RenderDrawRect)
{
	zval *z_renderer = NULL;
	zval *z_rect = NULL;
	SDL_Rect rect;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_rect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	zval_to_sdl_rect(z_rect, &rect);

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderDrawRect(renderer, &rect));
}

PHP_FUNCTION(SDL_RenderDrawLine)
{
	zval *z_renderer = NULL;
	SDL_Renderer *renderer = NULL;
	zend_long x1, y1, x2, y2;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_ZVAL(z_renderer)
		Z_PARAM_LONG(x1)
		Z_PARAM_LONG(y1)
		Z_PARAM_LONG(x2)
		Z_PARAM_LONG(y2)
	ZEND_PARSE_PARAMETERS_END();

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2));
}

PHP_FUNCTION(SDL_RenderPresent)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_RenderPresent(renderer);
}

PHP_FUNCTION(SDL_RenderDrawPoint)
{
	zval *z_renderer = NULL;
	SDL_Renderer *renderer = NULL;
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(z_renderer)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderDrawPoint(renderer, (int)x, (int)y));
}

PHP_FUNCTION(SDL_CreateTextureFromSurface)
{
	zval *z_renderer, *z_surface;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *surface = NULL;

	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_surface, get_php_sdl_surface_ce() ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	surface = zval_to_sdl_surface(z_surface);

	if( renderer && surface ) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		RETURN_RES(zend_register_resource(texture, le_sdl_texture));
	}
}

PHP_FUNCTION(SDL_CreateTexture)
{
	zval *z_renderer;
	zend_long format, access, w, h;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zllll", &z_renderer, &format, &access, &w, &h ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	if( renderer ) {
		texture = SDL_CreateTexture(renderer, format, access, w, h);
		RETURN_RES(zend_register_resource(texture, le_sdl_texture));
	}
}

PHP_FUNCTION(SDL_SetRenderTarget)
{
	zval *z_renderer, *z_texture;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz", &z_renderer, &z_texture ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if( renderer && texture ) {
		RETURN_LONG(SDL_SetRenderTarget(renderer, texture));
	}
}

PHP_FUNCTION(SDL_CreateRenderer)
{
	zend_long index, flags;
	zval *z_window;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "Oll", &z_window, get_php_sdl_window_ce(), &index, &flags) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	if( z_window != NULL ) {
		window = zval_to_sdl_window(z_window);
	}

	renderer = SDL_CreateRenderer(window, (int)index, (Uint32)flags);
	RETURN_RES(zend_register_resource(renderer, le_sdl_renderer));
}

PHP_FUNCTION(SDL_RenderCopy)
{
	zval *z_renderer, *z_texture;
	zval *z_srcrect, *z_dstrect;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect *srcrect = NULL, *dstrect = NULL;
	SDL_Rect def_srcrect, def_dstrect;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zzO!O!", &z_renderer, &z_texture, &z_srcrect, get_php_sdl_rect_ce(), &z_dstrect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if(z_srcrect != NULL && Z_TYPE_P(z_srcrect) != IS_NULL) {
		srcrect = &def_srcrect;
		zval_to_sdl_rect(z_srcrect, srcrect);
	}
	if(z_dstrect != NULL && Z_TYPE_P(z_dstrect) != IS_NULL) {
		dstrect = &def_dstrect;
		zval_to_sdl_rect(z_dstrect, dstrect);
	}

	RETURN_LONG(SDL_RenderCopy(renderer, texture, srcrect, dstrect));
}

PHP_FUNCTION(SDL_RenderCopyEx)
{
	zval *z_renderer, *z_texture;
	zval *z_srcrect, *z_dstrect;
	zval *z_center;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect *srcrect = NULL, *dstrect = NULL;
	SDL_Rect def_srcrect, def_dstrect;
	double angle;
	SDL_Point *center = NULL;
	SDL_Point def_center;
	zend_long flip;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zzO!O!dO!l", &z_renderer, &z_texture, &z_srcrect, get_php_sdl_rect_ce(), &z_dstrect, get_php_sdl_rect_ce(), &angle, &z_center, get_php_sdl_point_ce(), &flip) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if(z_srcrect != NULL && Z_TYPE_P(z_srcrect) != IS_NULL) {
		srcrect = &def_srcrect;
		zval_to_sdl_rect(z_srcrect, srcrect);
	}
	if(z_dstrect != NULL && Z_TYPE_P(z_dstrect) != IS_NULL) {
		dstrect = &def_dstrect;
		zval_to_sdl_rect(z_dstrect, dstrect);
	}
	if(z_center != NULL && Z_TYPE_P(z_center) != IS_NULL) {
		center = &def_center;
		zval_to_sdl_point(z_center, center);
	}

	RETURN_LONG(SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, (Uint32)flip));
}

PHP_FUNCTION(SDL_GetRendererOutputSize)
{
	zval *z_renderer, *z_width=NULL, *z_height=NULL;
	SDL_Renderer *renderer;
	int w, h;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz/z/", &z_renderer, &z_width, &z_height) == FAILURE ) {
		return;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_GetRendererOutputSize(renderer, &w, &h);

	zval_dtor(z_width);
	ZVAL_LONG(z_width, w);
	zval_dtor(z_height);
	ZVAL_LONG(z_height, h);
}

PHP_FUNCTION(SDL_QueryTexture)
{
	zval *z_texture, *z_format, *z_access, *z_width, *z_height;
	SDL_Texture *texture;
	int w, h, access, result;
	Uint32 format;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz/z/z/z/", &z_texture, &z_format, &z_access, &z_width, &z_height) == FAILURE ) {
		return;
	}

	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	result = SDL_QueryTexture(texture, &format, &access, &w, &h);

	zval_dtor(z_format);
	ZVAL_LONG(z_format, format);
	zval_dtor(z_access);
	ZVAL_LONG(z_access, access);
	zval_dtor(z_width);
	ZVAL_LONG(z_width, (long)w);
	zval_dtor(z_height);
	ZVAL_LONG(z_height, (long)h);

	RETURN_LONG(result);
}

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_render)
{
	REGISTER_LONG_CONSTANT("SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_FLIP_NONE", SDL_FLIP_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLIP_VERTICAL", SDL_FLIP_VERTICAL, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_STATIC", SDL_TEXTUREACCESS_STATIC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET, CONST_CS | CONST_PERSISTENT);

	le_sdl_renderer = zend_register_list_destructors_ex(NULL, NULL, SDL_RENDERER_RES_NAME, module_number);
	le_sdl_texture = zend_register_list_destructors_ex(NULL, NULL, SDL_TEXTURE_RES_NAME, module_number);

	return SUCCESS;
}
/* }}} */
