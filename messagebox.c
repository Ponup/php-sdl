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
  | SDL_MessageBoxColor                                                  |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "messagebox.h"
#include "window.h"

static zend_class_entry *php_sdl_messageboxcolor_ce;
static zend_object_handlers php_sdl_messageboxcolor_handlers;
struct php_sdl_messageboxcolor {
	zend_object   zo;
};

/* {{{ get_php_sdl_messageboxcolor_ce */
zend_class_entry *get_php_sdl_messageboxcolor_ce(void)
{
	return php_sdl_messageboxcolor_ce;
}
/* }}} */

/* {{{ sdl_messageboxcolor_to_zval */
zend_bool sdl_messageboxcolor_to_zval(SDL_MessageBoxColor *color, zval *value TSRMLS_DC)
{
	if (color) {
		object_init_ex(value, php_sdl_messageboxcolor_ce);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "r", 1, color->r TSRMLS_CC);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "g", 1, color->g TSRMLS_CC);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "b", 1, color->b TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_messageboxcolor( */
zend_bool zval_to_sdl_messageboxcolor(zval *value, SDL_MessageBoxColor *color TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_messageboxcolor_ce) {
		zval *val;

		/* we convert the properties, without copy: yes ! */

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "r", 1, 0 TSRMLS_CC);
		convert_to_long(val);
		color->r = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "g", 1, 0 TSRMLS_CC);
		convert_to_long(val);
		color->g = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "b", 1, 0 TSRMLS_CC);
		convert_to_long(val);
		color->b = (Uint8)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty color */
	memset(color, 0, sizeof(SDL_MessageBoxColor));
	return 0;
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MessageBoxColor__construct, 0, 0, 3)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_MessageBoxColor::__construct(int r, int g, int b, int a)

 * \brief RGB value used in a message box color scheme
typedef struct
{
    Uint8 r, g, b;
} SDL_MessageBoxColor;
*/
static PHP_METHOD(SDL_MessageBoxColor, __construct)
{
	long r, g, b;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &r, &g, &b)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "r", 1, r&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "g", 1, g&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "b", 1, b&255 TSRMLS_CC);
}
/* }}} */


/* {{{ proto SDL_MessageBoxColor::__toString()
*/
static PHP_METHOD(SDL_MessageBoxColor, __toString)
{
	char *buf;
	SDL_MessageBoxColor color;

//	intern = (struct php_sdl_pixelformat *)zend_object_store_get_object(__id TSRMLS_CC);
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_messageboxcolor(getThis(), &color);
	spprintf(&buf, 100, "SDL_MessageBoxColor(%u,%u,%u)", color.r, color.g, color.b);
	RETVAL_STRING(buf, 0);
}
/* }}} */


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


ZEND_BEGIN_ARG_INFO_EX(arginfo_messagebox_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ php_sdl_messageboxcolor_methods[] */
static const zend_function_entry php_sdl_messageboxcolor_methods[] = {
	PHP_ME(SDL_MessageBoxColor, __construct, arginfo_SDL_MessageBoxColor__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_MessageBoxColor, __toString,  arginfo_messagebox_none,                ZEND_ACC_PUBLIC)
	PHP_FE_END
};
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

#define REGISTER_MESSAGEBOXCOLOR_PROP(name) \
	zend_declare_property_long(php_sdl_messageboxcolor_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_messagebox)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_MessageBoxColor", php_sdl_messageboxcolor_methods);
	php_sdl_messageboxcolor_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_messageboxcolor_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_MESSAGEBOXCOLOR_PROP("r");
	REGISTER_MESSAGEBOXCOLOR_PROP("g");
	REGISTER_MESSAGEBOXCOLOR_PROP("b");

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

