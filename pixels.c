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

zend_class_entry *php_sdl_palette_ce;
static zend_object_handlers php_sdl_palette_handlers;
struct php_sdl_palette {
	zend_object   zo;
	SDL_Palette   *palette;
	Uint32        flags;
};

#define FETCH_PALETTE(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_palette *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->palette; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

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

/* {{{ sdl_palette_to_zval */
zend_bool sdl_palette_to_zval(SDL_Palette *palette, zval *z_val, Uint32 flags TSRMLS_DC)
{
	struct php_sdl_palette *intern;
	if (palette) {
		object_init_ex(z_val, php_sdl_palette_ce);
		intern = (struct php_sdl_palette *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->palette = palette;
		intern->flags = flags;

		return SUCCESS;
	}
	return FAILURE;
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


/**
 *  \brief Create an SDL_PixelFormat structure from a pixel format enum.
 extern DECLSPEC SDL_PixelFormat * SDLCALL SDL_AllocFormat(Uint32 pixel_format);
 */

/**
 *  \brief Free an SDL_PixelFormat structure.
 extern DECLSPEC void SDLCALL SDL_FreeFormat(SDL_PixelFormat *format);
 */

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


/**
 *  \brief Set the palette for a pixel format structure.
 extern DECLSPEC int SDLCALL SDL_SetPixelFormatPalette(SDL_PixelFormat * format,
                                                       SDL_Palette *palette);
 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetPaletteColors, 0, 0, 3)
       ZEND_ARG_INFO(0, palette)
       ZEND_ARG_INFO(0, colors)
       ZEND_ARG_INFO(0, first)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette_SetColors, 0, 0, 2)
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
	long first, ncolors=0, count;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oal|l", &object, php_sdl_palette_ce, &z_colors, &first, &ncolors) == FAILURE) {
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

/**
 *  \brief Maps an RGB triple to an opaque pixel value for a given pixel format.
 *
 *  \sa SDL_MapRGBA
 extern DECLSPEC Uint32 SDLCALL SDL_MapRGB(const SDL_PixelFormat * format,
                                           Uint8 r, Uint8 g, Uint8 b);
 */

/**
 *  \brief Maps an RGBA quadruple to a pixel value for a given pixel format.
 *
 *  \sa SDL_MapRGB
 extern DECLSPEC Uint32 SDLCALL SDL_MapRGBA(const SDL_PixelFormat * format,
                                            Uint8 r, Uint8 g, Uint8 b,
                                            Uint8 a);
 */

/**
 *  \brief Get the RGB components from a pixel of the specified format.
 *
 *  \sa SDL_GetRGBA
 extern DECLSPEC void SDLCALL SDL_GetRGB(Uint32 pixel,
                                         const SDL_PixelFormat * format,
                                         Uint8 * r, Uint8 * g, Uint8 * b);
 */

/**
 *  \brief Get the RGBA components from a pixel of the specified format.
 *
 *  \sa SDL_GetRGB
 extern DECLSPEC void SDLCALL SDL_GetRGBA(Uint32 pixel,
                                          const SDL_PixelFormat * format,
                                          Uint8 * r, Uint8 * g, Uint8 * b,
                                          Uint8 * a);
 */

/**
 *  \brief Calculate a 256 entry gamma ramp for a gamma value.
 extern DECLSPEC void SDLCALL SDL_CalculateGammaRamp(float gamma, Uint16 * ramp);
 */

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
	zval *retval;

	convert_to_string(member);

	MAKE_STD_ZVAL(retval);
	ZVAL_FALSE(retval);

	if (intern->palette) {
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
		}
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


/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_palette_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette, 0, 0, 1)
       ZEND_ARG_INFO(0, palette)
ZEND_END_ARG_INFO()


/* {{{ php_sdl_color_methods[] */
static const zend_function_entry php_sdl_color_methods[] = {
	PHP_ME(SDL_Color, __construct,     arginfo_SDL_Color__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

static const zend_function_entry php_sdl_palette_methods[] = {
	PHP_ME(SDL_Palette, __construct,  arginfo_SDL_AllocPalette, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(Free,             SDL_FreePalette,           arginfo_palette_none)
	PHP_FALIAS(SetColors,        SDL_SetPaletteColors,      arginfo_SDL_Palette_SetColors)

	PHP_FE_END
};

/* {{{ sdl_pixels_functions[] */
zend_function_entry sdl_pixels_functions[] = {
	ZEND_FE(SDL_GetPixelFormatName,					arginfo_SDL_GetPixelFormatName)
	ZEND_FE(SDL_PixelFormatEnumToMasks,				arginfo_SDL_PixelFormatEnumToMasks)
	ZEND_FE(SDL_MasksToPixelFormatEnum,				arginfo_SDL_MasksToPixelFormatEnum)

	ZEND_FE(SDL_AllocPalette,						arginfo_SDL_AllocPalette)
	ZEND_FE(SDL_FreePalette,						arginfo_SDL_Palette)
	ZEND_FE(SDL_SetPaletteColors,					arginfo_SDL_SetPaletteColors)
	ZEND_FE_END
};
/* }}} */

#define REGISTER_COLOR_PROP(name) \
	zend_declare_property_long(php_sdl_color_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

#define REGISTER_PALETTE_PROP(name) \
	zend_declare_property_long(php_sdl_palette_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_pixels)
{
	zend_class_entry ce_color, ce_palette;

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

	REGISTER_PALETTE_PROP("ncolors");
	REGISTER_PALETTE_PROP("version");
	REGISTER_PALETTE_PROP("refcount");
	zend_declare_property_null(php_sdl_palette_ce, "colors", sizeof("colors")-1, ZEND_ACC_PUBLIC TSRMLS_DC);

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

