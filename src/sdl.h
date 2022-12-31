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


#ifndef PHP_SDL_H
#define PHP_SDL_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Init, 0, 0, 0)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_Init);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_InitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_InitSubSystem);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_QuitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_QuitSubSystem);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WasInit, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_WasInit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Quit, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_Quit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetHint, 0, 0, 2)
       ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
       ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_SetHint);


PHP_MINIT_FUNCTION(sdl_sdl);

#ifdef  __cplusplus
} // extern "C" 
#endif


#endif /* PHP_SDL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
