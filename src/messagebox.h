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


#ifndef PHP_SDL_MESSAGEBOX_H
#define PHP_SDL_MESSAGEBOX_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

zend_class_entry *get_php_sdl_messageboxcolor_ce(void);
zend_bool sdl_messageboxcolor_to_zval(const SDL_MessageBoxColor *color, zval *value);
zend_bool zval_to_sdl_messageboxcolor(zval *value, SDL_MessageBoxColor *color);

zend_class_entry *get_php_sdl_messageboxbuttondata_ce(void);
zend_bool sdl_messageboxbuttondata_to_zval(const SDL_MessageBoxButtonData *data, zval *value);
zend_bool zval_to_sdl_messageboxbuttondata(zval *value, SDL_MessageBoxButtonData *data);

zend_class_entry *get_php_sdl_messageboxdata_ce(void);
zend_bool sdl_messageboxdata_to_zval(SDL_MessageBoxData *data, zval *z_val, Uint32 flags);
SDL_MessageBoxData *zval_to_sdl_messageboxdata(zval *z_val);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowMessageBox, 0, 0, 2)
       ZEND_ARG_INFO(0, messageboxdata)
       ZEND_ARG_INFO(1, buttonid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowSimpleMessageBox, 0, 0, 3)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, message)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_ShowMessageBox);
PHP_FUNCTION(SDL_ShowSimpleMessageBox);

PHP_MINIT_FUNCTION(sdl_messagebox);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_MESSAGEBOX_H */

