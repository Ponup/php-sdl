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


#ifndef PHP_SDL_VIDEO_H
#define PHP_SDL_VIDEO_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

zend_class_entry *get_php_sdl_displaymode_ce(void);
zend_bool sdl_displaymode_to_zval(SDL_DisplayMode *display, zval *value);
zend_bool zval_to_sdl_displaymode(zval *value, SDL_DisplayMode *display);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVideoDriver, 0, 0, 1)
       ZEND_ARG_INFO(0, driverIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_VideoInit, 0, 0, 0)
       ZEND_ARG_INFO(0, drivername)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetDisplayBounds, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_INFO(1, rect)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_INFO(0, modeIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetClosestDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_OBJ_INFO(0, desired, SDL_DisplayMode, 0)
       ZEND_ARG_INFO(1, closest)
ZEND_END_ARG_INFO()

/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_video_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_dysplayindex, 0, 0, 1)
       ZEND_ARG_INFO(0, displayIndex)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetNumVideoDrivers);
PHP_FUNCTION(SDL_GetVideoDriver);
PHP_FUNCTION(SDL_VideoInit);
PHP_FUNCTION(SDL_VideoQuit);
PHP_FUNCTION(SDL_GetCurrentVideoDriver);
PHP_FUNCTION(SDL_GetNumVideoDisplays);
PHP_FUNCTION(SDL_GetDisplayName);
PHP_FUNCTION(SDL_GetDisplayBounds);
PHP_FUNCTION(SDL_GetNumDisplayModes);
PHP_FUNCTION(SDL_GetDisplayMode);
PHP_FUNCTION(SDL_GetDesktopDisplayMode);
PHP_FUNCTION(SDL_GetCurrentDisplayMode);
PHP_FUNCTION(SDL_GetClosestDisplayMode);
PHP_FUNCTION(SDL_IsScreenSaverEnabled);
PHP_FUNCTION(SDL_EnableScreenSaver);
PHP_FUNCTION(SDL_DisableScreenSaver);

PHP_MINIT_FUNCTION(sdl_video);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_VIDEO_H */

