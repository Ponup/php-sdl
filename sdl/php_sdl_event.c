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

/* {{{ proto int sdl_button(int x)
 */
PHP_FUNCTION(sdl_button)
{
	long x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &x) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_PRESSED<<( ((Uint8)x) -1));
}
/* }}} */

/*
 * Convert SDL_Event into zval array (hash); make sure that *event_array
 * already IS_ARRAY. */
int php_sdl_event_to_array(SDL_Event *event, zval *event_array TSRMLS_DC)
{
	zval *active;
	zval *key, *keysym;
	zval *motion;
	zval *button;
	zval *jaxis;
	zval *jball;
	zval *jhat;
	zval *jbutton;
	zval *resize;
	zval *quit;
	zval *user;
	zval *syswm;

	add_assoc_long(event_array, "type", event->type);

	switch (event->type) {
		case SDL_ACTIVEEVENT:
			/* SDL_ActiveEvent active */
			MAKE_STD_ZVAL(active);
			array_init(active);
			add_assoc_long(active, "type", event->active.type);
			add_assoc_long(active, "gain", event->active.gain);
			add_assoc_long(active, "state", event->active.state);
			add_assoc_zval(event_array, "active", active);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			/* SDL_KeyboardEvent key */
			MAKE_STD_ZVAL(key);
			array_init(key);
			add_assoc_long(key, "type", event->key.type);
			add_assoc_long(key, "state", event->key.state);
			MAKE_STD_ZVAL(keysym);
			array_init(keysym);
			add_assoc_long(keysym, "scancode", event->key.keysym.scancode);
			add_assoc_long(keysym, "sym", event->key.keysym.sym);
			add_assoc_long(keysym, "mod", event->key.keysym.mod);
			add_assoc_long(keysym, "unicode", event->key.keysym.unicode);
			add_assoc_zval(key, "keysym", keysym);
			add_assoc_zval(event_array, "key", key);
			break;
		case SDL_MOUSEMOTION:
			/* SDL_MouseMotionEvent motion */
			MAKE_STD_ZVAL(motion);
			array_init(motion);
			add_assoc_long(motion, "type", event->motion.type);
			add_assoc_long(motion, "state", event->motion.state);
			add_assoc_long(motion, "x", event->motion.x);
			add_assoc_long(motion, "y", event->motion.y);
			add_assoc_long(motion, "xrel", event->motion.xrel);
			add_assoc_long(motion, "yrel", event->motion.yrel);
			add_assoc_zval(event_array, "motion", motion);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			/* SDL_MouseButtonEvent button */
			MAKE_STD_ZVAL(button);
			array_init(button);
			add_assoc_long(button, "type", event->button.type);
			add_assoc_long(button, "button", event->button.button);
			add_assoc_long(button, "state", event->button.state);
			add_assoc_long(button, "x", event->button.x);
			add_assoc_long(button, "y", event->button.y);
			add_assoc_zval(event_array, "button", button);
			break;
		case SDL_JOYAXISMOTION:
			/* SDL_JoyAxisEvent jaxis */
			MAKE_STD_ZVAL(jaxis);
			array_init(jaxis);
			add_assoc_long(jaxis, "type", event->jaxis.type);
			add_assoc_long(jaxis, "which", event->jaxis.which);
			add_assoc_long(jaxis, "axis", event->jaxis.axis);
			add_assoc_long(jaxis, "value", event->jaxis.value);
			add_assoc_zval(event_array, "jaxis", jaxis);
			break;
		case SDL_JOYBALLMOTION:
			/* SDL_JoyBallEvent jball */
			MAKE_STD_ZVAL(jball);
			array_init(jball);
			add_assoc_long(jball, "type", event->jball.type);
			add_assoc_long(jball, "which", event->jball.which);
			add_assoc_long(jball, "ball", event->jball.ball);
			add_assoc_long(jball, "xrel", event->jball.xrel);
			add_assoc_long(jball, "yrel", event->jball.yrel);
			add_assoc_zval(event_array, "jball", jball);
			break;
		case SDL_JOYHATMOTION:
			/* SDL_JoyHatEvent jhat */
			MAKE_STD_ZVAL(jhat);
			array_init(jhat);
			add_assoc_long(jhat, "type", event->jhat.type);
			add_assoc_long(jhat, "which", event->jhat.which);
			add_assoc_long(jhat, "hat", event->jhat.hat);
			add_assoc_long(jhat, "value", event->jhat.value);
			add_assoc_zval(event_array, "jhat", jhat);
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			/* SDL_JoyButtonEvent jbutton */
			MAKE_STD_ZVAL(jbutton);
			array_init(jbutton);
			add_assoc_long(jbutton, "type", event->jbutton.type);
			add_assoc_long(jbutton, "which", event->jbutton.which);
			add_assoc_long(jbutton, "button", event->jbutton.button);
			add_assoc_long(jbutton, "state", event->jbutton.state);
			add_assoc_zval(event_array, "jbutton", jbutton);
			break;
		case SDL_VIDEORESIZE:
			/* SDL_ResizeEvent resize */
			MAKE_STD_ZVAL(resize);
			array_init(resize);
			add_assoc_long(resize, "type", event->resize.type);
			add_assoc_long(resize, "w", event->resize.w);
			add_assoc_long(resize, "h", event->resize.h);
			add_assoc_zval(event_array, "resize", resize);
			break;
		case SDL_QUIT:
			/* SDL_QuitEvent quit */
			MAKE_STD_ZVAL(quit);
			array_init(quit);
			add_assoc_long(quit, "type", event->quit.type);
			add_assoc_zval(event_array, "quit", quit);
			break;
		case SDL_USEREVENT:
			/* SDL_UserEvent user */
			MAKE_STD_ZVAL(user);
			array_init(user);
			add_assoc_long(user, "code", event->user.code);
			add_assoc_zval(user, "data", event->user.data1);
			add_assoc_zval(event_array, "user", user);
			break;
		case SDL_SYSWMEVENT:
			/* SDL_SywWMEvent syswm */
			MAKE_STD_ZVAL(syswm);
			array_init(syswm);
			add_assoc_zval(event_array, "syswm", syswm);
			break;
		/* Silently ignore the following events as the do not have any further
		 * information. */
		case SDL_VIDEOEXPOSE:
			break;
		default:
			return 0;
	}
	return 1;
}

/* {{{ proto void sdl_pumpevents(void)
 */
PHP_FUNCTION(sdl_pumpevents)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_PumpEvents();
}
/* }}} */

/* {{{ proto int sdl_pollevent(array &event)
 */
PHP_FUNCTION(sdl_pollevent)
{
	int result = 0;
	SDL_Event *event = NULL;
	zval *event_arg = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &event_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (event_arg != NULL)
	{
		event = (SDL_Event*)emalloc(sizeof(SDL_Event));
	}

	result = SDL_PollEvent( event );

	if (event != NULL) {
		if (Z_TYPE_P( event_arg ) != IS_ARRAY) {
			convert_to_array(event_arg);
		}
		int success = php_sdl_event_to_array(event, event_arg TSRMLS_CC);
		efree( event ); event = NULL;
		if( !success ) {
			RETURN_FALSE; /* TODO: Log the error. */
		}
	}

	RETURN_BOOL( result );
}
/* }}} */

/* {{{ proto int sdl_waitevent(array &event)
 */
PHP_FUNCTION(sdl_waitevent)
{
	int result = 0;
	SDL_Event *event = NULL;
	zval *event_arg = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &event_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (event_arg != NULL)
	{
		event = (SDL_Event*)emalloc(sizeof(SDL_Event));
	}

	result = SDL_WaitEvent( event );

	if (event != NULL) {
		if (Z_TYPE_P( event_arg ) != IS_ARRAY) {
			convert_to_array(event_arg);
		}
		int success = php_sdl_event_to_array(event, event_arg TSRMLS_CC);
		efree( event ); event = NULL;
		if( !success ) {
			RETURN_FALSE; /* TODO: Log the error */
		}
	}

	RETURN_BOOL( result );
}
/* }}} */

/* {{{ proto int sdl_pushevent(array event)
 */
PHP_FUNCTION(sdl_pushevent)
{
	SDL_Event event;
	zval *event_arg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &event_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (!php_sdl_php_array_to_sdl_event(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, &event_arg, &event)) {
		RETURN_FALSE;
	}

	RETURN_BOOL(!SDL_PushEvent(&event));
}
/* }}} */

/* {{{ proto int sdl_peepevents(array &events, int numevents, int action, int mask)
 */
PHP_FUNCTION(sdl_peepevents)
{
	zval *events_arg;
	long numevents, action, result;
	long mask;
	SDL_Event *events = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "alll", &events_arg, &numevents, &action, &mask) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	switch (action) {
		case SDL_ADDEVENT:
			if (numevents < 1) {
				php_error(E_WARNING, "%s() parameter numevents must be greater than 0 when action specified is SDL_ADDEVENT",
					  get_active_function_name(TSRMLS_C));
				RETURN_FALSE;
			}
			{
				zval **tmp;
				/* If we have SDL_ADDEVENT then we expect the first argument to be
				 * an array. Either a single array which specifies exactly one
				 * event or a neested array which specifies a number of events. */
				if (zend_hash_index_find(Z_ARRVAL_P(events_arg), 0, (void**)&tmp) == FAILURE) {
					php_error(E_WARNING, "%s() parameter 1 cannot be an empty array when used with SDL_ADDEVENT",
							  get_active_function_name(TSRMLS_C));
					RETURN_FALSE;
				}
				if (Z_TYPE_PP(tmp) == IS_LONG) {
					/* Now we know we have a single event; this als means
					 * numevents has to be 1.*/
					if (numevents != 1) {
						php_error(E_WARNING, "%s() SDL_ADDEVENT called with one event but numevents is %lu",
								  get_active_function_name(TSRMLS_C), numevents);
						RETURN_FALSE;
					}
					events = (SDL_Event *)emalloc(numevents*sizeof(SDL_Event));
					if (!php_sdl_php_array_to_sdl_event(INTERNAL_FUNCTION_PARAM_PASSTHRU, -1, &events_arg, &(events[0]))) {
						efree(events);
						RETURN_FALSE;
					}
				} else if (Z_TYPE_PP(tmp) == IS_ARRAY) {
					int i;
					/* Here we assume that we have an array of events (neested
					 * array). Now verify that the number of events matches the
					 * size of the array. */
					if (zend_hash_num_elements(Z_ARRVAL_P(events_arg)) != numevents) {
						php_error(E_WARNING, "%s() parameter numevents (%lu) expected to match size of array (%d)",
								  get_active_function_name(TSRMLS_C), numevents, zend_hash_num_elements(Z_ARRVAL_PP(&events_arg)));
						RETURN_FALSE;
					}
					events = (SDL_Event *)emalloc(numevents*sizeof(SDL_Event));
					for (i = 0; i < numevents; i++) {
						if (zend_hash_index_find(Z_ARRVAL_P(events_arg), i, (void**)&tmp) == FAILURE) {
							php_error(E_WARNING, "%s() unable to fetch event element %d",
									  get_active_function_name(TSRMLS_C), i);
							efree(events);
							RETURN_FALSE;
						}
						if (Z_TYPE_PP(tmp) != IS_ARRAY) {
							php_error(E_WARNING, "%s() expected event array element %d to be array; %s found",
									  get_active_function_name(TSRMLS_C), i, zend_zval_type_name(*tmp));
							efree(events);
							RETURN_FALSE;
						}
						if (!php_sdl_php_array_to_sdl_event(INTERNAL_FUNCTION_PARAM_PASSTHRU, -1, tmp, &(events[i]))) {
							efree(events);
							RETURN_FALSE;
						}
					}
				} else {
					php_error(E_WARNING, "%s() SDL_ADDEVENT either expects a single event or an array of events",
							  get_active_function_name(TSRMLS_C));
					RETURN_FALSE;
				}
			}
			break;
		case SDL_PEEKEVENT:
		case SDL_GETEVENT:
			{
				char *which = (action == SDL_PEEKEVENT ? "SDL_PEEKEVENT" : "SDL_GETEVENT");
				if (numevents < 1) {
					php_error(E_WARNING, "%s() parameter numevents must be greater than 0 when action specified is %s",
						  get_active_function_name(TSRMLS_C), which);
					RETURN_FALSE;
				}
				if (NULL == (events = emalloc(numevents * sizeof(SDL_Event)))) {
					php_error(E_WARNING, "%s() unable to allocate buffer for %lu events",
							  get_active_function_name(TSRMLS_C), numevents);
					RETURN_FALSE;
				}
			}
			break;
		default:
			php_error(E_WARNING, "%s() parameter action must be one of SDL_ADDEVENT, SDL_PEEKEVENT or SDL_GETEVENT; %lu found",
					  get_active_function_name(TSRMLS_C), action);
			RETURN_FALSE;
	}

	result = SDL_PeepEvents(events, numevents, action, mask);

	if (result != -1 && events  && action != SDL_ADDEVENT) {
		int i;
		zval *tmp;
		/* Now that we have called either SDL_PEEKEVENT or SDL_GETEVENT and no
		 * error occured, we need to return the events. */
		array_init(events_arg);
		for (i = 0; i < result; i++) {
			MAKE_STD_ZVAL(tmp);
			array_init(tmp);
			if (!php_sdl_event_to_array(&(events[i]), tmp TSRMLS_CC)) {
				zval_ptr_dtor(&tmp);
				efree(events);
				RETURN_FALSE;
			}
			add_next_index_zval(events_arg, tmp);
		}
	}

	if (events) {
		efree(events);
	}
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_seteventfilter(string filter)
 */
PHP_FUNCTION(sdl_seteventfilter)
{
	php_error(E_WARNING, "%s() not implemented yet",
			  get_active_function_name(TSRMLS_C));
}
/* }}} */

/* {{{ proto int sdl_geteventfilter(void)
 */
PHP_FUNCTION(sdl_geteventfilter)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	/* TODO: Implement */
	php_error(E_WARNING, "%s() not implemented yet",
			  get_active_function_name(TSRMLS_C));
}
/* }}} */

/* {{{ proto int sdl_eventstate(int type, int state)
 */
PHP_FUNCTION(sdl_eventstate)
{
	long type, state;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &type, &state) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG( SDL_EventState( type, state ) );
}
/* }}} */

/* }}} */

/* {{{ SDL IO Functions */

/* {{{ proto int sdl_getkeystate(int &numkeys)
 */
PHP_FUNCTION(sdl_getkeystate)
{
	Uint8 *keystate;
	zval *numkeys_arg;
	int numkeys;
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &numkeys_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	keystate = SDL_GetKeyState(&numkeys);

	array_init(return_value);
	for(i = 0; i < numkeys; i++) {
		add_next_index_long(return_value, keystate[i]);
	}

	if (numkeys_arg != NULL) {
		ZVAL_LONG(numkeys_arg, numkeys);
	}
}
/* }}} */

/* {{{ proto int sdl_getmodstate(void)
 */
PHP_FUNCTION(sdl_getmodstate)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG(SDL_GetModState());
}
/* }}} */

/* {{{ proto int sdl_setmodstate(int modstate)

 void SDL_SetModState(SDLMod modstate);
 */
PHP_FUNCTION(sdl_setmodstate)
{
	int modState;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &modState) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	SDL_SetModState(modState);
}
/* }}} */

/* {{{ proto string sdl_getkeyname(int key)
 */
PHP_FUNCTION(sdl_getkeyname)
{
	long key;
	char *keyname = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	keyname = SDL_GetKeyName(key);

	RETURN_STRING(keyname,1);
}
/* }}} */

/* {{{ proto int sdl_enableunicode(int enable)
 */
PHP_FUNCTION(sdl_enableunicode)
{
	long enable;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &enable) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_EnableUNICODE(enable));
}
/* }}} */

/* {{{ proto int sdl_enablekeyrepeat(int delay, int interval)
 */
PHP_FUNCTION(sdl_enablekeyrepeat)
{
	long delay, interval;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &delay, &interval) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_EnableKeyRepeat(delay, interval));
}
/* }}} */

/* {{{ proto int sdl_getmousestate(int &x, int &y)
 */
PHP_FUNCTION(sdl_getmousestate)
{
	zval *x_arg, *y_arg;
	int x, y, x_null, y_null;
	Uint8 result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &x_arg, &y_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	x_null = (Z_TYPE_PP(&x_arg) == IS_NULL ? 1 : 0);
	y_null = (Z_TYPE_PP(&x_arg) == IS_NULL ? 1 : 0);

	convert_to_long_ex(&x_arg);
	convert_to_long_ex(&y_arg);

	result = SDL_GetMouseState((x_null) ? NULL : &x, (y_null) ? NULL : &y);
	
	ZVAL_LONG(x_arg, x);
	ZVAL_LONG(y_arg, y);

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_getrelativemousestate(int &x, int &y)
 */
PHP_FUNCTION(sdl_getrelativemousestate)
{
	zval *x_arg, *y_arg;
	int x, y, x_null, y_null;
	Uint8 result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &x_arg, &y_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	x_null = (Z_TYPE_PP(&x_arg) == IS_NULL ? 1 : 0);
	y_null = (Z_TYPE_PP(&x_arg) == IS_NULL ? 1 : 0);

	convert_to_long_ex(&x_arg);
	convert_to_long_ex(&y_arg);

	result = SDL_GetRelativeMouseState((x_null) ? NULL : &x, (y_null) ? NULL : &y);
	
	ZVAL_LONG(x_arg, x);
	ZVAL_LONG(y_arg, y);

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_getappstate(void)
 */
PHP_FUNCTION(sdl_getappstate)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG(SDL_GetAppState());
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
