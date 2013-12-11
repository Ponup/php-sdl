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
  | wrapper for SDL2/SDL_power.h                                         |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "power.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetPowerInfo, 0, 0, 0)
	ZEND_ARG_INFO(1, secs)
	ZEND_ARG_INFO(1, pct)
ZEND_END_ARG_INFO()

/**
 *  \brief Get the current power supply details.
 *
 *  \param secs Seconds of battery life left. You can pass a NULL here if
 *              you don't care. Will return -1 if we can't determine a
 *              value, or we're not running on a battery.
 *
 *  \param pct Percentage of battery life left, between 0 and 100. You can
 *             pass a NULL here if you don't care. Will return -1 if we
 *             can't determine a value, or we're not running on a battery.
 *
 *  \return The state of the battery (if any).
 */
PHP_FUNCTION(SDL_GetPowerInfo)
{
	int secs, pct;
	SDL_PowerState power_state;
	zval *z_secs = NULL, *z_pct = NULL;
	zend_bool has_secs, has_pct;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|zz", &z_secs, &z_pct) == FAILURE) {
		RETURN_FALSE;
	}

	has_secs = ( NULL == z_secs ? 0 : 1 );
	has_pct = ( NULL == z_pct ? 0 : 1 );

	power_state = SDL_GetPowerInfo(has_secs ? &secs : NULL, has_pct ? &pct : NULL);

	if (has_secs) {
		zval_dtor(z_secs);
		ZVAL_LONG(z_secs, (long)secs);
	}
	if (has_pct) {
		zval_dtor(z_pct);
		ZVAL_LONG(z_pct, (long)pct);
	}

	RETURN_LONG(power_state);
}


/* {{{ sdl_power_functions[] */
zend_function_entry sdl_power_functions[] = {
	ZEND_FE(SDL_GetPowerInfo,	arginfo_SDL_GetPowerInfo)
	ZEND_FE_END
};
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_power)
{
	REGISTER_LONG_CONSTANT("SDL_POWERSTATE_UNKNOWN",	SDL_POWERSTATE_UNKNOWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_POWERSTATE_ON_BATTERY",	SDL_POWERSTATE_ON_BATTERY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_POWERSTATE_NO_BATTERY",	SDL_POWERSTATE_NO_BATTERY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_POWERSTATE_CHARGING",	SDL_POWERSTATE_CHARGING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_POWERSTATE_CHARGED",	SDL_POWERSTATE_CHARGED, CONST_CS | CONST_PERSISTENT);

	return (zend_register_functions(NULL, sdl_power_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

