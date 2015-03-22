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

#include "php_sdl.h"
#include "timer.h"
#include "window.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Delay, 0, 0, 1)
       ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_Delay)
{
	long ms;

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ms) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	SDL_Delay((Uint32)ms);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ sdl_timer_functions[] */
zend_function_entry sdl_timer_functions[] = {
	ZEND_FE(SDL_Delay, arginfo_SDL_Delay)
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_timer)
{
	return (zend_register_functions(NULL, sdl_timer_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */
