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
  | Author: Santiago Lizardo <santiagolizardo@php.net>                   |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SDL_H
#define PHP_SDL_H

#define PHP_SDL_VERSION "0.9.3"

extern int le_surface;
#define le_surface_name "SDL Surface"

extern int le_pixelformat;
#define le_pixelformat_name "SDL Pixel format"

extern int le_cursor;
#define le_cursor_name "SDL Cursor"

extern int le_overlay;
#define le_overlay_name "SDL Overlay"

#include <SDL.h>

extern zend_module_entry sdl_module_entry;
#define phpext_sdl_ptr &sdl_module_entry

#ifdef PHP_WIN32
#	define PHP_SDL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SDL_API __attribute__ ((visibility("default")))
#else
#	define PHP_SDL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

void php_array_to_sdl_color(zval **array, SDL_Color *color);
void php_array_to_sdl_rect(zval **array, SDL_Rect *color);

void php_sdl_rect_to_array(SDL_Rect *rect, zval *rect_array);
void php_sdl_pixelformat_to_array(SDL_PixelFormat *pixelformat, zval *pixelformat_array TSRMLS_DC);
void php_sdl_surface_to_array(SDL_Surface *surface, zval *surface_array TSRMLS_DC);
int php_sdl_php_array_to_sdl_event(INTERNAL_FUNCTION_PARAMETERS, int user_index, zval **event_arg, SDL_Event *event);
int php_sdl_find_key_with_type(zval*, char*, int, int, zval***, const char* TSRMLS_DC);

PHP_MINIT_FUNCTION(sdl);
PHP_MSHUTDOWN_FUNCTION(sdl);
PHP_MINFO_FUNCTION(sdl);

PHP_FUNCTION(sdl_init);
PHP_FUNCTION(sdl_initsubsystem);
PHP_FUNCTION(sdl_quitsubsystem);
PHP_FUNCTION(sdl_quit);
PHP_FUNCTION(sdl_wasinit);
PHP_FUNCTION(sdl_mustlock);
PHP_FUNCTION(sdl_getvideosurface);
PHP_FUNCTION(sdl_getvideoinfo);
PHP_FUNCTION(sdl_videodrivername);
PHP_FUNCTION(sdl_listmodes);
PHP_FUNCTION(sdl_videomodeok);
PHP_FUNCTION(sdl_setvideomode);
PHP_FUNCTION(sdl_updaterect);
PHP_FUNCTION(sdl_updaterects);
PHP_FUNCTION(sdl_flip);
PHP_FUNCTION(sdl_setcolors);
PHP_FUNCTION(sdl_setpalette);
PHP_FUNCTION(sdl_setgamma);
PHP_FUNCTION(sdl_getgammaramp);
PHP_FUNCTION(sdl_setgammaramp);
PHP_FUNCTION(sdl_maprgb);
PHP_FUNCTION(sdl_maprgba);
PHP_FUNCTION(sdl_getrgb);
PHP_FUNCTION(sdl_getrgba);
PHP_FUNCTION(sdl_creatergbsurface);
PHP_FUNCTION(sdl_creatergbsurfacefrom);
PHP_FUNCTION(sdl_freesurface);
PHP_FUNCTION(sdl_locksurface);
PHP_FUNCTION(sdl_unlocksurface);
PHP_FUNCTION(sdl_loadbmp);
PHP_FUNCTION(sdl_savebmp);
PHP_FUNCTION(sdl_setcolorkey);
PHP_FUNCTION(sdl_setalpha);
PHP_FUNCTION(sdl_setcliprect);
PHP_FUNCTION(sdl_getcliprect);
PHP_FUNCTION(sdl_convertsurface);
PHP_FUNCTION(sdl_blitsurface);
PHP_FUNCTION(sdl_fillrect);
PHP_FUNCTION(sdl_displayformat);
PHP_FUNCTION(sdl_displayformatalpha);
PHP_FUNCTION(sdl_warpmouse);
PHP_FUNCTION(sdl_createcursor);
PHP_FUNCTION(sdl_freecursor);
PHP_FUNCTION(sdl_setcursor);
PHP_FUNCTION(sdl_getcursor);
PHP_FUNCTION(sdl_showcursor);
PHP_FUNCTION(sdl_gl_loadlibrary);
PHP_FUNCTION(sdl_gl_getprocaddress);
PHP_FUNCTION(sdl_gl_getattribute);
PHP_FUNCTION(sdl_gl_setattribute);
PHP_FUNCTION(sdl_gl_swapbuffers);
PHP_FUNCTION(sdl_createyuvoverlay);
PHP_FUNCTION(sdl_lockyuvoverlay);
PHP_FUNCTION(sdl_unlockyuvoverlay);
PHP_FUNCTION(sdl_displayyuvoverlay);
PHP_FUNCTION(sdl_freeyuvoverlay);
PHP_FUNCTION(sdl_getpixels);
PHP_FUNCTION(sdl_putpixels);
PHP_FUNCTION(sdl_button);
PHP_FUNCTION(sdl_getkeystate);
PHP_FUNCTION(sdl_getmodstate);
PHP_FUNCTION(sdl_setmodstate);
PHP_FUNCTION(sdl_getkeyname);
PHP_FUNCTION(sdl_enableunicode);
PHP_FUNCTION(sdl_enablekeyrepeat);
PHP_FUNCTION(sdl_getmousestate);
PHP_FUNCTION(sdl_getrelativemousestate);
PHP_FUNCTION(sdl_getappstate);

PHP_FUNCTION(sdl_expose_internal_errors);
PHP_FUNCTION(sdl_geterror);

#include "php_sdl_wm.h"
#include "php_sdl_event.h"
#include "php_sdl_cdrom.h"
#include "php_sdl_time.h"
#include "php_sdl_thread.h"
#include "php_sdl_joystick.h"
#include "php_sdl_audio.h"

ZEND_BEGIN_MODULE_GLOBALS(sdl)
	long expose_internal_errors;
	zval *user_events;
	zend_fcall_info *php_timer;
ZEND_END_MODULE_GLOBALS(sdl)

/* In every utility function you add that needs to use variables 
   in php_sdl_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SDL_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SDL_G(v) TSRMG(sdl_globals_id, zend_sdl_globals *, v)
#else
#define SDL_G(v) (sdl_globals.v)
#endif

/* ZEND_FE_END exists only in PHP >= 5.3.7 */
#ifndef ZEND_FE_END
#define ZEND_FE_END { NULL, NULL, NULL, 0, 0 }
#endif

#endif	/* PHP_SDL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

