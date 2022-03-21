/*
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

zend_class_entry *get_php_sdl_point_ce(void);
zend_bool sdl_point_to_zval(SDL_Point *pt, zval *value);
zend_bool zval_to_sdl_point(zval *value, SDL_Point *pt);

zend_class_entry *get_php_sdl_rect_ce(void);
zend_bool sdl_rect_to_zval(SDL_Rect *rect, zval *value);
zend_bool zval_to_sdl_rect(zval *value, SDL_Rect *rect);

zend_class_entry *get_php_sdl_frect_ce(void);
zend_bool zval_to_sdl_frect(zval *value, SDL_FRect *rect);

zend_class_entry *get_php_sdl_fpoint_ce(void);
zend_bool zval_to_sdl_fpoint(zval *value, SDL_FPoint *rect);

PHP_MINIT_FUNCTION(sdl_rect);
PHP_MSHUTDOWN_FUNCTION(sdl_rect);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_RECT_H */

