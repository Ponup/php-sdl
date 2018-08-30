/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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


/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_shape.h (only SDL_Window)                       |
  +----------------------------------------------------------------------+
  | class SDL_WindowShapeMode                                            |
  +----------------------------------------------------------------------+
*/


#include "php_sdl.h"
#include "pixels.h"
#include "shape.h"
#include "window.h"

static zend_class_entry *php_sdl_windowshapemode_ce;
static zend_object_handlers php_sdl_windowshapemode_handlers;
struct php_sdl_windowshapemode {
	zend_object          zo;
	SDL_WindowShapeMode  mode;
};


zend_class_entry *get_php_sdl_windowshapemode_ce(void)
{
	return php_sdl_windowshapemode_ce;
}


/* {{{ sdl_windowshapemode_to_zval */
zend_bool sdl_windowshapemode_to_zval(SDL_WindowShapeMode *mode, zval *z_val TSRMLS_DC)
{
	if (mode) {
		struct php_sdl_windowshapemode *intern;

		object_init_ex(z_val, php_sdl_windowshapemode_ce);
		intern = (struct php_sdl_windowshapemode *)Z_OBJ_P(z_val TSRMLS_CC);
		memcpy(&intern->mode, mode, sizeof(SDL_WindowShapeMode));

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ zval_to_sdl_windowshapemode */
SDL_WindowShapeMode *zval_to_sdl_windowshapemode(zval *z_val TSRMLS_DC)
{
	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_windowshapemode_ce) {
		struct php_sdl_windowshapemode *intern;

		intern = (struct php_sdl_windowshapemode *)Z_OBJ_P(z_val TSRMLS_CC);
		return &intern->mode;
		}
	return NULL;
}
/* }}} */


/* {{{ php_sdl_windowshapemode_free
	 */
static void php_sdl_windowshapemode_free(zend_object *object TSRMLS_DC)
{
	struct php_sdl_windowshapemode *intern = (struct php_sdl_windowshapemode *) object;

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_windowshapemode_new
 */
static zend_object php_sdl_windowshapemode_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object retval;
	struct php_sdl_windowshapemode *intern;

	intern = ecalloc(1, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

//	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_windowshapemode_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_windowshapemode_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_windowshapemode_read_property*/
zval *sdl_windowshapemode_read_property(zval *object, zval *member, int type, const zval *key TSRMLS_DC)
{
	struct php_sdl_windowshapemode *intern = (struct php_sdl_windowshapemode *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval, tmp_member, rv;

	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		key = NULL;
	}

	ALLOC_INIT_ZVAL(retval);
	Z_SET_REFCOUNT_P(retval, 0);

	if (!strcmp(Z_STRVAL_P(member), "mode")) {
		ZVAL_LONG(retval, intern->mode.mode);

	} else if (!strcmp(Z_STRVAL_P(member), "colorKey")) {
		if (intern->mode.mode == ShapeModeColorKey) {
			sdl_color_to_zval(&intern->mode.parameters.colorKey, retval TSRMLS_CC);
		} else {
			ZVAL_NULL(retval);
		}

	} else if (!strcmp(Z_STRVAL_P(member), "binarizationCutoff")) {
		if (SDL_SHAPEMODEALPHA(intern->mode.mode)) {
			ZVAL_LONG(retval, intern->mode.parameters.binarizationCutoff);
		} else {
			ZVAL_NULL(retval);
		}

	} else {
		FREE_ZVAL(retval);

		retval = (zend_get_std_object_handlers())->read_property(object, member, type, key, &rv TSRMLS_CC);
		if (member == &tmp_member) {
			zval_dtor(member);
		}
		return retval;
	}

	if (member == &tmp_member) {
		zval_dtor(member);
	}
	return retval;
}
/* }}} */


/* {{{ sdl_windowshapemode_read_property*/
static HashTable *sdl_windowshapemode_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv;
	struct php_sdl_windowshapemode *intern = (struct php_sdl_windowshapemode *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	MAKE_STD_ZVAL(zv);
	ZVAL_LONG(zv, (long)intern->mode.mode);
	// php7 zend_hash_update(props, "mode", sizeof("mode"), &zv, sizeof(zv), NULL);

	MAKE_STD_ZVAL(zv);
	ZVAL_NULL(zv);
	// php7 zend_hash_update(props, "binarizationCutoff", sizeof("binarizationCutoff"), &zv, sizeof(zv), NULL);
	// php7 zend_hash_update(props, "colorKey", sizeof("colorKey"), &zv, sizeof(zv), NULL);

	if (SDL_SHAPEMODEALPHA(intern->mode.mode)) {
		MAKE_STD_ZVAL(zv);
		ZVAL_LONG(zv, intern->mode.parameters.binarizationCutoff);
		// php7 zend_hash_update(props, "binarizationCutoff", sizeof("binarizationCutoff"), &zv, sizeof(zv), NULL);

	} else if (intern->mode.mode == ShapeModeColorKey) {
		MAKE_STD_ZVAL(zv);
		sdl_color_to_zval(&intern->mode.parameters.colorKey, zv  TSRMLS_CC);
		// php7 zend_hash_update(props, "colorKey", sizeof("colorKey"), &zv, sizeof(zv), NULL);
	}
	return props;
}
/* }}} */


/* {{{ sdl_windowshapemode_write_property */
void sdl_windowshapemode_write_property(zval *object, zval *member, zval *value, const zval *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported for SDL_WindowShapeMode object");
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
	long mode;
	zval *z_param;
	zend_error_handling error_handling;

	intern = (struct php_sdl_windowshapemode *)Z_OBJ_P(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &mode, &z_param)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	if (SDL_SHAPEMODEALPHA(mode)) {
		convert_to_long(z_param);
		intern->mode.mode = mode;
		intern->mode.parameters.binarizationCutoff = (Uint8)Z_LVAL_P(z_param);

	} else if (mode == ShapeModeColorKey) {
		if (Z_TYPE_P(z_param) == IS_OBJECT && Z_OBJCE_P(z_param) == get_php_sdl_color_ce()) {
			intern->mode.mode = ShapeModeColorKey;
			zval_to_sdl_color(z_param, &intern->mode.parameters.colorKey TSRMLS_CC);
		} else {
			zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Invalid parameter for mode=ShapeModeColorKey, SDL_Color object expected", 0 TSRMLS_CC);
		}


	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Invalid mode for SDL_WindowShapeMode", 0 TSRMLS_CC);
	}
}
/* }}} */


/* {{{ proto SDL_WindowShapeMode::__toString() */
static PHP_METHOD(SDL_WindowShapeMode, __toString)
{
	struct php_sdl_windowshapemode *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_windowshapemode *)Z_OBJ_P(getThis() TSRMLS_CC);
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



/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ php_sdl_windowshapemode_methods[] */
static const zend_function_entry php_sdl_windowshapemode_methods[] = {
	PHP_ME(SDL_WindowShapeMode,  __construct,  arginfo_SDL_WindowShapeMode__construct,    ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_WindowShapeMode,  __toString,   arginfo_none,                              ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */


/* {{{ sdl_shape_functions[] */
zend_function_entry sdl_shape_functions[] = {
	ZEND_FE_END
};
/* }}} */


#define REGISTER_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("ShapeMode" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_windowshapemode_ce, ZEND_STRL(const_name), value TSRMLS_CC); \


	/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_shape)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_WindowShapeMode", php_sdl_windowshapemode_methods);
	ce.create_object = php_sdl_windowshapemode_new;
	php_sdl_windowshapemode_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_windowshapemode_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_windowshapemode_handlers.read_property  = sdl_windowshapemode_read_property;
	php_sdl_windowshapemode_handlers.get_properties = sdl_windowshapemode_get_properties;
	php_sdl_windowshapemode_handlers.write_property = sdl_windowshapemode_write_property;

	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("mode"),               0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("colorKey"),           0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_windowshapemode_ce, ZEND_STRL("binarizationCutoff"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

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
