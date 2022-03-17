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


#include "error.h"

/* {{{ proto int SDL_SetError(string error)

 * SDL_SetError() unconditionally returns -1.
 extern DECLSPEC int SDLCALL SDL_SetError(const char *fmt, ...);
*/
PHP_FUNCTION(SDL_SetError) {
	char *error;
	size_t error_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &error, &error_len) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_SetError("%s", error));
}
/* }}} */

/* {{{ proto string SDL_GetError(void)

 extern DECLSPEC const char *SDLCALL SDL_GetError(void);
*/
PHP_FUNCTION(SDL_GetError) {
	const char *error;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	error = SDL_GetError();
	if (error) {
		RETURN_STRING(error);
	}
}
/* }}} */


/* {{{ proto string SDL_ClearError(void)

 extern DECLSPEC void SDLCALL SDL_ClearError(void);
*/
PHP_FUNCTION(SDL_ClearError) {

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	SDL_ClearError();
}
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_error)
{
	return SUCCESS;
}
/* }}} */
