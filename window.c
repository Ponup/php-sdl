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
  | wrapper for SDL2/SDL_video.h (only SDL_Window)                       |
  +----------------------------------------------------------------------+
  | class SDL_Window                                                     |
  +----------------------------------------------------------------------+
*/

/* Functions not wrapped

 extern DECLSPEC SDL_Window * SDLCALL SDL_CreateWindowFrom(const void *data);
*/

#include "php_sdl.h"
#include "rect.h"
#include "surface.h"
#include "video.h"

/* used to associate PHP object handle to SDL_Window */
#define PHP_SDL_MAGICDATA "__php__handle"

static zend_class_entry *php_sdl_window_ce;
static zend_object_handlers php_sdl_window_handlers;
struct php_sdl_window {
	zend_object   zo;
	SDL_Window   *window;
	Uint32        flags;
	/* allocation list, for window data */
	int           ndata;
	int           maxdata;
	void        **data;
};

zend_class_entry *get_php_sdl_window_ce(void)
{
	return php_sdl_window_ce;
}

/* {{{ sdl_window_to_zval */
zend_bool sdl_window_to_zval(SDL_Window *window, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (window) {
		struct php_sdl_window *intern;

		object_init_ex(z_val, php_sdl_window_ce);
		intern = (struct php_sdl_window *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->window = window;
		intern->flags  = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_window */
SDL_Window *zval_to_sdl_window(zval *z_val TSRMLS_DC)
{
	if (z_val && Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_window_ce) {
		struct php_sdl_window *intern;

		intern = (struct php_sdl_window *)zend_object_store_get_object(z_val TSRMLS_CC);
		return intern->window;
		}
	return NULL;
}
/* }}} */

static void php_add_window_data(struct php_sdl_window *intern, void *data) {
	if (intern->ndata == intern->maxdata) {
		if (intern->ndata) {
			intern->maxdata += 8;
			intern->data = erealloc(intern->data, sizeof(void *)*intern->maxdata);
		} else {
			intern->maxdata = 8;
			intern->data = emalloc(sizeof(void *)*intern->maxdata);
		}
	}
	intern->data[intern->ndata++] = data;
}

static void php_del_window_data(struct php_sdl_window *intern, void *data) {

	int i;

	for (i=0 ; i<intern->ndata && intern->data[i]!=data; i++);

	if (i<intern->ndata && intern->data[i]==data) {
		intern->ndata--;
		for (; i<intern->ndata ; i++) {
			intern->data[i] = intern->data[i+1];
		}
	}
}

#define FETCH_WINDOW(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_window *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->window; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}


/* {{{ proto void SDL_GetWindowDisplayIndex(SDL_Window window)

 *  \brief Get the display index associated with a window.
 *
 *  \return the display index of the display containing the center of the
 *          window, or -1 on error.
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayIndex(SDL_Window * window);
 */
static PHP_FUNCTION(SDL_GetWindowDisplayIndex)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);

	RETURN_LONG(SDL_GetWindowDisplayIndex(window));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, displaymode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_SetDisplayMode, 0, 0, 1)
       ZEND_ARG_INFO(0, displaymode)
ZEND_END_ARG_INFO()

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
static PHP_FUNCTION(SDL_SetWindowDisplayMode)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_mode;
	SDL_Window *window;
	SDL_DisplayMode mode;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &z_window, php_sdl_window_ce, &z_mode, get_php_sdl_displaymode_ce()) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	if (zval_to_sdl_displaymode(z_mode, &mode TSRMLS_CC)) {
		RETVAL_LONG(SDL_SetWindowDisplayMode(window, &mode));
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetWindowDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(1, displaymode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_GetDisplayMode, 0, 0, 1)
       ZEND_ARG_INFO(1, displaymode)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_GetWindowDisplayMode(SDL_Window window, SDL_DisplayMode mode)

 *  \brief Fill in information about the display mode used when a fullscreen
 *         window is visible.
 *
 *  \sa SDL_SetWindowDisplayMode()
 *  \sa SDL_SetWindowFullscreen()
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayMode(SDL_Window * window,
                                                      SDL_DisplayMode * mode);
 */
static PHP_FUNCTION(SDL_GetWindowDisplayMode)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_mode;
	SDL_Window *window;
	SDL_DisplayMode mode;
	int res;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz", &z_window, php_sdl_window_ce, &z_mode) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	res = SDL_GetWindowDisplayMode(window, &mode);
	if (0==res) {
		zval_dtor(z_mode);
		sdl_displaymode_to_zval(&mode, z_mode TSRMLS_CC);
	}
	RETVAL_LONG(res);
}
/* }}} */


/* {{{ proto int SDL_GetWindowPixelFormat(SDL_Window window)

 *  \brief Get the pixel format associated with the window.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowPixelFormat(SDL_Window * window);
 */
static PHP_FUNCTION(SDL_GetWindowPixelFormat)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_window, php_sdl_window_ce)) {
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
static PHP_FUNCTION(SDL_GetWindowID)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_window, php_sdl_window_ce)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_GetWindowID(window));
}
/* }}} */



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetWindowFromID, 0, 0, 1)
       ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Window SDL_GetWindowFromID(int id)

 *  \brief Get a window from a stored ID, or NULL if it doesn't exist.
 extern DECLSPEC SDL_Window * SDLCALL SDL_GetWindowFromID(Uint32 id);
 */
static PHP_FUNCTION(SDL_GetWindowFromID)
{
	long id;
	zend_object_handle h;
	SDL_Window *window;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &id)) {
		return;
	}
	window = SDL_GetWindowFromID((Uint32)id);
	if (window) {
		h = (zend_object_handle)(unsigned long)SDL_GetWindowData(window, PHP_SDL_MAGICDATA);
		if (h) {
			Z_TYPE_P(return_value) = IS_OBJECT;
			Z_OBJ_HANDLE_P(return_value) = h;
			Z_OBJ_HT_P(return_value) = (zend_object_handlers *) &php_sdl_window_handlers;
			zend_objects_store_add_ref(return_value TSRMLS_CC);
		}
	}
}

/* {{{ proto int SDL_GetWindowFlags(SDL_Window window)

 *  \brief Get the window flags.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window * window);
 */
static PHP_FUNCTION(SDL_GetWindowFlags)
{
	struct php_sdl_window *intern;
	zval *z_window;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_window, php_sdl_window_ce)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	RETVAL_LONG(SDL_GetWindowFlags(window));
}
/* }}} */



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowIcon, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, icon)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_SetIcon, 0, 0, 1)
       ZEND_ARG_INFO(0, icon)
ZEND_END_ARG_INFO()

/* {{{ proto void SDL_SetWindowIcon(SDL Window window, SDL_Surface icon)

 *  \brief Set the icon for a window.
 *
 *  \param window The window for which the icon should be set.
 *  \param icon The icon for the window.
 extern DECLSPEC void SDLCALL SDL_SetWindowIcon(SDL_Window * window,
                                                SDL_Surface * icon);
 */
static PHP_FUNCTION(SDL_SetWindowIcon)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_icon;
	SDL_Window *window;
	SDL_Surface *icon;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OO", &z_window, php_sdl_window_ce, &z_icon, get_php_sdl_surface_ce())) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	icon = zval_to_sdl_surface(z_icon TSRMLS_CC);

	if (icon) {
		SDL_SetWindowIcon(window, icon);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid SDL_Surface object");
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowData, 0, 0, 3)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, name)
       ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_SetData, 0, 0, 2)
       ZEND_ARG_INFO(0, name)
       ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

/* {{{ proto string SDL_SetWindowData(SDL Window window, string name, string value)

 *  \brief Associate an arbitrary named pointer with a window.
 *
 *  \param window   The window to associate with the pointer.
 *  \param name     The name of the pointer.
 *  \param userdata The associated pointer.
 *
 *  \return The previous value associated with 'name'
 *
 *  \note The name is case-sensitive.
 *
 *  \sa SDL_GetWindowData()
 extern DECLSPEC void* SDLCALL SDL_SetWindowData(SDL_Window * window,
                                                 const char *name,
                                                 void *userdata);
 */
static PHP_FUNCTION(SDL_SetWindowData)
{
	struct php_sdl_window *intern;
	zval *z_window;
	char *name, *value, *old;
	int name_len, value_len;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oss", &z_window, php_sdl_window_ce, &name, &name_len, &value, &value_len)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	if (!strcmp(name, PHP_SDL_MAGICDATA)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid name (reserved for internal use)");
		return;
	}
	value = estrndup(value, value_len);
	old = SDL_SetWindowData(window, name, value);
	php_add_window_data(intern, value);
	if (old) {
		php_del_window_data(intern, old);
		RETVAL_STRING(old, 0);
	} else {
		RETVAL_NULL();
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetWindowData, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_GetData, 0, 0, 1)
       ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/* {{{ proto string SDL_GetWindowData(SDL Window window, string name)

 *  \brief Retrieve the data pointer associated with a window.
 *
 *  \param window   The window to query.
 *  \param name     The name of the pointer.
 *
 *  \return The value associated with 'name'
 *
 *  \sa SDL_SetWindowData()
 extern DECLSPEC void *SDLCALL SDL_GetWindowData(SDL_Window * window,
                                                 const char *name);
 */
static PHP_FUNCTION(SDL_GetWindowData)
{
	struct php_sdl_window *intern;
	zval *z_window;
	char *name, *value;
	int name_len;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &z_window, php_sdl_window_ce, &name, &name_len)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	if (!strcmp(name, PHP_SDL_MAGICDATA)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid name (reserved for internal use)");
		return;
	}
	name = estrndup(name, name_len);
	value = SDL_GetWindowData(window, name);
	if (value) {
		RETVAL_STRING(value, 1);
	} else {
		RETVAL_NULL();
	}
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowPosition, 0, 0, 3)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_SetPosition, 0, 0, 2)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

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
static PHP_FUNCTION(SDL_SetWindowPosition)
{
	struct php_sdl_window *intern;
	zval *z_window;
	long x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &z_window, php_sdl_window_ce, &x, &y)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_SetWindowPosition(window, x, y);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WINDOWPOS_DISPLAY, 0, 0, 1)
       ZEND_ARG_INFO(0, display)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_WINDOWPOS_CENTERED_DISPLAY(int)

 define SDL_WINDOWPOS_CENTERED_DISPLAY(X)  (SDL_WINDOWPOS_CENTERED_MASK|(X))
*/
static PHP_FUNCTION(SDL_WINDOWPOS_CENTERED_DISPLAY)
{
	long display;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "l", &display)) {
		return;
	}
	RETVAL_LONG(SDL_WINDOWPOS_CENTERED_DISPLAY(display));
}
/* }}} */


/* {{{ proto int SDL_WINDOWPOS_UNDEFINED_DISPLAY(int)

 define SDL_WINDOWPOS_UNDEFINED_DISPLAY(X)  (SDL_WINDOWPOS_UNDEFINED_MASK|(X))
*/
static PHP_FUNCTION(SDL_WINDOWPOS_UNDEFINED_DISPLAY)
{
	long display;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "l", &display)) {
		return;
	}
	RETVAL_LONG(SDL_WINDOWPOS_UNDEFINED_DISPLAY(display));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetWindowPosition, 0, 0, 1)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(1, x)
       ZEND_ARG_INFO(1, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_GetPosition, 0, 0, 0)
       ZEND_ARG_INFO(1, x)
       ZEND_ARG_INFO(1, y)
ZEND_END_ARG_INFO()

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
static PHP_FUNCTION(SDL_GetWindowPosition)
{
	struct php_sdl_window *intern;
	zval *z_window, *z_x=NULL, *z_y=NULL;
	int x, y;
	SDL_Window *window;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|zz", &z_window, php_sdl_window_ce, &z_x, &z_y)) {
		return;
	}
	FETCH_WINDOW(window, z_window, 1);
	SDL_GetWindowPosition(window, &x, &y);
	if (z_x) {
		zval_dtor(z_x);
		ZVAL_LONG(z_x, x);
	}
	if (z_y) {
		zval_dtor(z_y);
		ZVAL_LONG(z_y, y);
	}
}
/* }}} */

/**
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

/**
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

/**
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

/**
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

/**
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

/**
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

/**
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


/* {{{ proto void SDL_ShowWindow(SDL_Window window)

 *  \brief Show a window.
 *
 *  \sa SDL_HideWindow()
 extern DECLSPEC void SDLCALL SDL_ShowWindow(SDL_Window * window);
 */
static PHP_FUNCTION(SDL_ShowWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_HideWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_RaiseWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_MaximizeWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_MinimizeWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_RestoreWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_RestoreWindow(window);
}
/* }}} */


/**
 *  \brief Set a window's fullscreen state.
 *
 *  \return 0 on success, or -1 if setting the display mode failed.
 *
 *  \sa SDL_SetWindowDisplayMode()
 *  \sa SDL_GetWindowDisplayMode()
 extern DECLSPEC int SDLCALL SDL_SetWindowFullscreen(SDL_Window * window,
                                                     Uint32 flags);
 */

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
static PHP_FUNCTION(SDL_GetWindowSurface)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;
	SDL_Surface *surface;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);

	surface = SDL_GetWindowSurface(window);
	sdl_surface_to_zval(surface, return_value TSRMLS_CC);
}
/* }}} */


/**
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

/**
 *  \brief Set a window's input grab mode.
 *
 *  \param window The window for which the input grab mode should be set.
 *  \param grabbed This is SDL_TRUE to grab input, and SDL_FALSE to release input.
 *
 *  \sa SDL_GetWindowGrab()
 extern DECLSPEC void SDLCALL SDL_SetWindowGrab(SDL_Window * window,
                                                SDL_bool grabbed);
 */

/**
 *  \brief Get a window's input grab mode.
 *
 *  \return This returns SDL_TRUE if input is grabbed, and SDL_FALSE otherwise.
 *
 *  \sa SDL_SetWindowGrab()
 extern DECLSPEC SDL_bool SDLCALL SDL_GetWindowGrab(SDL_Window * window);
 */

/**
 *  \brief Set the brightness (gamma correction) for a window.
 *
 *  \return 0 on success, or -1 if setting the brightness isn't supported.
 *
 *  \sa SDL_GetWindowBrightness()
 *  \sa SDL_SetWindowGammaRamp()
 extern DECLSPEC int SDLCALL SDL_SetWindowBrightness(SDL_Window * window, float brightness);
 */

/**
 *  \brief Get the brightness (gamma correction) for a window.
 *
 *  \return The last brightness value passed to SDL_SetWindowBrightness()
 *
 *  \sa SDL_SetWindowBrightness()
 extern DECLSPEC float SDLCALL SDL_GetWindowBrightness(SDL_Window * window);
 */

/**
 *  \brief Set the gamma ramp for a window.
 *
 *  \param window The window for which the gamma ramp should be set.
 *  \param red The translation table for the red channel, or NULL.
 *  \param green The translation table for the green channel, or NULL.
 *  \param blue The translation table for the blue channel, or NULL.
 *
 *  \return 0 on success, or -1 if gamma ramps are unsupported.
 *
 *  Set the gamma translation table for the red, green, and blue channels
 *  of the video hardware.  Each table is an array of 256 16-bit quantities,
 *  representing a mapping between the input and output for that channel.
 *  The input is the index into the array, and the output is the 16-bit
 *  gamma value at that index, scaled to the output color precision.
 *
 *  \sa SDL_GetWindowGammaRamp()
 extern DECLSPEC int SDLCALL SDL_SetWindowGammaRamp(SDL_Window * window,
                                                    const Uint16 * red,
                                                    const Uint16 * green,
                                                    const Uint16 * blue);
 */

/**
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
 *  \sa SDL_SetWindowGammaRamp()
 extern DECLSPEC int SDLCALL SDL_GetWindowGammaRamp(SDL_Window * window,
                                                    Uint16 * red,
                                                    Uint16 * green,
                                                    Uint16 * blue);
 */


/**
 *  \name OpenGL support functions
 */
/* @{ */

/**
 *  \brief Dynamically load an OpenGL library.
 *
 *  \param path The platform dependent OpenGL library name, or NULL to open the
 *              default OpenGL library.
 *
 *  \return 0 on success, or -1 if the library couldn't be loaded.
 *
 *  This should be done after initializing the video driver, but before
 *  creating any OpenGL windows.  If no OpenGL library is loaded, the default
 *  library will be loaded upon creation of the first OpenGL window.
 *
 *  \note If you do this, you need to retrieve all of the GL functions used in
 *        your program from the dynamic library using SDL_GL_GetProcAddress().
 *
 *  \sa SDL_GL_GetProcAddress()
 *  \sa SDL_GL_UnloadLibrary()
 extern DECLSPEC int SDLCALL SDL_GL_LoadLibrary(const char *path);
 */

/**
 *  \brief Get the address of an OpenGL function.
 extern DECLSPEC void *SDLCALL SDL_GL_GetProcAddress(const char *proc);
 */

/**
 *  \brief Unload the OpenGL library previously loaded by SDL_GL_LoadLibrary().
 *
 *  \sa SDL_GL_LoadLibrary()
 extern DECLSPEC void SDLCALL SDL_GL_UnloadLibrary(void);
 */

/**
 *  \brief Return true if an OpenGL extension is supported for the current
 *         context.
 extern DECLSPEC SDL_bool SDLCALL SDL_GL_ExtensionSupported(const char
                                                            *extension);
 */

/**
 *  \brief Set an OpenGL window attribute before window creation.
 extern DECLSPEC int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value);
 */

/**
 *  \brief Get the actual value for an attribute from the current context.
 extern DECLSPEC int SDLCALL SDL_GL_GetAttribute(SDL_GLattr attr, int *value);
 */

/**
 *  \brief Create an OpenGL context for use with an OpenGL window, and make it
 *         current.
 *
 *  \sa SDL_GL_DeleteContext()
 extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window *
                                                            window);
 */

/**
 *  \brief Set up an OpenGL context for rendering into an OpenGL window.
 *
 *  \note The context must have been created with a compatible window.
 extern DECLSPEC int SDLCALL SDL_GL_MakeCurrent(SDL_Window * window,
                                                SDL_GLContext context);
 */

/**
 *  \brief Get the currently active OpenGL window.
 extern DECLSPEC SDL_Window* SDLCALL SDL_GL_GetCurrentWindow(void);
 */

/**
 *  \brief Get the currently active OpenGL context.
 extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void);
 */

/**
 *  \brief Get the size of a window's underlying drawable (for use with glViewport).
 *
 *  \param window   Window from which the drawable size should be queried
 *  \param w        Pointer to variable for storing the width, may be NULL
 *  \param h        Pointer to variable for storing the height, may be NULL
 *
 * This may differ from SDL_GetWindowSize if we're rendering to a high-DPI
 * drawable, i.e. the window was created with SDL_WINDOW_ALLOW_HIGHDPI on a
 * platform with high-DPI support (Apple calls this "Retina"), and not disabled
 * by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
 *
 *  \sa SDL_GetWindowSize()
 *  \sa SDL_CreateWindow()
 extern DECLSPEC void SDLCALL SDL_GL_GetDrawableSize(SDL_Window * window, int *w,
                                                     int *h);
 */

/**
 *  \brief Set the swap interval for the current OpenGL context.
 *
 *  \param interval 0 for immediate updates, 1 for updates synchronized with the
 *                  vertical retrace. If the system supports it, you may
 *                  specify -1 to allow late swaps to happen immediately
 *                  instead of waiting for the next retrace.
 *
 *  \return 0 on success, or -1 if setting the swap interval is not supported.
 *
 *  \sa SDL_GL_GetSwapInterval()
 extern DECLSPEC int SDLCALL SDL_GL_SetSwapInterval(int interval);
 */

/**
 *  \brief Get the swap interval for the current OpenGL context.
 *
 *  \return 0 if there is no vertical retrace synchronization, 1 if the buffer
 *          swap is synchronized with the vertical retrace, and -1 if late
 *          swaps happen immediately instead of waiting for the next retrace.
 *          If the system can't determine the swap interval, or there isn't a
 *          valid current context, this will return 0 as a safe default.
 *
 *  \sa SDL_GL_SetSwapInterval()
 extern DECLSPEC int SDLCALL SDL_GL_GetSwapInterval(void);
 */

/**
 * \brief Swap the OpenGL buffers for a window, if double-buffering is
 *        supported.
 extern DECLSPEC void SDLCALL SDL_GL_SwapWindow(SDL_Window * window);
 */

/**
 *  \brief Delete an OpenGL context.
 *
 *  \sa SDL_GL_CreateContext()
 extern DECLSPEC void SDLCALL SDL_GL_DeleteContext(SDL_GLContext context);
 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateWindow, 0, 0, 6)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

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
static PHP_FUNCTION(SDL_CreateWindow)
{
	struct php_sdl_window *intern;
	long x, y, w, h, flags;
	char *title;
	int  *title_len;
	SDL_Window *window;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slllll", &title, &title_len, &x, &y, &w, &h, &flags)) {
		return;
	}
	window = SDL_CreateWindow(title, x, y, w, h, flags);
	if (window) {
		object_init_ex(return_value, php_sdl_window_ce);
		intern = (struct php_sdl_window *)zend_object_store_get_object(return_value TSRMLS_CC);
		intern->window = window;
		intern->flags  = 0;

		SDL_SetWindowData(intern->window, PHP_SDL_MAGICDATA, (void *)(unsigned long)Z_OBJ_HANDLE_P(return_value));
	}
}
/* }}} */

/* {{{ proto SDL_Window, __construct(string title, int x, int y, int w, int h, int flags)
 */
static PHP_METHOD(SDL_Window, __construct)
{
	struct php_sdl_window *intern;
	long x, y, w, h, flags;
	char *title;
	int  *title_len;
	zend_error_handling error_handling;

	intern = (struct php_sdl_window *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slllll", &title, &title_len, &x, &y, &w, &h, &flags)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->window = SDL_CreateWindow(title, x, y, w, h, flags);
	intern->flags  = 0;
	if (intern->window) {
		SDL_SetWindowData(intern->window, PHP_SDL_MAGICDATA, (void *)(unsigned long)Z_OBJ_HANDLE_P(getThis()));
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Can't create window", 0 TSRMLS_CC);
	}
}
/* }}} */


/* {{{ proto SDL_Window::__toString()
*/
static PHP_METHOD(SDL_Window, __toString)
{
	struct php_sdl_window *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_window *)zend_object_store_get_object(getThis() TSRMLS_CC);
	if (intern->window) {
		int x, y, w, h;

		SDL_GetWindowPosition(intern->window, &x, &y);
		SDL_GetWindowSize(intern->window, &w, &h);
		spprintf(&buf, 100, "SDL_Window(\"%s\",%d,%d,%d,%d,%u)",
			SDL_GetWindowTitle(intern->window), x, y, w, h, SDL_GetWindowFlags(intern->window));
		RETVAL_STRING(buf, 0);
	} else {
		RETVAL_STRING("SDL_Window()", 1);
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
static PHP_FUNCTION(SDL_UpdateWindowSurface)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);
	RETURN_LONG(SDL_UpdateWindowSurface(window));
}
/* }}} */


/* {{{ proto SDL_DestroyWindow(SDL_Window window)

 *  \brief Destroy a window.
 extern DECLSPEC void SDLCALL SDL_DestroyWindow(SDL_Window * window);
 */
static PHP_FUNCTION(SDL_DestroyWindow)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_GetWindowTitle)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_window_ce) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);

	RETURN_STRING(SDL_GetWindowTitle(window), 1);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetWindowTitle, 0, 0, 2)
       ZEND_ARG_INFO(0, window)
       ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window_SetTitle, 0, 0, 1)
       ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

/* {{{ proto void SDL_SetWindowTitle(SDL_Window window, string title)

 *  \brief Set the title of a window, in UTF-8 format.
 *
 *  \sa SDL_GetWindowTitle()
 extern DECLSPEC void SDLCALL SDL_SetWindowTitle(SDL_Window * window,
                                                 const char *title);
 */
static PHP_FUNCTION(SDL_SetWindowTitle)
{
	struct php_sdl_window *intern;
	zval *object;
	SDL_Window *window;
	char *title;
	int  *title_len;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &object, php_sdl_window_ce, &title, &title_len) == FAILURE) {
		return;
	}
	FETCH_WINDOW(window, object, 1);

	SDL_SetWindowTitle(window, title);
}
/* }}} */

/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_window_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window, 0, 0, 1)
       ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()


/* {{{ sdl_window_functions[] */
zend_function_entry sdl_window_functions[] = {
	ZEND_FE(SDL_CreateWindow,				arginfo_SDL_CreateWindow)
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
	ZEND_FE(SDL_WINDOWPOS_UNDEFINED_DISPLAY,	arginfo_SDL_WINDOWPOS_DISPLAY)
	ZEND_FE(SDL_WINDOWPOS_CENTERED_DISPLAY,	arginfo_SDL_WINDOWPOS_DISPLAY)

	ZEND_FE_END
};
/* }}} */

static const zend_function_entry php_sdl_window_methods[] = {
	PHP_ME(SDL_Window, __construct,     arginfo_SDL_CreateWindow, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Window, __toString,      arginfo_window_none,      ZEND_ACC_PUBLIC)

	PHP_FALIAS(UpdateSurface,    SDL_UpdateWindowSurface,     arginfo_window_none)
	PHP_FALIAS(Destroy,          SDL_DestroyWindow,           arginfo_window_none)
	PHP_FALIAS(GetTitle,         SDL_GetWindowTitle,          arginfo_window_none)
	PHP_FALIAS(SetTitle,         SDL_SetWindowTitle,          arginfo_SDL_Window_SetTitle)
	PHP_FALIAS(GetDisplayIndex,  SDL_GetWindowDisplayIndex,   arginfo_window_none)
	PHP_FALIAS(Show,             SDL_ShowWindow,              arginfo_window_none)
	PHP_FALIAS(Hide,             SDL_HideWindow,              arginfo_window_none)
	PHP_FALIAS(Raise,            SDL_RaiseWindow,             arginfo_window_none)
	PHP_FALIAS(Maximize,         SDL_MaximizeWindow,          arginfo_window_none)
	PHP_FALIAS(Minimize,         SDL_MinimizeWindow,          arginfo_window_none)
	PHP_FALIAS(Restore,          SDL_RestoreWindow,           arginfo_window_none)
	PHP_FALIAS(GetSurface,       SDL_GetWindowSurface,        arginfo_window_none)
	PHP_FALIAS(SetDisplayMode,   SDL_SetWindowDisplayMode,    arginfo_SDL_Window_SetDisplayMode)
	PHP_FALIAS(GetDisplayMode,   SDL_GetWindowDisplayMode,    arginfo_SDL_Window_GetDisplayMode)
	PHP_FALIAS(GetPixelFormat,   SDL_GetWindowPixelFormat,    arginfo_window_none)
	PHP_FALIAS(GetID,            SDL_GetWindowID,             arginfo_window_none)
	PHP_FALIAS(GetFlags,         SDL_GetWindowFlags,          arginfo_window_none)
	PHP_FALIAS(SetData,          SDL_SetWindowData,           arginfo_SDL_Window_SetData)
	PHP_FALIAS(GetData,          SDL_GetWindowData,           arginfo_SDL_Window_GetData)
	PHP_FALIAS(SetIcon,          SDL_SetWindowIcon,           arginfo_SDL_Window_SetIcon)
	PHP_FALIAS(SetPosition,      SDL_SetWindowPosition,       arginfo_SDL_Window_SetPosition)
	PHP_FALIAS(GetPosition,      SDL_GetWindowPosition,       arginfo_SDL_Window_GetPosition)

	PHP_FE_END
};

/* {{{ php_sdl_window_free
	 */
static void php_sdl_window_free(void *object TSRMLS_DC)
{
	struct php_sdl_window *intern = (struct php_sdl_window *) object;

	if (intern->window) {
		int i;

		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_DestroyWindow(intern->window);
		}
		for (i=0 ; i<intern->ndata ; i++) {
			efree(intern->data[i]);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_window_new
 */
static zend_object_value php_sdl_window_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_window *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->window  = NULL;
	intern->ndata   = 0;
	intern->maxdata = 0;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_window_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_window_handlers;

	return retval;
}
/* }}} */


#define REGISTER_WINDOW_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_WINDOW_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_window_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC); \

#define REGISTER_WINDOWPOS_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_WINDOWPOS_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_window_ce, "POS_" const_name, sizeof("POS_" const_name)-1, value TSRMLS_CC); \

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_window)
{
	zend_class_entry ce_window;

	INIT_CLASS_ENTRY(ce_window, "SDL_Window", php_sdl_window_methods);
	ce_window.create_object = php_sdl_window_new;
	php_sdl_window_ce = zend_register_internal_class(&ce_window TSRMLS_CC);
	memcpy(&php_sdl_window_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_WINDOW_CLASS_CONST_LONG("FULLSCREEN",         SDL_WINDOW_FULLSCREEN);
	REGISTER_WINDOW_CLASS_CONST_LONG("OPENGL",             SDL_WINDOW_OPENGL);
	REGISTER_WINDOW_CLASS_CONST_LONG("SHOWN",              SDL_WINDOW_SHOWN);
	REGISTER_WINDOW_CLASS_CONST_LONG("HIDDEN",             SDL_WINDOW_HIDDEN);
	REGISTER_WINDOW_CLASS_CONST_LONG("BORDERLESS",         SDL_WINDOW_BORDERLESS);
	REGISTER_WINDOW_CLASS_CONST_LONG("RESIZABLE",          SDL_WINDOW_RESIZABLE);
	REGISTER_WINDOW_CLASS_CONST_LONG("MINIMIZED",          SDL_WINDOW_MINIMIZED);
	REGISTER_WINDOW_CLASS_CONST_LONG("MAXIMIZED",          SDL_WINDOW_MAXIMIZED);
	REGISTER_WINDOW_CLASS_CONST_LONG("INPUT_GRABBED",      SDL_WINDOW_INPUT_GRABBED);
	REGISTER_WINDOW_CLASS_CONST_LONG("INPUT_FOCUS",        SDL_WINDOW_INPUT_FOCUS);
	REGISTER_WINDOW_CLASS_CONST_LONG("MOUSE_FOCUS",        SDL_WINDOW_MOUSE_FOCUS);
	REGISTER_WINDOW_CLASS_CONST_LONG("FULLSCREEN_DESKTOP", SDL_WINDOW_FULLSCREEN_DESKTOP);
	REGISTER_WINDOW_CLASS_CONST_LONG("FOREIGN",            SDL_WINDOW_FOREIGN);
#if SDL_COMPILEDVERSION > 2000
	REGISTER_WINDOW_CLASS_CONST_LONG("ALLOW_HIGHDPI",      SDL_WINDOW_ALLOW_HIGHDPI);
#endif
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("UNDEFINED_MASK",  SDL_WINDOWPOS_UNDEFINED_MASK);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("UNDEFINED",       SDL_WINDOWPOS_UNDEFINED);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("CENTERED_MASK",   SDL_WINDOWPOS_CENTERED_MASK);
	REGISTER_WINDOWPOS_CLASS_CONST_LONG("CENTERED",        SDL_WINDOWPOS_CENTERED);

	return (zend_register_functions(NULL, sdl_window_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
