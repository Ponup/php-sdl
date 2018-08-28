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


#include "php_sdl.h"
#include "blendmode.h"
#include "cpuinfo.h"
#include "error.h"
#include "event.h"
#include "filesystem.h"
#include "glcontext.h"
#include "keyboard.h"
#include "messagebox.h"
#include "mouse.h"
#include "mutex.h"
#include "platform.h"
#include "power.h"
#include "pixels.h"
#include "rect.h"
#include "render.h"
#include "rwops.h"
#include "sdl.h"
#include "shape.h"
#include "surface.h"
#include "timer.h"
#include "version.h"
#include "video.h"
#include "window.h"

#ifdef COMPILE_DL_SDL
ZEND_GET_MODULE(sdl)
#endif

/* {{{ php_sdl_check_overflow */
zend_bool php_sdl_check_overflow(int a, int b, int silent)
{
	TSRMLS_FETCH();

	if(a <= 0 || b <= 0) {
		if (!silent) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "one parameter to a memory allocation multiplication is negative or zero, failing operation gracefully");
		}
		return 1;
	}
	if(a > INT_MAX / b) {
		if (!silent) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "product of memory allocation multiplication would exceed INT_MAX, failing operation gracefully");
		}
		return 1;
	}
	return 0;
}
/* }}} */


#define PHP_MINIT_CALL(func) PHP_MINIT(func)(INIT_FUNC_ARGS_PASSTHRU)

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(sdl)
{
	if (   SUCCESS == PHP_MINIT_CALL(sdl_blendmode)
		&& SUCCESS == PHP_MINIT_CALL(sdl_cpuinfo)
		&& SUCCESS == PHP_MINIT_CALL(sdl_error)
		&& SUCCESS == PHP_MINIT_CALL(sdl_event)
		&& SUCCESS == PHP_MINIT_CALL(sdl_glcontext)
		&& SUCCESS == PHP_MINIT_CALL(sdl_keyboard)
		&& SUCCESS == PHP_MINIT_CALL(sdl_messagebox)
		&& SUCCESS == PHP_MINIT_CALL(sdl_mouse)
		&& SUCCESS == PHP_MINIT_CALL(sdl_mutex)
		&& SUCCESS == PHP_MINIT_CALL(sdl_platform)
		&& SUCCESS == PHP_MINIT_CALL(sdl_power)
		&& SUCCESS == PHP_MINIT_CALL(sdl_filesystem)
		&& SUCCESS == PHP_MINIT_CALL(sdl_pixels)
		&& SUCCESS == PHP_MINIT_CALL(sdl_rect)
		&& SUCCESS == PHP_MINIT_CALL(sdl_render)
		&& SUCCESS == PHP_MINIT_CALL(sdl_rwops)
		&& SUCCESS == PHP_MINIT_CALL(sdl_sdl)
		&& SUCCESS == PHP_MINIT_CALL(sdl_shape)
		&& SUCCESS == PHP_MINIT_CALL(sdl_surface)
		&& SUCCESS == PHP_MINIT_CALL(sdl_timer)
		&& SUCCESS == PHP_MINIT_CALL(sdl_version)
		&& SUCCESS == PHP_MINIT_CALL(sdl_video)
		&& SUCCESS == PHP_MINIT_CALL(sdl_window)
		) {
		return SUCCESS;
	}
	return FAILURE;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(sdl)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(sdl)
{
	SDL_version ver;
	char buf[64];

	php_info_print_table_start();
	php_info_print_table_header(2, "SDL support", "enabled");

	php_info_print_table_row(2, "SDL module version", PHP_SDL_VERSION);

	/* buildtime headers version */
	SDL_VERSION(&ver);
	snprintf(buf, sizeof(buf), "%d.%d.%d", ver.major, ver.minor, ver.patch);
	php_info_print_table_row(2, "SDL2 headers version", buf);

	/* runtime library version */
	SDL_GetVersion(&ver);
	snprintf(buf, sizeof(buf), "%d.%d.%d", ver.major, ver.minor, ver.patch);
	php_info_print_table_row(2, "SDL2 library version", buf);

	php_info_print_table_end();
}
/* }}} */

/* {{{ sdl_functions[] */
static zend_function_entry sdl_functions[] = {
	// Core
	ZEND_FE(SDL_Init,						arginfo_SDL_Init)
	ZEND_FE(SDL_InitSubSystem,				arginfo_SDL_InitSubSystem)
	ZEND_FE(SDL_Quit,						arginfo_SDL_Quit)
	ZEND_FE(SDL_QuitSubSystem,				arginfo_SDL_QuitSubSystem)
	ZEND_FE(SDL_WasInit,					arginfo_SDL_WasInit)

	// Window
	ZEND_FE(SDL_CreateWindow,				arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_CreateShapedWindow,			arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_DestroyWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_UpdateWindowSurface,		arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowTitle,				arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowTitle,				arginfo_SDL_SetWindowTitle)
	ZEND_FE(SDL_GetWindowDisplayIndex,		arginfo_SDL_Window)
	ZEND_FE(SDL_ShowWindow,					arginfo_SDL_Window)
	ZEND_FE(SDL_HideWindow,					arginfo_SDL_Window)
	ZEND_FE(SDL_RaiseWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_MaximizeWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_MinimizeWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_RestoreWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowSurface,			arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowDisplayMode,		arginfo_SDL_SetWindowDisplayMode)
	ZEND_FE(SDL_GetWindowDisplayMode,		arginfo_SDL_GetWindowDisplayMode)
	ZEND_FE(SDL_GetWindowPixelFormat,		arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowID,				arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowFromID,			arginfo_SDL_GetWindowFromID)
	ZEND_FE(SDL_GetWindowFlags,				arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowData,				arginfo_SDL_SetWindowData)
	ZEND_FE(SDL_GetWindowData,				arginfo_SDL_GetWindowData)
	ZEND_FE(SDL_SetWindowIcon,				arginfo_SDL_SetWindowIcon)
	ZEND_FE(SDL_SetWindowPosition,			arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowPosition,			arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowSize,				arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowSize,				arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMinimumSize,		arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMinimumSize,		arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMaximumSize,		arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMaximumSize,		arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowBordered,			arginfo_SDL_SetWindowBordered)
	ZEND_FE(SDL_SetWindowFullscreen,		arginfo_SDL_SetWindowFullscreen)
	ZEND_FE(SDL_UpdateWindowSurfaceRects,	arginfo_SDL_UpdateWindowSurfaceRects)
	ZEND_FE(SDL_SetWindowGrab,				arginfo_SDL_SetWindowGrab)
	ZEND_FE(SDL_GetWindowGrab,				arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowBrightness,		arginfo_SDL_SetWindowBrightness)
	ZEND_FE(SDL_GetWindowBrightness,		arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowGammaRamp, 		arginfo_SDL_SetWindowGammaRamp)
	ZEND_FE(SDL_GetWindowGammaRamp, 		arginfo_SDL_GetWindowGammaRamp)
	ZEND_FE(SDL_IsShapedWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowShape,				arginfo_SDL_SetWindowShape)
	ZEND_FE(SDL_GetShapedWindowMode,		arginfo_SDL_GetShapedWindowMode)

	ZEND_FE(SDL_WINDOWPOS_UNDEFINED_DISPLAY,	arginfo_SDL_WINDOWPOS_DISPLAY)
	ZEND_FE(SDL_WINDOWPOS_CENTERED_DISPLAY,	arginfo_SDL_WINDOWPOS_DISPLAY)

	// Version
	ZEND_FE(SDL_GetRevision,		arginfo_sdl_version_none)
	ZEND_FE(SDL_GetRevisionNumber,		arginfo_sdl_version_none)
	ZEND_FE(SDL_GetVersion,			arginfo_SDL_GetVersion)
	ZEND_FE(SDL_VERSION,			arginfo_SDL_VERSION)
	ZEND_FE(SDL_VERSIONNUM,			arginfo_SDL_VERSIONNUM)
	ZEND_FE(SDL_VERSION_ATLEAST,		arginfo_SDL_VERSION_ATLEAST)

	// Timer
	ZEND_FE(SDL_Delay, arginfo_SDL_Delay)

	// Render
	ZEND_FE(SDL_CreateRenderer, arginfo_SDL_CreateRenderer)
	ZEND_FE(SDL_DestroyRenderer, arginfo_SDL_DestroyRenderer)
	ZEND_FE(SDL_DestroyTexture, arginfo_SDL_DestroyTexture)
	ZEND_FE(SDL_SetRenderDrawColor, arginfo_SDL_SetRenderDrawColor)
	ZEND_FE(SDL_RenderDrawPoint, arginfo_SDL_RenderDrawPoint)
	ZEND_FE(SDL_RenderClear, arginfo_SDL_RenderClear)
	ZEND_FE(SDL_RenderCopy, arginfo_SDL_RenderCopy)
	ZEND_FE(SDL_RenderFillRect, arginfo_SDL_RenderFillRect)
	ZEND_FE(SDL_RenderPresent, arginfo_SDL_RenderPresent)
	ZEND_FE(SDL_CreateTextureFromSurface, arginfo_SDL_CreateTextureFromSurface)

	// Surface
	ZEND_FE(SDL_CreateRGBSurface,			arginfo_SDL_CreateRGBSurface)
	ZEND_FE(SDL_FreeSurface,				arginfo_SDL_Surface)
	ZEND_FE(SDL_FillRect,					arginfo_SDL_FillRect)
	ZEND_FE(SDL_FillRects,					arginfo_SDL_FillRects)
	ZEND_FE(SDL_MUSTLOCK,					arginfo_SDL_Surface)
	ZEND_FE(SDL_LockSurface,				arginfo_SDL_Surface)
	ZEND_FE(SDL_UnlockSurface,				arginfo_SDL_Surface)
	ZEND_FE(SDL_LoadBMP_RW,					arginfo_SDL_LoadBMP_RW)
	ZEND_FE(SDL_LoadBMP,					arginfo_SDL_LoadBMP)
	ZEND_FE(SDL_UpperBlit,					arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_LowerBlit,					arginfo_SDL_LowerBlit)
	ZEND_FE(SDL_UpperBlitScaled,			arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_LowerBlitScaled,			arginfo_SDL_LowerBlit)
	ZEND_FE(SDL_SoftStretch,				arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_SaveBMP_RW,					arginfo_SDL_SaveBMP_RW)
	ZEND_FE(SDL_SaveBMP,					arginfo_SDL_SaveBMP)
	ZEND_FE(SDL_SetSurfaceRLE,				arginfo_SDL_SetSurfaceRLE)
	ZEND_FE(SDL_SetColorKey,				arginfo_SDL_SetColorKey)
	ZEND_FE(SDL_GetColorKey,				arginfo_SDL_GetColorKey)
	ZEND_FE(SDL_SetSurfaceColorMod,			arginfo_SDL_SetSurfaceColorMod)
	ZEND_FE(SDL_GetSurfaceColorMod,			arginfo_SDL_GetSurfaceColorMod)
	ZEND_FE(SDL_SetSurfaceAlphaMod,			arginfo_SDL_SetSurfaceAlphaMod)
	ZEND_FE(SDL_GetSurfaceAlphaMod,			arginfo_SDL_GetSurfaceAlphaMod)
	ZEND_FE(SDL_SetSurfaceBlendMode,		arginfo_SDL_SetSurfaceBlendMode)
	ZEND_FE(SDL_GetSurfaceBlendMode,		arginfo_SDL_GetSurfaceBlendMode)
	ZEND_FE(SDL_SetClipRect,				arginfo_SDL_SetClipRect)
	ZEND_FE(SDL_GetClipRect,				arginfo_SDL_GetClipRect)
	ZEND_FE(SDL_ConvertSurface,				arginfo_SDL_ConvertSurface)
	ZEND_FE(SDL_ConvertSurfaceFormat,		arginfo_SDL_ConvertSurfaceFormat)
	ZEND_FE(SDL_ConvertPixels,				arginfo_SDL_ConvertPixels)
	//PHP_FALIAS(SDL_BlitSurface,   SDL_UpperBlit,          arginfo_SDL_UpperBlit)
	//PHP_FALIAS(SDL_BlitScaled,    SDL_UpperBlitScaled,    arginfo_SDL_UpperBlit)

	// Rect
	ZEND_FE(SDL_RectEmpty,					arginfo_SDL_Rect)
	ZEND_FE(SDL_RectEquals,					arginfo_SDL_Rect2)
	ZEND_FE(SDL_HasIntersection,			arginfo_SDL_Rect2)
	ZEND_FE(SDL_IntersectRect,				arginfo_SDL_Rect3)
	ZEND_FE(SDL_UnionRect,					arginfo_SDL_Rect3)
	ZEND_FE(SDL_IntersectRectAndLine,		arginfo_SDL_IntersectRectAndLine)
	ZEND_FE(SDL_EnclosePoints,				arginfo_SDL_EnclosePoints)

	// Events
	ZEND_FE(SDL_WaitEvent, arginfo_SDL_WaitEvent)
	ZEND_FE(SDL_PollEvent, arginfo_SDL_PollEvent)

	// Message box
	ZEND_FE(SDL_ShowSimpleMessageBox,     arginfo_SDL_ShowSimpleMessageBox)
	ZEND_FE(SDL_ShowMessageBox,           arginfo_SDL_ShowMessageBox)

	// Pixels
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

	// Filesystem
	ZEND_FE(SDL_GetBasePath, arginfo_SDL_GetBasePath)
	ZEND_FE(SDL_GetPrefPath, arginfo_SDL_GetPrefPath)

	// GL
	ZEND_FE(SDL_GL_ExtensionSupported,                   arginfo_SDL_GL_ExtensionSupported)
	ZEND_FE(SDL_GL_SetAttribute,                         arginfo_SDL_GL_SetAttribute)
	ZEND_FE(SDL_GL_GetAttribute,                         arginfo_SDL_GL_GetAttribute)
	ZEND_FE(SDL_GL_CreateContext,                        arginfo_SDL_GLContext__construct)
	ZEND_FE(SDL_GL_DeleteContext,                        arginfo_SDL_GLContext)
	ZEND_FE(SDL_GL_MakeCurrent,                          arginfo_SDL_GL_MakeCurrent)
	ZEND_FE(SDL_GL_GetCurrentWindow,                     arginfo_none)
	ZEND_FE(SDL_GL_GetCurrentContext,                    arginfo_none)
#if SDL_VERSION_ATLEAST(2,0,1)
	ZEND_FE(SDL_GL_GetDrawableSize,                      arginfo_SDL_GL_GetDrawableSize)
#endif
	ZEND_FE(SDL_GL_SwapWindow,                           arginfo_SDL_Window)
	ZEND_FE(SDL_GL_SetSwapInterval,                      arginfo_SDL_GL_SetSwapInterval)
	ZEND_FE(SDL_GL_GetSwapInterval,                      arginfo_none)

	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_module_entry
 */
zend_module_entry sdl_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	"SDL",
	sdl_functions,
	PHP_MINIT(sdl),     /* Replace with NULL if there is nothing to do at php startup   */
	PHP_MSHUTDOWN(sdl), /* Replace with NULL if there is nothing to do at php shutdown  */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	PHP_MINFO(sdl),
	PHP_SDL_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
