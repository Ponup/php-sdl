/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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


/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_video.h (without SDL_Window)                    |
  +----------------------------------------------------------------------+
  | class SDL_DisplayMode                                                |
  +----------------------------------------------------------------------+
*/

#include "video.h"
#include "rect.h"

static zend_class_entry *php_sdl_displaymode_ce;
static zend_object_handlers php_sdl_displaymode_handlers;
struct php_displaymode_rect {
	zend_object   zo;
};

zend_class_entry *get_php_sdl_displaymode_ce(void)
{
	return php_sdl_displaymode_ce;
}

#define update_displaymode_prop(z_value, name, value) \
	zend_update_property_long(php_sdl_displaymode_ce, Z_OBJ_P(z_value), ZEND_STRL(name), value)

zend_bool sdl_displaymode_to_zval(SDL_DisplayMode *display, zval *value)
{
	if (display) {
		object_init_ex(value, php_sdl_displaymode_ce);
		update_displaymode_prop(value, "format",       display->format);
		update_displaymode_prop(value, "w",            display->w);
		update_displaymode_prop(value, "h",            display->h);
		update_displaymode_prop(value, "refresh_rate", display->refresh_rate);

		return 1;
		}
	ZVAL_NULL(value);
	return 0;
}

#define read_displaymode_prop(z_value, name, value) \
{ \
	zval *val, rv; \
	val = zend_read_property(php_sdl_displaymode_ce, Z_OBJ_P(z_value), ZEND_STRL(name), 0, &rv); \
	convert_to_long(val); \
	Z_LVAL_P(val) = (value) = (int)Z_LVAL_P(val); \
}

zend_bool zval_to_sdl_displaymode(zval *value, SDL_DisplayMode *display)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_displaymode_ce) {
		read_displaymode_prop(value, "format",       display->format);
		read_displaymode_prop(value, "w",            display->w);
		read_displaymode_prop(value, "h",            display->h);
		read_displaymode_prop(value, "refresh_rate", display->refresh_rate);

		return 1;
		}
	/* create an empty rect */
	memset(display, 0, sizeof(SDL_DisplayMode));
	return 0;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DisplayMode__construct, 0, 0, 4)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, h)
       ZEND_ARG_INFO(0, refresh_rate)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_DisplayMode::__construct(int format, int w, int h, int refresh_rate)

 *  \brief  The structure that defines a display mode
*/
static PHP_METHOD(SDL_DisplayMode, __construct)
{
	zend_long format, w, h, rate;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "llll", &format, &w, &h, &rate)) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	update_displaymode_prop(getThis(), "format",       format);
	update_displaymode_prop(getThis(), "w",            w);
	update_displaymode_prop(getThis(), "h",            h);
	update_displaymode_prop(getThis(), "refresh_rate", rate);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_DisplayMode___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_DisplayMode::__toString() */
static PHP_METHOD(SDL_DisplayMode, __toString)
{
	char *buf;
    size_t buf_len;
	SDL_DisplayMode mode;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_displaymode(getThis(), &mode);
	buf_len = spprintf(&buf, 100, "SDL_DisplayMode(%s,%d,%d,%d)", SDL_GetPixelFormatName(mode.format), mode.w, mode.h, mode.refresh_rate);
	RETVAL_STRINGL(buf, buf_len);
    efree(buf);
}
/* }}} */


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
	zend_long driver;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &driver) == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetVideoDriver((int)driver);
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name);
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
	size_t name_len = 0;
	int res;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|s", &name, &name_len) == FAILURE) {
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
	RETURN_STRING(name);
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
	zend_long display;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	name = SDL_GetDisplayName((int)display);
	if (!name) {
		RETURN_FALSE;
	}
	RETURN_STRING(name);
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
	zend_long display;
	long err;
	SDL_Rect rect;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lz/", &display, &result) == FAILURE) {
		RETURN_FALSE;
	}
	err = SDL_GetDisplayBounds((int)display, &rect);
	if (!err) {
		zval_dtor(result);
		sdl_rect_to_zval(&rect, result);
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
	zend_long display;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &display) == FAILURE) {
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
	zend_long display, mode;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &display, &mode) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetDisplayMode((int)display, (int)mode, &dm)) {
		RETURN_FALSE;
	}
	sdl_displaymode_to_zval(&dm, return_value);
}
/* }}} */

/* {{{ proto array SDL_GetDesktopDisplayMode(int displayIndex)

 *  \brief Fill in information about the desktop display mode.
 extern DECLSPEC int SDLCALL SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetDesktopDisplayMode)
{
	zend_long display;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetDesktopDisplayMode((int)display, &dm)) {
		RETURN_FALSE;
	}
	sdl_displaymode_to_zval(&dm, return_value);
}
/* }}} */


/* {{{ proto array SDL_GetCurrentDisplayMode(int displayIndex)

 *  \brief Fill in information about the current display mode.
 extern DECLSPEC int SDLCALL SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
 */
PHP_FUNCTION(SDL_GetCurrentDisplayMode)
{
	zend_long display;
	SDL_DisplayMode dm;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &display) == FAILURE) {
		RETURN_FALSE;
	}
	if (SDL_GetCurrentDisplayMode((int)display, &dm)) {
		RETURN_FALSE;
	}
	sdl_displaymode_to_zval(&dm, return_value);
}
/* }}} */

/* {{{ proto SDL_DisplayMode SDL_GetClosestDisplayMode(int displayIndex, SDL_DisplayMode mode [, SDL_DisplayMode closest])

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
PHP_FUNCTION(SDL_GetClosestDisplayMode)
{
	zend_long display;
	zval *z_desired, *z_closest = NULL;
	SDL_DisplayMode desired, closest;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lO|z", &display, &z_desired, php_sdl_displaymode_ce, &z_closest, php_sdl_displaymode_ce) == FAILURE) {
		RETURN_FALSE;
	}

	zval_to_sdl_displaymode(z_desired, &desired);
	if (SDL_GetClosestDisplayMode((int)display, &desired, &closest)==NULL) {
		RETURN_NULL();
	}

	if (z_closest) {
		zval_dtor(z_closest);
		sdl_displaymode_to_zval(&closest, z_closest);

		RETURN_ZVAL(z_closest, 1, 0);
	}
	sdl_displaymode_to_zval(&closest, return_value);
}
/* }}} */


/* {{{ proto bool SDL_IsScreenSaverEnabled(void)

 *  \brief Returns whether the screensaver is currently enabled (default on).
 *
 *  \sa SDL_EnableScreenSaver()
 *  \sa SDL_DisableScreenSaver()
 extern DECLSPEC SDL_bool SDLCALL SDL_IsScreenSaverEnabled(void);
 */
PHP_FUNCTION(SDL_IsScreenSaverEnabled)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_BOOL(SDL_IsScreenSaverEnabled());
}
/* }}} */


/* {{{ proto void SDL_EnableScreenSaver(void)

 *  \brief Allow the screen to be blanked by a screensaver
 *
 *  \sa SDL_IsScreenSaverEnabled()
 *  \sa SDL_DisableScreenSaver()
 extern DECLSPEC void SDLCALL SDL_EnableScreenSaver(void);
 */
PHP_FUNCTION(SDL_EnableScreenSaver)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	SDL_EnableScreenSaver();
}
/* }}} */


/* {{{ proto void SDL_DisableScreenSaver(void)

 *  \brief Prevent the screen from being blanked by a screensaver
 *
 *  \sa SDL_IsScreenSaverEnabled()
 *  \sa SDL_EnableScreenSaver()
 extern DECLSPEC void SDLCALL SDL_DisableScreenSaver(void);
 */
PHP_FUNCTION(SDL_DisableScreenSaver)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	SDL_DisableScreenSaver();
}
/* }}} */

/* {{{ php_sdl_displaymode_methods[] */
static const zend_function_entry php_sdl_displaymode_methods[] = {
	PHP_ME(SDL_DisplayMode, __construct, arginfo_SDL_DisplayMode__construct, ZEND_ACC_PUBLIC)
	PHP_ME(SDL_DisplayMode, __toString,  arginfo_class_SDL_DisplayMode___toString,                 ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_video)
{
	zend_class_entry ce_displaymode;

	INIT_CLASS_ENTRY(ce_displaymode, "SDL_DisplayMode", php_sdl_displaymode_methods);
	php_sdl_displaymode_ce = zend_register_internal_class(&ce_displaymode);
	memcpy(&php_sdl_displaymode_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_property_long(php_sdl_displaymode_ce, ZEND_STRL("format"),       0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(php_sdl_displaymode_ce, ZEND_STRL("w"),            0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(php_sdl_displaymode_ce, ZEND_STRL("h"),            0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(php_sdl_displaymode_ce, ZEND_STRL("refresh_rate"), 0, ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */
