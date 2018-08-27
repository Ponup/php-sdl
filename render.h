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

#ifndef PHP_SDL_RENDER_H
#define PHP_SDL_RENDER_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderDrawColor, 0, 0, 5)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderClear, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyRenderer, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyTexture, 0, 0, 1)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderFillRect, 0, 0, 2)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
	//ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPresent, 0, 0, 1)
	//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderDrawPoint, 0, 0, 3)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTextureFromSurface, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)//ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateRenderer, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderCopy, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_SetRenderDrawColor);
PHP_FUNCTION(SDL_RenderClear);
PHP_FUNCTION(SDL_DestroyRenderer);
PHP_FUNCTION(SDL_DestroyTexture);
PHP_FUNCTION(SDL_RenderFillRect);
PHP_FUNCTION(SDL_RenderPresent);
PHP_FUNCTION(SDL_RenderDrawPoint);
PHP_FUNCTION(SDL_CreateTextureFromSurface);
PHP_FUNCTION(SDL_CreateRenderer);
PHP_FUNCTION(SDL_RenderCopy);

PHP_MINIT_FUNCTION(sdl_render);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_RENDER_H */

