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

#include "php_sdl.h"
#include "timer.h"
#include "window.h"

PHP_FUNCTION(SDL_Delay)
{
  zend_long ms;

  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(ms)
  ZEND_PARSE_PARAMETERS_END();

	SDL_Delay((Uint32)ms);
}

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_timer)
{
  return SUCCESS;
}
/* }}} */
