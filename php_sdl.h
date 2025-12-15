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

#ifndef PHP_PHPSDL_H
#define PHP_PHPSDL_H

#define ARG_PASS_BY_REF 1
#define ARG_NOT_PASS_BY_REF 0

#define ARG_ALLOW_NULL 1
#define ARG_NOT_ALLOW_NULL 0

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_exceptions.h>

#define PHP_SDL_VERSION "2.7.0"

#if defined(__APPLE__) && defined(__MACH__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef __cplusplus
} // extern "C"
#endif
#ifdef __cplusplus
extern "C"
{
#endif

  extern zend_module_entry sdl_module_entry;
#define phpext_sdl_ptr &sdl_module_entry

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

  zend_bool php_sdl_check_overflow(int a, int b, int silent);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_PHPSDL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
