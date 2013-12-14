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
  | wrapper for SDL2/SDL_messagebox.h                                    |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "messagebox.h"
#include "window.h"


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowSimpleMessageBox, 0, 0, 3)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, message)
       ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

/* {{{ proto bool SDLCALL SDL_ShowSimpleMessageBox(int flags, string title, string message, SDL_Window window)

 *  \brief Create a simple modal message box
 *
 *  \param flags    ::SDL_MessageBoxFlags
 *  \param title    UTF-8 title text
 *  \param message  UTF-8 message text
 *  \param window   The parent window, or NULL for no parent
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDL_ShowMessageBox
 extern DECLSPEC int SDLCALL SDL_ShowSimpleMessageBox(Uint32 flags, const char *title, const char *message, SDL_Window *window);
 */
PHP_FUNCTION(SDL_ShowSimpleMessageBox)
{
	char *title, *msg;
	zval *z_window;
	SDL_Window *window;
	long flags;
	int title_len, msg_len;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lss|O", &flags, &title, &title_len, &msg, &msg_len, &z_window, get_php_sdl_window_ce())) {
		return;
	}

	window = zval_to_sdl_window(z_window);
	RETVAL_LONG(SDL_ShowSimpleMessageBox(flags, title, msg, window));
}
/* }}} */


/* {{{ sdl_messagebox_functions[] */
zend_function_entry sdl_messagebox_functions[] = {
	ZEND_FE(SDL_ShowSimpleMessageBox,			arginfo_SDL_ShowSimpleMessageBox)
	ZEND_FE_END
};
/* }}} */

#define REGISTER_MESSAGEBOX_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_MESSAGEBOX_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	/*zend_declare_class_constant_long(php_sdl_window_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC);*/ \

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_messagebox)
{
	/* enum SDL_MessageBoxFlags: If supported will display warning icon, etc. */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("ERROR",       SDL_MESSAGEBOX_ERROR);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("WARNING",     SDL_MESSAGEBOX_WARNING);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("INFORMATION", SDL_MESSAGEBOX_INFORMATION);

	/* enum SDL_MessageBoxButtonFlags: Flags for SDL_MessageBoxButtonData. */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("BUTTON_RETURNKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("BUTTON_ESCAPEKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

	/* enum SDL_MessageBoxColorType */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_BACKGROUND",        SDL_MESSAGEBOX_COLOR_BACKGROUND);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_TEXT",              SDL_MESSAGEBOX_COLOR_TEXT);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_BUTTON_BORDER",     SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_BUTTON_BACKGROUND", SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_BUTTON_SELECTED",   SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_MAX",               SDL_MESSAGEBOX_COLOR_MAX);

	return (zend_register_functions(NULL, sdl_messagebox_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */

