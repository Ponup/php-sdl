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
  | Author: Santiago Lizardo <santiagolizardo@php.net>                   |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sdl.h"

#include <SDL.h>

#define GET_JOYSTICK_RESOURCE(joystick)	ZEND_FETCH_RESOURCE(joystick, SDL_Joystick *, &joystick_arg, -1, le_joystick_name, le_joystick)

/* Resources */
int le_joystick;

void _sdl_joystick(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	SDL_Joystick *joystick = (SDL_Joystick *)rsrc->ptr;
	if (joystick) {
		SDL_JoystickClose(joystick);
	}
}

/* {{{ proto int SDL_NumJoysticks(void);
   Count the number of joysticks attached to the system. */
PHP_FUNCTION(sdl_numjoysticks)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG(SDL_NumJoysticks());
}
/* }}} */

/* {{{ proto string SDL_JoystickName(int device_index)
   Get the implementation dependent name of a joystick.
   This can be called before any joysticks are opened.
   If no name can be found, this function returns FALSE. */
PHP_FUNCTION(sdl_joystickname)
{
	long device_index;
	char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &device_index) == FAILURE)
		return;

	if (NULL == (name = (char *)SDL_JoystickName(device_index))) {
		RETURN_FALSE;
	}
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto resource SDL_JoystickOpen(int device_index)
   Open a joystick for use - the index passed as an argument refers to the N'th joystick on the system.
   This index is the value which will identify this joystick in future joystick events.
   This function returns a joystick resource, or FALSE if an error occurred. */
PHP_FUNCTION(sdl_joystickopen)
{
	long device_index;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &device_index) == FAILURE)
		return;

	if (NULL == (joystick = SDL_JoystickOpen(device_index))) {
			php_error(E_WARNING, "%s() could not open joystick %ld: %s",
					  get_active_function_name(TSRMLS_C), device_index, SDL_GetError());
		
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, joystick, le_joystick);
}
/* }}} */

/* {{{ proto int SDL_JoystickOpened(int device_index)
   Returns TRUE if the joystick has been opened, or FALSE if it has not. */
PHP_FUNCTION(sdl_joystickopened)
{
	long device_index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &device_index) == FAILURE)
		return;

	RETURN_BOOL(SDL_JoystickOpened(device_index));
}
/* }}} */

/* {{{ proto int SDL_JoystickIndex(resource joystick)
   Get the device index of an opened joystick. */
PHP_FUNCTION(sdl_joystickindex)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);

	RETURN_LONG(SDL_JoystickIndex(joystick));
}
/* }}} */

/* {{{ proto int SDL_JoystickNumAxes(resource joystick)
   Get the number of general axis controls on a joystick. */
PHP_FUNCTION(sdl_joysticknumaxes)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickNumAxes(joystick));
}
/* }}} */

/* {{{ proto int SDL_JoystickNumBalls(resource joystick)
   Get the number of trackballs on a joystick.
   Joystick trackballs have only relative motion events associated with them and their state cannot be polled. */
PHP_FUNCTION(sdl_joysticknumballs)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickNumBalls(joystick));
}
/* }}} */

/* {{{ proto int SDL_JoystickNumHats(resource joystick)
   Get the number of POV hats on a joystick. */
PHP_FUNCTION(sdl_joysticknumhats)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickNumHats(joystick));
}
/* }}} */

/* {{{ proto int SDL_JoystickNumButtons(resource joystick)
   Get the number of buttons on a joystick. */
PHP_FUNCTION(sdl_joysticknumbuttons)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickNumButtons(joystick));
}
/* }}} */

/* {{{ proto void SDL_JoystickUpdate(void)
   Update the current state of the open joysticks.
   This is called automatically by the event loop if any joystick events are enabled. */
PHP_FUNCTION(sdl_joystickupdate)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_JoystickUpdate();
}
/* }}} */

/* {{{ proto int SDL_JoystickEventState(int state)
   Enable/disable joystick event polling.
   If joystick events are disabled, you must call SDL_JoystickUpdate() yourself and check the state of the joystick when you want joystick information.
   The state can be one of SDL_QUERY, SDL_ENABLE or SDL_IGNORE.  */
PHP_FUNCTION(sdl_joystickeventstate)
{
	long state;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &state) == FAILURE)
		return;

	RETURN_LONG(SDL_JoystickEventState(state));
}
/* }}} */

/* {{{ proto int SDL_JoystickGetAxis(resource joystick, int axis)
   Get the current state of an axis control on a joystick
   The state is a value ranging from -32768 to 32767.
   The axis indices start at index 0.  */
PHP_FUNCTION(sdl_joystickgetaxis)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;
	long axis;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &joystick_arg, &axis) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickGetAxis(joystick, axis));
}
/* }}} */

/* {{{ proto int SDL_JoystickGetHat(resource joystick, int hat
   Get the current state of a POV hat on a joystick.
   The return value is one of the following positions:
	 SDL_HAT_CENTERED	0x00
	 SDL_HAT_UP			0x01
	 SDL_HAT_RIGHT		0x02
	 SDL_HAT_DOWN		0x04
	 SDL_HAT_LEFT		0x08
	 SDL_HAT_RIGHTUP	(SDL_HAT_RIGHT|SDL_HAT_UP)
	 SDL_HAT_RIGHTDOWN	(SDL_HAT_RIGHT|SDL_HAT_DOWN)
	 SDL_HAT_LEFTUP		(SDL_HAT_LEFT|SDL_HAT_UP)
	 SDL_HAT_LEFTDOWN	(SDL_HAT_LEFT|SDL_HAT_DOWN)
   The hat indices start at index 0.  */
PHP_FUNCTION(sdl_joystickgethat)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;
	long hat;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &joystick_arg, &hat) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_LONG(SDL_JoystickGetHat(joystick, hat));
}
/* }}} */

/* {{{ proto array SDL_JoystickGetBall(resource joystick, int ball)
   Get the ball axis change since the last poll
   This returns 0, or -1 if you passed it invalid parameters.
   The ball indices start at index 0. */
PHP_FUNCTION(sdl_joystickgetball)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;
	long ball;
	int dx, dy;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &joystick_arg, &ball) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	if (-1 == SDL_JoystickGetBall(joystick, ball, &dx, &dy)) {
		RETURN_FALSE;
	} else {
		array_init(return_value);
		add_next_index_long(return_value, dx);
		add_next_index_long(return_value, dy);
	}
}
/* }}} */

/* {{{ proto bool SDL_JoystickGetButton(resource joystick, int button)
   Get the current state of a button on a joystick
   The button indices start at index 0.  */
PHP_FUNCTION(sdl_joystickgetbutton)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;
	long button;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &joystick_arg, &button) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	RETURN_BOOL(SDL_JoystickGetButton(joystick, button));
}
/* }}} */

/* {{{ proto void SDL_JoystickClose(resource joystick)
   Close a joystick previously opened with SDL_JoystickOpen(). */
PHP_FUNCTION(sdl_joystickclose)
{
	zval *joystick_arg;
	SDL_Joystick *joystick;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &joystick_arg) == FAILURE)
		return;

	GET_JOYSTICK_RESOURCE(joystick);
	
	zend_list_delete(Z_RESVAL_P(joystick_arg));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
