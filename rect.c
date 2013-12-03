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
  | Authors: Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#include "php_sdl2.h"
zend_class_entry *php_sdl_rect_ce;

static zend_object_handlers php_sdl_rect_handlers;

struct php_sdl_rect {
	zend_object   zo;
	SDL_Rect      rect;
};


void sdl_rect_to_zval(SDL_Rect *rect, zval *value TSRMLS_DC)
{
	object_init_ex(value, php_sdl_rect_ce);
	zend_update_property_long(php_sdl_rect_ce, value, "x", 1, rect->x TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, value, "y", 1, rect->y TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, value, "w", 1, rect->w TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, value, "h", 1, rect->h TSRMLS_CC);
}

void zval_to_sdl_rect(zval *value, SDL_Rect *rect TSRMLS_DC)
{
	zval *val;

	val = zend_read_property(php_sdl_rect_ce, value, "x", 1, 0 TSRMLS_DC);
	rect->x = (int)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_rect_ce, value, "y", 1, 0 TSRMLS_DC);
	rect->y = (int)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_rect_ce, value, "w", 1, 0 TSRMLS_DC);
	rect->w = (int)Z_LVAL_P(val);
	val = zend_read_property(php_sdl_rect_ce, value, "h", 1, 0 TSRMLS_DC);
	rect->h = (int)Z_LVAL_P(val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect__construct, 0, 0, 6)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Rect, __construct(, int x, int y, int w, int h)

 *  \brief A rectangle, with the origin at the upper left.
*/
static PHP_METHOD(SDL_Rect, __construct)
{
//	struct php_sdl_rect *intern;
	long x, y, w, h;
	zend_error_handling error_handling;

//	intern = (struct php_sdl_rect *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &x, &y, &w, &h)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_rect_ce, getThis(), "x", 1, x TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "y", 1, y TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "w", 1, w TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "h", 1, h TSRMLS_CC);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect, 0, 0, 1)
       ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

/* {{{ proto bool SDL_RectEmpty(SDL_Rect rect)

 *  \brief Returns true if the rectangle has no area.
 SDL_FORCE_INLINE SDL_bool SDL_RectEmpty(const SDL_Rect *r)
 */
PHP_FUNCTION(SDL_RectEmpty)
{
	zval *object;
	SDL_Rect rect;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_rect_ce) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(object, &rect);
	
	RETURN_BOOL(SDL_RectEmpty(&rect));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect2, 0, 0, 2)
       ZEND_ARG_INFO(0, rectA)
       ZEND_ARG_INFO(0, rectB)
ZEND_END_ARG_INFO()


/* {{{ proto bool SDL_RectEquals(SDL_Rect a, SDL_Rect b)

 *  \brief Returns true if the two rectangles are equal.
 SDL_FORCE_INLINE SDL_bool SDL_RectEquals(const SDL_Rect *a, const SDL_Rect *b)
 */
PHP_FUNCTION(SDL_RectEquals)
{
	zval *obj1, *obj2;
	SDL_Rect rect1, rect2;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	
	RETURN_BOOL(SDL_RectEquals(&rect1, &rect2));
}
/* }}} */


/* {{{ proto bool SDL_HasIntersection(SDL_Rect a, SDL_Rect b)

 *  \brief Determine whether two rectangles intersect.
 *
 *  \return SDL_TRUE if there is an intersection, SDL_FALSE otherwise.
 extern DECLSPEC SDL_bool SDLCALL SDL_HasIntersection(const SDL_Rect * A,
                                                      const SDL_Rect * B);
 */
PHP_FUNCTION(SDL_HasIntersection)
{
	zval *obj1, *obj2;
	SDL_Rect rect1, rect2;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	
	RETURN_BOOL(SDL_HasIntersection(&rect1, &rect2));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect3, 0, 0, 3)
       ZEND_ARG_INFO(0, rectA)
       ZEND_ARG_INFO(0, rectB)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect_Result, 0, 0, 2)
       ZEND_ARG_INFO(0, rect)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

/* {{{ proto bool SDL_IntersectRect(SDL_Rect a, SDL_Rect b, SDL_Rect &result)

 *  \brief Calculate the intersection of two rectangles.
 *
 *  \return SDL_TRUE if there is an intersection, SDL_FALSE otherwise.
 extern DECLSPEC SDL_bool SDLCALL SDL_IntersectRect(const SDL_Rect * A,
                                                    const SDL_Rect * B,
                                                    SDL_Rect * result);
 */
PHP_FUNCTION(SDL_IntersectRect)
{
	zval *obj1, *obj2, *result;
	SDL_Rect rect1, rect2, rect3;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OOz", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce, &result) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	if (SDL_IntersectRect(&rect1, &rect2, &rect3)) {
		zval_dtor(result);
		sdl_rect_to_zval(&rect3, result TSRMLS_CC);
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool SDL_UnionRect(SDL_Rect a, SDL_Rect b, SDL_Rect &result)

 *  \brief Calculate the union of two rectangles.
 extern DECLSPEC void SDLCALL SDL_UnionRect(const SDL_Rect * A,
                                            const SDL_Rect * B,
                                            SDL_Rect * result);
 */
PHP_FUNCTION(SDL_UnionRect)
{
	zval *obj1, *obj2, *result;
	SDL_Rect rect1, rect2, rect3;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OOz", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce, &result) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	SDL_UnionRect(&rect1, &rect2, &rect3);
	zval_dtor(result);
	sdl_rect_to_zval(&rect3, result TSRMLS_CC);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry php_sdl_rect_methods[] = {
	PHP_ME(SDL_Rect, __construct,     arginfo_SDL_Rect__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(Empty,            SDL_RectEmpty,          arginfo_none)
	PHP_FALIAS(Equal,            SDL_RectEquals,         arginfo_SDL_Rect)
	PHP_FALIAS(HasIntersection,  SDL_HasIntersection,    arginfo_SDL_Rect)
	PHP_FALIAS(Intersect,        SDL_IntersectRect,      arginfo_SDL_Rect_Result)
	PHP_FALIAS(Union,            SDL_UnionRect,          arginfo_SDL_Rect_Result)

	PHP_FE_END
};

/* {{{ php_sdl_rect_free
	 */
static void php_sdl_rect_free(void *object TSRMLS_DC)
{
	struct php_sdl_rect *intern = (struct php_sdl_rect *) object;

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_rect_new
 */
static zend_object_value php_sdl_rect_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_rect *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_rect_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_rect_handlers;

	return retval;
}
/* }}} */

/* {{{ sdl2_functions[] */
zend_function_entry sdl2_rect_functions[] = {
	ZEND_FE(SDL_RectEmpty,					arginfo_SDL_Rect)
	ZEND_FE(SDL_RectEquals,					arginfo_SDL_Rect2)
	ZEND_FE(SDL_HasIntersection,			arginfo_SDL_Rect2)
	ZEND_FE(SDL_IntersectRect,				arginfo_SDL_Rect3)
	ZEND_FE(SDL_UnionRect,					arginfo_SDL_Rect3)
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl2_rect)
{
	zend_class_entry ce_rect;

	INIT_CLASS_ENTRY(ce_rect, "SDL_Rect", php_sdl_rect_methods);
	ce_rect.create_object = php_sdl_rect_new;
	php_sdl_rect_ce = zend_register_internal_class(&ce_rect TSRMLS_CC);
	memcpy(&php_sdl_rect_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_rect_ce, "x", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "y", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "w", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "h", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	return (zend_register_functions(NULL, sdl2_rect_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
