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
#include "cpuinfo.h"
#include "error.h"
#include "power.h"
#include "pixels.h"
#include "rect.h"
#include "rwops.h"
#include "surface.h"
#include "version.h"
#include "video.h"
#include "window.h"

#ifdef COMPILE_DL_SDL
ZEND_GET_MODULE(sdl)
#endif

#define PHP_MINIT_CALL(func) PHP_MINIT(func)(INIT_FUNC_ARGS_PASSTHRU)

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(sdl)
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

	if (   SUCCESS == PHP_MINIT_CALL(sdl_cpuinfo)
		&& SUCCESS == PHP_MINIT_CALL(sdl_error)
		&& SUCCESS == PHP_MINIT_CALL(sdl_power)
		&& SUCCESS == PHP_MINIT_CALL(sdl_pixels)
		&& SUCCESS == PHP_MINIT_CALL(sdl_rect)
		&& SUCCESS == PHP_MINIT_CALL(sdl_rwops)
		&& SUCCESS == PHP_MINIT_CALL(sdl_surface)
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_sdl_none, 0, 0, 0)
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

/* {{{ sdl_functions[] */
zend_function_entry sdl_functions[] = {
	ZEND_FE(SDL_Init,						arginfo_SDL_Init)
	ZEND_FE(SDL_InitSubSystem,				arginfo_SDL_InitSubSystem)
	ZEND_FE(SDL_Quit,						arginfo_sdl_none)
	ZEND_FE(SDL_QuitSubSystem,				arginfo_SDL_QuitSubSystem)
	ZEND_FE(SDL_WasInit,					arginfo_SDL_WasInit)
	ZEND_FE_END
};
/* }}} */


/* {{{ sdl_module_entry
 */
zend_module_entry sdl_module_entry = {
	STANDARD_MODULE_HEADER,
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
