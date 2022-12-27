/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2022 The PHP Group                                |
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


#include "pixels.h"
#include "shape.h"
#include "window.h"

static zend_class_entry *php_sdl_windowshapemode_ce;
static zend_object_handlers php_sdl_windowshapemode_handlers;
struct php_sdl_windowshapemode {
	SDL_WindowShapeMode  mode;
	zend_object          zo;
};

zend_class_entry *get_php_sdl_windowshapemode_ce(void)
{
	return php_sdl_windowshapemode_ce;
}

static inline struct php_sdl_windowshapemode* php_sdl_windowshapemode_fetch_object(zend_object* obj)
{
	return (struct php_sdl_windowshapemode*) ((char*) obj - XtOffsetOf(struct php_sdl_windowshapemode, zo));
}


/* {{{ sdl_windowshapemode_to_zval */
zend_bool sdl_windowshapemode_to_zval(SDL_WindowShapeMode *mode, zval *z_val)
{
	if (mode) {
		struct php_sdl_windowshapemode *intern;

		object_init_ex(z_val, php_sdl_windowshapemode_ce);
		intern = php_sdl_windowshapemode_fetch_object(Z_OBJ_P(z_val));
		memcpy(&intern->mode, mode, sizeof(SDL_WindowShapeMode));

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_windowshapemode */
SDL_WindowShapeMode *zval_to_sdl_windowshapemode(zval *z_val)
{
	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_windowshapemode_ce) {
		struct php_sdl_windowshapemode *intern;
		intern = php_sdl_windowshapemode_fetch_object(Z_OBJ_P(z_val));
		return &intern->mode;
	}
	return NULL;
}
/* }}} */


/* {{{ php_sdl_windowshapemode_free
	 */
static void php_sdl_windowshapemode_free(zend_object *zo)
{
	struct php_sdl_windowshapemode *intern = (struct php_sdl_windowshapemode*)((char*)zo - XtOffsetOf(struct php_sdl_windowshapemode, zo));

	zend_object_std_dtor(&intern->zo);
}
/* }}} */


/* {{{ php_sdl_windowshapemode_new
 */
static zend_object* php_sdl_windowshapemode_new(zend_class_entry *class_type)
{
	struct php_sdl_windowshapemode *intern;

	intern = ecalloc(1, sizeof(struct php_sdl_windowshapemode) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->zo.handlers = (zend_object_handlers *) &php_sdl_windowshapemode_handlers;

	return &intern->zo;
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WindowShapeMode__construct, 0, 0, 2)
       ZEND_ARG_INFO(0, mode)
       ZEND_ARG_INFO(0, parameter)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_WindowShapeMode::__construct(int mode, mixed param) */
static PHP_METHOD(SDL_WindowShapeMode, __construct)
{
	struct php_sdl_windowshapemode *intern;
	zend_long mode;
	zval *z_param;
	zend_error_handling error_handling;

	intern = php_sdl_windowshapemode_fetch_object(Z_OBJ_P(getThis()));

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "lz", &mode, &z_param)) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	if (SDL_SHAPEMODEALPHA(mode)) {
		convert_to_long(z_param);
		intern->mode.mode = mode;
		intern->mode.parameters.binarizationCutoff = (Uint8)Z_LVAL_P(z_param);

	} else if (mode == ShapeModeColorKey) {
		if (Z_TYPE_P( z_param) == IS_OBJECT && Z_OBJCE_P(z_param) == get_php_sdl_color_ce()) {
			intern->mode.mode = ShapeModeColorKey;
			zval_to_sdl_color(z_param, &intern->mode.parameters.colorKey);
		} else {
			zend_throw_exception(zend_exception_get_default(), "Invalid parameter for mode=ShapeModeColorKey, SDL_Color object expected", 0);
		}


	} else {
		zend_throw_exception(zend_exception_get_default(), "Invalid mode for SDL_WindowShapeMode", 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_WindowShapeMode___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_WindowShapeMode::__toString() */
static PHP_METHOD(SDL_WindowShapeMode, __toString)
{
	struct php_sdl_windowshapemode *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = php_sdl_windowshapemode_fetch_object(Z_OBJ_P(getThis()));
	switch (intern->mode.mode) {
		case ShapeModeDefault:
			spprintf(&buf, 200, "SDL_WindowShapeMode(ShapeModeDefault, %u)", intern->mode.parameters.binarizationCutoff);
			break;
		case ShapeModeBinarizeAlpha:
			spprintf(&buf, 200, "SDL_WindowShapeMode(ShapeModeBinarizeAlpha, %u)", intern->mode.parameters.binarizationCutoff);
			break;
		case ShapeModeReverseBinarizeAlpha:
			spprintf(&buf, 200, "SDL_WindowShapeMode(ShapeModeReverseBinarizeAlpha, %u)", intern->mode.parameters.binarizationCutoff);
			break;
		case ShapeModeColorKey:
			spprintf(&buf, 200, "SDL_WindowShapeMode(ShapeModeColorKey, SDL_Color(%u,%u,%u,%u))",
					intern->mode.parameters.colorKey.r, intern->mode.parameters.colorKey.g,
					intern->mode.parameters.colorKey.b, intern->mode.parameters.colorKey.a);
			break;
		default:
			spprintf(&buf, 200, "SDL_WindowShapeMode()");
	}
	RETVAL_STRING(buf);
}
/* }}} */

/* {{{ php_sdl_windowshapemode_methods[] */
static const zend_function_entry php_sdl_windowshapemode_methods[] = {
	PHP_ME(SDL_WindowShapeMode,  __construct,  arginfo_SDL_WindowShapeMode__construct,    ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_WindowShapeMode,  __toString,   arginfo_class_SDL_WindowShapeMode___toString, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

#define REGISTER_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("ShapeMode" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_windowshapemode_ce, const_name, sizeof(const_name)-1, value); \

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_shape)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_WindowShapeMode", php_sdl_windowshapemode_methods);
	php_sdl_windowshapemode_ce = zend_register_internal_class(&ce);
	php_sdl_windowshapemode_ce->create_object = php_sdl_windowshapemode_new;
	memcpy(&php_sdl_windowshapemode_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_windowshapemode_handlers.free_obj = php_sdl_windowshapemode_free;
	php_sdl_windowshapemode_handlers.offset = XtOffsetOf(struct php_sdl_windowshapemode, zo);

	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("mode"),               0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("colorKey"),           0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("binarizationCutoff"), 0, ZEND_ACC_PUBLIC);

	/* typedef enum WindowShapeMode */
	REGISTER_CLASS_CONST_LONG("Default",              ShapeModeDefault);
	REGISTER_CLASS_CONST_LONG("BinarizeAlpha",        ShapeModeBinarizeAlpha);
	REGISTER_CLASS_CONST_LONG("ReverseBinarizeAlpha", ShapeModeReverseBinarizeAlpha);
	REGISTER_CLASS_CONST_LONG("ColorKey",             ShapeModeColorKey);

	REGISTER_LONG_CONSTANT("SDL_NONSHAPEABLE_WINDOW",    SDL_NONSHAPEABLE_WINDOW,    CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INVALID_SHAPE_ARGUMENT", SDL_INVALID_SHAPE_ARGUMENT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_WINDOW_LACKS_SHAPE",     SDL_WINDOW_LACKS_SHAPE,     CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */
