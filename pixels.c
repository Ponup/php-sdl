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

/* $ Id: $ */ 

#include "php_sdl.h"

zend_class_entry *php_sdl_color_ce;
static zend_object_handlers php_sdl_color_handlers;
struct php_sdl_color {
	zend_object   zo;
};

void sdl_color_to_zval(SDL_Color *color, zval *value TSRMLS_DC)
{
	object_init_ex(value, php_sdl_color_ce);
	zend_update_property_long(php_sdl_color_ce, value, "r", 1, color->r TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, value, "g", 1, color->g TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, value, "b", 1, color->b TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, value, "a", 1, color->a TSRMLS_CC);
}

void zval_to_sdl_color(zval *value, SDL_Color *color TSRMLS_DC)
{
	zval *val;

	val = zend_read_property(php_sdl_color_ce, value, "r", 1, 0 TSRMLS_CC);
	color->r = (Uint8)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_color_ce, value, "g", 1, 0 TSRMLS_CC);
	color->g = (Uint8)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_color_ce, value, "b", 1, 0 TSRMLS_CC);
	color->b = (Uint8)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_color_ce, value, "a", 1, 0 TSRMLS_CC);
	color->a = (Uint8)Z_LVAL_P(val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Color__construct, 0, 0, 4)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
       ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Color, __construct(int r, int g, int b, int a)
*/
static PHP_METHOD(SDL_Color, __construct)
{
	long r, g, b, a;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &r, &g, &b, &a)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_color_ce, getThis(), "r", 1, r&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, getThis(), "g", 1, g&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, getThis(), "b", 1, b&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_color_ce, getThis(), "a", 1, a&255 TSRMLS_CC);
}
/* }}} */

/* {{{ php_sdl_color_methods[] */
static const zend_function_entry php_sdl_color_methods[] = {
	PHP_ME(SDL_Color, __construct,     arginfo_SDL_Color__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ sdl_pixels_functions[] */
zend_function_entry sdl_pixels_functions[] = {
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_pixels)
{
	zend_class_entry ce_color;

	INIT_CLASS_ENTRY(ce_color, "SDL_Color", php_sdl_color_methods);
	php_sdl_color_ce = zend_register_internal_class(&ce_color TSRMLS_CC);
	memcpy(&php_sdl_color_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_color_ce, "r", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_color_ce, "g", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_color_ce, "b", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_color_ce, "a", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	return (zend_register_functions(NULL, sdl_pixels_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

