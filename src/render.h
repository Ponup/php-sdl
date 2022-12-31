/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2022 The PHP Group                                |
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
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderClear, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyRenderer, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyTexture, 0, 0, 1)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderFillRect, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderDrawRect, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderDrawLine, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPresent, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderDrawPoint, 0, 0, 3)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTextureFromSurface, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTexture, 0, 0, 5)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, access)
	ZEND_ARG_INFO(0, w)
	ZEND_ARG_INFO(0, h)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_UpdateTexture, 0, 0, 4)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 1)
    ZEND_ARG_OBJ_INFO(0, pixels, SDL_Pixels, 0)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_QueryTexture, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(1, format, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, access, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, w, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, h, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderTarget, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateRenderer, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateSoftwareRenderer, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderCopy, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderCopyEx, 0, 0, 7)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
	ZEND_ARG_INFO(0, angle)
	ZEND_ARG_OBJ_INFO(0, center, SDL_Point, 1)
	ZEND_ARG_INFO(0, flip)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderSetLogicalSize, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetRendererOutputSize, 0, 0, 3)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(1, w)
	ZEND_ARG_INFO(1, h)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderDrawPointF, 0, 3, IS_LONG, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderDrawLineF, 0, 5, IS_LONG, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderDrawRectF, 0, 2, IS_LONG, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_FRect, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_RenderFillRectF arginfo_SDL_RenderDrawRectF

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderCopyF, 0, 4, IS_LONG, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_FRect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RenderCopyExF, 0, 7, IS_LONG, 0)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, srcrect, SDL_Rect, 1, "null")
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_FRect, 1)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, angle, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, center, SDL_FPoint, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flip, IS_LONG, 0, "SDL_FLIP_NONE")
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_SetRenderDrawColor);
PHP_FUNCTION(SDL_RenderClear);
PHP_FUNCTION(SDL_DestroyRenderer);
PHP_FUNCTION(SDL_DestroyTexture);
PHP_FUNCTION(SDL_RenderFillRect);
PHP_FUNCTION(SDL_RenderDrawRect);
PHP_FUNCTION(SDL_RenderDrawLine);
PHP_FUNCTION(SDL_RenderPresent);
PHP_FUNCTION(SDL_RenderDrawPoint);
PHP_FUNCTION(SDL_CreateTextureFromSurface);
PHP_FUNCTION(SDL_CreateTexture);
PHP_FUNCTION(SDL_UpdateTexture);
PHP_FUNCTION(SDL_QueryTexture);
PHP_FUNCTION(SDL_SetRenderTarget);
PHP_FUNCTION(SDL_CreateRenderer);
PHP_FUNCTION(SDL_CreateSoftwareRenderer);
PHP_FUNCTION(SDL_RenderCopy);
PHP_FUNCTION(SDL_RenderCopyEx);
PHP_FUNCTION(SDL_RenderSetLogicalSize);
PHP_FUNCTION(SDL_GetRendererOutputSize);
ZEND_FUNCTION(SDL_RenderDrawPointF);
ZEND_FUNCTION(SDL_RenderDrawLineF);
ZEND_FUNCTION(SDL_RenderDrawRectF);
ZEND_FUNCTION(SDL_RenderFillRectF);
ZEND_FUNCTION(SDL_RenderCopyF);
ZEND_FUNCTION(SDL_RenderCopyExF);

PHP_MINIT_FUNCTION(sdl_render);

#ifdef  __cplusplus
} // extern "C"
#endif

#endif /* PHP_SDL_RENDER_H */

