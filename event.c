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
#include "event.h"

static zend_class_entry *php_sdl_event_ce;
static zend_object_handlers php_sdl_event_handlers;
struct php_sdl_event {
	zend_object zo;
};

zend_class_entry *get_php_sdl_event_ce(void)
{
	return php_sdl_event_ce;
}

zend_bool sdl_event_to_zval(SDL_Event *event, zval *value TSRMLS_DC)
{
	if(NULL == event) {
		ZVAL_NULL(value);
		return 0;
	}

	object_init_ex(value, php_sdl_event_ce);
	zend_update_property_long(php_sdl_event_ce, value, "type", sizeof("type")-1, event->type TSRMLS_CC);
	return 1;
}

zend_bool zval_to_sdl_event(zval *value, SDL_Event *event TSRMLS_DC)
{
	zval *val;
	
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_event_ce) {
		val = zend_read_property(php_sdl_event_ce, value, "type", sizeof("type")-1, 0 TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = event->type = (int)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty rect */
	memset(event, 0, sizeof(SDL_Event));
	return 0;
}

static PHP_METHOD(SDL_Event, __construct)
{
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters_none()) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);
}

/* {{{ proto SDL_Event::__toString() */
static PHP_METHOD(SDL_Event, __toString)
{
	char *buf;
	SDL_Event event;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_event(getThis(), &event TSRMLS_CC);
	spprintf(&buf, 100, "SDL_Event(type=%d)", event.type);
	RETVAL_STRING(buf, 0);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WaitEvent, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, event, SDL_Event, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_WaitEvent)
{
	zval *object;
	SDL_Event event;
	long ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &object, php_sdl_event_ce) == FAILURE) {
		return;
	}

	ret = SDL_WaitEvent(&event);
	sdl_event_to_zval(&event, object TSRMLS_CC);
	
	RETURN_LONG(ret);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

zend_function_entry sdl_event_functions[] = {
	ZEND_FE(SDL_WaitEvent, arginfo_SDL_WaitEvent)
	ZEND_FE_END
};

static const zend_function_entry php_sdl_event_methods[] = {
	PHP_ME(SDL_Event, __construct, arginfo_none, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Event, __toString, arginfo_none, ZEND_ACC_PUBLIC)

	/* non-static methods */
//	PHP_FALIAS(Empty,            SDL_RectEmpty,            arginfo_none)
	PHP_FE_END
};

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_event)
{
	zend_class_entry ce_event;

	REGISTER_LONG_CONSTANT("SDL_QUIT", SDL_QUIT, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_APP_TERMINATING", SDL_APP_TERMINATING, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APP_LOWMEMORY", SDL_APP_LOWMEMORY, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APP_WILLENTERBACKGROUND", SDL_APP_WILLENTERBACKGROUND, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APP_DIDENTERBACKGROUND", SDL_APP_DIDENTERBACKGROUND, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APP_WILLENTERFOREGROUND", SDL_APP_WILLENTERFOREGROUND, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APP_DIDENTERFOREGROUND", SDL_APP_DIDENTERFOREGROUND, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOWEVENT", SDL_WINDOWEVENT, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SYSWMEVENT", SDL_SYSWMEVENT, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYDOWN", SDL_KEYDOWN, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYUP", SDL_KEYUP, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTEDITING", SDL_TEXTEDITING, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTINPUT", SDL_TEXTINPUT, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEMOTION", SDL_MOUSEMOTION, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONUP", SDL_MOUSEBUTTONUP, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEWHEEL", SDL_MOUSEWHEEL, CONST_CS|CONST_PERSISTENT);

	INIT_CLASS_ENTRY(ce_event, "SDL_Event", php_sdl_event_methods);
	php_sdl_event_ce = zend_register_internal_class(&ce_event TSRMLS_CC);
	memcpy(&php_sdl_event_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_event_ce, "type", sizeof("type")-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	return (zend_register_functions(NULL, sdl_event_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

