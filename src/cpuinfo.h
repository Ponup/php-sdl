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


#ifndef PHP_SDL_CPUINFO_H
#define PHP_SDL_CPUINFO_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

PHP_FUNCTION(SDL_GetCPUCount);
PHP_FUNCTION(SDL_GetCPUCacheLineSize);
PHP_FUNCTION(SDL_HasRDTSC);
PHP_FUNCTION(SDL_HasAltiVec);
PHP_FUNCTION(SDL_HasMMX);
PHP_FUNCTION(SDL_Has3DNow);
PHP_FUNCTION(SDL_HasSSE);
PHP_FUNCTION(SDL_HasSSE2);
PHP_FUNCTION(SDL_HasSSE3);
PHP_FUNCTION(SDL_HasSSE41);
PHP_FUNCTION(SDL_HasSSE42);
PHP_FUNCTION(SDL_GetSystemRAM);

/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_cpuinfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_MINIT_FUNCTION(sdl_cpuinfo);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_CPUINFO_H */

