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


#ifndef PHP_SDL_VERSION_H
#define PHP_SDL_VERSION_H

#ifdef  __cplusplus
extern "C" {
#endif

zend_bool convert_sdl_version_to_php_array(SDL_version *version, zval *version_array);

ZEND_BEGIN_ARG_INFO_EX(arginfo_sdl_version_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVersion, 0, 0, 1)
	ZEND_ARG_INFO(1, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_VERSION, 0, 0, 1)
	ZEND_ARG_INFO(1, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_VERSIONNUM, 0, 0, 3)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, z)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_VERSION_ATLEAST, 0, 0, 3)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, z)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetRevision);
#ifdef HAVE_SDL_GETREVISIONNUMBER
PHP_FUNCTION(SDL_GetRevisionNumber);
#endif
PHP_FUNCTION(SDL_GetVersion);
PHP_FUNCTION(SDL_VERSION);
PHP_FUNCTION(SDL_VERSIONNUM);
PHP_FUNCTION(SDL_VERSION_ATLEAST);

PHP_MINIT_FUNCTION(sdl_version);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_VERSION_H */

