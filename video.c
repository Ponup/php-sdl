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
#include "rect.h"

zend_class_entry *php_sdl_window_ce;

static zend_object_handlers php_sdl_window_handlers;

struct php_sdl_window {
	zend_object   zo;
	SDL_Window   *window;
};

void DisplayModeToArray(SDL_DisplayMode *dm, zval **z) {
	array_init(*z);
	add_assoc_long(*z, "format",  dm->format);
	add_assoc_long(*z, "w",       dm->w);
	add_assoc_long(*z, "h",       dm->h);
	add_assoc_long(*z, "refresh", dm->refresh_rate);
}

/* {{{ proto int SDL_GetNumVideoDrivers(void)

 *  \brief Get the number of video drivers compiled into SDL
 *
 *  \sa SDL_GetVideoDriver()
 extern DECLSPEC int SDLCALL SDL_GetNumVideoDrivers(void);
*/
PHP_FUNCTION(SDL_GetNumVideoDrivers)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetNumVideoDrivers());
}
/* }}} */


/* {{{ proto string SDL_GetVideoDriver(int driverIndex)

 *  \brief Get the name of a built in video driver.
 *
 *  \note The video drivers are presented in the order in which they are
 *        normally checked during initialization.
 *
 *  \sa SDL_GetNumVideoDrivers()
 extern DECLSPEC const char *SDLCALL SDL_GetVideoDriver(int index);
*/
PHP_FUNCTION(SDL_GetVideoDriver)
{
	long driver;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &driver) == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetVideoDriver((int)driver);
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name, 1);
}
/* }}} */


/* {{{ proto string SDL_VideoInit([string driver])

 *  \brief Initialize the video subsystem, optionally specifying a video driver.
 *
 *  \param driver_name Initialize a specific driver by name, or NULL for the
 *                     default video driver.
 *
 *  \return 0 on success, -1 on error
 *
 *  This function initializes the video subsystem; setting up a connection
 *  to the window manager, etc, and determines the available display modes
 *  and pixel formats, but does not initialize a window or graphics mode.
 *
 *  \sa SDL_VideoQuit()
 extern DECLSPEC int SDLCALL SDL_VideoInit(const char *driver_name);
 */
PHP_FUNCTION(SDL_VideoInit)
{
	char *name = NULL;
	int  name_len = 0, res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &name, &name_len) == FAILURE) {
		RETURN_FALSE;
	}
	if (name && name_len) {
		res = SDL_VideoInit(name);
	} else {
		res = SDL_VideoInit(NULL);
	}
	RETURN_LONG(res);
}
/* }}} */


/* {{{ proto void SDL_VideoQuit(void)

 *  \brief Shuts down the video subsystem.
 *
 *  This function closes all windows, and restores the original video mode.
 *
 *  \sa SDL_VideoInit()
 extern DECLSPEC void SDLCALL SDL_VideoQuit(void);
 */
PHP_FUNCTION(SDL_VideoQuit)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	SDL_VideoQuit();
}
/* }}} */


/* {{{ proto string SDL_GetCurrentVideoDriver(void)

 *  \brief Returns the name of the currently initialized video driver.
 *
 *  \return The name of the current video driver or NULL if no driver
 *          has been initialized
 *
 *  \sa SDL_GetNumVideoDrivers()
 *  \sa SDL_GetVideoDriver()
 extern DECLSPEC const char *SDLCALL SDL_GetCurrentVideoDriver(void);
 */
PHP_FUNCTION(SDL_GetCurrentVideoDriver)
{
	const char *name;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetCurrentVideoDriver();
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto int SDL_GetNumVideoDisplays(void)

 *  \brief Returns the number of available video displays.
 *
 *  \sa SDL_GetDisplayBounds()
 extern DECLSPEC int SDLCALL SDL_GetNumVideoDisplays(void);
 */
PHP_FUNCTION(SDL_GetNumVideoDisplays)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetNumVideoDisplays());
}
/* }}} */


/* {{{ proto string SDL_GetDisplayName(int displayIndex)

 *  \brief Get the name of a display in UTF-8 encoding
 *
 *  \return The name of a display, or NULL for an invalid display index.
 *
 *  \sa SDL_GetNumVideoDisplays()
 extern DECLSPEC const char * SDLCALL SDL_GetDisplayName(int displayIndex);
*/
PHP_FUNCTION(SDL_GetDisplayName)
{
	long display;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetDisplayName((int)display);
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto array SDL_GetDisplayBounds(int displayIndex, SDL_Rect &rect)

 *  \brief Get the desktop area represented by a display, with the primary
 *         display located at 0,0
 *
 *  \return 0 on success, or -1 if the index is out of range.
 *
 *  \sa SDL_GetNumVideoDisplays()
 extern DECLSPEC int SDLCALL SDL_GetDisplayBounds(int displayIndex, SDL_Rect * rect);
 */
PHP_FUNCTION(SDL_GetDisplayBounds)
{
	long display, err;
	SDL_Rect rect;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &display, &result) == FAILURE) {
		RETURN_FALSE;
	}
	err = SDL_GetDisplayBounds((int)display, &rect);
	if (!err) {
		zval_dtor(result);
		sdl_rect_to_zval(&rect, result TSRMLS_CC);
	}
	RETURN_LONG(err);
}
/* }}} */


/* {{{ proto int SDL_GetNumDisplayModes(int displayIndex)

 *  \brief Returns the number of available display modes.
 *
 *  \sa SDL_GetDisplayMode()
 extern DECLSPEC int SDLCALL SDL_GetNumDisplayModes(int displayIndex);
 */
PHP_FUNCTION(SDL_GetNumDisplayModes)
{
	long display;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &display) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetNumDisplayModes((int)display));
}
/* }}} */


/* {{{ proto array SDL_GetDisplayMode(int displayIndex, int modeIndex)

 *  \brief Fill in information about a specific display mode.
 *
 *  \note The display modes are sorted in this priority:
 *        \li bits per pixel -> more colors to fewer colors
 *        \li width -> largest to smallest
 *        \li height -> largest to smallest
 *        \li refresh rate -> highest to lowest
 *
 *  \sa SDL_GetNumDisplayModes()
 extern DECLSPEC int SDLCALL SDL_GetDisplayMode(int displayIndex, int modeIndex,
                                               SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetDisplayMode)
{
	long display, mode;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &display, &mode) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetDisplayMode((int)display, (int)mode, &dm)) {
		RETURN_FALSE;
	}
	DisplayModeToArray(&dm, &return_value);
}
/* }}} */

/* {{{ proto array SDL_GetDesktopDisplayMode(int displayIndex)

 *  \brief Fill in information about the desktop display mode.
 extern DECLSPEC int SDLCALL SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetDesktopDisplayMode)
{
	long display;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetDesktopDisplayMode((int)display, &dm)) {
		RETURN_FALSE;
	}
	DisplayModeToArray(&dm, &return_value);
}
/* }}} */


/* {{{ proto array SDL_GetCurrentDisplayMode(int displayIndex)

 *  \brief Fill in information about the current display mode.
 extern DECLSPEC int SDLCALL SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetCurrentDisplayMode)
{
	long display;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetCurrentDisplayMode((int)display, &dm)) {
		RETURN_FALSE;
	}
	DisplayModeToArray(&dm, &return_value);
}
/* }}} */

/**
 *  \brief Get the closest match to the requested display mode.
 *
 *  \param displayIndex The index of display from which mode should be queried.
 *  \param mode The desired display mode
 *  \param closest A pointer to a display mode to be filled in with the closest
 *                 match of the available display modes.
 *
 *  \return The passed in value \c closest, or NULL if no matching video mode
 *          was available.
 *
 *  The available display modes are scanned, and \c closest is filled in with the
 *  closest mode matching the requested mode and returned.  The mode format and
 *  refresh_rate default to the desktop mode if they are 0.  The modes are
 *  scanned with size being first priority, format being second priority, and
 *  finally checking the refresh_rate.  If all the available modes are too
 *  small, then NULL is returned.
 *
 *  \sa SDL_GetNumDisplayModes()
 *  \sa SDL_GetDisplayMode()
 extern DECLSPEC SDL_DisplayMode * SDLCALL SDL_GetClosestDisplayMode(int displayIndex, const SDL_DisplayMode * mode, SDL_DisplayMode * closest);
 */

/**
 *  \brief Get the display index associated with a window.
 *
 *  \return the display index of the display containing the center of the
 *          window, or -1 on error.
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayIndex(SDL_Window * window);
 */

/**
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

/**
 *  \brief Fill in information about the display mode used when a fullscreen
 *         window is visible.
 *
 *  \sa SDL_SetWindowDisplayMode()
 *  \sa SDL_SetWindowFullscreen()
 extern DECLSPEC int SDLCALL SDL_GetWindowDisplayMode(SDL_Window * window,
                                                      SDL_DisplayMode * mode);
 */

/**
 *  \brief Get the pixel format associated with the window.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowPixelFormat(SDL_Window * window);
 */


/**
 *  \brief Create an SDL window from an existing native window.
 *
 *  \param data A pointer to driver-dependent window creation data
 *
 *  \return The id of the window created, or zero if window creation failed.
 *
 *  \sa SDL_DestroyWindow()
 extern DECLSPEC SDL_Window * SDLCALL SDL_CreateWindowFrom(const void *data);
 */

/**
 *  \brief Get the numeric ID of a window, for logging purposes.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowID(SDL_Window * window);
 */

/**
 *  \brief Get a window from a stored ID, or NULL if it doesn't exist.
 extern DECLSPEC SDL_Window * SDLCALL SDL_GetWindowFromID(Uint32 id);
 */

/**
 *  \brief Get the window flags.
 extern DECLSPEC Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window * window);
 */

/**
 *  \brief Set the icon for a window.
 *
 *  \param window The window for which the icon should be set.
 *  \param icon The icon for the window.
 extern DECLSPEC void SDLCALL SDL_SetWindowIcon(SDL_Window * window,
                                                SDL_Surface * icon);
 */

/**
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

/**
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

/**
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

/**
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

/**
 *  \brief Show a window.
 *
 *  \sa SDL_HideWindow()
 extern DECLSPEC void SDLCALL SDL_ShowWindow(SDL_Window * window);
 */

/**
 *  \brief Hide a window.
 *
 *  \sa SDL_ShowWindow()
 extern DECLSPEC void SDLCALL SDL_HideWindow(SDL_Window * window);
 */

/**
 *  \brief Raise a window above other windows and set the input focus.
 extern DECLSPEC void SDLCALL SDL_RaiseWindow(SDL_Window * window);
 */

/**
 *  \brief Make a window as large as possible.
 *
 *  \sa SDL_RestoreWindow()
 extern DECLSPEC void SDLCALL SDL_MaximizeWindow(SDL_Window * window);
 */

/**
 *  \brief Minimize a window to an iconic representation.
 *
 *  \sa SDL_RestoreWindow()
 extern DECLSPEC void SDLCALL SDL_MinimizeWindow(SDL_Window * window);
 */

/**
 *  \brief Restore the size and position of a minimized or maximized window.
 *
 *  \sa SDL_MaximizeWindow()
 *  \sa SDL_MinimizeWindow()
 extern DECLSPEC void SDLCALL SDL_RestoreWindow(SDL_Window * window);
 */

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

/**
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
 *  \brief Returns whether the screensaver is currently enabled (default on).
 *
 *  \sa SDL_EnableScreenSaver()
 *  \sa SDL_DisableScreenSaver()
 extern DECLSPEC SDL_bool SDLCALL SDL_IsScreenSaverEnabled(void);
 */

/**
 *  \brief Allow the screen to be blanked by a screensaver
 *
 *  \sa SDL_IsScreenSaverEnabled()
 *  \sa SDL_DisableScreenSaver()
 extern DECLSPEC void SDLCALL SDL_EnableScreenSaver(void);
 */

/**
 *  \brief Prevent the screen from being blanked by a screensaver
 *
 *  \sa SDL_IsScreenSaverEnabled()
 *  \sa SDL_EnableScreenSaver()
 extern DECLSPEC void SDLCALL SDL_DisableScreenSaver(void);
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Window__construct, 0, 0, 6)
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
PHP_FUNCTION(SDL_CreateWindow)
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
	if (!intern->window) {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Can't create window", 0 TSRMLS_CC);
	}
}
/* }}} */


#define FETCH_WINDOW(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_window *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->window; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

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
PHP_FUNCTION(SDL_DestroyWindow)
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
PHP_FUNCTION(SDL_GetWindowTitle)
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
PHP_FUNCTION(SDL_SetWindowTitle)
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry php_sdl_window_methods[] = {
	PHP_ME(SDL_Window, __construct,     arginfo_SDL_Window__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(UpdateSurface,    SDL_UpdateWindowSurface,     arginfo_none)
	PHP_FALIAS(Destroy,          SDL_DestroyWindow,           arginfo_none)
	PHP_FALIAS(GetTitle,         SDL_GetWindowTitle,          arginfo_none)
	PHP_FALIAS(SetTitle,         SDL_SetWindowTitle,          arginfo_SDL_Window_SetTitle)

	PHP_FE_END
};

/* {{{ php_sdl_window_free
	 */
static void php_sdl_window_free(void *object TSRMLS_DC)
{
	struct php_sdl_window *intern = (struct php_sdl_window *) object;

	if (intern->window) {
		SDL_DestroyWindow(intern->window);
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

	intern->window = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_window_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_window_handlers;

	return retval;
}
/* }}} */

#define REGISTER_WINDOW_CLASS_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(php_sdl_window_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC);

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl2_video)
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
	REGISTER_WINDOW_CLASS_CONST_LONG("ALLOW_HIGHDPI",      SDL_WINDOW_ALLOW_HIGHDPI);

	return SUCCESS;
}
