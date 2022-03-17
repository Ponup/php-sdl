/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/


/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_cpuinfo.h                                       |
  +----------------------------------------------------------------------+
*/

#include "cpuinfo.h"


/* {{{ proto void SDL_GetCPUCount(void )

 *  This function returns the number of CPU cores available.
 extern DECLSPEC int SDLCALL SDL_GetCPUCount(void);
*/
PHP_FUNCTION(SDL_GetCPUCount)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetCPUCount());
}
/* }}} */

/* {{{ proto void SDL_GetCPUCount(void )

 *  This function returns the L1 cache line size of the CPU
 *
 *  This is useful for determining multi-threaded structure padding
 *  or SIMD prefetch sizes.
 extern DECLSPEC int SDLCALL SDL_GetCPUCacheLineSize(void);
*/
PHP_FUNCTION(SDL_GetCPUCacheLineSize)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetCPUCacheLineSize());
}
/* }}} */

/* {{{ proto void SDL_HasRDTSC(void )

 *  This function returns true if the CPU has the RDTSC instruction.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasRDTSC(void);
*/
PHP_FUNCTION(SDL_HasRDTSC)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasRDTSC());
}
/* }}} */

/* {{{ proto void SDL_HasAltiVec(void )

 *  This function returns true if the CPU has AltiVec features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasAltiVec(void);
*/
PHP_FUNCTION(SDL_HasAltiVec)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasAltiVec());
}
/* }}} */

/* {{{ proto void SDL_HasMMX(void )

 *  This function returns true if the CPU has MMX features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasMMX(void);
*/
PHP_FUNCTION(SDL_HasMMX)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasMMX());
}
/* }}} */

/* {{{ proto void SDL_Has3DNow(void )

 *  This function returns true if the CPU has 3DNow! features.
 extern DECLSPEC SDL_bool SDLCALL SDL_Has3DNow(void);
*/
PHP_FUNCTION(SDL_Has3DNow)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_Has3DNow());
}
/* }}} */

/* {{{ proto void SDL_HasSSE(void )

 *  This function returns true if the CPU has SSE features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE(void);
*/
PHP_FUNCTION(SDL_HasSSE)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasSSE());
}
/* }}} */


/* {{{ proto void SDL_HasSSE2(void )

 *  This function returns true if the CPU has HasSSE2 features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE2(void);
*/
PHP_FUNCTION(SDL_HasSSE2)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasSSE2());
}
/* }}} */

/* {{{ proto void SDL_HasSSE3(void )

 *  This function returns true if the CPU has SSE3 features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE3(void);
*/
PHP_FUNCTION(SDL_HasSSE3)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasSSE3());
}
/* }}} */


/* {{{ proto void SDL_HasSSE41(void )

 *  This function returns true if the CPU has SSE4.1 features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE41(void);
*/
PHP_FUNCTION(SDL_HasSSE41)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasSSE41());
}
/* }}} */

/* {{{ proto void SDL_HasSSE42(void )

 *  This function returns true if the CPU has SSE4.2 features.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE42(void);
*/
PHP_FUNCTION(SDL_HasSSE42)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_HasSSE42());
}
/* }}} */


#if SDL_COMPILEDVERSION > 2000
/* {{{ proto void SDL_GetSystemRAM(void )

 *  This function returns the amount of RAM configured in the system, in MB.
 extern DECLSPEC int SDLCALL SDL_GetSystemRAM(void);
*/
PHP_FUNCTION(SDL_GetSystemRAM)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetSystemRAM());
}
/* }}} */
#endif

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_cpuinfo)
{
	return SUCCESS;
}
/* }}} */
