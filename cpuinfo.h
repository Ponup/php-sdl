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

#ifndef PHP_SDL2_CPUINFO_H
#define PHP_SDL2_CPUINFO_H

#ifdef  __cplusplus
extern "C" {
#endif

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

PHP_MINIT_FUNCTION(sdl2_cpuinfo);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL2_CPUINFO_H */

