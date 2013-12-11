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

/* $Id$ */ 

/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_error.h                                         |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "error.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetError, 0, 0, 1)
       ZEND_ARG_INFO(0, error_message)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_SetError(string error)

 * SDL_SetError() unconditionally returns -1.
 extern DECLSPEC int SDLCALL SDL_SetError(const char *fmt, ...);
*/
PHP_FUNCTION(SDL_SetError) {
	char *error;
	int  *error_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &error, &error_len) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_SetError(error));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_error_none, 0, 0, 0)
ZEND_END_ARG_INFO()

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
		RETURN_STRING(error, 1);
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


/* {{{ sdl_error_functions[] */
zend_function_entry sdl_error_functions[] = {
	ZEND_FE(SDL_SetError,     arginfo_SDL_SetError)
	ZEND_FE(SDL_GetError,     arginfo_error_none)
	ZEND_FE(SDL_ClearError,   arginfo_error_none)
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_error)
{
	return (zend_register_functions(NULL, sdl_error_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

