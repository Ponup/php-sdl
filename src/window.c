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

#include "window.h"
#include "glcontext.h"
#include "mouse.h"
#include "rect.h"
#include "shape.h"
#include "surface.h"
#include "video.h"

/* used to associate PHP object handle to SDL_Window */
#define PHP_SDL_MAGICDATA "__php__handle"

static zend_class_entry *php_sdl_window_ce;
static zend_object_handlers php_sdl_window_handlers;
struct php_sdl_window
{
	SDL_Window *window;
	int flags;
	zend_object zo;
};

typedef struct php_sdl_window php_sdl_window_t;

static inline php_sdl_window_t *php_sdl_window_fetch_object(zend_object *obj);

zend_class_entry *get_php_sdl_window_ce(void)
{
	return php_sdl_window_ce;
}

/* {{{ zval_to_sdl_window */
SDL_Window *zval_to_sdl_window(zval *z_val)
{
	if (z_val && Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_window_ce)
	{
		zend_object *zo = Z_OBJ_P(z_val);

		struct php_sdl_window *intern;
		intern = (struct php_sdl_window *)((char *)zo - zo->handlers->offset);
		return intern->window;
	}
	return NULL;
}
/* }}} */

static inline void sdl_window_add_long_property(HashTable *props, const char *name, zend_long value)
{
	zval zvalue;
	zend_string *zname = zend_string_init(name, strlen(name), 0);
	ZVAL_LONG(&zvalue, value);
	zend_hash_update(props, zname, &zvalue);
	zend_string_release(zname);
}

/* {{{ sdl_window_read_property*/
static HashTable *sdl_window_get_properties(zend_object *object)
{
	HashTable *props;
	zend_string *z_string;
	zval zv;
	struct php_sdl_window *intern = php_sdl_window_fetch_object(object);

	props = zend_std_get_properties(object);

	if (intern->window)
	{
		int w, h, x, y;

		SDL_GetWindowSize(intern->window, &w, &h);
		SDL_GetWindowPosition(intern->window, &x, &y);
		sdl_window_add_long_property(props, "id", SDL_GetWindowID(intern->window));
		sdl_window_add_long_property(props, "flags", SDL_GetWindowFlags(intern->window));
		sdl_window_add_long_property(props, "x", x);
		sdl_window_add_long_property(props, "y", y);
		sdl_window_add_long_property(props, "w", w);
		sdl_window_add_long_property(props, "h", h);
		ZVAL_STRING(&zv, SDL_GetWindowTitle(intern->window));
		z_string = zend_string_init("title", 6, 0);
		zend_hash_update(props, z_string, &zv);
		zend_string_release(z_string);
	}
	return props;
}
/* }}} */

static inline php_sdl_window_t *php_sdl_window_fetch_object(zend_object *obj)
{
	return (php_sdl_window_t *)((char *)obj - XtOffsetOf(php_sdl_window_t, zo));
}

#define FETCH_WINDOW(__ptr, __id, __check)                                                         \
	{                                                                                              \
		zend_object *zox = Z_OBJ_P(__id);                                                          \
		intern = (struct php_sdl_window *)((char *)zox - zox->handlers->offset);                   \
		__ptr = intern->window;                                                                    \
		if (__check && !__ptr)                                                                     \
		{                                                                                          \
			php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name)); \
			RETURN_FALSE;                                                                          \
		}                                                                                          \
	}

/* {{{ proto void SDL_GetWindowDisplayIndex(SDL_Window window)

 *  \brief Get the display index associated with a window.
 *
 *  \return the display index of the display containing the center of the
 *          window, or -1 on error.
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayIndex(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowDisplayIndex)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	RETURN_LONG(SDL_GetWindowDisplayIndex(window));
}
/* }}} */

/* {{{ proto int SDL_SetWindowDisplayMode(SDL_Window window, SDL_DisplayMode mode)

 *  \brief Set the display mode used when a fullscreen window is visible.
 *
 *  By default the window's dimensions and the desktop format and refresh rate
 *  are used.
 *
 *  \param window The window for which the display mode should be set.
 *  \param mode The mode to use, or NULL for the default mode.
 *
 *  \return 0 on success, or -1 if setting the display mode failed.
 *
 *  \sa SDL_GetWindowDisplayMode()
 *  \sa SDL_SetWindowFullscreen()
 extern DECLSPEC int SDLCALL SDL_SetWindowDisplayMode(SDL_Window * window,
													  const SDL_DisplayMode
														  * mode);
 */
PHP_FUNCTION(SDL_SetWindowDisplayMode)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_mode;
	SDL_Window *window;
	SDL_DisplayMode mode;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &z_window, php_sdl_window_ce, &z_mode, get_php_sdl_displaymode_ce()) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	if (zval_to_sdl_displaymode(z_mode, &mode))
	{
		RETVAL_LONG(SDL_SetWindowDisplayMode(window, &mode));
	}
}
/* }}} */

/* {{{ proto int SDL_GetWindowDisplayMode(SDL_Window window, SDL_DisplayMode mode)

 *  \brief Fill in information about the display mode used when a fullscreen
 *         window is visible.
 *
 *  \sa SDL_SetWindowDisplayMode()
 *  \sa SDL_SetWindowFullscreen()
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayMode(SDL_Window * window,
													  SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetWindowDisplayMode)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_mode;
	SDL_Window *window;
	SDL_DisplayMode mode;
	int res;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz", &z_window, php_sdl_window_ce, &z_mode) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	res = SDL_GetWindowDisplayMode(window, &mode);
	if (0 == res)
	{
		zval_dtor(z_mode);
		sdl_displaymode_to_zval(&mode, z_mode);
	}
	RETVAL_LONG(res);
}
/* }}} */

/* {{{ proto int SDL_GetWindowPixelFormat(SDL_Window window)

 *  \brief Get the pixel format associated with the window.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowPixelFormat(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowPixelFormat)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_GetWindowPixelFormat(window));
}
/* }}} */

/* {{{ proto int SDL_GetWindowID(SDL_Window window)

 *  \brief Get the numeric ID of a window, for logging purposes.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowID(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowID)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_GetWindowID(window));
}
/* }}} */

/* {{{ proto int SDL_GetWindowFlags(SDL_Window window)

 *  \brief Get the window flags.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowFlags)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_GetWindowFlags(window));
}
/* }}} */

/* {{{ proto void SDL_SetWindowIcon(SDL_Window window, SDL_Surface icon)

 *  \brief Set the icon for a window.
 *
 *  \param window The window for which the icon should be set.
 *  \param icon The icon for the window.
 extern DECLSPEC void SDLCALL SDL_SetWindowIcon(SDL_Window * window,
												SDL_Surface * icon);
 */
PHP_FUNCTION(SDL_SetWindowIcon)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_icon;
	SDL_Window *window;
	SDL_Surface *icon;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &z_window, php_sdl_window_ce, &z_icon, get_php_sdl_surface_ce()))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	icon = zval_to_sdl_surface(z_icon);

	if (icon)
	{
		SDL_SetWindowIcon(window, icon);
	}
	else
	{
		php_error_docref(NULL, E_WARNING, "Invalid SDL_Surface object");
	}
}
/* }}} */

/* {{{ proto void SDL_SetWindowPosition(SDL Window window, int x, int y)

 *  \brief Set the position of a window.
 *
 *  \param window   The window to reposition.
 *  \param x        The x coordinate of the window, ::SDL_WINDOWPOS_CENTERED, or
					::SDL_WINDOWPOS_UNDEFINED.
 *  \param y        The y coordinate of the window, ::SDL_WINDOWPOS_CENTERED, or
					::SDL_WINDOWPOS_UNDEFINED.
 *
 *  \note The window coordinate origin is the upper left of the display.
 *
 *  \sa SDL_GetWindowPosition()
 extern DECLSPEC void SDLCALL SDL_SetWindowPosition(SDL_Window * window,
													int x, int y);
 */
PHP_FUNCTION(SDL_SetWindowPosition)
{
	struct php_sdl_window *intern;
	zval *z_window;
	zend_long x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oll", &z_window, php_sdl_window_ce, &x, &y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowPosition(window, x, y);
}
/* }}} */

/* {{{ proto int SDL_WINDOWPOS_CENTERED_DISPLAY(int)

 define SDL_WINDOWPOS_CENTERED_DISPLAY(X)  (SDL_WINDOWPOS_CENTERED_MASK|(X))
*/
PHP_FUNCTION(SDL_WINDOWPOS_CENTERED_DISPLAY)
{
	zend_long display;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "l", &display))
	{
		return;
	}
	RETVAL_LONG(SDL_WINDOWPOS_CENTERED_DISPLAY(display));
}
/* }}} */

/* {{{ proto int SDL_WINDOWPOS_UNDEFINED_DISPLAY(int)

 define SDL_WINDOWPOS_UNDEFINED_DISPLAY(X)  (SDL_WINDOWPOS_UNDEFINED_MASK|(X))
*/
PHP_FUNCTION(SDL_WINDOWPOS_UNDEFINED_DISPLAY)
{
	zend_long display;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "l", &display))
	{
		return;
	}
	RETVAL_LONG(SDL_WINDOWPOS_UNDEFINED_DISPLAY(display));
}
/* }}} */

/* {{{ proto void SDL_GetWindowPosition(SDL Window window, int &x, int &y)

 *  \brief Get the position of a window.
 *
 *  \param window   The window to query.
 *  \param x        Pointer to variable for storing the x position, may be NULL
 *  \param y        Pointer to variable for storing the y position, may be NULL
 *
 *  \sa SDL_SetWindowPosition()
 extern DECLSPEC void SDLCALL SDL_GetWindowPosition(SDL_Window * window,
													int *x, int *y);
 */
PHP_FUNCTION(SDL_GetWindowPosition)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_x = NULL, *z_y = NULL;
	int x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz/z/", &z_window, php_sdl_window_ce, &z_x, &z_y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_GetWindowPosition(window, &x, &y);
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
}
/* }}} */

/* {{{ proto void SDL_SetWindowSize(SDL Window window, int x, int y)

 *  \brief Set the size of a window's client area.
 *
 *  \param window   The window to resize.
 *  \param w        The width of the window, must be >0
 *  \param h        The height of the window, must be >0
 *
 *  \note You can't change the size of a fullscreen window, it automatically
 *        matches the size of the display mode.
 *
 *  \sa SDL_GetWindowSize()
 extern DECLSPEC void SDLCALL SDL_SetWindowSize(SDL_Window * window, int w,
												int h);
 */
PHP_FUNCTION(SDL_SetWindowSize)
{
	struct php_sdl_window *intern;
	zval *z_window;
	zend_long x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oll", &z_window, php_sdl_window_ce, &x, &y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowSize(window, x, y);
}
/* }}} */

/* {{{ proto void SDL_GetWindowSize(SDL Window window, int &x, int &y)

 *  \brief Get the size of a window's client area.
 *
 *  \param window   The window to query.
 *  \param w        Pointer to variable for storing the width, may be NULL
 *  \param h        Pointer to variable for storing the height, may be NULL
 *
 *  \sa SDL_SetWindowSize()
 extern DECLSPEC void SDLCALL SDL_GetWindowSize(SDL_Window * window, int *w,
												int *h);
 */
PHP_FUNCTION(SDL_GetWindowSize)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_x = NULL, *z_y = NULL;
	int x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz/z/", &z_window, php_sdl_window_ce, &z_x, &z_y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_GetWindowSize(window, &x, &y);
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
}
/* }}} */

/* {{{ proto void SDL_SetWindowMinimumSize(SDL Window window, int x, int y)

 *  \brief Set the minimum size of a window's client area.
 *
 *  \param window    The window to set a new minimum size.
 *  \param min_w     The minimum width of the window, must be >0
 *  \param min_h     The minimum height of the window, must be >0
 *
 *  \note You can't change the minimum size of a fullscreen window, it
 *        automatically matches the size of the display mode.
 *
 *  \sa SDL_GetWindowMinimumSize()
 *  \sa SDL_SetWindowMaximumSize()
 extern DECLSPEC void SDLCALL SDL_SetWindowMinimumSize(SDL_Window * window,
													   int min_w, int min_h);
 */
PHP_FUNCTION(SDL_SetWindowMinimumSize)
{
	struct php_sdl_window *intern;
	zval *z_window;
	zend_long x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oll", &z_window, php_sdl_window_ce, &x, &y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowMinimumSize(window, x, y);
}
/* }}} */

/* {{{ proto void SDL_GetWindowMinimumSize(SDL Window window, int &x, int &y)

 *  \brief Get the minimum size of a window's client area.
 *
 *  \param window   The window to query.
 *  \param w        Pointer to variable for storing the minimum width, may be NULL
 *  \param h        Pointer to variable for storing the minimum height, may be NULL
 *
 *  \sa SDL_GetWindowMaximumSize()
 *  \sa SDL_SetWindowMinimumSize()
 extern DECLSPEC void SDLCALL SDL_GetWindowMinimumSize(SDL_Window * window,
													   int *w, int *h);
 */
PHP_FUNCTION(SDL_GetWindowMinimumSize)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_x = NULL, *z_y = NULL;
	int x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O|zz", &z_window, php_sdl_window_ce, &z_x, &z_y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_GetWindowMinimumSize(window, &x, &y);
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
}
/* }}} */

/* {{{ proto void SDL_SetWindowMaximumSize(SDL Window window, int x, int y)

 *  \brief Set the maximum size of a window's client area.
 *
 *  \param window    The window to set a new maximum size.
 *  \param max_w     The maximum width of the window, must be >0
 *  \param max_h     The maximum height of the window, must be >0
 *
 *  \note You can't change the maximum size of a fullscreen window, it
 *        automatically matches the size of the display mode.
 *
 *  \sa SDL_GetWindowMaximumSize()
 *  \sa SDL_SetWindowMinimumSize()
 extern DECLSPEC void SDLCALL SDL_SetWindowMaximumSize(SDL_Window * window,
													   int max_w, int max_h);
 */
PHP_FUNCTION(SDL_SetWindowMaximumSize)
{
	struct php_sdl_window *intern;
	zval *z_window;
	zend_long x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oll", &z_window, php_sdl_window_ce, &x, &y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowMaximumSize(window, x, y);
}
/* }}} */

/* {{{ proto void SDL_GetWindowMaximumSize(SDL Window window, int &x, int &y)

 *  \brief Get the maximum size of a window's client area.
 *
 *  \param window   The window to query.
 *  \param w        Pointer to variable for storing the maximum width, may be NULL
 *  \param h        Pointer to variable for storing the maximum height, may be NULL
 *
 *  \sa SDL_GetWindowMinimumSize()
 *  \sa SDL_SetWindowMaximumSize()
 extern DECLSPEC void SDLCALL SDL_GetWindowMaximumSize(SDL_Window * window,
													   int *w, int *h);
 */
PHP_FUNCTION(SDL_GetWindowMaximumSize)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_x = NULL, *z_y = NULL;
	int x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O|zz", &z_window, php_sdl_window_ce, &z_x, &z_y))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_GetWindowMaximumSize(window, &x, &y);
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
}
/* }}} */

/* {{{ proto void SDL_SetWindowBordered(SDL Window window, bool bordered)

 *  \brief Set the border state of a window.
 *
 *  This will add or remove the window's SDL_WINDOW_BORDERLESS flag and
 *  add or remove the border from the actual window. This is a no-op if the
 *  window's border already matches the requested state.
 *
 *  \param window The window of which to change the border state.
 *  \param bordered SDL_FALSE to remove border, SDL_TRUE to add border.
 *
 *  \note You can't change the border state of a fullscreen window.
 *
 *  \sa SDL_GetWindowFlags()
 extern DECLSPEC void SDLCALL SDL_SetWindowBordered(SDL_Window * window,
													SDL_bool bordered);
 */
PHP_FUNCTION(SDL_SetWindowBordered)
{
	struct php_sdl_window *intern;
	zval *z_window;
	bool bordered;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ob", &z_window, php_sdl_window_ce, &bordered))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowBordered(window, (bordered ? SDL_TRUE : SDL_FALSE));
}
/* }}} */

/* {{{ proto void SDL_ShowWindow(SDL_Window window)

 *  \brief Show a window.
 *
 *  \sa SDL_HideWindow()
 extern DECLSPEC void SDLCALL SDL_ShowWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_ShowWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_ShowWindow(window);
}
/* }}} */

/* {{{ proto void SDL_HideWindow(SDL_Window window)

 *  \brief Hide a window.
 *
 *  \sa SDL_ShowWindow()
 extern DECLSPEC void SDLCALL SDL_HideWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_HideWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_HideWindow(window);
}
/* }}} */

/* {{{ proto void SDL_RaiseWindow(SDL_Window window)

 *  \brief Raise a window above other windows and set the input focus.
 extern DECLSPEC void SDLCALL SDL_RaiseWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_RaiseWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_RaiseWindow(window);
}
/* }}} */

/* {{{ proto void SDL_MaximizeWindow(SDL_Window window)

 *  \brief Make a window as large as possible.
 *
 *  \sa SDL_RestoreWindow()
 extern DECLSPEC void SDLCALL SDL_MaximizeWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_MaximizeWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_MaximizeWindow(window);
}
/* }}} */

/* {{{ proto void SDL_MinimizeWindow(SDL_Window window)

 *  \brief Minimize a window to an iconic representation.
 *
 *  \sa SDL_RestoreWindow()
 extern DECLSPEC void SDLCALL SDL_MinimizeWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_MinimizeWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_MinimizeWindow(window);
}
/* }}} */

/* {{{ proto void SDL_RestoreWindow(SDL_Window window)

 *  \brief Restore the size and position of a minimized or maximized window.
 *
 *  \sa SDL_MaximizeWindow()
 *  \sa SDL_MinimizeWindow()
 extern DECLSPEC void SDLCALL SDL_RestoreWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_RestoreWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_RestoreWindow(window);
}
/* }}} */

/* {{{ proto void SDL_SetWindowFullscreen(SDL Window window, int flags)

 *  \brief Set a window's fullscreen state.
 *
 *  \return 0 on success, or -1 if setting the display mode failed.
 *
 *  \sa SDL_SetWindowDisplayMode()
 *  \sa SDL_GetWindowDisplayMode()
 extern DECLSPEC int SDLCALL SDL_SetWindowFullscreen(SDL_Window * window,
													 Uint32 flags);
 */
PHP_FUNCTION(SDL_SetWindowFullscreen)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;
	zend_long flags;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &object, php_sdl_window_ce, &flags) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	RETVAL_LONG(SDL_SetWindowFullscreen(window, (Uint32)flags));
}
/* }}} */

/* {{{ proto void SDL_GetWindowSurface(SDL_Window window)

 *  \brief Get the SDL surface associated with the window.
 *
 *  \return The window's framebuffer surface, or NULL on error.
 *
 *  A new surface will be created with the optimal format for the window,
 *  if necessary. This surface will be freed when the window is destroyed.
 *
 *  \note You may not combine this with 3D or the rendering API on this window.
 *
 *  \sa SDL_UpdateWindowSurface()
 *  \sa SDL_UpdateWindowSurfaceRects()
 extern DECLSPEC SDL_Surface * SDLCALL SDL_GetWindowSurface(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowSurface)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	surface = SDL_GetWindowSurface(intern->window);
	sdl_surface_to_zval(surface, return_value);
}
/* }}} */

/* {{{ proto int SDL_UpdateWindowSurfaceRects(SDL Window window, array rects [, int numrect])

 *  \brief Copy a number of rectangles on the window surface to the screen.
 *
 *  \return 0 on success, or -1 on error.
 *
 *  \sa SDL_GetWindowSurface()
 *  \sa SDL_UpdateWindowSurfaceRect()
 extern DECLSPEC int SDLCALL SDL_UpdateWindowSurfaceRects(SDL_Window * window,
														  const SDL_Rect * rects,
														  int numrects);
 */
PHP_FUNCTION(SDL_UpdateWindowSurfaceRects)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_array;
	zend_long num = 0;
	int nb, max;
	SDL_Window *window;
	SDL_Rect *rects;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oa|l", &z_window, php_sdl_window_ce, &z_array, &num))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);

	nb = 0;
	max = (int)(num ? num : zend_hash_num_elements(Z_ARRVAL_P(z_array)));
	if (max)
	{
		zval *ppzval;
		rects = emalloc(max * sizeof(SDL_Rect));

		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(z_array), ppzval)
		{
			if (zval_to_sdl_rect(ppzval, rects + nb))
			{
				nb++;
			}
			else
			{
				php_error_docref(NULL, E_NOTICE, "Ignore rect, not a SDL_Rect object");
			}
		}
		ZEND_HASH_FOREACH_END();
	}
	if (!nb)
	{
		php_error_docref(NULL, E_WARNING, "No SDL_Rect provided");
	}
	else
	{
		if (num && nb < max)
		{
			php_error_docref(NULL, E_NOTICE, "Only %d SDL_Rect provided, %d expected", nb, max);
		}
		RETVAL_LONG(SDL_UpdateWindowSurfaceRects(window, rects, nb));
	}
	if (max)
	{
		efree(rects);
	}
}
/* }}} */

/* {{{ proto void SDL_SetWindowGrab(SDL Window window, bool grabbed)

 *  \brief Set a window's input grab mode.
 *
 *  \param window The window for which the input grab mode should be set.
 *  \param grabbed This is SDL_TRUE to grab input, and SDL_FALSE to release input.
 *
 *  \sa SDL_GetWindowGrab()
 extern DECLSPEC void SDLCALL SDL_SetWindowGrab(SDL_Window * window,
												SDL_bool grabbed);
 */
PHP_FUNCTION(SDL_SetWindowGrab)
{
	struct php_sdl_window *intern;
	zval *z_window;
	bool grabbed;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ob", &z_window, php_sdl_window_ce, &grabbed))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowGrab(window, (grabbed ? SDL_TRUE : SDL_FALSE));
}
/* }}} */

/* {{{ proto bool SDL_GetWindowGrab(SDL Window window)

 *  \brief Get a window's input grab mode.
 *
 *  \return This returns SDL_TRUE if input is grabbed, and SDL_FALSE otherwise.
 *
 *  \sa SDL_SetWindowGrab()
 extern DECLSPEC SDL_bool SDLCALL SDL_GetWindowGrab(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowGrab)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_BOOL(SDL_GetWindowGrab(window));
}
/* }}} */

/* {{{ proto int SDL_SetWindowBrightness(SDL Window window, float brightness)

 *  \brief Set the brightness (gamma correction) for a window.
 *
 *  \return 0 on success, or -1 if setting the brightness isn't supported.
 *
 *  \sa SDL_GetWindowBrightness()
 extern DECLSPEC int SDLCALL SDL_SetWindowBrightness(SDL_Window * window, float brightness);
 */
PHP_FUNCTION(SDL_SetWindowBrightness)
{
	struct php_sdl_window *intern;
	zval *z_window;
	double brightness;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Od", &z_window, php_sdl_window_ce, &brightness))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_SetWindowBrightness(window, (float)brightness));
}
/* }}} */

/* {{{ proto void SDL_GetWindowBrightness(SDL Window window)

 *  \brief Get the brightness (gamma correction) for a window.
 *
 *  \return The last brightness value passed to SDL_SetWindowBrightness()
 *
 *  \sa SDL_SetWindowBrightness()
 extern DECLSPEC float SDLCALL SDL_GetWindowBrightness(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowBrightness)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_DOUBLE(SDL_GetWindowBrightness(window));
}
/* }}} */

/* {{{ proto int SDL_GetWindowGammaRamp(SDL Window window, array &red, array &green, array &blue)

 *  \brief Get the gamma ramp for a window.
 *
 *  \param window The window from which the gamma ramp should be queried.
 *  \param red   A pointer to a 256 element array of 16-bit quantities to hold
 *               the translation table for the red channel, or NULL.
 *  \param green A pointer to a 256 element array of 16-bit quantities to hold
 *               the translation table for the green channel, or NULL.
 *  \param blue  A pointer to a 256 element array of 16-bit quantities to hold
 *               the translation table for the blue channel, or NULL.
 *
 *  \return 0 on success, or -1 if gamma ramps are unsupported.
 *
 extern DECLSPEC int SDLCALL SDL_GetWindowGammaRamp(SDL_Window * window,
													Uint16 * red,
													Uint16 * green,
													Uint16 * blue);
 */
PHP_FUNCTION(SDL_GetWindowGammaRamp)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_r, *z_g, *z_b;
	SDL_Window *window;
	Uint16 r[256], g[256], b[256];
	// 	zval *tmp;
	int i, ret;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ozzz", &z_window, php_sdl_window_ce, &z_r, &z_g, &z_b))
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);

	ret = SDL_GetWindowGammaRamp(window, r, g, b);
	if (ret == 0)
	{
		zval_dtor(z_r);
		array_init(z_r);
		zval_dtor(z_g);
		array_init(z_g);
		zval_dtor(z_b);
		array_init(z_b);

		for (i = 0; i < 256; i++)
		{
			add_next_index_long(z_r, r[i]);
			add_next_index_long(z_g, g[i]);
			add_next_index_long(z_b, b[i]);
		}
	}
	RETVAL_LONG(ret);
}
/* }}} */

static void php_create_window(INTERNAL_FUNCTION_PARAMETERS, int opt)
{
	struct php_sdl_window *intern;
	zend_long x, y, w, h, flags;
	char *title;
	size_t title_len;
	SDL_Window *window;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "slllll", &title, &title_len, &x, &y, &w, &h, &flags))
	{
		return;
	}
	switch (opt)
	{
	case 1:
		window = SDL_CreateShapedWindow(title, x, y, w, h, flags);
		break;
	default:
		window = SDL_CreateWindow(title, x, y, w, h, flags);
	}
	if (window)
	{
		object_init_ex(return_value, php_sdl_window_ce);
		intern = php_sdl_window_fetch_object(Z_OBJ_P(return_value));
		intern->window = window;
		intern->flags = 0;

		SDL_SetWindowData(intern->window, PHP_SDL_MAGICDATA, (void *)(unsigned long)Z_OBJ_HANDLE_P(return_value));
	}
}
/* {{{ proto SDL_Window SDL_CreateShapedWindow(string title, int x, int y, int w, int h, int flags)

 *  \brief Create a window that can be shaped with the specified position, dimensions, and flags.
 *
 *  \param title The title of the window, in UTF-8 encoding.
 *  \param x     The x position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param y     The y position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param w     The width of the window.
 *  \param h     The height of the window.
 *  \param flags The flags for the window, a mask of SDL_WINDOW_BORDERLESS with any of the following:
 *               ::SDL_WINDOW_OPENGL,     ::SDL_WINDOW_INPUT_GRABBED,
 *               ::SDL_WINDOW_HIDDEN,     ::SDL_WINDOW_RESIZABLE,
 *               ::SDL_WINDOW_MAXIMIZED,  ::SDL_WINDOW_MINIMIZED,
 *       ::SDL_WINDOW_BORDERLESS is always set, and ::SDL_WINDOW_FULLSCREEN is always unset.
 *
 *  \return The window created, or NULL if window creation failed.
 *
 *  \sa SDL_DestroyWindow()
 extern DECLSPEC SDL_Window * SDLCALL SDL_CreateShapedWindow(const char *title,unsigned int x,unsigned int y,unsigned int w,unsigned int h,Uint32 flags);
*/
PHP_FUNCTION(SDL_CreateShapedWindow)
{
	php_create_window(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto SDL_Window SDL_CreateWindow(string title, int x, int y, int w, int h, int flags)

 *  \brief Create a window with the specified position, dimensions, and flags.
 *
 *  \param title The title of the window, in UTF-8 encoding.
 *  \param x     The x position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param y     The y position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param w     The width of the window.
 *  \param h     The height of the window.
 *  \param flags The flags for the window, a mask of any of the following:
 *               ::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 *               ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 *               ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 *               ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 *               ::SDL_WINDOW_ALLOW_HIGHDPI.
 *
 *  \return The id of the window created, or zero if window creation failed.
 *
 *  \sa SDL_DestroyWindow()
 extern DECLSPEC SDL_Window * SDLCALL SDL_CreateWindow(const char *title,
													   int x, int y, int w,
													   int h, Uint32 flags);
*/
PHP_FUNCTION(SDL_CreateWindow)
{
	php_create_window(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto SDL_Window::__construct(string title, int x, int y, int w, int h, int flags) */
static PHP_METHOD(SDL_Window, __construct)
{
	struct php_sdl_window *intern;
	zend_long x, y, w, h, flags;
	char *title;
	size_t title_len;
	zend_error_handling error_handling;

	intern = php_sdl_window_fetch_object(Z_OBJ_P(getThis()));

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "slllll", &title, &title_len, &x, &y, &w, &h, &flags))
	{
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	intern->window = SDL_CreateWindow(title, x, y, w, h, flags);
	intern->flags = 0;
	if (intern->window)
	{
		SDL_SetWindowData(intern->window, PHP_SDL_MAGICDATA, (void *)(unsigned long)Z_OBJ_HANDLE_P(getThis()));
	}
	else
	{
		zend_throw_exception(zend_exception_get_default(), "Can't create window", 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Window___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Window::__toString() */
static PHP_METHOD(SDL_Window, __toString)
{
	struct php_sdl_window *intern;
	char *buf = NULL;
	int buf_len;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	intern = php_sdl_window_fetch_object(Z_OBJ_P(getThis()));
	if (0 && intern->window)
	{
		int x, y, w, h;

		SDL_GetWindowPosition(intern->window, &x, &y);
		SDL_GetWindowSize(intern->window, &w, &h);
		buf_len = spprintf(&buf, 0, "SDL_Window(\"%s\",%d,%d,%d,%d,%u)", SDL_GetWindowTitle(intern->window), x, y, w, h, SDL_GetWindowFlags(intern->window));
		RETURN_STRINGL(buf, buf_len);
	}
	else
	{
		RETURN_STRING("SDL_Window()");
	}
}
/* }}} */

/* {{{ proto SDL_UpdateWindowSurface(SDL_Window window)

 *  \brief Copy the window surface to the screen.
 *
 *  \return 0 on success, or -1 on error.
 *
 *  \sa SDL_GetWindowSurface()
 *  \sa SDL_UpdateWindowSurfaceRects()
 extern DECLSPEC int SDLCALL SDL_UpdateWindowSurface(SDL_Window * window);
 */
PHP_FUNCTION(SDL_UpdateWindowSurface)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETURN_LONG(SDL_UpdateWindowSurface(window));
}
/* }}} */

/* {{{ proto SDL_DestroyWindow(SDL_Window window)

 *  \brief Destroy a window.
 extern DECLSPEC void SDLCALL SDL_DestroyWindow(SDL_Window * window);
 */
PHP_FUNCTION(SDL_DestroyWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_DestroyWindow(intern->window);
	intern->window = NULL;
}
/* }}} */

/* {{{ proto string SDL_GetWindowTitle(SDL_Window window)

 *  \brief Get the title of a window, in UTF-8 format.
 *
 *  \sa SDL_SetWindowTitle()
 extern DECLSPEC const char *SDLCALL SDL_GetWindowTitle(SDL_Window * window);
 */
PHP_FUNCTION(SDL_GetWindowTitle)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	RETURN_STRING(SDL_GetWindowTitle(window));
}
/* }}} */

/* {{{ proto void SDL_SetWindowTitle(SDL_Window window, string title)

 *  \brief Set the title of a window, in UTF-8 format.
 *
 *  \sa SDL_GetWindowTitle()
 extern DECLSPEC void SDLCALL SDL_SetWindowTitle(SDL_Window * window,
												 const char *title);
 */
PHP_FUNCTION(SDL_SetWindowTitle)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;
	char *title;
	size_t title_len;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os", &object, php_sdl_window_ce, &title, &title_len) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_SetWindowTitle(window, title);
}
/* }}} */

/* {{{ proto bool SDL_IsShapedWindow(SDL_Window window)

* \brief Return whether the given window is a shaped window.
 *
 * \param window The window to query for being shaped.
 *
 * \return SDL_TRUE if the window is a window that can be shaped, SDL_FALSE if the window is unshaped or NULL.
 * \sa SDL_CreateShapedWindow
extern DECLSPEC SDL_bool SDLCALL SDL_IsShapedWindow(const SDL_Window *window);
 */
PHP_FUNCTION(SDL_IsShapedWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_window_ce) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, object, 1);
	RETVAL_BOOL(SDL_IsShapedWindow(window));
}
/* }}} */

/* {{{ proto int SDL_SetWindowShape(SDL_Window window, SDL_Surface shape, SDL_WindowShapeMode shape_mode)

 * \brief Set the shape and parameters of a shaped window.
 *
 * \param window The shaped window whose parameters should be set.
 * \param shape A surface encoding the desired shape for the window.
 * \param shape_mode The parameters to set for the shaped window.
 *
 * \return 0 on success, SDL_INVALID_SHAPE_ARGUMENT on invalid an invalid shape argument, or SDL_NONSHAPEABLE_WINDOW
 *           if the SDL_Window* given does not reference a valid shaped window.
 *
 * \sa SDL_WindowShapeMode
 * \sa SDL_GetShapedWindowMode.
 extern DECLSPEC int SDLCALL SDL_SetWindowShape(SDL_Window *window,SDL_Surface *shape,SDL_WindowShapeMode *shape_mode);
 */
PHP_FUNCTION(SDL_SetWindowShape)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_surface, *z_mode;
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_WindowShapeMode *mode;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOO", &z_window, php_sdl_window_ce,
									 &z_surface, get_php_sdl_surface_ce(), &z_mode, get_php_sdl_windowshapemode_ce()) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	surface = zval_to_sdl_surface(z_surface);
	mode = zval_to_sdl_windowshapemode(z_mode);
	if (!surface)
	{
		php_error_docref(NULL, E_WARNING, "Invalid SDL_Surface object");
	}
	else if (!mode)
	{
		php_error_docref(NULL, E_WARNING, "Invalid SDL_WindowShapeMode object");
	}
	else
	{
		RETVAL_LONG(SDL_SetWindowShape(window, surface, mode));
	}
}
/* }}} */

/* {{{ proto int SDL_GetShapedWindowMode(SDL_Window window, SDL_WindowShapeMode &shape_mode)

 * \brief Get the shape parameters of a shaped window.
 *
 * \param window The shaped window whose parameters should be retrieved.
 * \param shape_mode An empty shape-mode structure to fill, or NULL to check whether the window has a shape.
 *
 * \return 0 if the window has a shape and, provided shape_mode was not NULL, shape_mode has been filled with the mode
 *           data, SDL_NONSHAPEABLE_WINDOW if the SDL_Window given is not a shaped window, or SDL_WINDOW_LACKS_SHAPE if
 *           the SDL_Window* given is a shapeable window currently lacking a shape.
 *
 * \sa SDL_WindowShapeMode
 * \sa SDL_SetWindowShape
 extern DECLSPEC int SDLCALL SDL_GetShapedWindowMode(SDL_Window *window,SDL_WindowShapeMode *shape_mode);
 */
PHP_FUNCTION(SDL_GetShapedWindowMode)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_mode;
	SDL_Window *window;
	SDL_WindowShapeMode mode;
	int ret;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_window, php_sdl_window_ce, &z_mode) == FAILURE)
	{
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	ret = SDL_GetShapedWindowMode(window, &mode);
	if (ret == 0)
	{
		zval_dtor(z_mode);
		sdl_windowshapemode_to_zval(&mode, z_mode);
	}
	RETVAL_LONG(ret);
}
/* }}} */

static const zend_function_entry php_sdl_window_methods[] = {
	PHP_ME(SDL_Window, __construct, arginfo_SDL_CreateWindow, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
		PHP_ME(SDL_Window, __toString, arginfo_class_SDL_Window___toString, ZEND_ACC_PUBLIC)

	/* non-static functions */
	PHP_FALIAS(UpdateSurface, SDL_UpdateWindowSurface, arginfo_window_none)
		PHP_FALIAS(Destroy, SDL_DestroyWindow, arginfo_window_none)
			PHP_FALIAS(GetTitle, SDL_GetWindowTitle, arginfo_window_none)
				PHP_FALIAS(SetTitle, SDL_SetWindowTitle, arginfo_SDL_Window_SetTitle)
					PHP_FALIAS(GetDisplayIndex, SDL_GetWindowDisplayIndex, arginfo_window_none)
						PHP_FALIAS(Show, SDL_ShowWindow, arginfo_window_none)
							PHP_FALIAS(Hide, SDL_HideWindow, arginfo_window_none)
								PHP_FALIAS(Raise, SDL_RaiseWindow, arginfo_window_none)
									PHP_FALIAS(Maximize, SDL_MaximizeWindow, arginfo_window_none)
										PHP_FALIAS(Minimize, SDL_MinimizeWindow, arginfo_window_none)
											PHP_FALIAS(Restore, SDL_RestoreWindow, arginfo_window_none)
												PHP_FALIAS(GetSurface, SDL_GetWindowSurface, arginfo_window_none)
													PHP_FALIAS(SetDisplayMode, SDL_SetWindowDisplayMode, arginfo_SDL_Window_SetDisplayMode)
														PHP_FALIAS(GetDisplayMode, SDL_GetWindowDisplayMode, arginfo_SDL_Window_GetDisplayMode)
															PHP_FALIAS(GetPixelFormat, SDL_GetWindowPixelFormat, arginfo_window_none)
																PHP_FALIAS(GetID, SDL_GetWindowID, arginfo_window_none)
																	PHP_FALIAS(GetFlags, SDL_GetWindowFlags, arginfo_window_none)
																		PHP_FALIAS(SetIcon, SDL_SetWindowIcon, arginfo_SDL_Window_SetIcon)
																			PHP_FALIAS(SetPosition, SDL_SetWindowPosition, arginfo_SDL_Window_SetPosition)
																				PHP_FALIAS(GetPosition, SDL_GetWindowPosition, arginfo_SDL_Window_GetPosition)
																					PHP_FALIAS(SetSize, SDL_SetWindowSize, arginfo_SDL_Window_SetSize)
																						PHP_FALIAS(GetSize, SDL_GetWindowSize, arginfo_SDL_Window_GetSize)
																							PHP_FALIAS(SetMinimumSize, SDL_SetWindowMinimumSize, arginfo_SDL_Window_SetPosition)
																								PHP_FALIAS(GetMinimumSize, SDL_GetWindowMinimumSize, arginfo_SDL_Window_GetPosition)
																									PHP_FALIAS(SetMaximumSize, SDL_SetWindowMaximumSize, arginfo_SDL_Window_SetPosition)
																										PHP_FALIAS(GetMaximumSize, SDL_GetWindowMaximumSize, arginfo_SDL_Window_GetPosition)
																											PHP_FALIAS(SetBordered, SDL_SetWindowBordered, arginfo_SDL_Window_SetBordered)
																												PHP_FALIAS(SetFullscreen, SDL_SetWindowFullscreen, arginfo_SDL_Window_SetFullscreen)
																													PHP_FALIAS(UpdateSurfaceRects, SDL_UpdateWindowSurfaceRects, arginfo_SDL_Window_UpdateSurfaceRects)
																														PHP_FALIAS(SetGrab, SDL_SetWindowGrab, arginfo_SDL_Window_SetGrab)
																															PHP_FALIAS(GetGrab, SDL_GetWindowGrab, arginfo_window_none)
																																PHP_FALIAS(SetBrightness, SDL_SetWindowBrightness, arginfo_SDL_Window_SetBrightness)
																																	PHP_FALIAS(GetBrightness, SDL_GetWindowBrightness, arginfo_window_none)
																																		PHP_FALIAS(GetGammaRamp, SDL_GetWindowGammaRamp, arginfo_SDL_Window_GetGammaRamp)
																																			PHP_FALIAS(GL_CreateContext, SDL_GL_CreateContext, arginfo_window_none)
																																				PHP_FALIAS(GL_MakeCurrent, SDL_GL_MakeCurrent, arginfo_SDL_GLContext)
#if SDL_VERSION_ATLEAST(2, 0, 1)
																																					PHP_FALIAS(GL_GetDrawableSize, SDL_GL_GetDrawableSize, arginfo_SDL_Window_GetPosition)
#endif
																																						PHP_FALIAS(GL_Swap, SDL_GL_SwapWindow, arginfo_window_none)
																																							PHP_FALIAS(WarpMouse, SDL_WarpMouseInWindow, arginfo_SDL_Window_SetPosition)
																																								PHP_FALIAS(IsShaped, SDL_IsShapedWindow, arginfo_window_none)
																																									PHP_FALIAS(SetShape, SDL_SetWindowShape, arginfo_SDL_Window_SetShape)
																																										PHP_FALIAS(GetShapedMode, SDL_GetShapedWindowMode, arginfo_SDL_Window_GetShapedMode)

	/* static methods */
	ZEND_FENTRY(GL_GetCurrent, ZEND_FN(SDL_GL_GetCurrentWindow), arginfo_window_none, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
		ZEND_FENTRY(GetMouseFocus, ZEND_FN(SDL_GetMouseFocus), arginfo_window_none, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

			PHP_FE_END};

/* {{{ php_sdl_window_free
 */
static void php_sdl_window_free(zend_object *zo)
{
	struct php_sdl_window *intern = (struct php_sdl_window *)((char *)zo - zo->handlers->offset);
	if (intern->window)
	{
		if (!(intern->flags & SDL_DONTFREE))
		{
			SDL_DestroyWindow(intern->window);
		}
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

/* {{{ php_sdl_window_new
 */
static zend_object *php_sdl_window_new(zend_class_entry *class_type)
{
	struct php_sdl_window *intern;

	intern = (struct php_sdl_window *)ecalloc(1, sizeof(struct php_sdl_window) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->window = NULL;

	php_sdl_window_handlers.offset = XtOffsetOf(struct php_sdl_window, zo);
	php_sdl_window_handlers.free_obj = php_sdl_window_free;
	intern->zo.handlers = &php_sdl_window_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ sdl_window_to_zval */
zend_bool sdl_window_to_zval(SDL_Window *window, zval *z_val, int flags)
{
	if (window)
	{
		struct php_sdl_window *intern;

		object_init_ex(z_val, php_sdl_window_ce);
		zend_object *zo = Z_OBJ_P(z_val);
		intern = (struct php_sdl_window *)((char *)zo - zo->handlers->offset);
		intern->window = window;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

#define REGISTER_WINDOW_CLASS_CONST_LONG(const_name, value)                               \
	REGISTER_LONG_CONSTANT("SDL_WINDOW_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_window_ce, ZEND_STRL(const_name), value);

#define REGISTER_WINDOWPOS_CLASS_CONST_LONG(const_name, value)                               \
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_window_ce, ZEND_STRL("POS_" const_name), value);

#define REGISTER_WINDOW_PROP(name) \
	zend_declare_property_long(php_sdl_window_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_window)
{
	zend_class_entry ce_window;

	INIT_CLASS_ENTRY(ce_window, "SDL_Window", php_sdl_window_methods);
	php_sdl_window_ce = zend_register_internal_class(&ce_window);
	php_sdl_window_ce->create_object = php_sdl_window_new;
	memcpy(&php_sdl_window_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_window_handlers.get_properties = sdl_window_get_properties;
	php_sdl_window_handlers.free_obj = php_sdl_window_free;
	php_sdl_window_handlers.offset = XtOffsetOf(struct php_sdl_window, zo);

	REGISTER_WINDOW_PROP("id");
	REGISTER_WINDOW_PROP("flags");
	REGISTER_WINDOW_PROP("x");
	REGISTER_WINDOW_PROP("y");
	REGISTER_WINDOW_PROP("w");
	REGISTER_WINDOW_PROP("h");

	zend_declare_property_null(php_sdl_window_ce, ZEND_STRL("title"), ZEND_ACC_PUBLIC);

	REGISTER_WINDOW_CLASS_CONST_LONG("FULLSCREEN", SDL_WINDOW_FULLSCREEN);
	REGISTER_WINDOW_CLASS_CONST_LONG("OPENGL", SDL_WINDOW_OPENGL);
	REGISTER_WINDOW_CLASS_CONST_LONG("SHOWN", SDL_WINDOW_SHOWN);
	REGISTER_WINDOW_CLASS_CONST_LONG("HIDDEN", SDL_WINDOW_HIDDEN);
	REGISTER_WINDOW_CLASS_CONST_LONG("BORDERLESS", SDL_WINDOW_BORDERLESS);
	REGISTER_WINDOW_CLASS_CONST_LONG("RESIZABLE", SDL_WINDOW_RESIZABLE);
	REGISTER_WINDOW_CLASS_CONST_LONG("MINIMIZED", SDL_WINDOW_MINIMIZED);
	REGISTER_WINDOW_CLASS_CONST_LONG("MAXIMIZED", SDL_WINDOW_MAXIMIZED);
	REGISTER_WINDOW_CLASS_CONST_LONG("INPUT_GRABBED", SDL_WINDOW_INPUT_GRABBED);
	REGISTER_WINDOW_CLASS_CONST_LONG("INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS);
	REGISTER_WINDOW_CLASS_CONST_LONG("MOUSE_FOCUS", SDL_WINDOW_MOUSE_FOCUS);
	REGISTER_WINDOW_CLASS_CONST_LONG("FULLSCREEN_DESKTOP", SDL_WINDOW_FULLSCREEN_DESKTOP);
	REGISTER_WINDOW_CLASS_CONST_LONG("FOREIGN", SDL_WINDOW_FOREIGN);
#if SDL_COMPILEDVERSION > 2000
	REGISTER_WINDOW_CLASS_CONST_LONG("ALLOW_HIGHDPI", SDL_WINDOW_ALLOW_HIGHDPI);
#endif
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("UNDEFINED_MASK", SDL_WINDOWPOS_UNDEFINED_MASK);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("UNDEFINED", SDL_WINDOWPOS_UNDEFINED);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("CENTERED_MASK", SDL_WINDOWPOS_CENTERED_MASK);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("CENTERED", SDL_WINDOWPOS_CENTERED);

	return SUCCESS;
}
/* }}} */
