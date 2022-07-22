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

#include "rect.h"
#include "rect_arginfo.h"

static zend_class_entry *php_sdl_rect_ce;
static zend_object_handlers php_sdl_rect_handlers;
struct php_sdl_rect
{
	zend_object zo;
};

static zend_class_entry *php_sdl_frect_ce;
static zend_object_handlers php_sdl_frect_handlers;
struct php_sdl_frect
{
	zend_object zo;
};

static zend_class_entry *php_sdl_point_ce;
static zend_object_handlers php_sdl_point_handlers;
struct php_sdl_point
{
	zend_object zo;
};

static zend_class_entry *php_sdl_fpoint_ce;
static zend_object_handlers php_sdl_fpoint_handlers;
struct php_sdl_fpoint
{
	zend_object zo;
};

zend_class_entry *get_php_sdl_rect_ce(void)
{
	return php_sdl_rect_ce;
}

zend_class_entry *get_php_sdl_frect_ce(void)
{
	return php_sdl_frect_ce;
}

zend_class_entry *get_php_sdl_point_ce(void)
{
	return php_sdl_point_ce;
}

zend_class_entry *get_php_sdl_fpoint_ce(void)
{
	return php_sdl_fpoint_ce;
}

zend_bool sdl_rect_to_zval(SDL_Rect *rect, zval *value)
{
	if (rect)
	{
		object_init_ex(value, php_sdl_rect_ce);
		zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(value), "x", 1, rect->x);
		zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(value), "y", 1, rect->y);
		zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(value), "w", 1, rect->w);
		zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(value), "h", 1, rect->h);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool sdl_frect_to_zval(SDL_FRect *rect, zval *value)
{
	if (rect)
	{
		object_init_ex(value, php_sdl_frect_ce);
		zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(value), "x", 1, rect->x);
		zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(value), "y", 1, rect->y);
		zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(value), "w", 1, rect->w);
		zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(value), "h", 1, rect->h);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool sdl_point_to_zval(SDL_Point *pt, zval *value)
{
	if (pt)
	{
		object_init_ex(value, php_sdl_point_ce);
		zend_update_property_long(php_sdl_point_ce, Z_OBJ_P(value), "x", 1, pt->x);
		zend_update_property_long(php_sdl_point_ce, Z_OBJ_P(value), "y", 1, pt->y);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool sdl_fpoint_to_zval(SDL_FPoint *pt, zval *value)
{
	if (pt)
	{
		object_init_ex(value, php_sdl_fpoint_ce);
		zend_update_property_double(php_sdl_fpoint_ce, Z_OBJ_P(value), "x", 1, pt->x);
		zend_update_property_double(php_sdl_fpoint_ce, Z_OBJ_P(value), "y", 1, pt->y);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool zval_to_sdl_rect(zval *value, SDL_Rect *rect)
{
	if (instanceof_function(Z_OBJCE_P(value), php_sdl_rect_ce))
	{
		zval *val, rv;

		val = zend_read_property(php_sdl_rect_ce, Z_OBJ_P(value), "x", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->x = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, Z_OBJ_P(value), "y", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->y = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, Z_OBJ_P(value), "w", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->w = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_rect_ce, Z_OBJ_P(value), "h", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = rect->h = (int)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty rect */
	memset(rect, 0, sizeof(SDL_Rect));
	return 0;
}

zend_bool zval_to_sdl_frect(zval *value, SDL_FRect *rect)
{
	if (instanceof_function(Z_OBJCE_P(value), php_sdl_frect_ce))
	{
		zval *val, rv;

		val = zend_read_property(php_sdl_frect_ce, Z_OBJ_P(value), "x", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = rect->x = (float)Z_DVAL_P(val);

		val = zend_read_property(php_sdl_frect_ce, Z_OBJ_P(value), "y", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = rect->y = (float)Z_DVAL_P(val);

		val = zend_read_property(php_sdl_frect_ce, Z_OBJ_P(value), "w", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = rect->w = (float)Z_DVAL_P(val);

		val = zend_read_property(php_sdl_frect_ce, Z_OBJ_P(value), "h", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = rect->h = (float)Z_DVAL_P(val);

		return 1;
	}
	/* create an empty rect */
	memset(rect, 0, sizeof(SDL_FRect));
	return 0;
}

zend_bool zval_to_sdl_point(zval *value, SDL_Point *pt)
{
	if (instanceof_function(Z_OBJCE_P(value), php_sdl_point_ce))
	{
		zval *val, rv;

		val = zend_read_property(php_sdl_point_ce, Z_OBJ_P(value), "x", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = pt->x = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_point_ce, Z_OBJ_P(value), "y", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = pt->y = (int)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty point */
	memset(pt, 0, sizeof(SDL_Point));
	return 0;
}

zend_bool zval_to_sdl_fpoint(zval *value, SDL_FPoint *pt)
{
	if (instanceof_function(Z_OBJCE_P(value), php_sdl_fpoint_ce))
	{
		zval *val, rv;

		val = zend_read_property(php_sdl_fpoint_ce, Z_OBJ_P(value), "x", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = pt->x = (float)Z_DVAL_P(val);

		val = zend_read_property(php_sdl_fpoint_ce, Z_OBJ_P(value), "y", 1, 0, &rv);
		convert_to_double(val);
		Z_DVAL_P(val) = pt->y = (float)Z_DVAL_P(val);

		return 1;
	}
	/* create an empty point */
	memset(pt, 0, sizeof(SDL_FPoint));
	return 0;
}

/* {{{ proto SDL_Rect::__construct(, int x, int y, int w, int h)

 *  \brief A rectangle, with the origin at the upper left.
*/
PHP_METHOD(SDL_Rect, __construct)
{
	zend_long x = 0, y = 0, w = 0, h = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "|llll", &x, &y, &w, &h))
	{
		return;
	}

	zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(getThis()), "x", 1, x);
	zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(getThis()), "y", 1, y);
	zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(getThis()), "w", 1, w);
	zend_update_property_long(php_sdl_rect_ce, Z_OBJ_P(getThis()), "h", 1, h);
}
/* }}} */

/* {{{ proto SDL_Rect::__toString() */
PHP_METHOD(SDL_Rect, __toString)
{
	zend_string *buf;
	SDL_Rect rect;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_rect(getThis(), &rect);
	buf = strpprintf(0, "SDL_Rect(%d,%d,%d,%d)", rect.x, rect.y, rect.w, rect.h);
	RETVAL_STR(buf);
}
/* }}} */

PHP_METHOD(SDL_FRect, __construct)
{
	double x = 0, y = 0, w = 0, h = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	Z_PARAM_DOUBLE(x)
	Z_PARAM_DOUBLE(y)
	Z_PARAM_DOUBLE(w)
	Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(getThis()), "x", 1, x);
	zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(getThis()), "y", 1, y);
	zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(getThis()), "w", 1, w);
	zend_update_property_double(php_sdl_frect_ce, Z_OBJ_P(getThis()), "h", 1, h);
}

PHP_METHOD(SDL_FRect, __toString)
{
	zend_string *buf;
	SDL_FRect rect;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_frect(getThis(), &rect);
	buf = strpprintf(0, "SDL_FRect(%f,%f,%f,%f)", rect.x, rect.y, rect.w, rect.h);
	RETVAL_STR(buf);
}

/* {{{ proto SDL_Point::__construct(, int x, int y)

 *  \brief A rectangle, with the origin at the upper left.
*/
PHP_METHOD(SDL_Point, __construct)
{
	zend_long x, y;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &x, &y))
	{
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	zend_update_property_long(php_sdl_point_ce, Z_OBJ_P(getThis()), "x", 1, x);
	zend_update_property_long(php_sdl_point_ce, Z_OBJ_P(getThis()), "y", 1, y);
}
/* }}} */

/* {{{ proto SDL_Point::__toString() */
PHP_METHOD(SDL_Point, __toString)
{
	zend_string *buf;
	SDL_Point point;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_point(getThis(), &point);
	buf = strpprintf(0, "SDL_Point(%d,%d)", point.x, point.y);
	RETVAL_STR(buf);
}
/* }}} */

PHP_METHOD(SDL_FPoint, __construct)
{
	double x = 0, y = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_DOUBLE(x)
	Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(php_sdl_fpoint_ce, Z_OBJ_P(getThis()), "x", 1, x);
	zend_update_property_double(php_sdl_fpoint_ce, Z_OBJ_P(getThis()), "y", 1, y);
}

PHP_METHOD(SDL_FPoint, __toString)
{
	zend_string *buf;
	SDL_FPoint point;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_fpoint(getThis(), &point);
	buf = strpprintf(0, "SDL_FPoint(%f,%f)", point.x, point.y);
	RETVAL_STR(buf);
}

/* {{{ proto bool SDL_RectEmpty(SDL_Rect rect)

 *  \brief Returns true if the rectangle has no area.
 SDL_FORCE_INLINE SDL_bool SDL_RectEmpty(const SDL_Rect *r)
 */
PHP_FUNCTION(SDL_RectEmpty)
{
	zval *object;
	SDL_Rect rect;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_rect_ce) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(object, &rect);

	RETURN_BOOL(SDL_RectEmpty(&rect));
}
/* }}} */

PHP_FUNCTION(SDL_FRectEmpty)
{
	zval *object;
	SDL_FRect rect;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_frect_ce) == FAILURE)
	{
		return;
	}
	zval_to_sdl_frect(object, &rect);

	RETURN_BOOL((rect.w <= 0.0f) || (rect.h <= 0.0f));
}

/* {{{ proto bool SDL_RectEquals(SDL_Rect a, SDL_Rect b)

 *  \brief Returns true if the two rectangles are equal.
 SDL_FORCE_INLINE SDL_bool SDL_RectEquals(const SDL_Rect *a, const SDL_Rect *b)
 */
PHP_FUNCTION(SDL_RectEquals)
{
	zval *obj1, *obj2;
	SDL_Rect rect1, rect2;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce) == FAILURE)
	{
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

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);

	RETURN_BOOL(SDL_HasIntersection(&rect1, &rect2));
}
/* }}} */

PHP_FUNCTION(SDL_HasIntersectionF)
{
	zval *obj1, *obj2;
	SDL_FRect A, B;
	float Amin, Amax, Bmin, Bmax;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &obj1, php_sdl_frect_ce, &obj2, php_sdl_frect_ce) == FAILURE)
	{
		return;
	}
	zval_to_sdl_frect(obj1, &A);
	zval_to_sdl_frect(obj2, &B);

	/** SDL_HasIntersectionF not yet available as public API (SDL <= 2.0.20) */
	/* Horizontal intersection */
	Amin = A.x;
	Amax = Amin + A.w;
	Bmin = B.x;
	Bmax = Bmin + B.w;
	if (Bmin > Amin)
	{
		Amin = Bmin;
	}
	if (Bmax < Amax)
	{
		Amax = Bmax;
	}
	if (Amax <= Amin)
	{
		RETURN_FALSE;
	}

	/* Vertical intersection */
	Amin = A.y;
	Amax = Amin + A.h;
	Bmin = B.y;
	Bmax = Bmin + B.h;
	if (Bmin > Amin)
	{
		Amin = Bmin;
	}
	if (Bmax < Amax)
	{
		Amax = Bmax;
	}
	if (Amax <= Amin)
	{
		RETURN_FALSE;
	}

	RETURN_TRUE;
	//	RETURN_BOOL(SDL_HasIntersectionF(&rect1, &rect2));
}

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

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOz/", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce, &result) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	if (SDL_IntersectRect(&rect1, &rect2, &rect3))
	{
		zval_ptr_dtor(result);
		sdl_rect_to_zval(&rect3, result);
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

PHP_FUNCTION(SDL_IntersectFRect)
{
	zval *obj1, *obj2, *result;
	SDL_FRect A, B, resultRect;
	float Amin, Amax, Bmin, Bmax;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOz/", &obj1, php_sdl_frect_ce, &obj2, php_sdl_frect_ce, &result) == FAILURE)
	{
		return;
	}
	zval_to_sdl_frect(obj1, &A);
	zval_to_sdl_frect(obj2, &B);

	/** SDL_IntersectFRect does not exists (SDL <= 2.0.20) */
	/* Special cases for empty rects */
	if ((A.w <= 0.0f) || (A.h <= 0.0f) || (B.w <= 0.0f) || (B.h <= 0.0f))
	{
		resultRect.w = 0;
		resultRect.h = 0;

		zval_ptr_dtor(result);
		sdl_frect_to_zval(&resultRect, result);

		RETURN_FALSE;
	}

	/* Horizontal intersection */
	Amin = A.x;
	Amax = Amin + A.w;
	Bmin = B.x;
	Bmax = Bmin + B.w;
	if (Bmin > Amin)
		Amin = Bmin;
	resultRect.x = Amin;
	if (Bmax < Amax)
		Amax = Bmax;
	resultRect.w = Amax - Amin;

	/* Vertical intersection */
	Amin = A.y;
	Amax = Amin + A.h;
	Bmin = B.y;
	Bmax = Bmin + B.h;
	if (Bmin > Amin)
		Amin = Bmin;
	resultRect.y = Amin;
	if (Bmax < Amax)
		Amax = Bmax;
	resultRect.h = Amax - Amin;

	if (!((resultRect.w <= 0.0f) || (resultRect.h <= 0.0f)))
	{ // !SDL_FRectEmpty
		zval_ptr_dtor(result);
		sdl_frect_to_zval(&resultRect, result);

		RETURN_TRUE;
	}

	RETURN_FALSE;
}

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

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOz/", &obj1, php_sdl_rect_ce, &obj2, php_sdl_rect_ce, &result) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(obj1, &rect1);
	zval_to_sdl_rect(obj2, &rect2);
	SDL_UnionRect(&rect1, &rect2, &rect3);
	zval_ptr_dtor(result);
	sdl_rect_to_zval(&rect3, result);
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
	zval *z_points, *z_clip, *z_result, *z_point;
	long i;
	zend_long count;
	int nb;
	SDL_Rect clip, result;
	SDL_Point *points;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "alOz/", &z_points, &count, &z_clip, php_sdl_rect_ce, &z_result) == FAILURE)
	{
		return;
	}
	RETVAL_FALSE;

	if (count <= 0)
	{
		count = zend_hash_next_free_element(Z_ARRVAL_P(z_points));
	}
	points = emalloc(sizeof(SDL_Point) * count);

	zval_to_sdl_rect(z_clip, &clip);
	for (i = 0, nb = 0; i < count; i++)
	{
		if (!(z_point = zend_hash_index_find(Z_ARRVAL_P(z_points), i)))
		{
			php_error_docref(NULL, E_WARNING, "point #%ld missing", i);
		}
		else if (Z_TYPE(*z_point) != IS_OBJECT || Z_OBJCE_P(z_point) != php_sdl_point_ce)
		{
			php_error_docref(NULL, E_WARNING, "point #%ld is not a SDL_Point object", i);
		}
		else
		{
			zval_to_sdl_point(z_point, points + nb);
			nb++;
		}
	}

	if (!nb)
	{
		php_error_docref(NULL, E_WARNING, "no point in provided array");
	}
	else if (SDL_EnclosePoints(points, nb, &clip, &result))
	{
		zval_ptr_dtor(z_result);
		sdl_rect_to_zval(&result, z_result);
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

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz/z/z/z/", &object, php_sdl_rect_ce, &z_x1, &z_y1, &z_x2, &z_y2) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(object, &rect);
	convert_to_long_ex(z_x1);
	convert_to_long_ex(z_y1);
	convert_to_long_ex(z_x2);
	convert_to_long_ex(z_y2);
	x1 = (int)Z_LVAL_P(z_x1);
	y1 = (int)Z_LVAL_P(z_y1);
	x2 = (int)Z_LVAL_P(z_x2);
	y2 = (int)Z_LVAL_P(z_y2);

	if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
	{
		Z_LVAL_P(z_x1) = x1;
		Z_LVAL_P(z_y1) = y1;
		Z_LVAL_P(z_x2) = x2;
		Z_LVAL_P(z_y2) = y2;
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

PHP_FUNCTION(SDL_PointInRect)
{
	zval *z_point, *z_rect;
	SDL_Point point;
	SDL_Rect rect;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &z_point, php_sdl_point_ce, &z_rect, php_sdl_rect_ce) == FAILURE)
	{
		return;
	}
	zval_to_sdl_rect(z_rect, &rect);
	zval_to_sdl_point(z_point, &point);

	if (SDL_PointInRect(&point, &rect))
	{
		RETURN_TRUE;
	}
	RETURN_FALSE;
}

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_rect)
{
	zend_register_functions(NULL, ext_functions, NULL, type);

	php_sdl_rect_ce = register_class_SDL_Rect();
	memcpy(&php_sdl_rect_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_sdl_frect_ce = register_class_SDL_FRect();
	memcpy(&php_sdl_frect_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_sdl_point_ce = register_class_SDL_Point();
	memcpy(&php_sdl_point_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_sdl_fpoint_ce = register_class_SDL_FPoint();
	memcpy(&php_sdl_fpoint_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(sdl_rect)
{
	zend_unregister_functions(ext_functions, -1, NULL);

	return SUCCESS;
}
/* }}} */
