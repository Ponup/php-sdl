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

/* $ Id: $ */ 

#ifndef PHP_SDL_H
#define PHP_SDL_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_exceptions.h>

#define PHP_SDL_VERSION "2.0.0-dev"

#include <SDL.h>

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry sdl_module_entry;

#ifdef PHP_WIN32
#define PHP_SDL_API __declspec(dllexport)
#else
#define PHP_SDL_API
#endif

PHP_MINIT_FUNCTION(sdl);
PHP_MSHUTDOWN_FUNCTION(sdl);
PHP_RINIT_FUNCTION(sdl);
PHP_RSHUTDOWN_FUNCTION(sdl);
PHP_MINFO_FUNCTION(sdl);

#ifdef ZTS
#include "TSRM.h"
#endif

/* ZEND_FE_END exists only in PHP >= 5.3.7 */
#ifndef ZEND_FE_END
#define ZEND_FE_END { NULL, NULL, NULL, 0, 0 }
#endif

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
