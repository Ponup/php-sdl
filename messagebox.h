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

/* $Id$ */ 

#ifndef PHP_SDL_MESSAGEBOX_H
#define PHP_SDL_MESSAGEBOX_H

#ifdef  __cplusplus
extern "C" {
#endif

zend_class_entry *get_php_sdl_messageboxcolor_ce(void);
zend_bool sdl_messageboxcolor_to_zval(const SDL_MessageBoxColor *color, zval *value TSRMLS_DC);
zend_bool zval_to_sdl_messageboxcolor(zval *value, SDL_MessageBoxColor *color TSRMLS_DC);

zend_class_entry *get_php_sdl_messageboxbuttondata_ce(void);
zend_bool sdl_messageboxbuttondata_to_zval(const SDL_MessageBoxButtonData *data, zval *value TSRMLS_DC);
zend_bool zval_to_sdl_messageboxbuttondata(zval *value, SDL_MessageBoxButtonData *data TSRMLS_DC);

zend_class_entry *get_php_sdl_messageboxdata_ce(void);
zend_bool sdl_messageboxdata_to_zval(SDL_MessageBoxData *data, zval *z_val, Uint32 flags TSRMLS_DC);
SDL_MessageBoxData *zval_to_sdl_messageboxdata(zval *z_val TSRMLS_DC);

PHP_MINIT_FUNCTION(sdl_messagebox);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_MESSAGEBOX_H */

