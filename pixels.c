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
  | wrapper for SDL2/SDL_pixels.h                                        |
  +----------------------------------------------------------------------+
  | class SDL_Color                                                      |
  | class SDL_Palette                                                    |
  | class SDL_PixelFormat                                                |
  | class SDL_Pixels (PHP specific for memory access)                    |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "pixels.h"

static zend_class_entry *php_sdl_color_ce;
static zend_object_handlers php_sdl_color_handlers;
struct php_sdl_color {
	zend_object   zo;
};

static zend_class_entry *php_sdl_palette_ce;
static zend_object_handlers php_sdl_palette_handlers;
struct php_sdl_palette {
	zend_object   zo;
	SDL_Palette   *palette;
	Uint32        flags;
};

static zend_class_entry *php_sdl_pixelformat_ce;
static zend_object_handlers php_sdl_pixelformat_handlers;
struct php_sdl_pixelformat {
	zend_object      zo;
	SDL_PixelFormat *format;
	Uint32           flags;
};

static zend_class_entry *php_sdl_pixels_ce;
static zend_object_handlers php_sdl_pixels_handlers;
struct php_sdl_pixels {
	zend_object      zo;
	SDL_Pixels       pixels;
	Uint32           flags;
};

zend_class_entry *get_php_sdl_color_ce(void)
{
	return php_sdl_color_ce;
}

zend_class_entry *get_php_sdl_pixelformat_ce(void)
{
	return php_sdl_pixelformat_ce;
}

zend_class_entry *get_php_sdl_palette_ce(void)
{
	return php_sdl_palette_ce;
}

zend_class_entry *get_php_sdl_pixels_ce(void)
{
	return php_sdl_pixels_ce;
}

#define FETCH_PALETTE(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_palette *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->palette; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

#define FETCH_PIXELFORMAT(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_pixelformat *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->format; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

zend_bool sdl_color_to_zval(SDL_Color *color, zval *value TSRMLS_DC)
{
	if (color) {
		object_init_ex(value, php_sdl_color_ce);
		zend_update_property_long(php_sdl_color_ce, value, "r", 1, color->r TSRMLS_CC);
		zend_update_property_long(php_sdl_color_ce, value, "g", 1, color->g TSRMLS_CC);
		zend_update_property_long(php_sdl_color_ce, value, "b", 1, color->b TSRMLS_CC);
		zend_update_property_long(php_sdl_color_ce, value, "a", 1, color->a TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool zval_to_sdl_color(zval *value, SDL_Color *color TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_color_ce) {
		zval *val;

		val = zend_read_property(php_sdl_color_ce, value, "r", 1, 0 TSRMLS_CC);
		color->r = (Uint8)Z_LVAL_P(val);
		val = zend_read_property(php_sdl_color_ce, value, "g", 1, 0 TSRMLS_CC);
		color->g = (Uint8)Z_LVAL_P(val);
		val = zend_read_property(php_sdl_color_ce, value, "b", 1, 0 TSRMLS_CC);
		color->b = (Uint8)Z_LVAL_P(val);
		val = zend_read_property(php_sdl_color_ce, value, "a", 1, 0 TSRMLS_CC);
		color->a = (Uint8)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty color */
	memset(color, 0, sizeof(SDL_Color));
	return 0;
}


/* {{{ sdl_palette_to_zval */
zend_bool sdl_palette_to_zval(SDL_Palette *palette, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (palette) {
		struct php_sdl_palette *intern;

		object_init_ex(z_val, php_sdl_palette_ce);
		intern = (struct php_sdl_palette *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->palette = palette;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ sdl_pixelformat_to_zval */
zend_bool sdl_pixelformat_to_zval(SDL_PixelFormat *format, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (format) {
		struct php_sdl_pixelformat *intern;

		object_init_ex(z_val, php_sdl_pixelformat_ce);
		intern = (struct php_sdl_pixelformat *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->format = format;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ sdl_pixels_to_zval */
zend_bool sdl_pixels_to_zval(SDL_Pixels *pixels, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (pixels) {
		struct php_sdl_pixels *intern;

		object_init_ex(z_val, php_sdl_pixels_ce);
		intern = (struct php_sdl_pixels *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->pixels = *pixels;
		intern->flags  = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_pixelformat */
SDL_PixelFormat *zval_to_sdl_pixelformat(zval *z_val TSRMLS_DC)
{
	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_pixelformat_ce) {
		struct php_sdl_pixelformat *intern;

		intern = (struct php_sdl_pixelformat *)zend_object_store_get_object(z_val TSRMLS_CC);
		return intern->format;
		}
	return NULL;
}
/* }}} */

/* {{{ zval_to_sdl_pixels */
SDL_Pixels *zval_to_sdl_pixels(zval *z_val TSRMLS_DC)
{
	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_pixels_ce) {
		struct php_sdl_pixels *intern;

		intern = (struct php_sdl_pixels *)zend_object_store_get_object(z_val TSRMLS_CC);
		return &intern->pixels;
		}
	return NULL;
}
/* }}} */

/* {{{ zval_to_sdl_palette */
SDL_Palette *zval_to_sdl_palette(zval *z_val TSRMLS_DC)
{
	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_palette_ce) {
		struct php_sdl_palette *intern;

		intern = (struct php_sdl_palette *)zend_object_store_get_object(z_val TSRMLS_CC);
		return intern->palette;
		}
	return NULL;
}
/* }}} */

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



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetPixelFormatName, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

/* {{{ proto string SDL_GetPixelFormatName(int format)

 * \brief Get the human readable name of a pixel format
 extern DECLSPEC const char* SDLCALL SDL_GetPixelFormatName(Uint32 format);
 */
PHP_FUNCTION(SDL_GetPixelFormatName)
{
	long format;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &format) == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetPixelFormatName((Uint32)format);
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name, 1);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormatEnumToMasks, 0, 0, 6)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(1, bpp)
       ZEND_ARG_INFO(1, Rmask)
       ZEND_ARG_INFO(1, Gmask)
       ZEND_ARG_INFO(1, Bmask)
       ZEND_ARG_INFO(1, Amask)
ZEND_END_ARG_INFO()

/* {{{ proto bool SDL_PixelFormatEnumToMasks(int format, int &bpp, int &Rmask, int &Gmask, int &Bmask, int &Amask)

 *  \brief Convert one of the enumerated pixel formats to a bpp and RGBA masks.
 *
 *  \return SDL_TRUE, or SDL_FALSE if the conversion wasn't possible.
 *
 *  \sa SDL_MasksToPixelFormatEnum()
 extern DECLSPEC SDL_bool SDLCALL SDL_PixelFormatEnumToMasks(Uint32 format,
                                                             int *bpp,
                                                             Uint32 * Rmask,
                                                             Uint32 * Gmask,
                                                             Uint32 * Bmask,
                                                             Uint32 * Amask);
 */
PHP_FUNCTION(SDL_PixelFormatEnumToMasks)
{
	zval *z_bpp, *z_rmask, *z_gmask, *z_bmask, *z_amask;
	long format;
	int bpp;
	Uint32 rmask, gmask, bmask, amask;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lzzzzz", &format, &z_bpp, &z_rmask, &z_gmask, &z_bmask, &z_amask) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_PixelFormatEnumToMasks((Uint32)format, &bpp, &rmask, &gmask, &bmask, &amask)) {
		zval_dtor(z_bpp);
		ZVAL_LONG(z_bpp, bpp);
		zval_dtor(z_rmask);
		ZVAL_LONG(z_rmask, rmask);
		zval_dtor(z_gmask);
		ZVAL_LONG(z_gmask, gmask);
		zval_dtor(z_bmask);
		ZVAL_LONG(z_bmask, bmask);
		zval_dtor(z_amask);
		ZVAL_LONG(z_amask, amask);

		RETURN_TRUE;
	}
	RETURN_FALSE;;
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MasksToPixelFormatEnum, 0, 0, 5)
       ZEND_ARG_INFO(0, bpp)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()

/* {{{ proto bool SDL_MasksToPixelFormatEnum(int format, int bpp, int Rmask, int Gmask, int Bmask, int Amask)
 *  \brief Convert a bpp and RGBA masks to an enumerated pixel format.
 *
 *  \return The pixel format, or ::SDL_PIXELFORMAT_UNKNOWN if the conversion
 *          wasn't possible.
 *
 *  \sa SDL_PixelFormatEnumToMasks()
 extern DECLSPEC Uint32 SDLCALL SDL_MasksToPixelFormatEnum(int bpp,
                                                           Uint32 Rmask,
                                                           Uint32 Gmask,
                                                           Uint32 Bmask,
                                                           Uint32 Amask);
 */
PHP_FUNCTION(SDL_MasksToPixelFormatEnum)
{
	long bpp, rmask, gmask, bmask, amask;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllll", &bpp, &rmask, &gmask, &bmask, &amask) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_MasksToPixelFormatEnum((int)bpp, (Uint32)rmask, (Uint32)gmask, (Uint32)bmask, (Uint32)amask));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_AllocFormat, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Palette SDL_AllocFormat(int ncolors)

 *  \brief Create an SDL_PixelFormat structure from a pixel format enum.
 extern DECLSPEC SDL_PixelFormat * SDLCALL SDL_AllocFormat(Uint32 pixel_format);
 */
PHP_FUNCTION(SDL_AllocFormat)
{
	long index;
	SDL_PixelFormat *format;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	format = SDL_AllocFormat((Uint32)index);
	sdl_pixelformat_to_zval(format, return_value, 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto SDL_PixelFormat, __construct(format)
 */
static PHP_METHOD(SDL_PixelFormat, __construct)
{
	struct php_sdl_pixelformat *intern;
	long format;
	zend_error_handling error_handling;

	intern = (struct php_sdl_pixelformat *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &format)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->format = SDL_AllocFormat((Uint32)format);
	if (intern->format) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), SDL_GetError(), 0 TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto void SDL_FreeFormat(SDL_PixelFormat format)

 *  \brief Free an SDL_PixelFormat structure.
 extern DECLSPEC void SDLCALL SDL_FreeFormat(SDL_PixelFormat *format);
 */
PHP_FUNCTION(SDL_FreeFormat)
{
	struct php_sdl_pixelformat *intern;
	zval *object;
	SDL_PixelFormat *format;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_pixelformat_ce) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, object, 1);

	SDL_FreeFormat(intern->format);
	intern->format = NULL;
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_AllocPalette, 0, 0, 1)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Palette SDL_AllocPalette(int ncolors)

 *  \brief Create a palette structure with the specified number of color
 *         entries.
 *
 *  \return A new palette, or NULL if there wasn't enough memory.
 *
 *  \note The palette entries are initialized to white.
 *
 *  \sa SDL_FreePalette()
 extern DECLSPEC SDL_Palette *SDLCALL SDL_AllocPalette(int ncolors);
*/
PHP_FUNCTION(SDL_AllocPalette)
{
	long ncolors;
	SDL_Palette *palette;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ncolors)) {
		return;
	}
	palette = SDL_AllocPalette(ncolors);
	sdl_palette_to_zval(palette, return_value, 0 TSRMLS_CC);
}
/* }}} */

/* {{{ proto SDL_Palette, __construct(ncolors)
 */
static PHP_METHOD(SDL_Palette, __construct)
{
	struct php_sdl_palette *intern;
	long ncolors;
	zend_error_handling error_handling;

	intern = (struct php_sdl_palette *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ncolors)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->palette = SDL_AllocPalette(ncolors);
	if (intern->palette) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), SDL_GetError(), 0 TSRMLS_CC);
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetPixelFormatPalette, 0, 0, 2)
       ZEND_ARG_INFO(0, pixelformat)
       ZEND_ARG_INFO(0, palette)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_SetPalette, 0, 0, 1)
       ZEND_ARG_INFO(0, palette)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_SetPixelFormatPalette(SDL_PixelFormat format, SDL_Palette palette);

 *  \brief Set the palette for a pixel format structure.
 extern DECLSPEC int SDLCALL SDL_SetPixelFormatPalette(SDL_PixelFormat * format,
                                                       SDL_Palette *palette);
 */
PHP_FUNCTION(SDL_SetPixelFormatPalette)
{
	struct php_sdl_palette *intern;
	zval *z_format, *z_palette;
	SDL_Palette *palette;
	SDL_PixelFormat *format;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &z_format, php_sdl_pixelformat_ce, &z_palette, php_sdl_palette_ce) == FAILURE) {
		return;
	}
	FETCH_PALETTE(palette, z_palette, 1);
	format = zval_to_sdl_pixelformat(z_format);

	RETURN_LONG(SDL_SetPixelFormatPalette(format, palette));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetPaletteColors, 0, 0, 2)
       ZEND_ARG_INFO(0, palette)
       ZEND_ARG_INFO(0, colors)
       ZEND_ARG_INFO(0, first)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette_SetColors, 0, 0, 1)
       ZEND_ARG_INFO(0, colors)
       ZEND_ARG_INFO(0, first)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_SetPaletteColors(SDL_Palette palette, array colors, int first, int ncolors)

 *  \brief Set a range of colors in a palette.
 *
 *  \param palette    The palette to modify.
 *  \param colors     An array of colors to copy into the palette.
 *  \param firstcolor The index of the first palette entry to modify.
 *  \param ncolors    The number of entries to modify.
 *
 *  \return 0 on success, or -1 if not all of the colors could be set.
 extern DECLSPEC int SDLCALL SDL_SetPaletteColors(SDL_Palette * palette,
                                                  const SDL_Color * colors,
                                                  int firstcolor, int ncolors);
 */
PHP_FUNCTION(SDL_SetPaletteColors)
{
	struct php_sdl_palette *intern;
	zval *object, *z_colors, **z_color;
	SDL_Palette *palette;
	SDL_Color *colors;
	int i, nb;
	long first=0, ncolors=0, count;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa|ll", &object, php_sdl_palette_ce, &z_colors, &first, &ncolors) == FAILURE) {
		return;
	}
	FETCH_PALETTE(palette, object, 1);
	count = zend_hash_next_free_element(Z_ARRVAL_P(z_colors));

	if (ncolors <= 0) {
		ncolors = count;
	} else if (ncolors > count) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Invalid color number, %ld will be used instead of %ld", count, ncolors);
		ncolors = count;
	}
	if (first >= intern->palette->ncolors) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid first color index, %ld >= %d", first, intern->palette->ncolors);
		RETURN_LONG(-1);
	}
	if (first+ncolors > intern->palette->ncolors) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid color number, %ld > %d", first+ncolors, intern->palette->ncolors);
		RETURN_LONG(-1);
	}
	colors = emalloc(sizeof(SDL_Color) * ncolors);
	for (nb=i=0 ; i<ncolors ; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(z_colors), i, (void **)&z_color) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Unable to find colors[%d]", i);

		} else if (Z_TYPE_PP(z_color) != IS_OBJECT || Z_OBJCE_PP(z_color) != php_sdl_color_ce) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "colors[%d] is not a SDL_Color object", i);
		} else {
			zval_to_sdl_color(*z_color, colors+nb TSRMLS_CC);
			nb++;
		}
	}
	if (nb) {
		RETVAL_LONG(SDL_SetPaletteColors(palette, colors, (int)first, nb));
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "no color in provided array");
		RETVAL_LONG(-1);
	}
	efree(colors);
}
/* }}} */


/* {{{ proto void SDL_FreePalette(SDL_Palette palette)

 *  \brief Free a palette created with SDL_AllocPalette().
 *
 *  \sa SDL_AllocPalette()
 extern DECLSPEC void SDLCALL SDL_FreePalette(SDL_Palette * palette);
 */
PHP_FUNCTION(SDL_FreePalette)
{
	struct php_sdl_palette *intern;
	zval *object;
	SDL_Palette *palette;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_palette_ce) == FAILURE) {
		return;
	}
	FETCH_PALETTE(palette, object, 1);

	SDL_FreePalette(intern->palette);
	intern->palette = NULL;
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MapRGB, 0, 0, 4)
       ZEND_ARG_INFO(0, pixelformat)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_MapRGB, 0, 0, 3)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_MapRGB(SDL_PixelFormat format, int r, int g, int b)

 *  \brief Maps an RGB triple to an opaque pixel value for a given pixel format.
 *
 *  \sa SDL_MapRGBA
 extern DECLSPEC Uint32 SDLCALL SDL_MapRGB(const SDL_PixelFormat * format,
                                           Uint8 r, Uint8 g, Uint8 b);
 */
PHP_FUNCTION(SDL_MapRGB)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format;
	SDL_PixelFormat *format;
	long r, g, b;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olll", &z_format, php_sdl_pixelformat_ce, &r, &g, &b) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);

	RETURN_LONG(SDL_MapRGB(format, (Uint8)r, (Uint8)g, (Uint8)b));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MapRGBA, 0, 0, 5)
       ZEND_ARG_INFO(0, pixelformat)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
       ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_MapRGBA, 0, 0, 4)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
       ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_MapRGBA(SDL_PixelFormat format, int r, int g, int b, int a)

 *  \brief Maps an RGBA quadruple to a pixel value for a given pixel format.
 *
 *  \sa SDL_MapRGB
 extern DECLSPEC Uint32 SDLCALL SDL_MapRGBA(const SDL_PixelFormat * format,
                                            Uint8 r, Uint8 g, Uint8 b,
                                            Uint8 a);
 */
PHP_FUNCTION(SDL_MapRGBA)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format;
	SDL_PixelFormat *format;
	long r, g, b, a;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ollll", &z_format, php_sdl_pixelformat_ce, &r, &g, &b, &a) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);

	RETURN_LONG(SDL_MapRGBA(format, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetRGB, 0, 0, 5)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(0, pixelformat)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
ZEND_END_ARG_INFO()

/* {{{ proto void SDL_GetRGB(int pixel, SDL_PixelFormat format, int &r, int &g, int &b)

 *  \brief Get the RGB components from a pixel of the specified format.
 *
 *  \sa SDL_GetRGBA
 extern DECLSPEC void SDLCALL SDL_GetRGB(Uint32 pixel,
                                         const SDL_PixelFormat * format,
                                         Uint8 * r, Uint8 * g, Uint8 * b);
 */
PHP_FUNCTION(SDL_GetRGB)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format, *z_r, *z_g, *z_b;
	SDL_PixelFormat *format;
	Uint8 r, g, b;
	long pix;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "lOzzz", &pix, &z_format, php_sdl_pixelformat_ce, &z_r, &z_g, &z_b) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);
	SDL_GetRGB((Uint32)pix, format, &r, &g, &b);
	zval_dtor(z_r);
	ZVAL_LONG(z_r, r);
	zval_dtor(z_g);
	ZVAL_LONG(z_g, g);
	zval_dtor(z_b);
	ZVAL_LONG(z_b, b);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_GetRGB, 0, 0, 4)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_PixelFormat::GetRGB(int pixel, int &r, int &g, int &b)

 Duplicate implementation because for param order
*/
PHP_METHOD(SDL_PixelFormat, GetRGB)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format, *z_r, *z_g, *z_b;
	SDL_PixelFormat *format;
	Uint8 r, g, b;
	long pix;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olzzz", &z_format, php_sdl_pixelformat_ce, &pix, &z_r, &z_g, &z_b) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);
	SDL_GetRGB((Uint32)pix, format, &r, &g, &b);
	zval_dtor(z_r);
	ZVAL_LONG(z_r, r);
	zval_dtor(z_g);
	ZVAL_LONG(z_g, g);
	zval_dtor(z_b);
	ZVAL_LONG(z_b, b);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetRGBA, 0, 0, 6)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(0, pixelformat)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
       ZEND_ARG_INFO(1, a)
ZEND_END_ARG_INFO()

/* {{{ proto void SDL_GetRGBA(int pixel, SDL_PixelFormat format, int &r, int &g, int &b, int &a)

 *  \brief Get the RGBA components from a pixel of the specified format.
 *
 *  \sa SDL_GetRGB
 extern DECLSPEC void SDLCALL SDL_GetRGBA(Uint32 pixel,
                                          const SDL_PixelFormat * format,
                                          Uint8 * r, Uint8 * g, Uint8 * b,
                                          Uint8 * a);
 */
PHP_FUNCTION(SDL_GetRGBA)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format, *z_r, *z_g, *z_b, *z_a;
	SDL_PixelFormat *format;
	Uint8 r, g, b, a;
	long pix;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "lOzzzz", &pix, &z_format, php_sdl_pixelformat_ce, &z_r, &z_g, &z_b, &z_a) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);
	SDL_GetRGBA((Uint32)pix, format, &r, &g, &b, &a);
	zval_dtor(z_r);
	ZVAL_LONG(z_r, r);
	zval_dtor(z_g);
	ZVAL_LONG(z_g, g);
	zval_dtor(z_b);
	ZVAL_LONG(z_b, b);
	zval_dtor(z_a);
	ZVAL_LONG(z_a, a);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_GetRGBA, 0, 0, 5)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
       ZEND_ARG_INFO(1, a)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_PixelFormat::GetRGBA(int pixel, int &r, int &g, int &b, int &a)

 Duplicate implementation because for param order
*/
PHP_METHOD(SDL_PixelFormat, GetRGBA)
{
	struct php_sdl_pixelformat *intern;
	zval *z_format, *z_r, *z_g, *z_b, *z_a;
	SDL_PixelFormat *format;
	Uint8 r, g, b, a;
	long pix;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olzzzz", &z_format, php_sdl_pixelformat_ce, &pix, &z_r, &z_g, &z_b, &z_a) == FAILURE) {
		return;
	}
	FETCH_PIXELFORMAT(format, z_format, 1);
	SDL_GetRGBA((Uint32)pix, format, &r, &g, &b, &a);
	zval_dtor(z_r);
	ZVAL_LONG(z_r, r);
	zval_dtor(z_g);
	ZVAL_LONG(z_g, g);
	zval_dtor(z_b);
	ZVAL_LONG(z_b, b);
	zval_dtor(z_a);
	ZVAL_LONG(z_a, a);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CalculateGammaRamp, 0, 0, 2)
       ZEND_ARG_INFO(0, gamma)
       ZEND_ARG_INFO(1, ramp)
ZEND_END_ARG_INFO()

/* {{{ proto void SDL_CalculateGammaRamp(float gamma, array &ramp)

 *  \brief Calculate a 256 entry gamma ramp for a gamma value.
 extern DECLSPEC void SDLCALL SDL_CalculateGammaRamp(float gamma, Uint16 * ramp);
 */
PHP_FUNCTION(SDL_CalculateGammaRamp)
{
	double gamma;
	zval *z_ramp, *zv;
	Uint16 ramp[256];
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dz", &gamma, &z_ramp) == FAILURE) {
		RETURN_FALSE;
	}
	SDL_CalculateGammaRamp((float)gamma, ramp);
	zval_dtor(z_ramp);
	array_init(z_ramp);
	for (i=0 ; i<256 ; i++) {
		MAKE_STD_ZVAL(zv);
		ZVAL_LONG(zv, ramp[i]);
		add_next_index_zval(z_ramp, zv);
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Pixels__construct, 0, 0, 2)
       ZEND_ARG_INFO(0, pitch)
       ZEND_ARG_INFO(0, h)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Pixels, __construct(int pitch, int h)
 */
static PHP_METHOD(SDL_Pixels, __construct)
{
	struct php_sdl_pixels *intern;
	long pitch, h;
	zend_error_handling error_handling;

	intern = (struct php_sdl_pixels *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &pitch, &h)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	if (php_sdl_check_overflow(pitch, h, 1)) {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Invalid size", 0 TSRMLS_CC);
	} else {
		if (pitch & 3) {
			pitch = (pitch + 3) & ~3;
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Pitch set to %ld", pitch);
		}
		intern->pixels.pixels = ecalloc(pitch, h);
		intern->pixels.pitch  = pitch;
		intern->pixels.h      = h;
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Pixels_GetByte, 0, 0, 2)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_Pixels::GetByte(int x, int y)
*/
PHP_METHOD(SDL_Pixels, GetByte)
{
	struct php_sdl_pixels *intern;
	zval *z_pixels;
	long x, y;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &z_pixels, php_sdl_pixels_ce, &x, &y) == FAILURE) {
		return;
	}
	intern = (struct php_sdl_pixels *)zend_object_store_get_object(z_pixels TSRMLS_CC);\

	if (x < 0 || x >= intern->pixels.pitch || y < 0 || y >= intern->pixels.h) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Invalid position (%ld,%ld) in SDL_Pixels (%d,%d)", x, y, intern->pixels.pitch, intern->pixels.h);
		RETURN_FALSE;
	}
	RETVAL_LONG(intern->pixels.pixels[y*intern->pixels.pitch+x]);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Pixels_SetByte, 0, 0, 3)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, byte)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_Pixels::SetByte(int x, int y, int byte)
*/
PHP_METHOD(SDL_Pixels, SetByte)
{
	struct php_sdl_pixels *intern;
	zval *z_pixels;
	long x, y, v;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Olll", &z_pixels, php_sdl_pixels_ce, &x, &y, &v) == FAILURE) {
		return;
	}
	intern = (struct php_sdl_pixels *)zend_object_store_get_object(z_pixels TSRMLS_CC);\

	if (x < 0 || x >= intern->pixels.pitch || y < 0 || y >= intern->pixels.h) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Invalid position (%ld,%ld) in SDL_Pixels (%d,%d)", x, y, intern->pixels.pitch, intern->pixels.h);
		RETURN_FALSE;
	}
	RETVAL_LONG(intern->pixels.pixels[y*intern->pixels.pitch+x]);
	intern->pixels.pixels[y*intern->pixels.pitch+x] = (Uint8)v;
}
/* }}} */



/* {{{ php_sdl_palette_free
	 */
static void php_sdl_palette_free(void *object TSRMLS_DC)
{
	struct php_sdl_palette *intern = (struct php_sdl_palette *) object;

	if (intern->palette) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_FreePalette(intern->palette);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_palette_new
 */
static zend_object_value php_sdl_palette_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_palette *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->palette = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_palette_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_palette_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_palette_read_property*/
zval *sdl_palette_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
{
	struct php_sdl_palette *intern = (struct php_sdl_palette *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval, tmp_member;

	if (!intern->palette) {
		return (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
	}

	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		key = NULL;
	}

	ALLOC_INIT_ZVAL(retval);
	Z_SET_REFCOUNT_P(retval, 0);

	if (!strcmp(Z_STRVAL_P(member), "ncolors")) {
		ZVAL_LONG(retval, intern->palette->ncolors);

	} else if (!strcmp(Z_STRVAL_P(member), "version")) {
		ZVAL_LONG(retval, intern->palette->version);

	} else if (!strcmp(Z_STRVAL_P(member), "refcount")) {
		ZVAL_LONG(retval, intern->palette->refcount);

	} else if (!strcmp(Z_STRVAL_P(member), "colors")) {
		int i;
		zval *z_color;
		array_init(retval);
		for (i=0 ; i<intern->palette->ncolors ; i++) {
			MAKE_STD_ZVAL(z_color);
			sdl_color_to_zval(&intern->palette->colors[i], z_color  TSRMLS_CC);
			add_next_index_zval(retval, z_color);
		}

	} else {
		FREE_ZVAL(retval);

		retval = (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
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

#define SDL_PALETTE_ADD_PROPERTY(n,f) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_LONG(zv, (long)f); \
	zend_hash_update(props, n, sizeof(n), &zv, sizeof(zv), NULL)

/* {{{ sdl_palette_read_property*/
static HashTable *sdl_palette_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv, *z_color;
	int i;
	struct php_sdl_palette *intern = (struct php_sdl_palette *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->palette) {
		SDL_PALETTE_ADD_PROPERTY("ncolors",  intern->palette->ncolors);
		SDL_PALETTE_ADD_PROPERTY("version",  intern->palette->version);
		SDL_PALETTE_ADD_PROPERTY("refcount", intern->palette->refcount);

		MAKE_STD_ZVAL(zv);
		array_init(zv);
		for (i=0 ; i<intern->palette->ncolors ; i++) {
			MAKE_STD_ZVAL(z_color);
			sdl_color_to_zval(&intern->palette->colors[i], z_color  TSRMLS_CC);
			add_next_index_zval(zv, z_color);
		}
		zend_hash_update(props, "colors", sizeof("colors"), &zv, sizeof(zv), NULL);
	}
	return props;
}
/* }}} */

/* {{{ sdl_palette_write_property */
void sdl_palette_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported, use SDL_SetPaletteColors() or SDL_Palette::SetColors()");
}
/* }}} */

/* {{{ php_sdl_pixelformat_free
	 */
static void php_sdl_pixelformat_free(void *object TSRMLS_DC)
{
	struct php_sdl_pixelformat *intern = (struct php_sdl_pixelformat *) object;

	if (intern->format) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_FreeFormat(intern->format);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_pixelformat_new
 */
static zend_object_value php_sdl_pixelformat_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_pixelformat *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->format = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_pixelformat_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_pixelformat_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_pixelformat_read_property*/
zval *sdl_pixelformat_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
{
	struct php_sdl_pixelformat *intern = (struct php_sdl_pixelformat *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval, tmp_member;

	if (!intern->format) {
		return (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
	}

	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		key = NULL;
	}

	ALLOC_INIT_ZVAL(retval);
	Z_SET_REFCOUNT_P(retval, 0);

	if (!strcmp(Z_STRVAL_P(member), "format")) {
		ZVAL_LONG(retval, intern->format->format);

	} else if (!strcmp(Z_STRVAL_P(member), "BitsPerPixel")) {
		ZVAL_LONG(retval, intern->format->BitsPerPixel);

	} else if (!strcmp(Z_STRVAL_P(member), "BytesPerPixel")) {
		ZVAL_LONG(retval, intern->format->BytesPerPixel);

	} else if (!strcmp(Z_STRVAL_P(member), "Rmask")) {
		ZVAL_LONG(retval, intern->format->Rmask);

	} else if (!strcmp(Z_STRVAL_P(member), "Gmask")) {
		ZVAL_LONG(retval, intern->format->Gmask);

	} else if (!strcmp(Z_STRVAL_P(member), "Bmask")) {
		ZVAL_LONG(retval, intern->format->Bmask);

	} else if (!strcmp(Z_STRVAL_P(member), "Amask")) {
		ZVAL_LONG(retval, intern->format->Amask);

	} else if (!strcmp(Z_STRVAL_P(member), "Rloss")) {
		ZVAL_LONG(retval, intern->format->Rloss);

	} else if (!strcmp(Z_STRVAL_P(member), "Gloss")) {
		ZVAL_LONG(retval, intern->format->Gloss);

	} else if (!strcmp(Z_STRVAL_P(member), "Bloss")) {
		ZVAL_LONG(retval, intern->format->Bloss);

	} else if (!strcmp(Z_STRVAL_P(member), "Aloss")) {
		ZVAL_LONG(retval, intern->format->Aloss);

	} else if (!strcmp(Z_STRVAL_P(member), "Rshift")) {
		ZVAL_LONG(retval, intern->format->Rshift);

	} else if (!strcmp(Z_STRVAL_P(member), "Gshift")) {
		ZVAL_LONG(retval, intern->format->Gshift);

	} else if (!strcmp(Z_STRVAL_P(member), "Bshift")) {
		ZVAL_LONG(retval, intern->format->Bshift);

	} else if (!strcmp(Z_STRVAL_P(member), "Ashift")) {
		ZVAL_LONG(retval, intern->format->Ashift);

	} else if (!strcmp(Z_STRVAL_P(member), "palette")) {
		sdl_palette_to_zval(intern->format->palette, retval, SDL_DONTFREE);

	} else {
		FREE_ZVAL(retval);

		retval = (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
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

#define SDL_PIXELFORMAT_ADD_PROPERTY(n,f) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_LONG(zv, (long)f); \
	zend_hash_update(props, n, sizeof(n), &zv, sizeof(zv), NULL)

/* {{{ sdl_pixelformat_read_property*/
static HashTable *sdl_pixelformat_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv;
	struct php_sdl_pixelformat *intern = (struct php_sdl_pixelformat *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->format) {
		SDL_PIXELFORMAT_ADD_PROPERTY("format",        intern->format->format);
		SDL_PIXELFORMAT_ADD_PROPERTY("BitsPerPixel",  intern->format->BitsPerPixel);
		SDL_PIXELFORMAT_ADD_PROPERTY("BytesPerPixel", intern->format->BytesPerPixel);
		SDL_PIXELFORMAT_ADD_PROPERTY("Rmask",         intern->format->Rmask);
		SDL_PIXELFORMAT_ADD_PROPERTY("Gmask",         intern->format->Gmask);
		SDL_PIXELFORMAT_ADD_PROPERTY("Bmask",         intern->format->Bmask);
		SDL_PIXELFORMAT_ADD_PROPERTY("Amask",         intern->format->Amask);
		SDL_PIXELFORMAT_ADD_PROPERTY("Rloss",         intern->format->Rloss);
		SDL_PIXELFORMAT_ADD_PROPERTY("Gloss",         intern->format->Gloss);
		SDL_PIXELFORMAT_ADD_PROPERTY("Bloss",         intern->format->Bloss);
		SDL_PIXELFORMAT_ADD_PROPERTY("Aloss",         intern->format->Aloss);
		SDL_PIXELFORMAT_ADD_PROPERTY("Rshift",        intern->format->Rshift);
		SDL_PIXELFORMAT_ADD_PROPERTY("Gshift",        intern->format->Rshift);
		SDL_PIXELFORMAT_ADD_PROPERTY("Bshift",        intern->format->Rshift);
		SDL_PIXELFORMAT_ADD_PROPERTY("Ashift",        intern->format->Rshift);

		MAKE_STD_ZVAL(zv);
		sdl_palette_to_zval(intern->format->palette, zv, SDL_DONTFREE);
		zend_hash_update(props, "palette", sizeof("palette"), &zv, sizeof(zv), NULL);
	}
	return props;
}
/* }}} */

/* {{{ sdl_pixelformat_write_property */
void sdl_pixelformat_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported, SDL_PixelFormat is read-only");
}
/* }}} */

/* {{{ php_sdl_pixels_free
	 */
static void php_sdl_pixels_free(void *object TSRMLS_DC)
{
	struct php_sdl_pixels *intern = (struct php_sdl_pixels *) object;

	if (intern->pixels.pixels) {
		if (!(intern->flags & SDL_DONTFREE)) {
			efree(intern->pixels.pixels);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_pixels_new
 */
static zend_object_value php_sdl_pixels_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_pixels *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_pixels_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_pixels_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_pixels_read_property*/
zval *sdl_pixels_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
{
	struct php_sdl_pixels *intern = (struct php_sdl_pixels *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval, tmp_member;

	if (!intern->pixels.pixels) {
		return (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
	}

	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		key = NULL;
	}

	ALLOC_INIT_ZVAL(retval);
	Z_SET_REFCOUNT_P(retval, 0);

	if (!strcmp(Z_STRVAL_P(member), "h")) {
		ZVAL_LONG(retval, intern->pixels.h);

	} else if (!strcmp(Z_STRVAL_P(member), "pitch")) {
		ZVAL_LONG(retval, intern->pixels.pitch);

	} else {
		FREE_ZVAL(retval);

		retval = (zend_get_std_object_handlers())->read_property(object, member, type, key TSRMLS_CC);
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

#define SDL_PIXELS_ADD_PROPERTY(n,f) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_LONG(zv, (long)f); \
	zend_hash_update(props, n, sizeof(n), &zv, sizeof(zv), NULL)

/* {{{ sdl_pixels_read_properties */
static HashTable *sdl_pixels_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv;
	struct php_sdl_pixels *intern = (struct php_sdl_pixels *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->pixels.pixels) {
		SDL_PIXELS_ADD_PROPERTY("pitch",  intern->pixels.pitch);
		SDL_PIXELS_ADD_PROPERTY("h",      intern->pixels.h);
	}
	return props;
}
/* }}} */

/* {{{ sdl_pixels_write_property */
void sdl_pixels_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported, SDL_Pixels is read-only");
}
/* }}} */

/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_palette_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette, 0, 0, 1)
       ZEND_ARG_INFO(0, palette)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_format_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()


/* {{{ php_sdl_color_methods[] */
static const zend_function_entry php_sdl_color_methods[] = {
	PHP_ME(SDL_Color, __construct,     arginfo_SDL_Color__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_palette_methods[] */
static const zend_function_entry php_sdl_palette_methods[] = {
	PHP_ME(SDL_Palette, __construct,  arginfo_SDL_AllocPalette, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(Free,             SDL_FreePalette,           arginfo_palette_none)
	PHP_FALIAS(SetColors,        SDL_SetPaletteColors,      arginfo_SDL_Palette_SetColors)
	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_pixelformat_methods[] */
static const zend_function_entry php_sdl_pixelformat_methods[] = {
	PHP_ME(SDL_PixelFormat, __construct,  arginfo_SDL_AllocFormat,            ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_PixelFormat, GetRGB,       arginfo_SDL_PixelFormat_GetRGB,     ZEND_ACC_PUBLIC)
	PHP_ME(SDL_PixelFormat, GetRGBA,      arginfo_SDL_PixelFormat_GetRGBA,    ZEND_ACC_PUBLIC)

	PHP_FALIAS(Free,             SDL_FreeFormat,             arginfo_format_none)
	PHP_FALIAS(SetPalette,       SDL_SetPixelFormatPalette,  arginfo_SDL_PixelFormat_SetPalette)
	PHP_FALIAS(MapRGB,           SDL_MapRGB,                 arginfo_SDL_PixelFormat_MapRGB)
	PHP_FALIAS(MapRGBA,          SDL_MapRGBA,                arginfo_SDL_PixelFormat_MapRGBA)
	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_pixels_methods[] */
static const zend_function_entry php_sdl_pixels_methods[] = {
	PHP_ME(SDL_Pixels,    __construct,   arginfo_SDL_Pixels__construct,     ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Pixels,    GetByte,       arginfo_SDL_Pixels_GetByte,        ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Pixels,    SetByte,       arginfo_SDL_Pixels_SetByte,        ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ sdl_pixels_functions[] */
zend_function_entry sdl_pixels_functions[] = {
	ZEND_FE(SDL_GetPixelFormatName,					arginfo_SDL_GetPixelFormatName)
	ZEND_FE(SDL_PixelFormatEnumToMasks,				arginfo_SDL_PixelFormatEnumToMasks)
	ZEND_FE(SDL_MasksToPixelFormatEnum,				arginfo_SDL_MasksToPixelFormatEnum)

	ZEND_FE(SDL_AllocPalette,						arginfo_SDL_AllocPalette)
	ZEND_FE(SDL_FreePalette,						arginfo_SDL_Palette)
	ZEND_FE(SDL_SetPaletteColors,					arginfo_SDL_SetPaletteColors)

	ZEND_FE(SDL_AllocFormat,						arginfo_SDL_AllocFormat)
	ZEND_FE(SDL_FreeFormat,							arginfo_SDL_PixelFormat)
	ZEND_FE(SDL_SetPixelFormatPalette,				arginfo_SDL_SetPixelFormatPalette)
	ZEND_FE(SDL_MapRGB,								arginfo_SDL_MapRGB)
	ZEND_FE(SDL_MapRGBA,							arginfo_SDL_MapRGBA)
	ZEND_FE(SDL_GetRGB,								arginfo_SDL_GetRGB)
	ZEND_FE(SDL_GetRGBA,							arginfo_SDL_GetRGBA)
	ZEND_FE(SDL_CalculateGammaRamp,					arginfo_SDL_CalculateGammaRamp)
	ZEND_FE_END
};
/* }}} */

#define REGISTER_COLOR_PROP(name) \
	zend_declare_property_long(php_sdl_color_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

#define REGISTER_PALETTE_PROP(name) \
	zend_declare_property_long(php_sdl_palette_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

#define REGISTER_FORMAT_PROP(name) \
	zend_declare_property_long(php_sdl_pixelformat_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

#define REGISTER_PIXELS_PROP(name) \
	zend_declare_property_long(php_sdl_pixels_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_pixels)
{
	zend_class_entry ce_color, ce_palette, ce_format, ce_pixels;

	INIT_CLASS_ENTRY(ce_color, "SDL_Color", php_sdl_color_methods);
	php_sdl_color_ce = zend_register_internal_class(&ce_color TSRMLS_CC);
	memcpy(&php_sdl_color_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_COLOR_PROP("r");
	REGISTER_COLOR_PROP("g");
	REGISTER_COLOR_PROP("b");
	REGISTER_COLOR_PROP("a");

	INIT_CLASS_ENTRY(ce_palette, "SDL_Palette", php_sdl_palette_methods);
	ce_palette.create_object = php_sdl_palette_new;
	php_sdl_palette_ce = zend_register_internal_class(&ce_palette TSRMLS_CC);
	memcpy(&php_sdl_palette_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_palette_handlers.read_property  = sdl_palette_read_property;
	php_sdl_palette_handlers.get_properties = sdl_palette_get_properties;
	php_sdl_palette_handlers.write_property = sdl_palette_write_property;

	REGISTER_PALETTE_PROP("ncolors");
	REGISTER_PALETTE_PROP("version");
	REGISTER_PALETTE_PROP("refcount");
	zend_declare_property_null(php_sdl_palette_ce, "colors", sizeof("colors")-1, ZEND_ACC_PUBLIC TSRMLS_DC);

	INIT_CLASS_ENTRY(ce_format, "SDL_PixelFormat", php_sdl_pixelformat_methods);
	ce_format.create_object = php_sdl_pixelformat_new;
	php_sdl_pixelformat_ce = zend_register_internal_class(&ce_format TSRMLS_CC);
	memcpy(&php_sdl_pixelformat_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_pixelformat_handlers.read_property  = sdl_pixelformat_read_property;
	php_sdl_pixelformat_handlers.get_properties = sdl_pixelformat_get_properties;
	php_sdl_pixelformat_handlers.write_property = sdl_pixelformat_write_property;

	REGISTER_FORMAT_PROP("format");
	REGISTER_FORMAT_PROP("BitsPerPixel");
	REGISTER_FORMAT_PROP("BytesPerPixel");
	REGISTER_FORMAT_PROP("Rmask");
	REGISTER_FORMAT_PROP("Gmask");
	REGISTER_FORMAT_PROP("Bmask");
	REGISTER_FORMAT_PROP("Amask");
	REGISTER_FORMAT_PROP("Rloss");
	REGISTER_FORMAT_PROP("Gloss");
	REGISTER_FORMAT_PROP("Bloss");
	REGISTER_FORMAT_PROP("Aloss");
	REGISTER_FORMAT_PROP("Rshift");
	REGISTER_FORMAT_PROP("Gshift");
	REGISTER_FORMAT_PROP("Bshift");
	REGISTER_FORMAT_PROP("Ashift");
	zend_declare_property_null(php_sdl_pixelformat_ce, "palette", sizeof("palette")-1, ZEND_ACC_PUBLIC TSRMLS_DC);

	INIT_CLASS_ENTRY(ce_pixels, "SDL_Pixels", php_sdl_pixels_methods);
	ce_pixels.create_object = php_sdl_pixels_new;
	php_sdl_pixels_ce = zend_register_internal_class(&ce_pixels TSRMLS_CC);
	memcpy(&php_sdl_pixels_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_pixels_handlers.read_property  = sdl_pixels_read_property;
	php_sdl_pixels_handlers.get_properties = sdl_pixels_get_properties;
	php_sdl_pixels_handlers.write_property = sdl_pixels_write_property;

	REGISTER_PIXELS_PROP("pitch");
	REGISTER_PIXELS_PROP("h");

	/* Pixel type. */
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_UNKNOWN",          SDL_PIXELTYPE_UNKNOWN,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_INDEX1",           SDL_PIXELTYPE_INDEX1,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_INDEX4",           SDL_PIXELTYPE_INDEX4,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_INDEX8",           SDL_PIXELTYPE_INDEX8,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_PACKED8",          SDL_PIXELTYPE_PACKED8,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_PACKED16",         SDL_PIXELTYPE_PACKED16,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_PACKED32",         SDL_PIXELTYPE_PACKED32,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_ARRAYU8",          SDL_PIXELTYPE_ARRAYU8,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_ARRAYU16",         SDL_PIXELTYPE_ARRAYU16,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_ARRAYU32",         SDL_PIXELTYPE_ARRAYU32,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_ARRAYF16",         SDL_PIXELTYPE_ARRAYF16,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELTYPE_ARRAYF32",         SDL_PIXELTYPE_ARRAYF32,           CONST_CS | CONST_PERSISTENT);

	/* Bitmap pixel order, high bit -> low bit. */
	REGISTER_LONG_CONSTANT("SDL_BITMAPORDER_NONE",           SDL_BITMAPORDER_NONE,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BITMAPORDER_4321",           SDL_BITMAPORDER_4321,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BITMAPORDER_1234",           SDL_BITMAPORDER_1234,             CONST_CS | CONST_PERSISTENT);

	/* Packed component order, high bit -> low bit. */
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_NONE",           SDL_PACKEDORDER_NONE,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_XRGB",           SDL_PACKEDORDER_XRGB,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_RGBX",           SDL_PACKEDORDER_RGBX,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_ARGB",           SDL_PACKEDORDER_ARGB,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_RGBA",           SDL_PACKEDORDER_RGBA,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_XBGR",           SDL_PACKEDORDER_XBGR,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_BGRX",           SDL_PACKEDORDER_BGRX,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_ABGR",           SDL_PACKEDORDER_ABGR,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDORDER_BGRA",           SDL_PACKEDORDER_BGRA,             CONST_CS | CONST_PERSISTENT);

	/* Packed component layout. */
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_NONE",          SDL_PACKEDLAYOUT_NONE,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_332",           SDL_PACKEDLAYOUT_332,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_4444",          SDL_PACKEDLAYOUT_4444,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_1555",          SDL_PACKEDLAYOUT_1555,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_5551",          SDL_PACKEDLAYOUT_5551,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_565",           SDL_PACKEDLAYOUT_565,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_8888",          SDL_PACKEDLAYOUT_8888,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_2101010",       SDL_PACKEDLAYOUT_2101010,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PACKEDLAYOUT_1010102",       SDL_PACKEDLAYOUT_1010102,         CONST_CS | CONST_PERSISTENT);

	/* Pixel format */
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_UNKNOWN",        SDL_PIXELFORMAT_UNKNOWN,          CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_INDEX1LSB",      SDL_PIXELFORMAT_INDEX1LSB,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_INDEX1MSB",      SDL_PIXELFORMAT_INDEX1MSB,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_INDEX4LSB",      SDL_PIXELFORMAT_INDEX4LSB,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_INDEX4MSB",      SDL_PIXELFORMAT_INDEX4MSB,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_INDEX8",         SDL_PIXELFORMAT_INDEX8,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB332",         SDL_PIXELFORMAT_RGB332,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB444",         SDL_PIXELFORMAT_RGB444,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB555",         SDL_PIXELFORMAT_RGB555,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGR555",         SDL_PIXELFORMAT_BGR555,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ARGB4444",       SDL_PIXELFORMAT_ARGB4444,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGBA4444",       SDL_PIXELFORMAT_RGBA4444,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ABGR4444",       SDL_PIXELFORMAT_ABGR4444,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGRA4444",       SDL_PIXELFORMAT_BGRA4444,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ARGB1555",       SDL_PIXELFORMAT_ARGB1555,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGBA5551",       SDL_PIXELFORMAT_RGBA5551,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ABGR1555",       SDL_PIXELFORMAT_ABGR1555,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGRA5551",       SDL_PIXELFORMAT_BGRA5551,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB565",         SDL_PIXELFORMAT_RGB565,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGR565",         SDL_PIXELFORMAT_BGR565,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB24",          SDL_PIXELFORMAT_RGB24,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGR24",          SDL_PIXELFORMAT_BGR24,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGB888",         SDL_PIXELFORMAT_RGB888,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGBX8888",       SDL_PIXELFORMAT_RGBX8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGR888",         SDL_PIXELFORMAT_BGR888,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGRX8888",       SDL_PIXELFORMAT_BGRX8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ARGB8888",       SDL_PIXELFORMAT_ARGB8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_RGBA8888",       SDL_PIXELFORMAT_RGBA8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ABGR8888",       SDL_PIXELFORMAT_ABGR8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_BGRA8888",       SDL_PIXELFORMAT_BGRA8888,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_ARGB2101010",    SDL_PIXELFORMAT_ARGB2101010,      CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_YV12",           SDL_PIXELFORMAT_YV12,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_IYUV",           SDL_PIXELFORMAT_IYUV,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_YUY2",           SDL_PIXELFORMAT_YUY2,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_UYVY",           SDL_PIXELFORMAT_UYVY,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PIXELFORMAT_YVYU",           SDL_PIXELFORMAT_YVYU,             CONST_CS | CONST_PERSISTENT);

	return (zend_register_functions(NULL, sdl_pixels_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

