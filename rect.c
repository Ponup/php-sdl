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
  | wrapper for SDL2/SDL_rect.h                                          |
  +----------------------------------------------------------------------+
  | class SDL_Point                                                      |
  | class SDL_Rect                                                       |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "rect.h"

static zend_class_entry *php_sdl_rect_ce;
static zend_object_handlers php_sdl_rect_handlers;
struct php_sdl_rect {
	zend_object   zo;
};

static zend_class_entry *php_sdl_point_ce;
static zend_object_handlers php_sdl_point_handlers;
struct php_sdl_point {
	zend_object   zo;
};

zend_class_entry *get_php_sdl_point_ce(void)
{
	return php_sdl_point_ce;
}

zend_class_entry *get_php_sdl_rect_ce(void)
{
	return php_sdl_rect_ce;
}

zend_bool sdl_rect_to_zval(SDL_Rect *rect, zval *value TSRMLS_DC)
{
	if (rect) {
		object_init_ex(value, php_sdl_rect_ce);
		zend_update_property_long(php_sdl_rect_ce, value, "x", 1, rect->x TSRMLS_CC);
		zend_update_property_long(php_sdl_rect_ce, value, "y", 1, rect->y TSRMLS_CC);
		zend_update_property_long(php_sdl_rect_ce, value, "w", 1, rect->w TSRMLS_CC);
		zend_update_property_long(php_sdl_rect_ce, value, "h", 1, rect->h TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool sdl_point_to_zval(SDL_Point *pt, zval *value TSRMLS_DC)
{
	if (pt) {
		object_init_ex(value, php_sdl_rect_ce);
		zend_update_property_long(php_sdl_rect_ce, value, "x", 1, pt->x TSRMLS_CC);
		zend_update_property_long(php_sdl_rect_ce, value, "y", 1, pt->y TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool zval_to_sdl_rect(zval *value, SDL_Rect *rect TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_rect_ce) {
		zval *val, rv;

		val = zend_read_property(php_sdl_rect_ce, value, "x", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->x = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, value, "y", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->y = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, value, "w", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->w = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, value, "h", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->h = (int)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty rect */
	memset(rect, 0, sizeof(SDL_Rect));
	return 0;
}

zend_bool zval_to_sdl_point(zval *value, SDL_Point *pt TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_point_ce) {
		zval *val, rv;

		val = zend_read_property(php_sdl_rect_ce, value, "x", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = pt->x = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, value, "y", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = pt->y = (int)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty point */
	memset(pt, 0, sizeof(SDL_Point));
	return 0;
}

/* {{{ proto SDL_Rect::__construct(, int x, int y, int w, int h)

 *  \brief A rectangle, with the origin at the upper left.
*/
static PHP_METHOD(SDL_Rect, __construct)
{
	long x, y, w, h;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|llll", &x, &y, &w, &h)) {
		return;
	}

	zend_update_property_long(php_sdl_rect_ce, getThis(), "x", 1, x TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "y", 1, y TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "w", 1, w TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "h", 1, h TSRMLS_CC);
}
/* }}} */


/* {{{ proto SDL_Rect::__toString() */
static PHP_METHOD(SDL_Rect, __toString)
{
	char *buf;
    size_t buf_len;
	SDL_Rect rect;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_rect(getThis(), &rect TSRMLS_CC);
	buf_len = spprintf(&buf, 100, "SDL_Rect(%d,%d,%d,%d)", rect.x, rect.y, rect.w, rect.h);
	RETVAL_STRINGL(buf, buf_len);
    efree(buf);
}
/* }}} */

/* {{{ proto SDL_Point::__construct(, int x, int y)

 *  \brief A rectangle, with the origin at the upper left.
*/
static PHP_METHOD(SDL_Point, __construct)
{
	long x, y;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_rect_ce, getThis(), "x", 1, x TSRMLS_CC);
	zend_update_property_long(php_sdl_rect_ce, getThis(), "y", 1, y TSRMLS_CC);
}
/* }}} */


/* {{{ proto SDL_Point::__toString() */
static PHP_METHOD(SDL_Point, __toString)
{
	char *buf;
	SDL_Point point;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_point(getThis(), &point TSRMLS_CC);
	spprintf(&buf, 100, "SDL_Point(%d,%d)", point.x, point.y);
	RETVAL_STRING(buf);
}
/* }}} */


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
	zval_to_sdl_rect(object, &rect TSRMLS_CC);
	
	RETURN_BOOL(SDL_RectEmpty(&rect));
}
/* }}} */


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
	zval_to_sdl_rect(obj1, &rect1 TSRMLS_CC);
	zval_to_sdl_rect(obj2, &rect2 TSRMLS_CC);
	
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
	zval_to_sdl_rect(obj1, &rect1 TSRMLS_CC);
	zval_to_sdl_rect(obj2, &rect2 TSRMLS_CC);
	
	RETURN_BOOL(SDL_HasIntersection(&rect1, &rect2));
}
/* }}} */

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
	zval_to_sdl_rect(obj1, &rect1 TSRMLS_CC);
	zval_to_sdl_rect(obj2, &rect2 TSRMLS_CC);
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
	zval_to_sdl_rect(obj1, &rect1 TSRMLS_CC);
	zval_to_sdl_rect(obj2, &rect2 TSRMLS_CC);
	SDL_UnionRect(&rect1, &rect2, &rect3);
	zval_dtor(result);
	sdl_rect_to_zval(&rect3, result TSRMLS_CC);
}
/* }}} */



/* {{{ proto bool SDL_EnclosePoints(array points, int count, SDL_Rect clip, SDL_Rect &result)

 *  \brief Calculate a minimal rectangle enclosing a set of points
 *
 *  \return SDL_TRUE if any points were within the clipping rect
 extern DECLSPEC SDL_bool SDLCALL SDL_EnclosePoints(const SDL_Point * points,
                                                    int count,
                                                    const SDL_Rect * clip,
                                                    SDL_Rect * result);
 */
PHP_FUNCTION(SDL_EnclosePoints)
{
	zval *z_points, *z_clip, *z_result, **z_point;
	long i, count;
	int nb;
	SDL_Rect clip, result;
	SDL_Point *points;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "alOz", &z_points, &count, &z_clip, php_sdl_rect_ce, &z_result) == FAILURE) {
		return;
	}
	RETVAL_FALSE;

	if (count<=0) {
		count = zend_hash_next_free_element(Z_ARRVAL_P(z_points));
	}
	points = emalloc(sizeof(SDL_Point)*count);

	zval_to_sdl_rect(z_clip, &clip TSRMLS_CC);
	for (i=0, nb=0 ; i<count ; i++) {
		if (!(z_point = zend_hash_index_find(Z_ARRVAL_P(z_points), i))) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "point #%ld missing", i);

		} else if (Z_TYPE_PP(z_point) != IS_OBJECT || Z_OBJCE_PP(z_point) != php_sdl_point_ce) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "point #%ld is not a SDL_Point object", i);

		} else {
			zval_to_sdl_point(*z_point, points+nb TSRMLS_CC);
			nb++;
		}
	}

	if (!nb) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "no point in provided array");

	} else if (SDL_EnclosePoints(points, nb, &clip, &result)) {
		zval_dtor(z_result);
		sdl_rect_to_zval(&result, z_result TSRMLS_CC);
		RETVAL_TRUE;
	}
	efree(points);
}
/* }}} */


/* {{{ proto bool SDL_IntersectRectAndLine(const SDL_Rect *, int &x1, int &y1, int &x2, int &y2)

 *  \brief Calculate the intersection of a rectangle and line segment.
 *
 *  \return SDL_TRUE if there is an intersection, SDL_FALSE otherwise.
 extern DECLSPEC SDL_bool SDLCALL SDL_IntersectRectAndLine(const SDL_Rect *
                                                           rect, int *X1,
                                                           int *Y1, int *X2,
                                                           int *Y2);
 */
PHP_FUNCTION(SDL_IntersectRectAndLine)
{
	zval *object, *z_x1, *z_x2, *z_y1, *z_y2;
	SDL_Rect rect;
	int x1, y1, x2, y2;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ozzzz", &object, php_sdl_rect_ce, &z_x1, &z_y1, &z_x2, &z_y2) == FAILURE) {
		return;
	}
	zval_to_sdl_rect(object, &rect TSRMLS_CC);
	convert_to_long_ex(z_x1);
	convert_to_long_ex(z_y1);
	convert_to_long_ex(z_x2);
	convert_to_long_ex(z_y2);
	x1 = (int)Z_LVAL_P(z_x1);
	y1 = (int)Z_LVAL_P(z_y1);
	x2 = (int)Z_LVAL_P(z_x2);
	y2 = (int)Z_LVAL_P(z_y2);

	if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2)) {
		Z_LVAL_P(z_x1) = x1;
		Z_LVAL_P(z_y1) = y1;
		Z_LVAL_P(z_x2) = x2;
		Z_LVAL_P(z_y2) = y2;
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ php_sdl_rect_methods[] */
static const zend_function_entry php_sdl_rect_methods[] = {
	PHP_ME(SDL_Rect, __construct,     arginfo_SDL_Rect__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Rect, __toString,      arginfo_none,                ZEND_ACC_PUBLIC)

	/* non-static methods */
	PHP_FALIAS(Empty,            SDL_RectEmpty,            arginfo_none)
	PHP_FALIAS(Equal,            SDL_RectEquals,           arginfo_SDL_Rect)
	PHP_FALIAS(HasIntersection,  SDL_HasIntersection,      arginfo_SDL_Rect)
	PHP_FALIAS(Intersect,        SDL_IntersectRect,        arginfo_SDL_Rect_Result)
	PHP_FALIAS(Union,            SDL_UnionRect,            arginfo_SDL_Rect_Result)
	PHP_FALIAS(IntersectLine,    SDL_IntersectRectAndLine, arginfo_SDL_Rect_IntersectLine)

	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_point_methods[] */
static const zend_function_entry php_sdl_point_methods[] = {
	PHP_ME(SDL_Point, __construct,     arginfo_SDL_Point__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Point, __toString,      arginfo_none,                 ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_rect)
{
	zend_class_entry ce_rect, ce_point;

	INIT_CLASS_ENTRY(ce_rect, "SDL_Rect", php_sdl_rect_methods);
	php_sdl_rect_ce = zend_register_internal_class(&ce_rect TSRMLS_CC);
	memcpy(&php_sdl_rect_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_rect_ce, "x", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "y", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "w", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_rect_ce, "h", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_point, "SDL_Point", php_sdl_point_methods);
	php_sdl_point_ce = zend_register_internal_class(&ce_point TSRMLS_CC);
	memcpy(&php_sdl_point_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_point_ce, "x", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_point_ce, "y", 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;
}
/* }}} */
