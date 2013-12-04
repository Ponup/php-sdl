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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sdl.h"

#include <SDL.h>

#define FIND_EVENT(array, key, type) \
	{ \
		if (!php_sdl_find_key_with_type(*array, #key, sizeof(#key), IS_##type, &event_##key, "event" TSRMLS_CC)) { \
			return 0; \
		} \
	}

#define FIND_KEYSYM_EVENT(array, key, type) \
	{ \
		if (!php_sdl_find_key_with_type(array, #key, sizeof(#key), IS_##type, &event_##key, "event['keysym']" TSRMLS_CC)) { \
			return 0; \
		} \
	}

/* If you declare any globals in php_sdl.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(sdl)

/* {{{ Resources */
int le_surface;
int le_pixelformat;

int le_cursor;
int le_overlay;
/* }}} */

/* {{{ Resource destructors */
static void _sdl_surface (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}
static void _sdl_pixelformat (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}
static void _sdl_cursor (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}
static void _sdl_overlay (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}
/* }}} */

/* {{{ arginfo */

/* common arginfo */

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cdromoption, 0, 0, 1)
       ZEND_ARG_INFO(0, cdrom)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_flagoption, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_surfaceoption, 0, 0, 1)
       ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_screenoption, 0, 0, 1)
       ZEND_ARG_INFO(0, screen)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_refeventoption, 0, 0, 0)
       ZEND_ARG_INFO(1, event)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_eventoption, 0, 0, 1)
       ZEND_ARG_INFO(0, event)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cursoroption, 0, 0, 1)
       ZEND_ARG_INFO(0, cursor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_overlayoption, 0, 0, 1)
       ZEND_ARG_INFO(0, overlay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_driveoption, 0, 0, 1)
       ZEND_ARG_INFO(0, drive)
ZEND_END_ARG_INFO()

/* function specific arginfo - Video Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_listmodes, 0, 0, 2)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_videomode, 0, 0, 4)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, bpp)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_updaterect, 0, 0, 5)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, h)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_updaterects, 0, 0, 3)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, numrects)
       ZEND_ARG_INFO(0, rects)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setcolors, 0, 0, 4)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, colors)
       ZEND_ARG_INFO(0, firstcolor)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setpalette, 0, 0, 5)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, colors)
       ZEND_ARG_INFO(0, firstcolor)
       ZEND_ARG_INFO(0, ncolors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setgamma, 0, 0, 3)
       ZEND_ARG_INFO(0, redgamma)
       ZEND_ARG_INFO(0, greengamma)
       ZEND_ARG_INFO(0, bluegamma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getgammaramp, 0, 0, 3)
       ZEND_ARG_INFO(1, redtable)
       ZEND_ARG_INFO(1, greentable)
       ZEND_ARG_INFO(1, bluetable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setgammaramp, 0, 0, 3)
       ZEND_ARG_INFO(0, redtable)
       ZEND_ARG_INFO(0, greentable)
       ZEND_ARG_INFO(0, bluetable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_maprgb, 0, 0, 4)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, red)
       ZEND_ARG_INFO(0, green)
       ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_maprgba, 0, 0, 5)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, red)
       ZEND_ARG_INFO(0, green)
       ZEND_ARG_INFO(0, blue)
       ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getrgb, 0, 0, 5)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(1, red)
       ZEND_ARG_INFO(1, green)
       ZEND_ARG_INFO(1, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getrgba, 0, 0, 6)
       ZEND_ARG_INFO(0, pixel)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(1, red)
       ZEND_ARG_INFO(1, green)
       ZEND_ARG_INFO(1, blue)
       ZEND_ARG_INFO(1, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_creatergbsurface, 0, 0, 8)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, depth)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_creatergbsurfacefrom, 0, 0, 9)
       ZEND_ARG_INFO(0, pixels)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, depth)
       ZEND_ARG_INFO(0, pitch)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_loadbmp, 0, 0, 1)
       ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_savebmp, 0, 0, 2)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setcolorkey, 0, 0, 3)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, flag)
       ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setalpha, 0, 0, 3)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, flag)
       ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setcliprect, 0, 0, 2)
       ZEND_ARG_INFO(1, surface)
       ZEND_ARG_INFO(0, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getcliprect, 0, 0, 2)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(1, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_convertsurface, 0, 0, 3)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_blitsurface, 0, 0, 4)
       ZEND_ARG_INFO(0, srcsurface)
       ZEND_ARG_INFO(0, srcrect)
       ZEND_ARG_INFO(0, dstsurface)
       ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fillrect, 0, 0, 3)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, rect)
       ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_warpmouse, 0, 0, 2)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_createcursor, 0, 0, 6)
       ZEND_ARG_INFO(0, data)
       ZEND_ARG_INFO(0, mask)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, h)
       ZEND_ARG_INFO(0, hot_x)
       ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_showcursor, 0, 0, 1)
       ZEND_ARG_INFO(0, toggle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_gl_loadlibrary, 0, 0, 1)
       ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_gl_getattribute, 0, 0, 2)
       ZEND_ARG_INFO(0, attr)
       ZEND_ARG_INFO(1, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_gl_setattribute, 0, 0, 2)
       ZEND_ARG_INFO(0, attr)
       ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_createyuvoverlay, 0, 0, 4)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_displayyuvoverlay, 0, 0, 2)
       ZEND_ARG_INFO(0, overlay)
       ZEND_ARG_INFO(0, dstrect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getpixels, 0, 0, 2)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(1, pixels)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_putpixels, 0, 0, 2)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, pixels)
ZEND_END_ARG_INFO()

/* function specific arginfo - Window Management Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_wm_setcaption, 0, 0, 2)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, icon)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wm_getcaption, 0, 0, 2)
       ZEND_ARG_INFO(1, title)
       ZEND_ARG_INFO(1, icon)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wm_seticon, 0, 0, 2)
       ZEND_ARG_INFO(0, surface)
       ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wm_grabinput, 0, 0, 1)
       ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

/* function specific arginfo - Events Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_button, 0, 0, 1)
       ZEND_ARG_INFO(0, button)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_peepevents, 0, 0, 4)
       ZEND_ARG_INFO(1, events)
       ZEND_ARG_INFO(0, numevents)
       ZEND_ARG_INFO(0, action)
       ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_eventstate, 0, 0, 2)
       ZEND_ARG_INFO(0, type)
       ZEND_ARG_INFO(0, state)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getkeystate, 0, 0, 0)
       ZEND_ARG_INFO(1, numkeys)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_setmodstate, 0, 0, 1)
       ZEND_ARG_INFO(0, modstate)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getkeyname, 0, 0, 1)
       ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_enableunicode, 0, 0, 1)
       ZEND_ARG_INFO(0, enable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_enablekeyrepeat, 0, 0, 2)
       ZEND_ARG_INFO(0, delay)
       ZEND_ARG_INFO(0, interval)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getmousestate, 0, 0, 2)
       ZEND_ARG_INFO(1, x)
       ZEND_ARG_INFO(1, y)
ZEND_END_ARG_INFO()

/* function specific arginfo - CD-ROM Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_cd_indrive, 0, 0, 1)
       ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_frames_to_msf, 0, 0, 1)
       ZEND_ARG_INFO(0, frame)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_msf_to_frames, 0, 0, 3)
       ZEND_ARG_INFO(0, minute)
       ZEND_ARG_INFO(0, second)
       ZEND_ARG_INFO(0, frame)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cdstatus, 0, 0, 1)
       ZEND_ARG_INFO(1, cdrom)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cdplay, 0, 0, 3)
       ZEND_ARG_INFO(0, cdrom)
       ZEND_ARG_INFO(0, start)
       ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cdplaytracks, 0, 0, 5)
       ZEND_ARG_INFO(0, cdrom)
       ZEND_ARG_INFO(0, start_track)
       ZEND_ARG_INFO(0, start_frame)
       ZEND_ARG_INFO(0, ntracks)
       ZEND_ARG_INFO(0, nframes)
ZEND_END_ARG_INFO()

/* function specific arginfo - SDL Joystick Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_joystickeventstate, 0, 0, 1)
       ZEND_ARG_INFO(1, state)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_joystickindexoption, 0, 0, 1)
       ZEND_ARG_INFO(0, joystickindex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_joystickoption, 0, 0, 1)
       ZEND_ARG_INFO(0, joystick)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_joysticknumoption, 0, 0, 2)
       ZEND_ARG_INFO(0, joystick)
       ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

/* function specific arginfo - SDL Thread Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_mutexoption, 0, 0, 1)
       ZEND_ARG_INFO(0, mutex)
ZEND_END_ARG_INFO()

/* function specific arginfo - SDL Time Functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_delay, 0, 0, 1)
       ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()

/* function specific arginfo - SDL Audio Functions */
ZEND_BEGIN_ARG_INFO_EX(arginfo_openaudio, 0, 0, 2)
       ZEND_ARG_INFO(0, desired)
       ZEND_ARG_INFO(1, obtained)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_pauseaudio, 0, 0, 1)
       ZEND_ARG_INFO(0, pause_on)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_loadwav, 0, 0, 4)
       ZEND_ARG_INFO(0, file)
       ZEND_ARG_INFO(1, spec)
       ZEND_ARG_INFO(1, buf)
       ZEND_ARG_INFO(1, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_expose_internal_errors, 0, 0, 1)
       ZEND_ARG_INFO(0, expose)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ sdl_functions[]
 *
 * Every user visible function must have an entry in sdl_functions[].
 */
const zend_function_entry sdl_functions[] = {
	/* General */
	ZEND_FE(sdl_init,						arginfo_flagoption)
	ZEND_FE(sdl_initsubsystem,				arginfo_flagoption)
	ZEND_FE(sdl_quitsubsystem,				arginfo_flagoption)
	ZEND_FE(sdl_quit,						arginfo_flagoption)

	/* Video */
	ZEND_FE(sdl_wasinit,					arginfo_flagoption)
	ZEND_FE(sdl_mustlock,					arginfo_surfaceoption)
	ZEND_FE(sdl_getvideosurface,			arginfo_none)
	ZEND_FE(sdl_getvideoinfo,				arginfo_none)
	ZEND_FE(sdl_videodrivername,			arginfo_none)
	ZEND_FE(sdl_listmodes,					arginfo_listmodes)
	ZEND_FE(sdl_videomodeok,				arginfo_videomode)
	ZEND_FE(sdl_setvideomode,				arginfo_videomode)
	ZEND_FE(sdl_updaterect,					arginfo_updaterect)
	ZEND_FE(sdl_updaterects,				arginfo_updaterects)
	ZEND_FE(sdl_flip,						arginfo_screenoption)
	ZEND_FE(sdl_setcolors,					arginfo_setcolors)
	ZEND_FE(sdl_setpalette,					arginfo_setpalette)
	ZEND_FE(sdl_setgamma,					arginfo_setgamma)
	ZEND_FE(sdl_getgammaramp,				arginfo_getgammaramp)
	ZEND_FE(sdl_setgammaramp,				arginfo_setgammaramp)
	ZEND_FE(sdl_maprgb,						arginfo_maprgb)
	ZEND_FE(sdl_maprgba,					arginfo_maprgba)
	ZEND_FE(sdl_getrgb,						arginfo_getrgb)
	ZEND_FE(sdl_getrgba,					arginfo_getrgba)
	ZEND_FE(sdl_creatergbsurface,			arginfo_creatergbsurface)
	ZEND_FE(sdl_creatergbsurfacefrom,		arginfo_creatergbsurfacefrom)
	ZEND_FE(sdl_freesurface,				arginfo_surfaceoption)
	ZEND_FE(sdl_locksurface,				arginfo_surfaceoption)
	ZEND_FE(sdl_unlocksurface,				arginfo_surfaceoption)
	ZEND_FE(sdl_loadbmp,					arginfo_loadbmp)
	ZEND_FE(sdl_savebmp,					arginfo_savebmp)
	ZEND_FE(sdl_setcolorkey,				arginfo_setcolorkey)
	ZEND_FE(sdl_setalpha,					arginfo_setalpha)
	ZEND_FE(sdl_setcliprect,				arginfo_setcliprect)
	ZEND_FE(sdl_getcliprect,				arginfo_getcliprect)
	ZEND_FE(sdl_convertsurface,				arginfo_convertsurface)
	ZEND_FE(sdl_blitsurface,				arginfo_blitsurface)
	ZEND_FE(sdl_fillrect,					arginfo_fillrect)
	ZEND_FE(sdl_displayformat,				arginfo_surfaceoption)
	ZEND_FE(sdl_displayformatalpha,			arginfo_surfaceoption)
	ZEND_FE(sdl_warpmouse,					arginfo_warpmouse)
	ZEND_FE(sdl_createcursor,				arginfo_createcursor)
	ZEND_FE(sdl_freecursor,					arginfo_cursoroption)
	ZEND_FE(sdl_setcursor,					arginfo_cursoroption)
	ZEND_FE(sdl_getcursor,					arginfo_none)
	ZEND_FE(sdl_showcursor,					arginfo_showcursor)
	ZEND_FE(sdl_gl_loadlibrary,				arginfo_gl_loadlibrary)
	ZEND_FE(sdl_gl_getprocaddress,			NULL) /* not implemented */
	ZEND_FE(sdl_gl_getattribute,			arginfo_gl_getattribute)
	ZEND_FE(sdl_gl_setattribute,			arginfo_gl_setattribute)
	ZEND_FE(sdl_gl_swapbuffers,				arginfo_none)
	ZEND_FE(sdl_createyuvoverlay,			arginfo_createyuvoverlay)
	ZEND_FE(sdl_lockyuvoverlay,				arginfo_overlayoption)
	ZEND_FE(sdl_unlockyuvoverlay,			arginfo_overlayoption)
	ZEND_FE(sdl_displayyuvoverlay,			arginfo_displayyuvoverlay)
	ZEND_FE(sdl_freeyuvoverlay,				arginfo_overlayoption)
	ZEND_FE(sdl_getpixels,					arginfo_getpixels)
	ZEND_FE(sdl_putpixels,					arginfo_putpixels)

	/* Window Management */
	ZEND_FE(sdl_wm_setcaption,				arginfo_wm_setcaption)
	ZEND_FE(sdl_wm_getcaption,				arginfo_wm_getcaption)
	ZEND_FE(sdl_wm_seticon,					arginfo_wm_seticon)
	ZEND_FE(sdl_wm_iconifywindow,			arginfo_none)
	ZEND_FE(sdl_wm_togglefullscreen,		arginfo_surfaceoption)
	ZEND_FE(sdl_wm_grabinput,				arginfo_wm_grabinput)

	/* Events */
	ZEND_FE(sdl_button,						arginfo_button)
	ZEND_FE(sdl_pumpevents,					arginfo_none)
	ZEND_FE(sdl_peepevents,					arginfo_peepevents)
	ZEND_FE(sdl_pollevent,					arginfo_refeventoption)
	ZEND_FE(sdl_waitevent,					arginfo_refeventoption)
	ZEND_FE(sdl_pushevent,					arginfo_eventoption)
	ZEND_FE(sdl_seteventfilter,				NULL) /* not implemented */
	ZEND_FE(sdl_geteventfilter,				arginfo_none)
	ZEND_FE(sdl_eventstate,					arginfo_eventstate)
	ZEND_FE(sdl_getkeystate,				arginfo_getkeystate)
	ZEND_FE(sdl_getmodstate,				arginfo_none)
	ZEND_FE(sdl_setmodstate,				arginfo_setmodstate)
	ZEND_FE(sdl_getkeyname,					arginfo_getkeyname)
	ZEND_FE(sdl_enableunicode,				arginfo_enableunicode)
	ZEND_FE(sdl_enablekeyrepeat,			arginfo_enablekeyrepeat)
	ZEND_FE(sdl_getmousestate,				arginfo_getmousestate)
	ZEND_FE(sdl_getrelativemousestate,		arginfo_getmousestate)
	ZEND_FE(sdl_getappstate,				arginfo_none)

	/* SDL Joystick Functions */
	ZEND_FE(sdl_numjoysticks,				arginfo_none)
	ZEND_FE(sdl_joystickname,				arginfo_joystickindexoption)
	ZEND_FE(sdl_joystickopen,				arginfo_joystickindexoption)
	ZEND_FE(sdl_joystickopened,				arginfo_joystickindexoption)
	ZEND_FE(sdl_joystickindex,				arginfo_joystickoption)
	ZEND_FE(sdl_joysticknumaxes,			arginfo_joystickoption)
	ZEND_FE(sdl_joysticknumballs,			arginfo_joystickoption)
	ZEND_FE(sdl_joysticknumhats,			arginfo_joystickoption)
	ZEND_FE(sdl_joysticknumbuttons,			arginfo_joystickoption)
	ZEND_FE(sdl_joystickupdate,				arginfo_none)
	ZEND_FE(sdl_joystickeventstate,			arginfo_joystickeventstate)
	ZEND_FE(sdl_joystickgetaxis,			arginfo_joysticknumoption)
	ZEND_FE(sdl_joystickgethat,				arginfo_joysticknumoption)
	ZEND_FE(sdl_joystickgetball,			arginfo_joysticknumoption)
	ZEND_FE(sdl_joystickgetbutton,			arginfo_joysticknumoption)
	ZEND_FE(sdl_joystickclose,				arginfo_joystickoption)

	/* SDL CD-ROM Functions */
	ZEND_FE(sdl_cd_indrive,					arginfo_cd_indrive)
	ZEND_FE(sdl_frames_to_msf,				arginfo_frames_to_msf)
	ZEND_FE(sdl_msf_to_frames,				arginfo_msf_to_frames)
	ZEND_FE(sdl_cdnumdrives,				arginfo_none)
	ZEND_FE(sdl_cdname,						arginfo_driveoption)
	ZEND_FE(sdl_cdopen,						arginfo_driveoption)
	ZEND_FE(sdl_cdstatus,					arginfo_cdstatus)
	ZEND_FE(sdl_cdplay,						arginfo_cdplay)
	ZEND_FE(sdl_cdplaytracks,				arginfo_cdplaytracks)
	ZEND_FE(sdl_cdpause,					arginfo_cdromoption)
	ZEND_FE(sdl_cdresume,					arginfo_cdromoption)
	ZEND_FE(sdl_cdstop,						arginfo_cdromoption)
	ZEND_FE(sdl_cdeject,					arginfo_cdromoption)
	ZEND_FE(sdl_cdclose,					arginfo_cdromoption)

	/* Thread specifics */
	ZEND_FE(sdl_createmutex,				arginfo_none)
	ZEND_FE(sdl_destroymutex,				arginfo_mutexoption)
	ZEND_FE(sdl_mutexp,						arginfo_mutexoption)
	ZEND_FE(sdl_mutexv,						arginfo_mutexoption)
	PHP_FALIAS(sdl_lockmutex, sdl_mutexp,	arginfo_mutexoption)
	PHP_FALIAS(sdl_unlockmutex, sdl_mutexv,	arginfo_mutexoption)

	/* Time functions */
	ZEND_FE(sdl_getticks,					arginfo_none)
	ZEND_FE(sdl_delay,						arginfo_delay)
	ZEND_FE(sdl_addtimer,					NULL) /* not implemented */
	ZEND_FE(sdl_removetimer,				NULL) /* not implemented */

	/* Audio functions */
	ZEND_FE(sdl_openaudio,					arginfo_openaudio)
	ZEND_FE(sdl_pauseaudio,					arginfo_pauseaudio)
	ZEND_FE(sdl_getaudiostatus,				arginfo_none)
	ZEND_FE(sdl_loadwav,					arginfo_loadwav)
	ZEND_FE(sdl_freewav,					NULL)
	ZEND_FE(sdl_buildaudiocvt,				NULL) /* not implemented */
	ZEND_FE(sdl_convertaudio,				NULL) /* not implemented */
	ZEND_FE(sdl_mixaudio,					NULL) /* not implemented */
	ZEND_FE(sdl_lockaudio,					arginfo_none)
	ZEND_FE(sdl_unlockaudio,				arginfo_none)
	ZEND_FE(sdl_closeaudio,					arginfo_none)

	ZEND_FE(sdl_geterror,					arginfo_none)
	ZEND_FE(sdl_expose_internal_errors,		arginfo_expose_internal_errors)
	ZEND_FE_END
};

/* {{{ sdl_module_entry
 */
zend_module_entry sdl_module_entry = {
	STANDARD_MODULE_HEADER,
	"SDL",
	sdl_functions,
	PHP_MINIT(sdl),
	PHP_MSHUTDOWN(sdl),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl),
	PHP_SDL_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL
ZEND_GET_MODULE(sdl)
#endif

static void php_sdl_init_globals(zend_sdl_globals *sdl_globals)
{
	sdl_globals->expose_internal_errors = 1;
	MAKE_STD_ZVAL(sdl_globals->user_events);
	array_init(sdl_globals->user_events);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl)
{
	ZEND_INIT_MODULE_GLOBALS(sdl, php_sdl_init_globals, NULL);

	le_cdrom			= zend_register_list_destructors_ex(_sdl_cdrom, NULL, le_cdrom_name, module_number);
	le_sdl_audiospec 	= zend_register_list_destructors_ex(_sdl_audiospec, NULL, le_sdl_audiospec_name, module_number);
	le_sdl_audiocvt		= zend_register_list_destructors_ex(_sdl_audiocvt, NULL, le_sdl_audiocvt_name, module_number);
	le_surface			= zend_register_list_destructors_ex(_sdl_surface, NULL, le_surface_name, module_number);
	le_pixelformat		= zend_register_list_destructors_ex(_sdl_pixelformat, NULL, le_pixelformat_name, module_number);
	le_cursor			= zend_register_list_destructors_ex(_sdl_cursor, NULL, le_cursor_name, module_number);
	le_overlay			= zend_register_list_destructors_ex(_sdl_overlay, NULL, le_overlay_name, module_number);
	le_mutex			= zend_register_list_destructors_ex(_sdl_mutex, NULL, le_mutex_name, module_number);

	le_timer			= zend_register_list_destructors_ex(_sdl_timer, NULL, le_timer_name, module_number);
	le_joystick			= zend_register_list_destructors_ex(_sdl_joystick, NULL, le_joystick_name, module_number);

	/* {{{ SDL Constants */
	REGISTER_LONG_CONSTANT("SDL_INIT_TIMER",SDL_INIT_TIMER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_AUDIO",SDL_INIT_AUDIO,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_VIDEO",SDL_INIT_VIDEO,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_CDROM",SDL_INIT_CDROM,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_JOYSTICK",SDL_INIT_JOYSTICK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_NOPARACHUTE",SDL_INIT_NOPARACHUTE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_EVENTTHREAD",SDL_INIT_EVENTTHREAD,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_EVERYTHING",SDL_INIT_EVERYTHING,CONST_CS | CONST_PERSISTENT);

	/* SDL_Cdrom */
	REGISTER_LONG_CONSTANT("SDL_CD_TRAYEMPTY", CD_TRAYEMPTY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_CD_STOPPED", CD_STOPPED,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_CD_PLAYING", CD_PLAYING,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_CD_PAUSED", CD_PAUSED,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_CD_ERROR", CD_ERROR,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_AUDIO_TRACK", SDL_AUDIO_TRACK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_DATA_TRACK", SDL_DATA_TRACK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_CD_FPS", CD_FPS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MAX_TRACKS",SDL_MAX_TRACKS,CONST_CS | CONST_PERSISTENT);

	/* SDL_Video */
	REGISTER_LONG_CONSTANT("SDL_SRCALPHA",SDL_SRCALPHA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RLEACCEL",SDL_RLEACCEL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SWSURFACE",SDL_SWSURFACE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HWSURFACE",SDL_HWSURFACE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ASYNCBLIT",SDL_ASYNCBLIT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ANYFORMAT",SDL_ANYFORMAT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HWPALETTE",SDL_HWPALETTE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_DOUBLEBUF",SDL_DOUBLEBUF,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FULLSCREEN",SDL_FULLSCREEN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_OPENGL",SDL_OPENGL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_OPENGLBLIT",SDL_OPENGLBLIT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SRCCOLORKEY", SDL_SRCCOLORKEY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BYTEORDER", SDL_BYTEORDER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BIG_ENDIAN", SDL_BIG_ENDIAN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RESIZABLE",SDL_RESIZABLE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_NOFRAME",SDL_NOFRAME,CONST_CS | CONST_PERSISTENT);
	
	REGISTER_LONG_CONSTANT("SDL_GL_RED_SIZE",SDL_GL_RED_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_GREEN_SIZE",SDL_GL_GREEN_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_BLUE_SIZE",SDL_GL_BLUE_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ALPHA_SIZE",SDL_GL_ALPHA_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_BUFFER_SIZE",SDL_GL_BUFFER_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_DOUBLEBUFFER",SDL_GL_DOUBLEBUFFER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_DEPTH_SIZE",SDL_GL_DEPTH_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_STENCIL_SIZE",SDL_GL_STENCIL_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ACCUM_RED_SIZE",SDL_GL_ACCUM_RED_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ACCUM_GREEN_SIZE",SDL_GL_ACCUM_GREEN_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ACCUM_BLUE_SIZE",SDL_GL_ACCUM_BLUE_SIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GL_ACCUM_ALPHA_SIZE",SDL_GL_ACCUM_ALPHA_SIZE,CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_YV12_OVERLAY",SDL_YV12_OVERLAY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_IYUV_OVERLAY",SDL_IYUV_OVERLAY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_YUY2_OVERLAY",SDL_YUY2_OVERLAY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_UYVY_OVERLAY",SDL_UYVY_OVERLAY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_YVYU_OVERLAY",SDL_YVYU_OVERLAY,CONST_CS | CONST_PERSISTENT);

	/* SDL_WM */
	REGISTER_LONG_CONSTANT("SDL_GRAB_QUERY",SDL_GRAB_QUERY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GRAB_OFF",SDL_GRAB_OFF,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GRAB_ON",SDL_GRAB_ON,CONST_CS | CONST_PERSISTENT);
	
	/* SDL_Event */
	REGISTER_LONG_CONSTANT("SDL_DEFAULT_REPEAT_INTERVAL",SDL_DEFAULT_REPEAT_INTERVAL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_DEFAULT_REPEAT_DELAY",SDL_DEFAULT_REPEAT_DELAY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PRESSED",SDL_PRESSED,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RELEASED",SDL_RELEASED,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_QUERY",SDL_QUERY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_IGNORE",SDL_IGNORE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_DISABLE",SDL_DISABLE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ENABLE",SDL_ENABLE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ADDEVENT",SDL_ADDEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PEEKEVENT",SDL_PEEKEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_GETEVENT",SDL_GETEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ALLEVENTS",SDL_ALLEVENTS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ACTIVEEVENTMASK",SDL_ACTIVEEVENTMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYDOWNMASK",SDL_KEYDOWNMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYUPMASK",SDL_KEYUPMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEMOTIONMASK",SDL_MOUSEMOTIONMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONDOWNMASK",SDL_MOUSEBUTTONDOWNMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONUPMASK",SDL_MOUSEBUTTONUPMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEEVENTMASK",SDL_MOUSEEVENTMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYAXISMOTIONMASK",SDL_JOYAXISMOTIONMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBALLMOTIONMASK",SDL_JOYBALLMOTIONMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYHATMOTIONMASK",SDL_JOYHATMOTIONMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBUTTONDOWNMASK",SDL_JOYBUTTONDOWNMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBUTTONUPMASK",SDL_JOYBUTTONUPMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYEVENTMASK",SDL_JOYEVENTMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_VIDEORESIZEMASK",SDL_VIDEORESIZEMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_VIDEOEXPOSEMASK",SDL_VIDEOEXPOSEMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_QUITMASK",SDL_QUITMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SYSWMEVENTMASK",SDL_SYSWMEVENTMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_NOEVENT",SDL_NOEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_ACTIVEEVENT",SDL_ACTIVEEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYDOWN",SDL_KEYDOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_KEYUP",SDL_KEYUP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEMOTION",SDL_MOUSEMOTION,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONDOWN",SDL_MOUSEBUTTONDOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MOUSEBUTTONUP",SDL_MOUSEBUTTONUP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYAXISMOTION",SDL_JOYAXISMOTION,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBALLMOTION",SDL_JOYBALLMOTION,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYHATMOTION",SDL_JOYHATMOTION,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBUTTONDOWN",SDL_JOYBUTTONDOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_JOYBUTTONUP",SDL_JOYBUTTONUP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_QUIT",SDL_QUIT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_SYSWMEVENT",SDL_SYSWMEVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVEDA",SDL_EVENT_RESERVEDA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVEDB",SDL_EVENT_RESERVEDB,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_VIDEORESIZE",SDL_VIDEORESIZE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_VIDEOEXPOSE",SDL_VIDEOEXPOSE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED2",SDL_EVENT_RESERVED2,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED3",SDL_EVENT_RESERVED3,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED4",SDL_EVENT_RESERVED4,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED5",SDL_EVENT_RESERVED5,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED6",SDL_EVENT_RESERVED6,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_RESERVED7",SDL_EVENT_RESERVED7,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_USEREVENT",SDL_USEREVENT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_NUMEVENTS",SDL_NUMEVENTS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APPMOUSEFOCUS",SDL_APPMOUSEFOCUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APPINPUTFOCUS",SDL_APPINPUTFOCUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_APPACTIVE",SDL_APPACTIVE,CONST_CS | CONST_PERSISTENT);

	/* SDL keysym */
	REGISTER_LONG_CONSTANT("SDLK_UNKNOWN",SDLK_UNKNOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_FIRST",SDLK_FIRST,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_BACKSPACE",SDLK_BACKSPACE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_TAB",SDLK_TAB,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_CLEAR",SDLK_CLEAR,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RETURN",SDLK_RETURN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PAUSE",SDLK_PAUSE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_ESCAPE",SDLK_ESCAPE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_SPACE",SDLK_SPACE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_EXCLAIM",SDLK_EXCLAIM,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_QUOTEDBL",SDLK_QUOTEDBL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_HASH",SDLK_HASH,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_DOLLAR",SDLK_DOLLAR,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_AMPERSAND",SDLK_AMPERSAND,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_QUOTE",SDLK_QUOTE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LEFTPAREN",SDLK_LEFTPAREN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RIGHTPAREN",SDLK_RIGHTPAREN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_ASTERISK",SDLK_ASTERISK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PLUS",SDLK_PLUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_COMMA",SDLK_COMMA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_MINUS",SDLK_MINUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PERIOD",SDLK_PERIOD,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_SLASH",SDLK_SLASH,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_0",SDLK_0,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_1",SDLK_1,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_2",SDLK_2,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_3",SDLK_3,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_4",SDLK_4,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_5",SDLK_5,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_6",SDLK_6,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_7",SDLK_7,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_8",SDLK_8,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_9",SDLK_9,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_COLON",SDLK_COLON,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_SEMICOLON",SDLK_SEMICOLON,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LESS",SDLK_LESS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_EQUALS",SDLK_EQUALS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_GREATER",SDLK_GREATER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_QUESTION",SDLK_QUESTION,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_AT",SDLK_AT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LEFTBRACKET",SDLK_LEFTBRACKET,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_BACKSLASH",SDLK_BACKSLASH,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RIGHTBRACKET",SDLK_RIGHTBRACKET,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_CARET",SDLK_CARET,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_UNDERSCORE",SDLK_UNDERSCORE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_BACKQUOTE",SDLK_BACKQUOTE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_a",SDLK_a,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_b",SDLK_b,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_c",SDLK_c,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_d",SDLK_d,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_e",SDLK_e,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_f",SDLK_f,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_g",SDLK_g,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_h",SDLK_h,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_i",SDLK_i,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_j",SDLK_j,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_k",SDLK_k,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_l",SDLK_l,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_m",SDLK_m,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_n",SDLK_n,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_o",SDLK_o,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_p",SDLK_p,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_q",SDLK_q,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_r",SDLK_r,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_s",SDLK_s,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_t",SDLK_t,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_u",SDLK_u,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_v",SDLK_v,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_w",SDLK_w,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_x",SDLK_x,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_y",SDLK_y,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_z",SDLK_z,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_DELETE",SDLK_DELETE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_0",SDLK_WORLD_0,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_1",SDLK_WORLD_1,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_2",SDLK_WORLD_2,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_3",SDLK_WORLD_3,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_4",SDLK_WORLD_4,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_5",SDLK_WORLD_5,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_6",SDLK_WORLD_6,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_7",SDLK_WORLD_7,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_8",SDLK_WORLD_8,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_9",SDLK_WORLD_9,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_10",SDLK_WORLD_10,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_11",SDLK_WORLD_11,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_12",SDLK_WORLD_12,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_13",SDLK_WORLD_13,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_14",SDLK_WORLD_14,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_15",SDLK_WORLD_15,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_16",SDLK_WORLD_16,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_17",SDLK_WORLD_17,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_18",SDLK_WORLD_18,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_19",SDLK_WORLD_19,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_20",SDLK_WORLD_20,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_21",SDLK_WORLD_21,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_22",SDLK_WORLD_22,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_23",SDLK_WORLD_23,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_24",SDLK_WORLD_24,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_25",SDLK_WORLD_25,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_26",SDLK_WORLD_26,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_27",SDLK_WORLD_27,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_28",SDLK_WORLD_28,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_29",SDLK_WORLD_29,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_30",SDLK_WORLD_30,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_31",SDLK_WORLD_31,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_32",SDLK_WORLD_32,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_33",SDLK_WORLD_33,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_34",SDLK_WORLD_34,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_35",SDLK_WORLD_35,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_36",SDLK_WORLD_36,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_37",SDLK_WORLD_37,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_38",SDLK_WORLD_38,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_39",SDLK_WORLD_39,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_40",SDLK_WORLD_40,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_41",SDLK_WORLD_41,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_42",SDLK_WORLD_42,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_43",SDLK_WORLD_43,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_44",SDLK_WORLD_44,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_45",SDLK_WORLD_45,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_46",SDLK_WORLD_46,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_47",SDLK_WORLD_47,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_48",SDLK_WORLD_48,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_49",SDLK_WORLD_49,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_50",SDLK_WORLD_50,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_51",SDLK_WORLD_51,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_52",SDLK_WORLD_52,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_53",SDLK_WORLD_53,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_54",SDLK_WORLD_54,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_55",SDLK_WORLD_55,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_56",SDLK_WORLD_56,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_57",SDLK_WORLD_57,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_58",SDLK_WORLD_58,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_59",SDLK_WORLD_59,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_60",SDLK_WORLD_60,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_61",SDLK_WORLD_61,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_62",SDLK_WORLD_62,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_63",SDLK_WORLD_63,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_64",SDLK_WORLD_64,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_65",SDLK_WORLD_65,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_66",SDLK_WORLD_66,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_67",SDLK_WORLD_67,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_68",SDLK_WORLD_68,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_69",SDLK_WORLD_69,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_70",SDLK_WORLD_70,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_71",SDLK_WORLD_71,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_72",SDLK_WORLD_72,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_73",SDLK_WORLD_73,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_74",SDLK_WORLD_74,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_75",SDLK_WORLD_75,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_76",SDLK_WORLD_76,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_77",SDLK_WORLD_77,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_78",SDLK_WORLD_78,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_79",SDLK_WORLD_79,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_80",SDLK_WORLD_80,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_81",SDLK_WORLD_81,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_82",SDLK_WORLD_82,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_83",SDLK_WORLD_83,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_84",SDLK_WORLD_84,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_85",SDLK_WORLD_85,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_86",SDLK_WORLD_86,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_87",SDLK_WORLD_87,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_88",SDLK_WORLD_88,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_89",SDLK_WORLD_89,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_90",SDLK_WORLD_90,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_91",SDLK_WORLD_91,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_92",SDLK_WORLD_92,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_93",SDLK_WORLD_93,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_94",SDLK_WORLD_94,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_WORLD_95",SDLK_WORLD_95,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP0",SDLK_KP0,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP1",SDLK_KP1,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP2",SDLK_KP2,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP3",SDLK_KP3,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP4",SDLK_KP4,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP5",SDLK_KP5,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP6",SDLK_KP6,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP7",SDLK_KP7,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP8",SDLK_KP8,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP9",SDLK_KP9,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_PERIOD",SDLK_KP_PERIOD,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_DIVIDE",SDLK_KP_DIVIDE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_MULTIPLY",SDLK_KP_MULTIPLY,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_MINUS",SDLK_KP_MINUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_PLUS",SDLK_KP_PLUS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_ENTER",SDLK_KP_ENTER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_KP_EQUALS",SDLK_KP_EQUALS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_UP",SDLK_UP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_DOWN",SDLK_DOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RIGHT",SDLK_RIGHT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LEFT",SDLK_LEFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_INSERT",SDLK_INSERT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_HOME",SDLK_HOME,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_END",SDLK_END,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PAGEUP",SDLK_PAGEUP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PAGEDOWN",SDLK_PAGEDOWN,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F1",SDLK_F1,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F2",SDLK_F2,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F3",SDLK_F3,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F4",SDLK_F4,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F5",SDLK_F5,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F6",SDLK_F6,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F7",SDLK_F7,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F8",SDLK_F8,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F9",SDLK_F9,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F10",SDLK_F10,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F11",SDLK_F11,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F12",SDLK_F12,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F13",SDLK_F13,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F14",SDLK_F14,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_F15",SDLK_F15,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_NUMLOCK",SDLK_NUMLOCK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_CAPSLOCK",SDLK_CAPSLOCK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_SCROLLOCK",SDLK_SCROLLOCK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RSHIFT",SDLK_RSHIFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LSHIFT",SDLK_LSHIFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RCTRL",SDLK_RCTRL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LCTRL",SDLK_LCTRL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RALT",SDLK_RALT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LALT",SDLK_LALT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RMETA",SDLK_RMETA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LMETA",SDLK_LMETA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LSUPER",SDLK_LSUPER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_RSUPER",SDLK_RSUPER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_MODE",SDLK_MODE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_COMPOSE",SDLK_COMPOSE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_HELP",SDLK_HELP,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_PRINT",SDLK_PRINT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_SYSREQ",SDLK_SYSREQ,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_BREAK",SDLK_BREAK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_MENU",SDLK_MENU,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_POWER",SDLK_POWER,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_EURO",SDLK_EURO,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDLK_LAST",SDLK_LAST,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_NONE",KMOD_NONE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_LSHIFT",KMOD_LSHIFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_RSHIFT",KMOD_RSHIFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_LCTRL",KMOD_LCTRL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_RCTRL",KMOD_RCTRL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_LALT",KMOD_LALT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_RALT",KMOD_RALT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_LMETA",KMOD_LMETA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_RMETA",KMOD_RMETA,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_NUM",KMOD_NUM,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_CAPS",KMOD_CAPS,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_MODE",KMOD_MODE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_RESERVED",KMOD_RESERVED,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_CTRL",KMOD_CTRL,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_SHIFT",KMOD_SHIFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_ALT",KMOD_ALT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KMOD_META",KMOD_META,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_LEFT",SDL_BUTTON_LEFT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_MIDDLE",SDL_BUTTON_MIDDLE,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_RIGHT",SDL_BUTTON_RIGHT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_LMASK",SDL_BUTTON_LMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_MMASK",SDL_BUTTON_MMASK,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BUTTON_RMASK",SDL_BUTTON_RMASK,CONST_CS | CONST_PERSISTENT);

	/* SDL Joystick */
	REGISTER_LONG_CONSTANT("SDL_HAT_CENTERED",		SDL_HAT_CENTERED,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_UP",			SDL_HAT_UP,				CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_RIGHT",			SDL_HAT_RIGHT,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_DOWN",			SDL_HAT_DOWN,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_LEFT",			SDL_HAT_LEFT,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_RIGHTUP",		SDL_HAT_RIGHTUP,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_RIGHTDOWN",		SDL_HAT_RIGHTDOWN,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_LEFTUP",		SDL_HAT_LEFTUP,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_HAT_LEFTDOWN",		SDL_HAT_LEFTDOWN,		CONST_CS | CONST_PERSISTENT);

	/* SDL Audio */
	REGISTER_LONG_CONSTANT("AUDIO_U8", AUDIO_U8,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_S8", AUDIO_S8,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_U16",	AUDIO_U16,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_U16LSB", AUDIO_U16LSB,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_S16",	AUDIO_S16,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_S16LSB", AUDIO_S16LSB,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_U16MSB", AUDIO_U16MSB,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_S16MSB", AUDIO_S16MSB,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_U16SYS", AUDIO_U16SYS,		CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("AUDIO_S16SYS", AUDIO_S16SYS,		CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_AUDIO_STOPPED", SDL_AUDIO_STOPPED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_AUDIO_PLAYING", SDL_AUDIO_PLAYING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_AUDIO_PAUSED", SDL_AUDIO_PAUSED, CONST_CS | CONST_PERSISTENT);
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl)
{
	const SDL_version *ver;
	char buf[64];

	php_info_print_table_start();
	php_info_print_table_header(2, "SDL support", "enabled");
	php_info_print_table_row(2, "SDL module version", PHP_SDL_VERSION);

	/* Buildtime headers version */
	snprintf(buf, sizeof(buf), "%d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
	php_info_print_table_row(2, "SDL headers version", buf);

	/* Runtime library version */
	ver = SDL_Linked_Version();
	snprintf(buf, sizeof(buf), "%d.%d.%d", ver->major, ver->minor, ver->patch);
	php_info_print_table_row(2, "SDL library version", buf);

	php_info_print_table_end();
}
/* }}} */

/* {{{ proto int sdl_init(int flags)
*/
PHP_FUNCTION(sdl_init) {
	long flags;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE) {
		return;
	}

	if (SDL_Init((Uint32)flags) == -1) {
		if(SDL_G(expose_internal_errors)) {
		php_error(E_WARNING, "%s() could not initialize SDL: %s",
				get_active_function_name(TSRMLS_C), SDL_GetError());
		}
		RETURN_LONG(-1);
		
		}

	RETURN_LONG(0);
}
/* }}} */

/* {{{ proto int sdl_initsubsystem(int flags)

 */
PHP_FUNCTION(sdl_initsubsystem)
{
	long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE)
		return;

    /* Initialize according to flag value*/
    if ((SDL_Init((Uint32)flags) == -1)) {
		
			php_error(E_WARNING, "%s() could not initialize SDL: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
    }

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto void sdl_quitsubsystem(int flags)

 */
PHP_FUNCTION(sdl_quitsubsystem)
{
	long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE)
		return;

	SDL_QuitSubSystem((Uint32)flags);
}
/* }}} */

/* {{{ proto void sdl_quit(void )
    */
PHP_FUNCTION(sdl_quit)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_Quit();
}
/* }}} */

/* {{{ proto mix sdl_listmodes(mixed format, int flags)

 */
PHP_FUNCTION(sdl_listmodes)
{
	/* According to SDL source code, BitsPerPixel's the only value used in SDL_PixelFormat structure... */
	zval *format_arg, *rect, **BitsPerPixel_value;
	long flags;
	int bpp = 0, i, format_null;
	SDL_Rect **modes;
	SDL_PixelFormat *format = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &format_arg, &flags) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	format_null = 0;

	if (Z_TYPE_P(format_arg) == IS_LONG) {
		bpp = Z_LVAL_P(format_arg);
	} else if (Z_TYPE_P(format_arg) == IS_ARRAY) {
		if (zend_hash_find(Z_ARRVAL_P(format_arg), "BitsPerPixel", sizeof("BitsPerPixel"), (void **)&BitsPerPixel_value) == FAILURE) {
				php_error(E_WARNING, "%s() unable to find format['BitsPerPixel']",
						  get_active_function_name(TSRMLS_C));
				format_null = 1;
		}
		convert_to_long_ex(BitsPerPixel_value);
		bpp = Z_LVAL_PP(BitsPerPixel_value);
	} else {
		format_null = 1;
	}

	if (format_null == 0) {
		/* Allocate an empty pixel format structure */
		format = emalloc(sizeof(*format));
		if ( format == NULL ) {
			format_null = 1;
		}

		memset(format, 0, sizeof(*format));
		format->BitsPerPixel = bpp;
	}

	modes = SDL_ListModes((format_null == 1) ? NULL : format, (Uint32)flags);

	/* Check is there are any modes available */
	if (modes == (SDL_Rect **)0) {
		RETURN_FALSE;
	}

	/* Check if or resolution is restricted */
	if (modes == (SDL_Rect **)-1) {
		RETURN_FALSE;
	} else {
		array_init(return_value);
		for(i=0;modes[i];++i)
		{
			MAKE_STD_ZVAL(rect);
			array_init(rect);
			add_assoc_long(rect, "x", modes[i]->x);
			add_assoc_long(rect, "y", modes[i]->y);
			add_assoc_long(rect, "w", modes[i]->w);
			add_assoc_long(rect, "h", modes[i]->h);
			add_next_index_zval(return_value, rect);
		}
	}

	if (format) {
		efree(format);
	}
}
/* {{{ proto int sdl_wasinit(int flags)

 */
PHP_FUNCTION(sdl_wasinit)
{
	long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &flags) == FAILURE)
		return;

	RETURN_LONG(SDL_WasInit((Uint32)flags));
}
/* }}} */

/* {{{ proto string sdl_geterror(void)
 */
PHP_FUNCTION(sdl_geterror)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;
	RETURN_STRING(SDL_GetError(), 1);
}
/* }}} */

/* {{{ proto void sdl_expose_internal_errors(bool expose)
   Whether to expose internal SDL errors automatic or not. */
PHP_FUNCTION(sdl_expose_internal_errors)
{
	zend_bool value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &value) == FAILURE)
		return;

	SDL_G(expose_internal_errors) = value;
}
/* }}} */

/* }}} */

/* {{{ SDL Video Functions */

/* {{{ proto int sdl_mustlock(array surface)

 */
/*
 #define SDL_MUSTLOCK(surface)	\
  (surface->offset ||		\
  ((surface->flags & (SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_RLEACCEL)) != 0))
*/
PHP_FUNCTION(sdl_mustlock)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_LONG( SDL_MUSTLOCK( surface ) );
}
/* }}} */

/**
 * Converts a PHP array to a SDL_Color structure
 */
void php_array_to_sdl_color(zval **array, SDL_Color *color) {
	zval **r, **g, **b;

	/* By default a black color */
	color->r = color->g = color->b = 0;

	if(zend_hash_find(Z_ARRVAL_PP(array), "r", sizeof("r"), (void **)&r) != FAILURE) {
		convert_to_long_ex(r);
		color->r = (Uint8)Z_LVAL_PP(r);
	}

	if(zend_hash_find(Z_ARRVAL_PP(array), "g", sizeof("g"), (void **)&g) != FAILURE) {
		convert_to_long_ex(g);
		color->g = (Uint8)Z_LVAL_PP(g);
	}

	if(zend_hash_find(Z_ARRVAL_PP(array), "b", sizeof("b"), (void **)&b) != FAILURE) {
		convert_to_long_ex(b);
		color->b = (Uint8)Z_LVAL_PP(b);
	}
}

/**
 * Converts a PHP array to a SDL_Rect structure
 */
void php_array_to_sdl_rect(zval **array, SDL_Rect *rect) {
	zval **array_value = NULL;
	size_t character_size = sizeof("x");

	rect->x = rect->y = rect->w = rect->h = 0;

	if(zend_hash_find(Z_ARRVAL_PP(array), "x", character_size, (void **)&array_value) != FAILURE) {
		convert_to_long_ex(array_value);
		rect->x = (Sint16)Z_LVAL_PP(array_value);
	}

	if(zend_hash_find(Z_ARRVAL_PP(array), "y", character_size, (void **)&array_value) != FAILURE) {
		convert_to_long_ex(array_value);
		rect->y = (Sint16)Z_LVAL_PP(array_value);
	}

	if(zend_hash_find(Z_ARRVAL_PP(array), "w", character_size, (void **)&array_value) != FAILURE) {
		convert_to_long_ex(array_value);
		rect->w = (Uint16)Z_LVAL_PP(array_value);
	}

	if(zend_hash_find(Z_ARRVAL_PP(array), "h", character_size, (void **)&array_value) != FAILURE) {
		convert_to_long_ex(array_value);
		rect->h = (Uint16)Z_LVAL_PP(array_value);
	}
}

/* Converts a php array to a sdl_event. The INTERNAL parameters are used for
 * user_events with custom data. user_index is the index from where to take
 * the passed parameter to the function; -1 to disable it. */
int php_sdl_php_array_to_sdl_event(INTERNAL_FUNCTION_PARAMETERS, int user_index, zval **event_arg, SDL_Event *event) {
	zval **event_type = NULL;

	FIND_EVENT(event_arg, type, LONG);

	switch(Z_LVAL_PP(event_type)) {
		case SDL_ACTIVEEVENT:
			{
				zval **event_gain = NULL, **event_state = NULL;

				FIND_EVENT(event_arg, gain, LONG);
				FIND_EVENT(event_arg, state, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->active.type			= (Uint8)Z_LVAL_PP(event_type);
				event->active.gain			= (Uint8)Z_LVAL_PP(event_gain);
			}
			break;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			{
				zval **event_state = NULL, **event_keysym = NULL, **event_scancode = NULL, **event_sym = NULL, **event_mod = NULL, **event_unicode = NULL;

				FIND_EVENT(event_arg, state, LONG);
				FIND_EVENT(event_arg, keysym, ARRAY);
				FIND_KEYSYM_EVENT(*event_keysym, scancode, LONG);
				FIND_KEYSYM_EVENT(*event_keysym, sym, LONG);
				FIND_KEYSYM_EVENT(*event_keysym, mod, LONG);
				FIND_KEYSYM_EVENT(*event_keysym, unicode, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->key.type				= (Uint8)Z_LVAL_PP(event_type);
				event->key.keysym.scancode	= (Uint8)Z_LVAL_PP(event_scancode);
				event->key.keysym.sym		= (SDLKey)Z_LVAL_PP(event_sym);
				event->key.keysym.mod		= (SDLMod)Z_LVAL_PP(event_mod);
				event->key.keysym.unicode	= (Uint16)Z_LVAL_PP(event_unicode);
			}
			break;

		case SDL_MOUSEMOTION:
			{
				zval **event_state = NULL, **event_x = NULL, **event_y = NULL, **event_xrel = NULL, **event_yrel = NULL;

				FIND_EVENT(event_arg, state, LONG);
				FIND_EVENT(event_arg, x, LONG);
				FIND_EVENT(event_arg, y, LONG);
				FIND_EVENT(event_arg, xrel, LONG);
				FIND_EVENT(event_arg, yrel, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->motion.type			= (Uint8)Z_LVAL_PP(event_type);
				event->motion.x				= (Uint16)Z_LVAL_PP(event_x);
				event->motion.y				= (Uint16)Z_LVAL_PP(event_y);
				event->motion.xrel			= (Sint16)Z_LVAL_PP(event_xrel);
				event->motion.yrel			= (Sint16)Z_LVAL_PP(event_yrel);
			}
			break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			{
				zval **event_button = NULL, **event_state = NULL, **event_x = NULL, **event_y = NULL;

				FIND_EVENT(event_arg, button, LONG);
				FIND_EVENT(event_arg, state, LONG);
				FIND_EVENT(event_arg, x, LONG);
				FIND_EVENT(event_arg, y, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->button.type			= (Uint8)Z_LVAL_PP(event_type);
				event->button.button			= (Uint8)Z_LVAL_PP(event_button);
				event->button.state			= (Uint8)Z_LVAL_PP(event_state);
				event->button.x				= (Uint16)Z_LVAL_PP(event_x);
				event->button.y				= (Uint16)Z_LVAL_PP(event_y);
			}
			break;

		case SDL_JOYAXISMOTION:
			{
				zval **event_which = NULL, **event_axis = NULL, **event_value = NULL;

				FIND_EVENT(event_arg, which, LONG);
				FIND_EVENT(event_arg, axis, LONG);
				FIND_EVENT(event_arg, value, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->jaxis.type			= (Uint8)Z_LVAL_PP(event_type);
				event->jaxis.which			= (Uint8)Z_LVAL_PP(event_which);
				event->jaxis.axis			= (Uint8)Z_LVAL_PP(event_axis);
				event->jaxis.value			= (Sint16)Z_LVAL_PP(event_value);
			}
			break;

		case SDL_JOYBALLMOTION:
			{
				zval **event_which = NULL, **event_ball = NULL, **event_xrel = NULL, **event_yrel = NULL;

				FIND_EVENT(event_arg, which, LONG);
				FIND_EVENT(event_arg, ball, LONG);
				FIND_EVENT(event_arg, xrel, LONG);
				FIND_EVENT(event_arg, yrel, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->jball.type			= (Uint8)Z_LVAL_PP(event_type);
				event->jball.which			= (Uint8)Z_LVAL_PP(event_which);
				event->jball.ball			= (Uint8)Z_LVAL_PP(event_ball);
				event->jball.xrel			= (Sint16)Z_LVAL_PP(event_xrel);
				event->jball.yrel			= (Sint16)Z_LVAL_PP(event_yrel);
			}
			break;

		case SDL_JOYHATMOTION:
			{
				zval **event_which = NULL, **event_hat = NULL, **event_value = NULL;

				FIND_EVENT(event_arg, which, LONG);
				FIND_EVENT(event_arg, hat, LONG);
				FIND_EVENT(event_arg, value, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->jhat.type				= (Uint8)Z_LVAL_PP(event_type);
				event->jhat.which			= (Uint8)Z_LVAL_PP(event_which);
				event->jhat.hat				= (Uint8)Z_LVAL_PP(event_hat);
				event->jhat.value			= (Uint8)Z_LVAL_PP(event_value);
			}
			break;

		case SDL_JOYBUTTONUP:
		case SDL_JOYBUTTONDOWN:
			{
				zval **event_which = NULL, **event_button = NULL, **event_state = NULL;

				FIND_EVENT(event_arg, which, LONG);
				FIND_EVENT(event_arg, button, LONG);
				FIND_EVENT(event_arg, state, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->jbutton.type			= (Uint8)Z_LVAL_PP(event_type);
				event->jbutton.which			= (Uint8)Z_LVAL_PP(event_which);
				event->jbutton.button		= (Uint8)Z_LVAL_PP(event_button);
				event->jbutton.state			= (Uint8)Z_LVAL_PP(event_state);
			}
			break;

		case SDL_VIDEORESIZE:
			{
				zval **event_w = NULL, **event_h = NULL;

				FIND_EVENT(event_arg, w, LONG);
				FIND_EVENT(event_arg, h, LONG);

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->resize.type			= (Uint8)Z_LVAL_PP(event_type);
				event->resize.w				= (int)Z_LVAL_PP(event_w);
				event->resize.h				= (int)Z_LVAL_PP(event_h);
			}
			break;

		case SDL_VIDEOEXPOSE:
			{
				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->expose.type			= SDL_QUIT;
			}
			break;

		case SDL_QUIT:
			{
				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->quit.type				= SDL_QUIT;
			}
			break;

		case SDL_SYSWMEVENT:
			{
				event->type					= (Uint8)Z_LVAL_PP(event_type);
			}
			break;

		default:
			if (SDL_USEREVENT <= Z_LVAL_PP(event_type) && Z_LVAL_PP(event_type) < SDL_NUMEVENTS) {
				zval *user_args = NULL, **event_code = NULL;

				FIND_EVENT(event_arg, code, LONG);

				MAKE_STD_ZVAL(user_args);
				array_init(user_args);

				if (user_index != -1) {
					if (ZEND_NUM_ARGS() > user_index) {
						int i;
						zval ***args = (zval ***)emalloc(ZEND_NUM_ARGS() * sizeof(zval **));
						if (zend_get_parameters_array_ex(ZEND_NUM_ARGS(), args) == FAILURE) {
							efree(args);
							php_error(E_WARNING, "%s() unable to obtain user arguments",
									  get_active_function_name(TSRMLS_C));
							return 0;
						}
						for(i = user_index; i < ZEND_NUM_ARGS(); i++) {
							zval_add_ref(args[i]);
							add_next_index_zval(user_args, *args[i]);
						}
						efree(args);
					}
				}

				event->type					= (Uint8)Z_LVAL_PP(event_type);
				event->user.type			= (Uint8)Z_LVAL_PP(event_type);
				event->user.code			= (int)Z_LVAL_PP(event_code);
				event->user.data1			= (void*)user_args;
				event->user.data2			= NULL;
			} else  {
				php_error(E_WARNING,"%s() unknown or unsupported event type %ld",
						  get_active_function_name(TSRMLS_C), Z_LVAL_PP(event_type));
				return 0;
			}
	}
	return 1;
}

/* Stuff SDL_Rect structure into a zval array */
void php_sdl_rect_to_array(SDL_Rect *rect, zval *rect_array)
{
	array_init(rect_array);
	add_assoc_long(rect_array, "x", rect->x);
	add_assoc_long(rect_array, "y", rect->y);
	add_assoc_long(rect_array, "w", rect->w);
	add_assoc_long(rect_array, "h", rect->h);
}

/* Stuff SDL_PixelFormat structure into a zval array */
void php_sdl_pixelformat_to_array(SDL_PixelFormat *pixelformat, zval *pixelformat_array TSRMLS_DC)
{
	zval *palette, *colors, *color;
	int handle, i;

	handle = zend_list_insert(pixelformat, le_pixelformat TSRMLS_CC);
	
	array_init(pixelformat_array);
	add_assoc_resource(pixelformat_array, "handle", handle);
	zend_list_addref(handle);

	add_assoc_long(pixelformat_array, "BitsPerPixel", pixelformat->BitsPerPixel);
	add_assoc_long(pixelformat_array, "BytesPerPixel", pixelformat->BytesPerPixel);
	add_assoc_long(pixelformat_array, "Rmask", pixelformat->Rmask);
	add_assoc_long(pixelformat_array, "Gmask", pixelformat->Gmask);
	add_assoc_long(pixelformat_array, "Bmask", pixelformat->Bmask);
	add_assoc_long(pixelformat_array, "Amask", pixelformat->Amask);
	add_assoc_long(pixelformat_array, "Rshift", pixelformat->Rshift);
	add_assoc_long(pixelformat_array, "Gshift", pixelformat->Gshift);
	add_assoc_long(pixelformat_array, "Bshift", pixelformat->Bshift);
	add_assoc_long(pixelformat_array, "Ashift", pixelformat->Ashift);
	add_assoc_long(pixelformat_array, "Rloss", pixelformat->Rloss);
	add_assoc_long(pixelformat_array, "Gloss", pixelformat->Gloss);
	add_assoc_long(pixelformat_array, "Bloss", pixelformat->Bloss);
	add_assoc_long(pixelformat_array, "Aloss", pixelformat->Aloss);
	add_assoc_long(pixelformat_array, "colorkey", pixelformat->colorkey);
	add_assoc_long(pixelformat_array, "alpha", pixelformat->alpha);

	if (pixelformat->palette == NULL) {
		add_assoc_null(pixelformat_array, "palette");
	} else {
		MAKE_STD_ZVAL(palette);
		array_init(palette);
		MAKE_STD_ZVAL(colors);
		add_assoc_long(palette, "ncolors", pixelformat->palette->ncolors);
		array_init(colors);
	
		for(i=0; i < pixelformat->palette->ncolors; i++)
		{
			MAKE_STD_ZVAL(color);
			array_init(color);
			add_assoc_long(color, "r", pixelformat->palette->colors[i].r);
			add_assoc_long(color, "g", pixelformat->palette->colors[i].g);
			add_assoc_long(color, "b", pixelformat->palette->colors[i].b);
			add_next_index_zval(colors, color);
		}
		add_assoc_zval(palette, "colors", colors);
		add_assoc_zval(pixelformat_array, "palette", palette);
	}
}
/* Stuff SDL_Surface structure into a zval array */
void php_sdl_surface_to_array(SDL_Surface *surface, zval *surface_array TSRMLS_DC)
{
	zval *format, *rect;
	int handle;

	handle = zend_list_insert(surface, le_surface TSRMLS_CC);

	array_init(surface_array);
	add_assoc_resource(surface_array, "handle", handle);
	zend_list_addref(handle);

	add_assoc_long(surface_array, "flags", surface->flags);
	add_assoc_long(surface_array, "w", surface->w);
	add_assoc_long(surface_array, "h", surface->h);
	add_assoc_long(surface_array, "pitch", surface->pitch);
	add_assoc_long(surface_array, "refcount", surface->refcount);

	MAKE_STD_ZVAL(format);
	php_sdl_pixelformat_to_array(surface->format, format TSRMLS_CC);
	add_assoc_zval(surface_array, "format", format);

	MAKE_STD_ZVAL(rect);
	php_sdl_rect_to_array(&surface->clip_rect, rect);
	add_assoc_zval(surface_array, "clip_rect", rect);
}

/* {{{ proto array sdl_getvideosurface(void)

 */
PHP_FUNCTION(sdl_getvideosurface)
{
	SDL_Surface *surface;

	if (zend_parse_parameters_none() == FAILURE)
		return;

	surface = SDL_GetVideoSurface();
	if (!surface) {
		
			php_error(E_WARNING, "%s() couldn't get surface: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto array sdl_getvideoinfo(void)

 */
PHP_FUNCTION(sdl_getvideoinfo)
{
	zval *vfmt;
	SDL_VideoInfo *videoinfo = NULL;

	if (zend_parse_parameters_none() == FAILURE)
		return;

	videoinfo = (SDL_VideoInfo*) SDL_GetVideoInfo();

	if (!videoinfo) {
		php_error(E_WARNING, "%s() couldn't get videoinfo: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	array_init(return_value);

	add_assoc_long(return_value, "hw_available", videoinfo->hw_available);
	add_assoc_long(return_value, "wm_available", videoinfo->wm_available);
	add_assoc_long(return_value, "blit_hw", videoinfo->blit_hw);
	add_assoc_long(return_value, "blit_hw_CC", videoinfo->blit_hw_CC);
	add_assoc_long(return_value, "blit_hw_A", videoinfo->blit_hw_A);
	add_assoc_long(return_value, "blit_sw", videoinfo->blit_sw);
	add_assoc_long(return_value, "blit_sw_CC", videoinfo->blit_sw_CC);
	add_assoc_long(return_value, "blit_sw_A", videoinfo->blit_sw_A);
	add_assoc_long(return_value, "blit_fill", videoinfo->blit_fill);
	add_assoc_long(return_value, "video_mem", videoinfo->video_mem);

	MAKE_STD_ZVAL(vfmt);
	php_sdl_pixelformat_to_array(videoinfo->vfmt, vfmt TSRMLS_CC);
	add_assoc_zval(return_value, "vfmt", vfmt);
}
/* }}} */

/* {{{ proto string sdl_videodrivername(void)

 */
PHP_FUNCTION(sdl_videodrivername)
{
	char namebuf[2048];

	RETURN_STRING(SDL_VideoDriverName((char*)namebuf, (2048 - 1)),1);
}
/* }}} */

/* {{{ proto array sdl_setvideomode(int width, int height, int bpp, int flags)

 */
PHP_FUNCTION(sdl_setvideomode)
{
	long width, height, bpp, flags;
	SDL_Surface *surface;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &bpp, &flags) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
   
	surface =SDL_SetVideoMode(width, height, bpp, flags);
	if (!surface) {
		php_error(E_WARNING, "%s() couldn't set %lx%lx%lx: %s",
			  get_active_function_name(TSRMLS_C), width, height, bpp, SDL_GetError());
			
		RETURN_FALSE;
	}
	
	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}

/* {{{ proto int sdl_videomodeok(int width, int height, int bpp, int flags)

 */
PHP_FUNCTION(sdl_videomodeok)
{
	long width, height, bpp, flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &width, &height, &bpp, &flags) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_VideoModeOK((int)width, (int)height, (int)bpp, (Uint32)flags));
}
/* }}} */


/* {{{ proto void sdl_updaterect(array surface, int x, int y, int w, int h)

 */
PHP_FUNCTION(sdl_updaterect)
{
	zval *surface_arg, **handle_resource;
	long x, y, w, h;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "allll", &surface_arg, &x, &y, &w, &h) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	SDL_UpdateRect(surface, x, y, w, h);
}
/* }}} */

/* {{{ proto int sdl_updaterects(array surface, int numrects, array rects)

 */
PHP_FUNCTION(sdl_updaterects)
{
	zval *surface_arg, *rects_arg, **handle_resource, **rect_array;
	SDL_Rect *rects;
	SDL_Rect one_rect;
	long numrects;
	int rects_count, i;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ala", &surface_arg, &numrects, &rects_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (numrects < 1) {
		php_error(E_WARNING, "%s() parameter numrects must be greater than 0",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	if (numrects == 1) {

		php_array_to_sdl_rect(&rects_arg, &one_rect);

		SDL_UpdateRects(surface, 1, &one_rect);

	} else {

		rects_count = zend_hash_next_free_element(Z_ARRVAL_P(rects_arg));

		if (rects_count <= 0) {
			/* Something is really wrong!  Probably an associative array! */
			php_error(E_WARNING, "%s() parameter rects array has a size of %d",
					  get_active_function_name(TSRMLS_C), rects_count);
			RETURN_FALSE;
		}

		if (numrects > rects_count) {
			php_error(E_WARNING, "%s() parameter numrects is greater than the size of rects array, auto-reducing to %d",
					  get_active_function_name(TSRMLS_C), rects_count);
			numrects = rects_count;
		}

		rects  = (SDL_Rect *)emalloc(numrects*sizeof(SDL_Rect));

		for(i=0; i < numrects; i++) {

			if (zend_hash_index_find(Z_ARRVAL_P(rects_arg), i, (void **)&rect_array) == FAILURE) {
				php_error(E_WARNING, "%s() unable to find rects[%d]",
					  get_active_function_name(TSRMLS_C), rects_count);
			}

			php_array_to_sdl_rect(rect_array, &rects[i]);
		}

		SDL_UpdateRects(surface, (int)numrects, rects);
		efree(rects);
	}
}
/* }}} */

/* {{{ proto int sdl_flip(array screen)

 */
PHP_FUNCTION(sdl_flip)
{
	zval *screen_arg, **handle_resource;
	SDL_Surface *screen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &screen_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(screen_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find screen['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(screen, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_LONG(SDL_Flip(screen));
}
/* }}} */
/* {{{ proto int sdl_setcolors(array surface, array colors, int firstcolor, int ncolors)

 */
PHP_FUNCTION(sdl_setcolors)
{
	zval *surface_arg, *colors_arg, **color, **handle_resource;
	long firstcolor, ncolors;
	int i, result;
	SDL_Surface *surface;
    SDL_Color *colors;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aall", &surface_arg, &colors_arg, &firstcolor, &ncolors) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	colors  = (SDL_Color *)emalloc(ncolors*sizeof(SDL_Color));

	for(i=0;i < ncolors; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(colors_arg), i, (void **)&color) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find colors[%d]",
					  get_active_function_name(TSRMLS_C), i);
		}

		php_array_to_sdl_color(color, &colors[i]);		
	}

	result = SDL_SetColors(surface, colors, (int)firstcolor, (int)ncolors);

	efree(colors);

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_setpalette(array surface, int flags, array colors, int firstcolor, int ncolors)

 */
PHP_FUNCTION(sdl_setpalette)
{
	zval *surface_arg, *colors_arg, **color, **handle_resource;
	long firstcolor, ncolors, flags;
	int i, result;
	SDL_Surface *surface;
	SDL_Color *colors;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "alall", &surface_arg, &flags, &colors_arg, &firstcolor, &ncolors) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	colors  = (SDL_Color *)emalloc(ncolors*sizeof(SDL_Color));

	for(i=0;i < ncolors; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(colors_arg), i, (void **)&color) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find colors[%d]",
				get_active_function_name(TSRMLS_C), i);
		}
		
		php_array_to_sdl_color(color, &colors[i]);
	}

	result = SDL_SetPalette(surface, (int)flags, colors, (int)firstcolor, (int)ncolors);

	efree(colors);

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_setgamma(double redgamma, double greengamma, double bluegamma)

 */
PHP_FUNCTION(sdl_setgamma)
{
	double redgamma, greengamma, bluegamma;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &redgamma, &greengamma, &bluegamma) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_SetGamma((float)redgamma, (float)greengamma, (float)bluegamma));
}
/* }}} */

/* {{{ proto int sdl_getgammaramp(array &redtable, array &greentable, array &bluetable)

 */
PHP_FUNCTION(sdl_getgammaramp)
{
	zval *redtable_arg, *greentable_arg, *bluetable_arg;
	Uint16 redtable[256], greentable[256], bluetable[256];
	int result, i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &redtable_arg, &greentable_arg, &bluetable_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	result = SDL_GetGammaRamp(redtable, greentable, bluetable);
	if (result==0) {
		zval_dtor(redtable_arg);
		array_init(redtable_arg);
		zval_dtor(greentable_arg);
		array_init(greentable_arg);
		zval_dtor(bluetable_arg);
		array_init(bluetable_arg);

		for(i = 0; i < 256; i++) {
			add_index_long(redtable_arg, i,redtable[i]);
			add_index_long(greentable_arg, i,greentable[i]);
			add_index_long(bluetable_arg, i,bluetable[i]);
		}
	}

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_setgammaramp(array redtable, array greentable, array bluetable)

 */
PHP_FUNCTION(sdl_setgammaramp)
{
	zval *redtable_arg, *greentable_arg, *bluetable_arg, **red, **green, **blue;
	Uint16 redtable[256], greentable[256], bluetable[256];
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aaa", &redtable_arg, &greentable_arg, &bluetable_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	for(i = 0; i < 256; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(redtable_arg), i, (void **)&red) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find redtable[%d]",
					  get_active_function_name(TSRMLS_C), i);
			redtable[i] = 0;
		} else {
			redtable[i] = (Uint16) Z_LVAL_PP(red);
		}

		if (zend_hash_index_find(Z_ARRVAL_P(greentable_arg), i, (void **)&green) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find greentable[%d]",
					  get_active_function_name(TSRMLS_C), i);
			greentable[i] = 0;
		} else {
			greentable[i] = (Uint16) Z_LVAL_PP(green);
		}

		if (zend_hash_index_find(Z_ARRVAL_P(bluetable_arg), i, (void **)&blue) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find bluetable[%d]",
					  get_active_function_name(TSRMLS_C), i);
			bluetable[i] = 0;
		} else {
			bluetable[i] = (Uint16) Z_LVAL_PP(blue);
		}
	}

	RETURN_LONG(SDL_SetGammaRamp(redtable, greentable, bluetable));
}
/* }}} */

/* {{{ proto int sdl_maprgb(array fmt, int r, int g, int b)

 */
PHP_FUNCTION(sdl_maprgb)
{
	zval *fmt_arg, **handle_resource;
	long r, g, b;
	SDL_PixelFormat *fmt;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "alll", &fmt_arg, &r, &g, &b) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(fmt_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find fmt['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(fmt, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);

	RETURN_LONG(SDL_MapRGB(fmt, (Uint8)r, (Uint8)g, (Uint8)b));
}
/* }}} */

/* {{{ proto int sdl_maprgba(array fmt, int r, int g, int b, int a)

 */
PHP_FUNCTION(sdl_maprgba)
{
	zval *fmt_arg, **handle_resource;
	SDL_PixelFormat *fmt;
	long r, g, b, a;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "allll", &fmt_arg, &r, &g, &b, &a) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(fmt_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find fmt['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(fmt, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);

	RETURN_LONG(SDL_MapRGBA(fmt, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a));
}
/* }}} */

/* {{{ proto void sdl_getrgb(int pixel, array fmt, int &r, int &g, int &b)

 */
PHP_FUNCTION(sdl_getrgb)
{
	zval *fmt_arg, *r_arg, *g_arg, *b_arg, **handle_resource;
	SDL_PixelFormat *fmt;
	long pixel;
	Uint8 r, g, b;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lazzz", &pixel, &fmt_arg, &r_arg, &g_arg, &b_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(fmt_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find fmt['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(fmt, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);

	SDL_GetRGB(pixel, fmt, &r, &g, &b);

	ZVAL_LONG(r_arg, r);
	ZVAL_LONG(g_arg, g);
	ZVAL_LONG(b_arg, b);
}
/* }}} */

/* {{{ proto void sdl_getrgba(int pixel, array fmt, int &r, int &g, int &b, int &a)

 */
PHP_FUNCTION(sdl_getrgba)
{
	zval *fmt_arg, *r_arg, *g_arg, *b_arg, *a_arg, **handle_resource;
	SDL_PixelFormat *fmt;
	long pixel;
	Uint8 r, g, b, a;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lazzzz", &pixel, &fmt_arg, &r_arg, &g_arg, &b_arg, &a_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(fmt_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find fmt['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(fmt, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);

	SDL_GetRGBA((Uint32)pixel, fmt, &r, &g, &b, &a);

	ZVAL_LONG(r_arg, r);
	ZVAL_LONG(g_arg, g);
	ZVAL_LONG(b_arg, b);
	ZVAL_LONG(a_arg, a);
}
/* }}} */

/* {{{ proto array sdl_creatergbsurface(int flags, int width, int height, int depth, int Rmask, int Gmask, int Bmask, int Amask)

 */
PHP_FUNCTION(sdl_creatergbsurface)
{
	long flags, Rmask, Gmask, Bmask, Amask;
	long width, height, depth;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllllll", &flags, &width, &height, &depth, &Rmask, &Gmask, &Bmask, &Amask) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	surface = SDL_CreateRGBSurface((Uint32)flags, (int)width, (int)height, (int)depth, (Uint32)Rmask, (Uint32)Gmask, (Uint32)Bmask, (Uint32)Amask);
	if (!surface) {
		
			php_error(E_WARNING, "%s() couldn't create surface: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}
/* }}} */
/* {{{ proto int sdl_locksurface(array surface)

 */
PHP_FUNCTION(sdl_locksurface)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_LONG( SDL_LockSurface( surface ) );
}
/* }}} */

/* {{{ proto void sdl_unlocksurface(array surface)

 */
PHP_FUNCTION(sdl_unlocksurface)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	SDL_UnlockSurface(surface);
}
/* }}} */

/* {{{ proto array sdl_loadbmp(char file)

 */
PHP_FUNCTION(sdl_loadbmp)
{
	char *file_arg = NULL;
	int file_arg_len = 0;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file_arg, &file_arg_len) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	surface = SDL_LoadBMP(file_arg);
	if (!surface) {
		php_error(E_WARNING, "%s() couldn't load %s: %s",
					  get_active_function_name(TSRMLS_C), file_arg, SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto int sdl_savebmp(array surface, string file)

 */
PHP_FUNCTION(sdl_savebmp)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface;
	char *path;
	zend_uint pathlen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "as", &surface_arg, &path, &pathlen) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_LONG(SDL_SaveBMP(surface, path));
}
/* }}} */

/* {{{ proto int sdl_setcolorkey(array surface, int flag, int key)

 */
PHP_FUNCTION(sdl_setcolorkey)
{
	zval *surface_arg, **handle_resource;
	long flag, key;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "all", &surface_arg, &flag, &key) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	RETURN_LONG(SDL_SetColorKey(surface, flag, key));
}
/* }}} */

/* {{{ proto int sdl_setalpha(array surface, int flag, int alpha)

 */
PHP_FUNCTION(sdl_setalpha)
{
	zval *surface_arg, **handle_resource;
	long flag, alpha;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "all", &surface_arg, &flag, &alpha) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	php_printf("%s() mudança de alfa %ld e flag=%ld",
		   get_active_function_name(TSRMLS_C), alpha,flag);
	RETURN_LONG(SDL_SetAlpha(surface, (Uint32)flag, (Uint8)alpha));
}
/* }}} */

/* {{{ proto void sdl_setcliprect(array &surface, array rect)

 */
PHP_FUNCTION(sdl_setcliprect)
{
	zval *surface_arg, *rect_arg, **handle_resource, **clip_rect_array;
	SDL_Rect rect;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &surface_arg, &rect_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	php_array_to_sdl_rect(&rect_arg, &rect);

	SDL_SetClipRect(surface, &rect);

	/* Update surface array's clip_rect structure */
	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "clip_rect", sizeof("clip_rect"), (void **)&clip_rect_array) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['clip_rect'] array",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	add_assoc_long((*clip_rect_array),"x", surface->clip_rect.x);
	add_assoc_long((*clip_rect_array),"y", surface->clip_rect.y);
	add_assoc_long((*clip_rect_array),"w", surface->clip_rect.w);
	add_assoc_long((*clip_rect_array),"h", surface->clip_rect.h);

}
/* }}} */

/* {{{ proto void sdl_getcliprect(array surface, array &rect)

 */
PHP_FUNCTION(sdl_getcliprect)
{
	zval *surface_arg, *rect_arg, **handle_resource;
	SDL_Rect rect;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "az", &surface_arg, &rect_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	SDL_GetClipRect(surface, &rect);
	zval_dtor(rect_arg);
	array_init(rect_arg);
	add_assoc_long(rect_arg, "x",rect.x);
	add_assoc_long(rect_arg, "y",rect.y);
	add_assoc_long(rect_arg, "w",rect.w);
	add_assoc_long(rect_arg, "h",rect.h);
}
/* }}} */

/* {{{ proto array sdl_convertsurface(array src, array fmt, int flags)

 */
PHP_FUNCTION(sdl_convertsurface)
{
	zval *src_arg, *fmt_arg, **handle_resource;
	long flags;
	SDL_PixelFormat *fmt;
	SDL_Surface *src, *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aal", &src_arg, &fmt_arg, &flags) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(src_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(src, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	if (zend_hash_find(Z_ARRVAL_P(fmt_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find fmt['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(fmt, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);

	surface = (SDL_Surface *) SDL_ConvertSurface(src, fmt, (Uint32)flags);
	if (!surface) {
		
			php_error(E_WARNING, "%s() couldn't create new surface: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto int sdl_blitsurface(array src, array srcrect, array dst, array dstrect)

 */
PHP_FUNCTION(sdl_blitsurface)
{
	zval *src_arg, *srcrect_arg, *dst_arg, *dstrect_arg, **handle_resource;
	SDL_Rect srcrect, dstrect;
	SDL_Surface *src, *dst;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "azzz", &src_arg, &srcrect_arg, &dst_arg, &dstrect_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	dstrect.x = dstrect.y = dstrect.w = dstrect.h = 0;

	if (zend_hash_find(Z_ARRVAL_P(src_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find src['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	ZEND_FETCH_RESOURCE(src, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	if (zend_hash_find(Z_ARRVAL_P(dst_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find dst['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(dst, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	int dstRectIsNull = Z_TYPE_PP(&dstrect_arg) == IS_ARRAY ? 0 : 1;
	if(!dstRectIsNull)
	{
		php_array_to_sdl_rect(&dstrect_arg, &dstrect);
	}

	int srcRectIsNull = Z_TYPE_PP(&srcrect_arg) == IS_ARRAY ? 0 : 1;
	if (!srcRectIsNull)
	{
		php_array_to_sdl_rect(&srcrect_arg, &srcrect);
	}

	RETURN_LONG(SDL_BlitSurface(src, srcRectIsNull ? NULL : &srcrect, dst, dstRectIsNull ? NULL : &dstrect));
}
/* }}} */

/* {{{ proto int sdl_fillrect(array dst, array dstrect, int color)

 */
PHP_FUNCTION(sdl_fillrect)
{
	zval *dst_arg, *dstrect_arg, **handle_resource;
	long color;
	SDL_Rect *dstrect = NULL;
	SDL_Surface *dst;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "azl", &dst_arg, &dstrect_arg, &color) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(dst_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find dst['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(dst, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	if (IS_NULL != Z_TYPE_P(dstrect_arg)) {
		dstrect = (SDL_Rect*)emalloc(sizeof(SDL_Rect));
		convert_to_array_ex(&dstrect_arg);
		php_array_to_sdl_rect(&dstrect_arg, dstrect);
	}

	int sdl_return_value = SDL_FillRect(dst, dstrect, color);
	
	if (NULL != dstrect) {
		efree(dstrect);
		dstrect = NULL;
	}

	RETURN_LONG(sdl_return_value);
}
/* }}} */

/* {{{ proto array sdl_displayformat(array surface)

 */
PHP_FUNCTION(sdl_displayformat)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface, *newsurface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	newsurface = (SDL_Surface *) SDL_DisplayFormat(surface);
	if (!newsurface) {
		
			php_error(E_WARNING, "%s() couldn't create new surface: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(newsurface,return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto array sdl_displayformatalpha(array surface)

 */
PHP_FUNCTION(sdl_displayformatalpha)
{
	zval *surface_arg, **handle_resource;
	SDL_Surface *surface, *newsurface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	newsurface = (SDL_Surface *) SDL_DisplayFormatAlpha(surface);
	if (!newsurface) {
		
			php_error(E_WARNING, "%s() couldn't create new surface: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(newsurface,return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto void sdl_warpmouse(int x, int y)

 */
PHP_FUNCTION(sdl_warpmouse)
{
	long x, y;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	SDL_WarpMouse(x, y);
}
/* }}} */

/* {{{ proto resource sdl_createcursor(array data, array mask, int w, int h, int hot_x, int hot_y)

 */
PHP_FUNCTION(sdl_createcursor)
{
	zval *data_arg, *mask_arg, **data_value, **mask_value;
	long w, h, hot_x, hot_y;
	int handle;
	ulong data_count, mask_count, i;
	Uint8 *data;
	Uint8 *mask;
	SDL_Cursor *cursor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzllll", &data_arg, &mask_arg, &w, &h, &hot_x, &hot_y) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	data_count = 0;
	mask_count = 0;

	data_count = zend_hash_next_free_element(Z_ARRVAL_P(data_arg));
	mask_count = zend_hash_next_free_element(Z_ARRVAL_P(mask_arg));

	if (data_count != mask_count) {
		php_error(E_WARNING, "%s() array size of data and mask are not equal",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (data_count == 0) {
		php_error(E_WARNING, "%s() array is empty!",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	data = (Uint8 *)emalloc(data_count*sizeof(Uint8));
	mask = (Uint8 *)emalloc(mask_count*sizeof(Uint8));

	for(i = 0; i < data_count; i++) {

		if (zend_hash_index_find(Z_ARRVAL_P(data_arg), i, (void **)&data_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find data[%lu]",
				  get_active_function_name(TSRMLS_C), i);
		}

		if (zend_hash_index_find(Z_ARRVAL_P(mask_arg), i, (void **)&mask_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find mask[%lu]",
				  get_active_function_name(TSRMLS_C), i);
		}

		data[i] = (Uint8) Z_LVAL_PP(data_value);
		mask[i] = (Uint8) Z_LVAL_PP(mask_value);
	}

	cursor = SDL_CreateCursor(data, mask, (int)w, (int)h, (int)hot_x, (int)hot_y);

	efree(data);
	efree(mask);

	if (cursor) {
		handle = zend_list_insert(cursor, le_cursor TSRMLS_CC);
		RETURN_RESOURCE(handle);
	}
	
	RETURN_FALSE;
}
/* }}} */
/* {{{ proto array sdl_creatergbsurfacefrom(array *pixels, int width, int height, int depth,int pitch,int Rmask,int Gmask, int Bmask, int Amask)
 */
PHP_FUNCTION(sdl_creatergbsurfacefrom)
{
	long width, height, depth, pitch;
	long Rmask, Gmask, Bmask, Amask;
	SDL_Surface *surface;
	char *string;
	int string_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sllllllll", &string, &string_len, &width, &height, &depth, &pitch, &Rmask, &Gmask, &Bmask, &Amask) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	surface = SDL_CreateRGBSurfaceFrom(string, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask);
	if (!surface) {
		if (SDL_G(expose_internal_errors)) {
			php_error(E_WARNING, "%s() Surface not created %s",
				  get_active_function_name(TSRMLS_C), SDL_GetError());
		}
		RETURN_FALSE;
	}
	
	php_sdl_surface_to_array(surface, return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto void sdl_freesurface(array surface)

 */
PHP_FUNCTION(sdl_freesurface)
{
	zval *surface_arg, **handle_resource, **format_array;
	int handle;
	SDL_Surface *surface;
	SDL_PixelFormat *format;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &surface_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	handle = Z_LVAL_PP(handle_resource);
	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);
	zend_list_delete(handle);

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "format", sizeof("format"), (void **)&format_array) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['format'] array",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (zend_hash_find(Z_ARRVAL_PP(format_array), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['format']['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	handle = Z_LVAL_PP(handle_resource);
	ZEND_FETCH_RESOURCE(format, SDL_PixelFormat *, handle_resource, -1, le_pixelformat_name, le_pixelformat);
	zend_list_delete(handle);

	SDL_FreeSurface(surface);
}
/* }}} */
/* {{{ proto void sdl_freecursor(resource cursor)

 */
PHP_FUNCTION(sdl_freecursor)
{
	zval *cursor_arg;
	SDL_Cursor *cursor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cursor_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(cursor, SDL_Cursor *, &cursor_arg, -1, le_cursor_name, le_cursor);
	SDL_FreeCursor(cursor);
	zend_list_delete(Z_LVAL_P(cursor_arg));
}
/* }}} */

/* {{{ proto void sdl_setcursor(resource cursor)

 */
PHP_FUNCTION(sdl_setcursor)
{
	zval *cursor_arg;
	SDL_Cursor *cursor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &cursor_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(cursor, SDL_Cursor *, &cursor_arg, -1, le_cursor_name, le_cursor);

	SDL_SetCursor(cursor);
}
/* }}} */

/* {{{ proto resource sdl_getcursor(void)

 */
PHP_FUNCTION(sdl_getcursor)
{
	int handle;
	SDL_Cursor *cursor;

	if (zend_parse_parameters_none() == FAILURE)
		return;

	cursor = SDL_GetCursor();

	if (cursor) {
		handle = zend_list_insert(cursor,le_cursor TSRMLS_CC);
		RETURN_RESOURCE(handle);
	}
	
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int sdl_showcursor(int toggle)

 */
PHP_FUNCTION(sdl_showcursor)
{
	zend_bool toggle;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &toggle) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_ShowCursor(toggle));
}
/* }}} */

/* {{{ proto int sdl_gl_loadlibrary(char path)

 */
PHP_FUNCTION(sdl_gl_loadlibrary)
{
    char *path;
    zend_uint pathlen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &pathlen) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_GL_LoadLibrary(path));
}
/* }}} */

/* {{{ proto int sdl_gl_getprocaddress(string proc)

 */
PHP_FUNCTION(sdl_gl_getprocaddress)
{
	/* TODO: implement */
	php_error(E_WARNING, "%s() not implemented yet",
			  get_active_function_name(TSRMLS_C));
}
/* }}} */

/* {{{ proto int sdl_gl_getattribute(int attr, int &value)

 */
PHP_FUNCTION(sdl_gl_getattribute)
{
	zval *value_arg;
	long attr;
	int value, result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "az", &attr, &value_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	result = SDL_GL_GetAttribute((int)attr, &value );

	if (result == 0) {
		convert_to_long_ex(&value_arg);
		ZVAL_LONG(value_arg, value);
	}

	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int sdl_gl_setattribute(int attr, int value)

 */
PHP_FUNCTION(sdl_gl_setattribute)
{
	long attr, value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &attr, &value) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(SDL_GL_SetAttribute((int)attr, (int)value));
}
/* }}} */

/* {{{ proto void sdl_gl_swapbuffers(void)

 */
PHP_FUNCTION(sdl_gl_swapbuffers)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_GL_SwapBuffers();
}
/* }}} */

/* {{{ proto array sdl_createyuvoverlay(int width, int height, int format, array display)

 */
PHP_FUNCTION(sdl_createyuvoverlay)
{
	zval *display_arg, **handle_resource;
	int handle;
	long format, width, height;
	SDL_Surface *display;
	SDL_Overlay *overlay;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llla", &width, &height, &format, &display_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(display_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find display['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(display, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	overlay = SDL_CreateYUVOverlay((int)width, (int)height, (Uint32)format, display);

	if (!overlay) {
		
			php_error(E_WARNING, "%s() unable to create overlay: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	handle = zend_list_insert(overlay, le_overlay TSRMLS_CC);

	array_init(return_value);
	add_assoc_resource(return_value, "handle", handle);
	zend_list_addref(handle);

	add_assoc_long(return_value, "format", overlay->format);
	add_assoc_long(return_value, "w", overlay->w);
	add_assoc_long(return_value, "h", overlay->h);
	add_assoc_long(return_value, "planes", overlay->planes);
	add_assoc_long(return_value, "hw_overlay", overlay->hw_overlay);
}
/* }}} */

/* {{{ proto int sdl_lockyuvoverlay(array overlay)

 */
PHP_FUNCTION(sdl_lockyuvoverlay)
{
	zval *overlay_arg, **handle_resource;
	SDL_Overlay *overlay;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &overlay_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(overlay_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find overlay['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(overlay, SDL_Overlay *, handle_resource, -1, le_overlay_name, le_overlay);

	RETURN_LONG(SDL_LockYUVOverlay(overlay));
}
/* }}} */

/* {{{ proto void sdl_unlockyuvoverlay(array overlay)

 */
PHP_FUNCTION(sdl_unlockyuvoverlay)
{
	zval *overlay_arg, **handle_resource;
	SDL_Overlay *overlay;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &overlay_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(overlay_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find overlay['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(overlay, SDL_Overlay *, handle_resource, -1, le_overlay_name, le_overlay);

	SDL_UnlockYUVOverlay(overlay);
}
/* }}} */

/* {{{ proto int sdl_displayyuvoverlay(array overlay, array dstrect)

 */
PHP_FUNCTION(sdl_displayyuvoverlay)
{
	zval *overlay_arg, *dstrect_arg, **handle_resource;
	SDL_Rect dstrect;
	SDL_Overlay *overlay;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &overlay_arg, &dstrect_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(overlay_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find overlay['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	ZEND_FETCH_RESOURCE(overlay, SDL_Overlay *, handle_resource, -1, le_overlay_name, le_overlay);

	php_array_to_sdl_rect(&dstrect_arg, &dstrect);

	RETURN_LONG(SDL_DisplayYUVOverlay(overlay, &dstrect));
}
/* }}} */

/* {{{ proto void sdl_freeyuvoverlay(array overlay)

 */
PHP_FUNCTION(sdl_freeyuvoverlay)
{
	zval *overlay_arg, **handle_resource;
	int handle;
	SDL_Overlay *overlay;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &overlay_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(overlay_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find overlay['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	
	handle = Z_LVAL_PP(handle_resource);
	ZEND_FETCH_RESOURCE(overlay, SDL_Overlay *, handle_resource, -1, le_overlay_name, le_overlay);
	zend_list_delete(handle);

	SDL_FreeYUVOverlay(overlay);
}
/* }}} */


/* }}} */

/* {{{ proto void sdl_getpixels(array surface, array &pixels)
 */
PHP_FUNCTION(sdl_getpixels)
{       
	zval *surface_arg, *pixels_arg, **handle_resource, **pixel_array, **x_value, **y_value;
	Uint16 x, y;
	Uint32 pixel;
	ulong pixels_count, i;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &surface_arg, &pixels_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
			  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	pixels_count = zend_hash_next_free_element(Z_ARRVAL_PP(&pixels_arg));

	for( i = 0; i < pixels_count; i++) { 
		if (zend_hash_index_find(Z_ARRVAL_P(pixels_arg), i, (void **)&pixel_array) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]",
				  get_active_function_name(TSRMLS_C), i);
		}

		if (zend_hash_find(Z_ARRVAL_PP(pixel_array), "x", sizeof("x"), (void **)&x_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]['x']",
				  get_active_function_name(TSRMLS_C), i);
			x = 0;
		} else {
			
			x = (Uint16) Z_LVAL_PP(x_value);
			}

		if (zend_hash_find(Z_ARRVAL_PP(pixel_array), "y", sizeof("y"), (void **)&y_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]['y']",
				  get_active_function_name(TSRMLS_C), i);
			y = 0;
		} else {
			y = (Uint16) Z_LVAL_PP(y_value);
			
		}
				
		switch (surface->format->BytesPerPixel) {
			case 1:
				pixel = *((Uint8 *)surface->pixels + y * surface->pitch + x);
				break;
			case 2:
				pixel = *((Uint16 *)surface->pixels + y * surface->pitch/2 + x);
				break;
			case 3:
				pixel = *((Uint8 *)surface->pixels + y * surface->pitch + x * 3);
				break;
			case 4:
				pixel = *((Uint32 *)surface->pixels + y * surface->pitch/4 + x);
				break;
			default:
				pixel = 0;
				php_error(E_WARNING, "%s() unknown surface BytesPerPixel!\n",
					  get_active_function_name(TSRMLS_C));
				break;
		}

		add_assoc_long((*pixel_array), "pixel", pixel);
	}
}

/* }}} */
/* {{{ proto void sdl_putpixels(array surface, array pixels)
*/
PHP_FUNCTION(sdl_putpixels)
{
	/* Borrowed from fast_putpixel1-4 from stars by Nathan Strong */
	zval *surface_arg, *pixels_arg, **handle_resource, **pixel_array, **x_value, **y_value, **pixel_value;
	Uint8 *pix;
	ulong pixels_count, i;
	SDL_Surface *surface;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &surface_arg, &pixels_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	if (zend_hash_find(Z_ARRVAL_P(surface_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, handle_resource, -1, le_surface_name, le_surface);

	pixels_count = zend_hash_next_free_element(Z_ARRVAL_PP(&pixels_arg));

	for( i = 0; i < pixels_count; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(pixels_arg), i, (void **)&pixel_array) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]",
				  get_active_function_name(TSRMLS_C), i);
		}

		if (zend_hash_find(Z_ARRVAL_PP(pixel_array), "x", sizeof("x"), (void **)&x_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]['x']",
				  get_active_function_name(TSRMLS_C), i);
			RETURN_FALSE;
		}

		if (zend_hash_find(Z_ARRVAL_PP(pixel_array), "y", sizeof("y"), (void **)&y_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]['y']",
				  get_active_function_name(TSRMLS_C), i);
			RETURN_FALSE;
		}

		if (zend_hash_find(Z_ARRVAL_PP(pixel_array), "pixel", sizeof("pixel"), (void **)&pixel_value) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find pixels[%lu]['pixel']",
				  get_active_function_name(TSRMLS_C), i);
			RETURN_FALSE;
		}

		switch (surface->format->BytesPerPixel) {
			case 1:
				*((Uint8 *)surface->pixels + (Uint16) Z_LVAL_PP(y_value) * surface->pitch + (Uint16) Z_LVAL_PP(x_value)) = (Uint32) Z_LVAL_PP(pixel_value);
				break;
			case 2:
				*((Uint16 *)surface->pixels + (Uint16) Z_LVAL_PP(y_value) * surface->pitch/2 + (Uint16) Z_LVAL_PP(x_value)) = (Uint32) Z_LVAL_PP(pixel_value);
				break;
			case 3:
				pix = (Uint8 *)surface->pixels + (Uint16) Z_LVAL_PP(y_value) * surface->pitch + (Uint16) Z_LVAL_PP(x_value) * 3;

				if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					pix[2] = (Uint32) Z_LVAL_PP(pixel_value);
					pix[1] = (Uint32) Z_LVAL_PP(pixel_value) >> 8;
					pix[0] = (Uint32) Z_LVAL_PP(pixel_value) >> 16;
				} else {
					pix[0] = (Uint32) Z_LVAL_PP(pixel_value);
					pix[1] = (Uint32) Z_LVAL_PP(pixel_value) >> 8;
					pix[2] = (Uint32) Z_LVAL_PP(pixel_value) >> 16;
				}
				break;
			case 4:
				*((Uint32 *)surface->pixels + (Uint16) Z_LVAL_PP(y_value) * surface->pitch/4 + (Uint16) Z_LVAL_PP(x_value)) = (Uint32) Z_LVAL_PP(pixel_value);
				break;
			default:
				php_error(E_WARNING, "%s() unknown surface BytesPerPixel!\n",
				  get_active_function_name(TSRMLS_C));
				break;
		}
	}
}
/* }}} */

/* }}} */

int php_sdl_find_key_with_type(zval *array, char *key, int key_len, int expected_type, zval ***value, const char *prefix TSRMLS_DC)
{
	if (Z_TYPE_P(array) != IS_ARRAY) {
		php_error(E_WARNING, "%s() expected to search for key %s in array but %s found",
				  get_active_function_name(TSRMLS_C), key, zend_zval_type_name(array));
		return 0;
	}
	if (zend_hash_find(Z_ARRVAL_P(array), key, key_len, (void**)value) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find %s['%s']",
				  get_active_function_name(TSRMLS_C), prefix, key);
		return 0;
	}
	if (Z_TYPE_PP(*value) != expected_type) {
		zval dummy;
		dummy.type = expected_type;
		php_error(E_WARNING, "%s() %s['%s'] expected to be %s; %s given",
				  get_active_function_name(TSRMLS_C), prefix, key, zend_zval_type_name(&dummy), zend_zval_type_name(**value));
		return 0;
	}
	return 1;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
