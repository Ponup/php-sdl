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
  | wrapper for SDL2/SDL.h                                               |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"

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

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(sdl_sdl)
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

	return (zend_register_functions(NULL, sdl_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
