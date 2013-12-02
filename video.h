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

#ifndef PHP_SDL2_VIDEO_H
#define PHP_SDL2_VIDEO_H

#ifdef  __cplusplus
extern "C" {
#endif

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

PHP_FUNCTION(SDL_CreateWindow);
PHP_FUNCTION(SDL_DestroyWindow);
PHP_FUNCTION(SDL_UpdateWindowSurface);
PHP_FUNCTION(SDL_GetWindowTitle);
PHP_FUNCTION(SDL_SetWindowTitle);

PHP_MINIT_FUNCTION(sdl2_video);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL2_VIDEO_H */

