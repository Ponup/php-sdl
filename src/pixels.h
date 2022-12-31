/*
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


#ifndef PHP_SDL_PIXELS_H
#define PHP_SDL_PIXELS_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

/* PHP specific struct to manage memory access */
typedef struct SDL_Pixels
{
    Uint8 *pixels;
} SDL_Pixels;

zend_class_entry *get_php_sdl_color_ce(void);
zend_bool sdl_color_to_zval(SDL_Color *color, zval *value);
zend_bool zval_to_sdl_color(zval *value, SDL_Color *color);

zend_class_entry *get_php_sdl_pixelformat_ce(void);
zend_bool sdl_pixelformat_to_zval(SDL_PixelFormat *format, zval *z_val, Uint32 flags);
SDL_PixelFormat *zval_to_sdl_pixelformat(zval *z_val);

zend_class_entry *get_php_sdl_palette_ce(void);
zend_bool sdl_palette_to_zval(SDL_Palette *palette, zval *z_val, Uint32 flags);
SDL_Palette *zval_to_sdl_palette(zval *z_val);

zend_class_entry *get_php_sdl_pixels_ce(void);
zend_bool sdl_pixels_to_zval(SDL_Pixels *pixels, zval *z_val, Uint32 flags);
SDL_Pixels *zval_to_sdl_pixels(zval *z_val);


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetPixelFormatName, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormatEnumToMasks, 0, 0, 6)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(1, bpp)
       ZEND_ARG_INFO(1, Rmask)
       ZEND_ARG_INFO(1, Gmask)
       ZEND_ARG_INFO(1, Bmask)
       ZEND_ARG_INFO(1, Amask)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MasksToPixelFormatEnum, 0, 0, 5)
       ZEND_ARG_INFO(0, bpp)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_AllocFormat, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_AllocPalette, 0, 0, 1)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetPixelFormatPalette, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, pixelformat, SDL_PixelFormat, 0)
       ZEND_ARG_OBJ_INFO(0, palette, SDL_Palette, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_SetPalette, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, palette, SDL_Palette, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetPaletteColors, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, palette, SDL_Palette, 0)
       ZEND_ARG_ARRAY_INFO(0, colors, 0)
       ZEND_ARG_INFO(0, first)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette_SetColors, 0, 0, 1)
       ZEND_ARG_ARRAY_INFO(0, colors, 0)
       ZEND_ARG_INFO(0, first)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MapRGB, 0, 0, 4)
       //ZEND_ARG_OBJ_INFO(0, pixelformat, SDL_PixelFormat, 0)
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


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MapRGBA, 0, 0, 5)
       ZEND_ARG_OBJ_INFO(0, pixelformat, SDL_PixelFormat, 0)
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


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetRGBA, 0, 0, 6)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_OBJ_INFO(0, format, SDL_PixelFormat, 0)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
       ZEND_ARG_INFO(1, a)
ZEND_END_ARG_INFO()



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat_GetRGBA, 0, 0, 5)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
       ZEND_ARG_INFO(1, a)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CalculateGammaRamp, 0, 0, 2)
       ZEND_ARG_INFO(0, gamma)
       ZEND_ARG_INFO(1, ramp)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_palette_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Palette, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, palette, SDL_Palette, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_format_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PixelFormat, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, format, SDL_PixelFormat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetRGB, 0, 0, 5)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_OBJ_INFO(0, format, SDL_PixelFormat, 0)
       ZEND_ARG_INFO(1, r)
       ZEND_ARG_INFO(1, g)
       ZEND_ARG_INFO(1, b)
ZEND_END_ARG_INFO()


PHP_FUNCTION(SDL_GetPixelFormatName);
PHP_FUNCTION(SDL_PixelFormatEnumToMasks);
PHP_FUNCTION(SDL_MasksToPixelFormatEnum);
PHP_FUNCTION(SDL_AllocFormat);
PHP_FUNCTION(SDL_FreeFormat);
PHP_FUNCTION(SDL_AllocPalette);
PHP_FUNCTION(SDL_SetPixelFormatPalette);
PHP_FUNCTION(SDL_SetPaletteColors);
PHP_FUNCTION(SDL_FreePalette);
PHP_FUNCTION(SDL_MapRGB);
PHP_FUNCTION(SDL_MapRGBA);
PHP_FUNCTION(SDL_GetRGB);
PHP_FUNCTION(SDL_GetRGBA);
PHP_FUNCTION(SDL_CalculateGammaRamp);

PHP_MINIT_FUNCTION(sdl_pixels);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_PIXELS_H */

