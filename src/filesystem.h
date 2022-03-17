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


#ifndef PHP_SDL_FILESYSTEM_H
#define PHP_SDL_FILESYSTEM_H

#ifdef  __cplusplus
extern "C" {
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetPrefPath, 0, 0, 2)
       ZEND_ARG_INFO(0, org)
       ZEND_ARG_INFO(0, app)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetBasePath, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetPrefPath);
PHP_FUNCTION(SDL_GetBasePath);

PHP_MINIT_FUNCTION(sdl_filesystem);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_FILESYSTEM_H */

