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


#ifndef PHP_SDL_RECT_H
#define PHP_SDL_RECT_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

zend_class_entry *php_sdl_rect_ce;

zend_class_entry *get_php_sdl_point_ce(void);
zend_bool sdl_point_to_zval(SDL_Point *pt, zval *value);
zend_bool zval_to_sdl_point(zval *value, SDL_Point *pt);

zend_class_entry *get_php_sdl_rect_ce(void);
zend_bool sdl_rect_to_zval(SDL_Rect *rect, zval *value);
zend_bool zval_to_sdl_rect(zval *value, SDL_Rect *rect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect__construct, /*unused*/0, /*ret ref*/0, /*req num args*/0)
       ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
       ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
       ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
       ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Point__construct, 0, 0, 2)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect2, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, rectA, SDL_Rect, 0)
       ZEND_ARG_OBJ_INFO(0, rectB, SDL_Rect, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect3, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, rectA, SDL_Rect, 0)
       ZEND_ARG_OBJ_INFO(0, rectB, SDL_Rect, 0)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_IntersectRect, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, rectA, SDL_Rect, 0)
       ZEND_ARG_OBJ_INFO(0, rectB, SDL_Rect, 0)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect_Result, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_EnclosePoints, 0, 0, 4)
       ZEND_ARG_ARRAY_INFO(0, point, 0)
       ZEND_ARG_INFO(0, count)
       ZEND_ARG_OBJ_INFO(0, clip, SDL_Rect, 0)
       ZEND_ARG_INFO(1, rect)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_IntersectRectAndLine, 0, 0, 5)
       ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
       ZEND_ARG_INFO(1, X1)
       ZEND_ARG_INFO(1, Y1)
       ZEND_ARG_INFO(1, X2)
       ZEND_ARG_INFO(1, Y2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect_IntersectLine, 0, 0, 4)
       ZEND_ARG_INFO(1, X1)
       ZEND_ARG_INFO(1, Y1)
       ZEND_ARG_INFO(1, X2)
       ZEND_ARG_INFO(1, Y2)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_RectEmpty);
PHP_FUNCTION(SDL_RectEquals);
PHP_FUNCTION(SDL_HasIntersection);
PHP_FUNCTION(SDL_IntersectRect);
PHP_FUNCTION(SDL_UnionRect);
PHP_FUNCTION(SDL_EnclosePoints);
PHP_FUNCTION(SDL_IntersectRectAndLine);

PHP_MINIT_FUNCTION(sdl_rect);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_RECT_H */

