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

#include "mouse.h"
#include "surface.h"
#include "window.h"

static zend_class_entry *php_sdl_cursor_ce;
static zend_object_handlers php_sdl_cursor_handlers;
struct php_sdl_cursor
{
	SDL_Cursor *cursor;
	Uint32 flags;
	zend_object zo;
};

/* {{{ get_php_sdl_cursor_ce */
zend_class_entry *get_php_sdl_cursor_ce(void)
{
	return php_sdl_cursor_ce;
}
/* }}} */

#define FETCH_CURSOR(__ptr, __id, __check)                                                         \
	{                                                                                              \
		zend_object *zo = Z_OBJ_P(__id);                                                           \
		intern = (struct php_sdl_cursor *)((char *)zo - zo->handlers->offset);                     \
		__ptr = intern->cursor;                                                                    \
		if (__check && !__ptr)                                                                     \
		{                                                                                          \
			php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name)); \
			RETURN_FALSE;                                                                          \
		}                                                                                          \
	}

/* {{{ sdl_cursor_to_zval */
zend_bool sdl_cursor_to_zval(SDL_Cursor *cursor, zval *z_val, Uint32 flags)
{
	if (cursor)
	{
		struct php_sdl_cursor *intern;

		object_init_ex(z_val, php_sdl_cursor_ce);
		zend_object *zo = Z_OBJ_P(z_val);
		intern = (struct php_sdl_cursor *)((char *)zo - zo->handlers->offset);
		intern->cursor = cursor;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_cursor */
SDL_GLContext zval_to_sdl_cursor(zval *z_val)
{
	struct php_sdl_cursor *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_cursor_ce)
	{
		zend_object *zo = Z_OBJ_P(z_val);
		intern = (struct php_sdl_cursor *)((char *)zo - zo->handlers->offset);
		return intern->cursor;
	}
	return NULL;
}
/* }}} */

/* {{{ php_sdl_cursor_free */
static void php_sdl_cursor_free(zend_object *object)
{
	struct php_sdl_cursor *intern = (struct php_sdl_cursor *)((char *)object - object->handlers->offset);

	if (intern->cursor && !(intern->flags & SDL_DONTFREE))
	{
		SDL_FreeCursor(intern->cursor);
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

/* {{{ php_sdl_cursor_new
 */
static zend_object *php_sdl_cursor_new(zend_class_entry *class_type)
{
	struct php_sdl_cursor *intern;

	intern = ecalloc(1, sizeof(struct php_sdl_cursor) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->cursor = NULL;
	php_sdl_cursor_handlers.offset = XtOffsetOf(struct php_sdl_cursor, zo);
	intern->zo.handlers = &php_sdl_cursor_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ proto SDL_Cursor::__construct(void) */
static PHP_METHOD(SDL_Cursor, __construct)
{
	struct php_sdl_cursor *intern;
	zend_error_handling error_handling;
	char *data, *mask;
	size_t data_len, mask_len;
	zend_long w, h, x, y;
	long size;

	intern = (struct php_sdl_cursor *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "ssllll", &data, &data_len, &mask, &mask_len, &w, &h, &x, &y))
	{
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	if (w <= 0 || w & 7 || h <= 0)
	{
		zend_throw_exception(zend_exception_get_default(), "Invalid cursor size", 0);
		return;
	}
	size = w / 8 * h;
	if (data_len != size || mask_len != size)
	{
		zend_throw_exception_ex(zend_exception_get_default(), 0, "Invalid data or mask, size must be %ld", size);
		return;
	}
	intern->cursor = SDL_CreateCursor((Uint8 *)data, (Uint8 *)mask, (int)w, (int)h, (int)x, (int)y);
	if (intern->cursor)
	{
		intern->flags = 0;
	}
	else
	{
		zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Cursor___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Cursor::__toString()
 */
static PHP_METHOD(SDL_Cursor, __toString)
{
	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}
	RETVAL_STRING("SDL_Cursor()");
}
/* }}} */

/* {{{ proto SDL_Cursor SDL_CreateCursor(string data, string mask, int w, int h, int hot_x, int hot_y)

 *  \brief Create a cursor, using the specified bitmap data and
 *         mask (in MSB format).
 *
 *  The cursor width must be a multiple of 8 bits.
 *
 *  The cursor is created in black and white according to the following:
 *  <table>
 *  <tr><td> data </td><td> mask </td><td> resulting pixel on screen </td></tr>
 *  <tr><td>  0   </td><td>  1   </td><td> White </td></tr>
 *  <tr><td>  1   </td><td>  1   </td><td> Black </td></tr>
 *  <tr><td>  0   </td><td>  0   </td><td> Transparent </td></tr>
 *  <tr><td>  1   </td><td>  0   </td><td> Inverted color if possible, black
 *                                         if not. </td></tr>
 *  </table>
 *
 *  \sa SDL_FreeCursor()
 extern DECLSPEC SDL_Cursor *SDLCALL SDL_CreateCursor(const Uint8 * data,
													  const Uint8 * mask,
													  int w, int h, int hot_x,
													  int hot_y);
 */
PHP_FUNCTION(SDL_CreateCursor)
{
	char *data, *mask;
	size_t data_len, mask_len;
	zend_long w, h, x, y;
	long size;
	SDL_Cursor *cursor;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "ssllll", &data, &data_len, &mask, &mask_len, &w, &h, &x, &y))
	{
		return;
	}
	if (w <= 0 || w & 7 || h <= 0)
	{
		php_error_docref(NULL, E_WARNING, "Invalid cursor size");
		return;
	}
	size = w / 8 * h;
	if (data_len != size || mask_len != size)
	{
		php_error_docref(NULL, E_WARNING, "Invalid data or mask, size must be %ld", size);
		return;
	}
	cursor = SDL_CreateCursor((Uint8 *)data, (Uint8 *)mask, (int)w, (int)h, (int)x, (int)y);
	sdl_cursor_to_zval(cursor, return_value, 0);
}
/* }}} */

/* {{{ proto SDL_Cursor SDL_CreateSystemCursor(int id)

 *  \brief Create a system cursor.
 *
 *  \sa SDL_FreeCursor()
 extern DECLSPEC SDL_Cursor *SDLCALL SDL_CreateSystemCursor(SDL_SystemCursor id);
 */
PHP_FUNCTION(SDL_CreateSystemCursor)
{
	zend_long id;
	SDL_Cursor *cursor;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "l", &id))
	{
		return;
	}
	cursor = SDL_CreateSystemCursor(id);
	sdl_cursor_to_zval(cursor, return_value, 0);
}
/* }}} */

/* {{{ proto SDL_Cursor SDL_CreateSystemCursor(int id)

 *  \brief Create a color cursor.
 *
 *  \sa SDL_FreeCursor()
 extern DECLSPEC SDL_Cursor *SDLCALL SDL_CreateColorCursor(SDL_Surface *surface,
														   int hot_x,
														   int hot_y);
 */
PHP_FUNCTION(SDL_CreateColorCursor)
{
	zend_long x, y;
	zval *z_surface;
	SDL_Surface *surface;
	SDL_Cursor *cursor;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Oll", &z_surface, get_php_sdl_surface_ce(), &x, &y))
	{
		return;
	}
	surface = zval_to_sdl_surface(z_surface);
	if (surface)
	{
		cursor = SDL_CreateColorCursor(surface, (int)x, (int)y);
		sdl_cursor_to_zval(cursor, return_value, 0);
	}
	else
	{
		php_error_docref(NULL, E_WARNING, "Invalid SDL_Window object");
	}
}
/* }}} */

/* {{{ proto void SDL_FreeCursor(SDL_Cursor cursor)

 *  \brief Frees a cursor created with SDL_CreateCursor().
 *
 *  \sa SDL_CreateCursor()
 extern DECLSPEC void SDLCALL SDL_FreeCursor(SDL_Cursor * cursor);
 */
PHP_FUNCTION(SDL_FreeCursor)
{
	struct php_sdl_cursor *intern;
	zval *z_cursor;
	SDL_Cursor *cursor;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_cursor, php_sdl_cursor_ce) == FAILURE)
	{
		return;
	}
	FETCH_CURSOR(cursor, z_cursor, 1);

	SDL_FreeCursor(intern->cursor);
	intern->cursor = NULL;
}
/* }}} */

/* {{{ proto void SDL_SetCursor(SDL_Cursor cursor)

 *  \brief Set the active cursor.
 extern DECLSPEC void SDLCALL SDL_SetCursor(SDL_Cursor * cursor);
 */
PHP_FUNCTION(SDL_SetCursor)
{
	struct php_sdl_cursor *intern;
	zval *z_cursor;
	SDL_Cursor *cursor;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_cursor, php_sdl_cursor_ce) == FAILURE)
	{
		return;
	}
	FETCH_CURSOR(cursor, z_cursor, 1);

	SDL_SetCursor(cursor);
}
/* }}} */

/* {{{ proto SDL_Cursor SDL_GetCursor(void)

 *  \brief Return the active cursor.
 extern DECLSPEC SDL_Cursor *SDLCALL SDL_GetCursor(void);
 */
PHP_FUNCTION(SDL_GetCursor)
{
	SDL_Cursor *cursor;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}
	cursor = SDL_GetCursor();
	sdl_cursor_to_zval(cursor, return_value, SDL_DONTFREE);
}
/* }}} */

/* {{{ proto SDL_Cursor SDL_GetDefaultCursor(void)

 *  \brief Return the default cursor.
 extern DECLSPEC SDL_Cursor *SDLCALL SDL_GetDefaultCursor(void);
 */
PHP_FUNCTION(SDL_GetDefaultCursor)
{
	SDL_Cursor *cursor;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}
	cursor = SDL_GetDefaultCursor();
	sdl_cursor_to_zval(cursor, return_value, SDL_DONTFREE);
}
/* }}} */

/* {{{ proto int SDL_ShowCursor(bool toogle)

 *  \brief Toggle whether or not the cursor is shown.
 *
 *  \param toggle 1 to show the cursor, 0 to hide it, -1 to query the current
 *                state.
 *
 *  \return 1 if the cursor is shown, or 0 if the cursor is hidden.
 extern DECLSPEC int SDLCALL SDL_ShowCursor(int toggle);
 */
PHP_FUNCTION(SDL_ShowCursor)
{
	bool toggle;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "b", &toggle))
	{
		return;
	}
	RETVAL_BOOL(SDL_ShowCursor(toggle));
}
/* }}} */

/* {{{ proto SDL_Window SDL_GetMouseFocus(void)

 *  \brief Get the window which currently has mouse focus.
 extern DECLSPEC SDL_Window * SDLCALL SDL_GetMouseFocus(void);
 */
PHP_FUNCTION(SDL_GetMouseFocus)
{
	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}
	sdl_window_to_zval(SDL_GetMouseFocus(), return_value, SDL_DONTFREE);
}

/* {{{ proto int SDL_GetMouseState(int &x, int &y)

 *  \brief Retrieve the current state of the mouse.
 *
 *  The current button state is returned as a button bitmask, which can
 *  be tested using the SDL_BUTTON(X) macros, and x and y are set to the
 *  mouse cursor position relative to the focus window for the currently
 *  selected mouse.  You can pass NULL for either x or y.
 extern DECLSPEC Uint32 SDLCALL SDL_GetMouseState(int *x, int *y);
 */
PHP_FUNCTION(SDL_GetMouseState)
{
	zval *z_x = NULL, *z_y = NULL;
	int x, y;
	Uint32 state;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "|zz", &z_x, &z_y))
	{
		return;
	}
	state = SDL_GetMouseState(&x, &y);
	if (z_x)
	{
		zval_dtor(z_x);
		ZVAL_LONG(z_x, x);
	}
	if (z_y)
	{
		zval_dtor(z_y);
		ZVAL_LONG(z_y, y);
	}
	RETVAL_LONG(state);
}
/* }}} */

/* {{{ proto int SDL_GetRelativeMouseState(int &x, int &y)

 *  \brief Retrieve the relative state of the mouse.
 *
 *  The current button state is returned as a button bitmask, which can
 *  be tested using the SDL_BUTTON(X) macros, and x and y are set to the
 *  mouse deltas since the last call to SDL_GetRelativeMouseState().
 extern DECLSPEC Uint32 SDLCALL SDL_GetRelativeMouseState(int *x, int *y);
 */
PHP_FUNCTION(SDL_GetRelativeMouseState)
{
	zval *z_x = NULL, *z_y = NULL;
	int x, y;
	Uint32 state;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "|zz", &z_x, &z_y))
	{
		return;
	}
	state = SDL_GetRelativeMouseState(&x, &y);
	if (z_x)
	{
		zval_dtor(z_x);
		ZVAL_LONG(z_x, x);
	}
	if (z_y)
	{
		zval_dtor(z_y);
		ZVAL_LONG(z_y, y);
	}
	RETVAL_LONG(state);
}
/* }}} */

/* {{{ proto void SDL_WarpMouseInWindow(SDL_Window window, int x, int y)

 *  \brief Moves the mouse to the given position within the window.
 *
 *  \param window The window to move the mouse into, or NULL for the current mouse focus
 *  \param x The x coordinate within the window
 *  \param y The y coordinate within the window
 *
 *  \note This function generates a mouse motion event
 extern DECLSPEC void SDLCALL SDL_WarpMouseInWindow(SDL_Window * window,
													int x, int y);
 */
PHP_FUNCTION(SDL_WarpMouseInWindow)
{
	zval *z_window;
	SDL_Window *window;
	zend_long x, y;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Oll", &z_window, get_php_sdl_window_ce(), &x, &y))
	{
		return;
	}
	window = zval_to_sdl_window(z_window);
	if (window)
	{
		SDL_WarpMouseInWindow(window, (int)x, (int)y);
	}
	else
	{
		php_error_docref(NULL, E_WARNING, "Invalid SDL_Window object");
	}
}
/* }}} */

/* {{{ proto int SDL_SetRelativeMouseMode(bool enabled)

 *  \brief Set relative mouse mode.
 *
 *  \param enabled Whether or not to enable relative mode
 *
 *  \return 0 on success, or -1 if relative mode is not supported.
 *
 *  While the mouse is in relative mode, the cursor is hidden, and the
 *  driver will try to report continuous motion in the current window.
 *  Only relative motion events will be delivered, the mouse position
 *  will not change.
 *
 *  \note This function will flush any pending mouse motion.
 *
 *  \sa SDL_GetRelativeMouseMode()
 extern DECLSPEC int SDLCALL SDL_SetRelativeMouseMode(SDL_bool enabled);
 */
PHP_FUNCTION(SDL_SetRelativeMouseMode)
{
	bool enabled;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "b", &enabled))
	{
		return;
	}
	RETVAL_LONG(SDL_SetRelativeMouseMode(enabled));
}
/* }}} */

/* {{{ proto bool SDL_GetRelativeMouseMode(void)

 *  \brief Query whether relative mouse mode is enabled.
 *
 *  \sa SDL_SetRelativeMouseMode()
extern DECLSPEC SDL_bool SDLCALL SDL_GetRelativeMouseMode(void);
 */
PHP_FUNCTION(SDL_GetRelativeMouseMode)
{
	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}
	RETVAL_BOOL(SDL_GetRelativeMouseMode());
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ sdl_cursor_methods[] */
static const zend_function_entry php_sdl_cursor_methods[] = {
	PHP_ME(SDL_Cursor, __construct, arginfo_SDL_Cursor__construct, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Cursor, __toString, arginfo_class_SDL_Cursor___toString, ZEND_ACC_PUBLIC)

	/* non-static methods */
	PHP_FALIAS(Free, SDL_FreeCursor, arginfo_none)
	PHP_FALIAS(Set, SDL_SetCursor, arginfo_none)

	/* static methods */
	ZEND_FENTRY(Create, ZEND_FN(SDL_CreateCursor), arginfo_SDL_Cursor__construct, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
		ZEND_FENTRY(CreateSystem, ZEND_FN(SDL_CreateSystemCursor), arginfo_SDL_CreateSystemCursor, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
			ZEND_FENTRY(CreateColor, ZEND_FN(SDL_CreateColorCursor), arginfo_SDL_CreateColorCursor, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
				ZEND_FENTRY(Get, ZEND_FN(SDL_GetCursor), arginfo_none, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
					ZEND_FENTRY(GetDefault, ZEND_FN(SDL_GetDefaultCursor), arginfo_none, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
						ZEND_FENTRY(Show, ZEND_FN(SDL_ShowCursor), arginfo_SDL_ShowCursor, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

							ZEND_FE_END};
/* }}} */

#define REGISTER_CURSOR_CLASS_CONST_LONG(const_name, value)                                      \
	REGISTER_LONG_CONSTANT("SDL_SYSTEM_CURSOR_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_cursor_ce, ZEND_STRL(const_name), value)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_mouse)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_Cursor", php_sdl_cursor_methods);
	php_sdl_cursor_ce = zend_register_internal_class(&ce);
	php_sdl_cursor_ce->create_object = php_sdl_cursor_new;
	memcpy(&php_sdl_cursor_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_cursor_handlers.free_obj = php_sdl_cursor_free;
	php_sdl_cursor_handlers.offset = XtOffsetOf(struct php_sdl_cursor, zo);

	/* Cursor types for SDL_CreateSystemCursor.
	   typedef enum SDL_SystemCursor; */
	REGISTER_CURSOR_CLASS_CONST_LONG("ARROW", SDL_SYSTEM_CURSOR_ARROW);
	REGISTER_CURSOR_CLASS_CONST_LONG("IBEAM", SDL_SYSTEM_CURSOR_IBEAM);
	REGISTER_CURSOR_CLASS_CONST_LONG("WAIT", SDL_SYSTEM_CURSOR_WAIT);
	REGISTER_CURSOR_CLASS_CONST_LONG("CROSSHAIR", SDL_SYSTEM_CURSOR_CROSSHAIR);
	REGISTER_CURSOR_CLASS_CONST_LONG("WAITARROW", SDL_SYSTEM_CURSOR_WAITARROW);
	REGISTER_CURSOR_CLASS_CONST_LONG("SIZENWSE", SDL_SYSTEM_CURSOR_SIZENWSE);
	REGISTER_CURSOR_CLASS_CONST_LONG("SIZENESW", SDL_SYSTEM_CURSOR_SIZENESW);
	REGISTER_CURSOR_CLASS_CONST_LONG("SIZEWE", SDL_SYSTEM_CURSOR_SIZEWE);
	REGISTER_CURSOR_CLASS_CONST_LONG("SIZENS", SDL_SYSTEM_CURSOR_SIZENS);
	REGISTER_CURSOR_CLASS_CONST_LONG("SIZEALL", SDL_SYSTEM_CURSOR_SIZEALL);
	REGISTER_CURSOR_CLASS_CONST_LONG("NO", SDL_SYSTEM_CURSOR_NO);
	REGISTER_CURSOR_CLASS_CONST_LONG("HAND", SDL_SYSTEM_CURSOR_HAND);

	REGISTER_LONG_CONSTANT("SDL_NUM_SYSTEM_CURSORS", SDL_NUM_SYSTEM_CURSORS, CONST_CS | CONST_PERSISTENT);
	zend_declare_class_constant_long(php_sdl_cursor_ce, ZEND_STRL("NUM_SYSTEM"), SDL_NUM_SYSTEM_CURSORS);

	/*
	 *  Used as a mask when testing buttons in buttonstate.
	 *   - Button 1:  Left mouse button
	 *   - Button 2:  Middle mouse button
	 *   - Button 3:  Right mouse button
	 */
	REGISTER_LONG_CONSTANT("SDL_BUTTON_LEFT", SDL_BUTTON_LEFT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_MIDDLE", SDL_BUTTON_MIDDLE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_RIGHT", SDL_BUTTON_RIGHT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X1", SDL_BUTTON_X1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X2", SDL_BUTTON_X2, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_LMASK", SDL_BUTTON_LMASK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_MMASK", SDL_BUTTON_MMASK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_RMASK", SDL_BUTTON_RMASK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X1MASK", SDL_BUTTON_X1MASK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_X2MASK", SDL_BUTTON_X2MASK, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */
