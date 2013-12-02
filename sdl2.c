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
#include "cpuinfo.h"
#include "rect.h"
#include "video.h"

#ifdef COMPILE_DL_SDL2
ZEND_GET_MODULE(sdl2)
#endif

#define PHP_MINIT_CALL(func) PHP_MINIT(func)(INIT_FUNC_ARGS_PASSTHRU)

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(sdl2)
{
/*
 *  These are the flags which may be passed to SDL_Init().  You should
 *  specify the subsystems which you will be using in your application.
 */
	REGISTER_LONG_CONSTANT("SDL_INIT_TIMER",           SDL_INIT_TIMER,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_AUDIO",           SDL_INIT_AUDIO,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_VIDEO",           SDL_INIT_VIDEO,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_JOYSTICK",        SDL_INIT_JOYSTICK,          CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_HAPTIC",          SDL_INIT_HAPTIC,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_GAMECONTROLLER",  SDL_INIT_GAMECONTROLLER,    CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_EVENTS",          SDL_INIT_EVENTS,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_NOPARACHUTE",     SDL_INIT_NOPARACHUTE,       CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_EVERYTHING",      SDL_INIT_EVERYTHING,        CONST_CS | CONST_PERSISTENT);

	if (1
		&& SUCCESS == PHP_MINIT_CALL(sdl2_video)
		&& SUCCESS == PHP_MINIT_CALL(sdl2_rect)) {
		return SUCCESS;
	}
	return FAILURE;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(sdl2)
{
	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(sdl2)
{
	SDL_version ver;
	char buf[64];


	php_info_print_table_start();
	php_info_print_table_header(2, "SDL2 support", "enabled");

	php_info_print_table_row(2, "SDL2 module version", PHP_SDL2_VERSION);

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_sdl2_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Init, 0, 0, 0)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_Init([int flags=SDL_INIT_EVERYTHING])

 *  This function initializes  the subsystems specified by \c flags
 *  Unless the ::SDL_INIT_NOPARACHUTE flag is set, it will install cleanup
 *  signal handlers for some commonly ignored fatal signals (like SIGSEGV).
extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);
*/
PHP_FUNCTION(SDL_Init) {
	long flags = SDL_INIT_EVERYTHING;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_Init((Uint32)flags));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_InitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_InitSubSystem(int flags)

 *  This function initializes specific SDL subsystems
extern DECLSPEC int SDLCALL SDL_InitSubSystem(Uint32 flags);
*/
PHP_FUNCTION(SDL_InitSubSystem) {
	long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_InitSubSystem((Uint32)flags));
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_QuitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_QuitSubSystem(int flags)

 *  This function cleans up specific SDL subsystems
extern DECLSPEC void SDLCALL SDL_QuitSubSystem(Uint32 flags);
*/
PHP_FUNCTION(SDL_QuitSubSystem) {
	long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	SDL_QuitSubSystem((Uint32)flags);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WasInit, 0, 0, 0)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_WasInit(int flags)

 *  This function returns a mask of the specified subsystems which have
 *  previously been initialized.
 *
 *  If \c flags is 0, it returns a mask of all initialized subsystems.
extern DECLSPEC Uint32 SDLCALL SDL_WasInit(Uint32 flags);
*/
PHP_FUNCTION(SDL_WasInit) {
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_WasInit((Uint32)flags));
}
/* }}} */

/* {{{ proto void SDL_Quit(void )

 *  This function cleans up all initialized subsystems. You should
 *  call it upon all exit conditions.
extern DECLSPEC void SDLCALL SDL_Quit(void);
*/
PHP_FUNCTION(SDL_Quit)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	SDL_Quit();
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVideoDriver, 0, 0, 1)
       ZEND_ARG_INFO(0, driverIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_VideoInit, 0, 0, 0)
       ZEND_ARG_INFO(0, drivername)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_dysplayindex, 0, 0, 1)
       ZEND_ARG_INFO(0, displayIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_INFO(0, modeIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetDisplayBounds, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_INFO(1, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window, 0, 0, 1)
       ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateWindow, 0, 0, 6)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowTitle, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect, 0, 0, 1)
       ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect2, 0, 0, 2)
       ZEND_ARG_INFO(0, rectA)
       ZEND_ARG_INFO(0, rectB)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Rect3, 0, 0, 3)
       ZEND_ARG_INFO(0, rectA)
       ZEND_ARG_INFO(0, rectB)
       ZEND_ARG_INFO(1, result)
ZEND_END_ARG_INFO()

/* {{{ sdl2_functions[] */
zend_function_entry sdl2_functions[] = {
	/* SDL */
	ZEND_FE(SDL_Init,						arginfo_SDL_Init)
	ZEND_FE(SDL_InitSubSystem,				arginfo_SDL_InitSubSystem)
	ZEND_FE(SDL_Quit,						arginfo_sdl2_none)
	ZEND_FE(SDL_QuitSubSystem,				arginfo_SDL_QuitSubSystem)
	ZEND_FE(SDL_WasInit,					arginfo_SDL_WasInit)

	/* SDL_cpuinfo */
	ZEND_FE(SDL_GetCPUCount,				arginfo_sdl2_none)
	ZEND_FE(SDL_GetCPUCacheLineSize,		arginfo_sdl2_none)
	ZEND_FE(SDL_HasRDTSC,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasAltiVec,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasMMX,						arginfo_sdl2_none)
	ZEND_FE(SDL_Has3DNow,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasSSE,						arginfo_sdl2_none)
	ZEND_FE(SDL_HasSSE2,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasSSE3,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasSSE41,					arginfo_sdl2_none)
	ZEND_FE(SDL_HasSSE42,					arginfo_sdl2_none)
	ZEND_FE(SDL_GetSystemRAM,				arginfo_sdl2_none)

	/* SDL video */
	ZEND_FE(SDL_GetNumVideoDrivers,			arginfo_sdl2_none)
	ZEND_FE(SDL_GetVideoDriver,				arginfo_SDL_GetVideoDriver)
	ZEND_FE(SDL_VideoInit,					arginfo_SDL_VideoInit)
	ZEND_FE(SDL_VideoQuit,					arginfo_sdl2_none)
	ZEND_FE(SDL_GetCurrentVideoDriver,		arginfo_sdl2_none)
	ZEND_FE(SDL_GetNumVideoDisplays,		arginfo_sdl2_none)
	ZEND_FE(SDL_GetDisplayName,				arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetDisplayBounds,			arginfo_SDL_GetDisplayBounds)
	ZEND_FE(SDL_GetNumDisplayModes,			arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetDisplayMode,				arginfo_SDL_GetDisplayMode)
	ZEND_FE(SDL_GetDesktopDisplayMode,		arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetCurrentDisplayMode,		arginfo_SDL_dysplayindex)

	/* SDL video / window */
	ZEND_FE(SDL_CreateWindow,				arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_DestroyWindow,				arginfo_SDL_Window)
	ZEND_FE(SDL_UpdateWindowSurface,		arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowTitle,				arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowTitle,				arginfo_SDL_SetWindowTitle)

	/* SDL rect */
	ZEND_FE(SDL_RectEmpty,					arginfo_SDL_Rect)
	ZEND_FE(SDL_RectEquals,					arginfo_SDL_Rect2)
	ZEND_FE(SDL_HasIntersection,			arginfo_SDL_Rect2)
	ZEND_FE(SDL_IntersectRect,				arginfo_SDL_Rect3)
	ZEND_FE(SDL_UnionRect,					arginfo_SDL_Rect3)

	ZEND_FE_END
};
/* }}} */


/* {{{ sdl2_module_entry
 */
zend_module_entry sdl2_module_entry = {
	STANDARD_MODULE_HEADER,
	"SDL2",
	sdl2_functions,
	PHP_MINIT(sdl2),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(sdl2), /* Replace with NULL if there is nothing to do at php shutdown  */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	PHP_MINFO(sdl2),
	PHP_SDL2_VERSION, 
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
