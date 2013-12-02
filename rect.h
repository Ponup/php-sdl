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
  | Authors: Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#ifndef PHP_SDL2_RECT_H
#define PHP_SDL2_RECT_H

#ifdef  __cplusplus
extern "C" {
#endif

void sdl_rect_to_zval(SDL_Rect *rect, zval *value TSRMLS_DC);
void zval_to_sdl_rect(zval *value, SDL_Rect *rect TSRMLS_DC);

PHP_FUNCTION(SDL_RectEmpty);
PHP_FUNCTION(SDL_RectEquals);
PHP_FUNCTION(SDL_HasIntersection);
PHP_FUNCTION(SDL_IntersectRect);
PHP_FUNCTION(SDL_UnionRect);

PHP_MINIT_FUNCTION(sdl2_rect);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL2_RECT_H */

