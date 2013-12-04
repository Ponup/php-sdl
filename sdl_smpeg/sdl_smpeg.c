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
#include "php_sdl_smpeg.h"
#include "ext/sdl/php_sdl.h"

#include <smpeg/smpeg.h>

ZEND_DECLARE_MODULE_GLOBALS(sdl_smpeg)

/* True global resources - no need for thread safety here */
static int le_smpeg;

static zend_class_entry *sdl_smpeg_class_entry_ptr;

ZEND_BEGIN_ARG_INFO(func_second_arg_force_ref, 0)
       ZEND_ARG_PASS_INFO(0)
       ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO()

static zend_module_dep sdl_smpeg_deps[] = { 
	ZEND_MOD_REQUIRED("sdl")
	ZEND_MOD_END
};

/* {{{ sdl_smpeg_functions[]
 *
 * Every user visible function must have an entry in sdl_smpeg_functions[].
 */
const zend_function_entry sdl_smpeg_functions[] = {
	ZEND_FE(smpeg_new,			func_second_arg_force_ref)
	/*
	ZEND_FE(smpeg_new_descr,					NULL)
	*/
	ZEND_FE(smpeg_new_data,					NULL)
	/*
	ZEND_FE(smpeg_new_rwops,					NULL)
	*/
	ZEND_FE(smpeg_getinfo,					NULL)
	ZEND_FE(smpeg_enableaudio,				NULL)
	ZEND_FE(smpeg_enablevideo,				NULL)
	ZEND_FE(smpeg_delete,					NULL)
	ZEND_FE(smpeg_status,					NULL)
	ZEND_FE(smpeg_setvolume,					NULL)
	ZEND_FE(smpeg_setdisplay,				NULL)
	ZEND_FE(smpeg_loop,						NULL)
	ZEND_FE(smpeg_scalexy,					NULL)
	ZEND_FE(smpeg_scale,						NULL)
	ZEND_FE(smpeg_double,					NULL)
	ZEND_FE(smpeg_move,						NULL)
	ZEND_FE(smpeg_setdisplayregion,			NULL)
	ZEND_FE(smpeg_play,						NULL)
	ZEND_FE(smpeg_pause,						NULL)
	ZEND_FE(smpeg_stop,						NULL)
	ZEND_FE(smpeg_rewind,					NULL)
	ZEND_FE(smpeg_seek,						NULL)
	ZEND_FE(smpeg_skip,						NULL)
	ZEND_FE(smpeg_renderframe,				NULL)
	ZEND_FE(smpeg_renderfinal,				NULL)
	/*
	ZEND_FE(smpeg_filter,					NULL)
	*/
	ZEND_FE(smpeg_error,						NULL)
	/*
	ZEND_FE(smpeg_playaudio,					NULL)
	ZEND_FE(smpeg_playaudiosdl,				NULL)
	ZEND_FE(smpeg_wantedspec,				NULL)
	ZEND_FE(smpeg_actualspec,				NULL)
	*/

	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_smpeg_module_entry
 */
zend_module_entry sdl_smpeg_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	sdl_smpeg_deps,
	"SDL_smpeg",
	sdl_smpeg_functions,
	PHP_MINIT(sdl_smpeg),
	PHP_MSHUTDOWN(sdl_smpeg),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl_smpeg),
	PHP_SDL_SMPEG_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL_SMPEG
ZEND_GET_MODULE(sdl_smpeg)
#endif

static void _sdl_smpeg (zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	SMPEG *smpeg = (SMPEG *)rsrc->ptr;
	if (smpeg) {
		if (SMPEG_PLAYING == SMPEG_status(smpeg)) {
			SMPEG_stop(smpeg);
		}
		SMPEG_delete(smpeg);
	}
}

/* {{{ php_sdl_smpeg_init_globals
 */
static void php_sdl_smpeg_init_globals(zend_sdl_smpeg_globals *sdl_smpeg_globals)
{
	sdl_smpeg_globals->smpeg_update_callback = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl_smpeg)
{
	le_smpeg		= zend_register_list_destructors_ex(_sdl_smpeg, NULL, le_smpeg_name, module_number);

	REGISTER_LONG_CONSTANT("SMPEG_ERROR",			SMPEG_ERROR,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SMPEG_STOPPED",			SMPEG_STOPPED,			CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SMPEG_PLAYING",			SMPEG_PLAYING,			CONST_CS | CONST_PERSISTENT);
	
	zend_class_entry sdl_smpeg_class_entry;
	/* Initialize plain class body with not methods */
	INIT_CLASS_ENTRY(sdl_smpeg_class_entry, "SMPEG_Info", NULL);
	sdl_smpeg_class_entry_ptr = zend_register_internal_class(&sdl_smpeg_class_entry TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl_smpeg)
{
	if (SDL_SMPEG_G(smpeg_update_callback)) {
		zval_ptr_dtor(&SDL_SMPEG_G(smpeg_update_callback));
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl_smpeg)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_smpeg support", "enabled");
	php_info_print_table_row(2, "SDL_smpeg module version", PHP_SDL_SMPEG_VERSION);
	php_info_print_table_end();
}
/* }}} */

int php_sdl_convert_smpeg_info_to_object(zval *object, SMPEG_Info *smpeg_info TSRMLS_DC)
{
	if (!object || !smpeg_info) {
		return 0;
	}
	object_init_ex(object, sdl_smpeg_class_entry_ptr);
	add_property_bool(object, 	"has_audio",			smpeg_info->has_audio);
	add_property_bool(object, 	"has_video",			smpeg_info->has_video);
	add_property_long(object, 	"width",				smpeg_info->width);
	add_property_long(object, 	"height",				smpeg_info->height);
	add_property_long(object, 	"current_frame",		smpeg_info->current_frame);
	add_property_double(object, "current_fps",			smpeg_info->current_fps);
	add_property_string(object, "audio_string",			smpeg_info->audio_string, 1);
	add_property_long(object,	"audio_current_frame",	smpeg_info->audio_current_frame);
	add_property_long(object,	"current_offset",		smpeg_info->current_offset);
	add_property_long(object,	"total_size",			smpeg_info->total_size);
	add_property_double(object,	"current_time",			smpeg_info->current_time);
	add_property_double(object,	"total_time",			smpeg_info->total_time);
	return 1;
}
/* }}} */

/* {{{ proto resource smpeg_new(string filename, object &info, int audio)
   On return, if 'info' is not NULL, it will be filled with information 
   about the MPEG object.
   This function returns a new SMPEG object.  Use SMPEG_error() to find out
   whether or not there was a problem building the MPEG stream.
   The sdl_audio parameter indicates if SMPEG should initialize the SDL audio
   subsystem. If not, you will have to use the SMPEG_playaudio() function below
   to extract the decoded data. 
*/
PHP_FUNCTION(smpeg_new)
{
	char *filename;
	long filename_len, sdl_audio;
	zval *z_info;
	SMPEG *smpeg;
	SMPEG_Info smpeg_info;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "szl", &filename, &filename_len, &z_info, &sdl_audio) == FAILURE)
		return;
	
	if (NULL == (smpeg = SMPEG_new(filename, &smpeg_info, sdl_audio))) {
			php_error(E_WARNING, "%s() could not create SMPEG resource: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		RETURN_FALSE;
	}
	ZEND_REGISTER_RESOURCE(return_value, smpeg, le_smpeg);
	zval_dtor(z_info);
	php_sdl_convert_smpeg_info_to_object(z_info, &smpeg_info TSRMLS_CC);
}
/* }}} */

/* {{{ proto resource smpeg_new_data(string data, object &info, int sdl_audio)
   The same as above but for a raw chunk of data.  SMPEG makes a copy of the
   data, so the application is free to delete after a successful call to this
   function. */
PHP_FUNCTION(smpeg_new_data)
{
	char *data;
	long data_len, sdl_audio;
	zval *z_info;
	SMPEG *smpeg;
	SMPEG_Info smpeg_info;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "szl", &data, &data_len, &z_info, &sdl_audio) == FAILURE)
		return;
	
	if (NULL == (smpeg = SMPEG_new_data(data, data_len, &smpeg_info, sdl_audio))) {
		
			php_error(E_WARNING, "%s() could not create SMPEG resource: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}
	ZEND_REGISTER_RESOURCE(return_value, smpeg, le_smpeg);
	zval_dtor(z_info);
	php_sdl_convert_smpeg_info_to_object(z_info, &smpeg_info TSRMLS_CC);
}
/* }}} */

/* {{{ proto object smpeg_getinfo(resource smpeg)
   Get current information about an SMPEG object. */
PHP_FUNCTION(smpeg_getinfo)
{
	zval *z_smpeg;
	SMPEG *smpeg;
	SMPEG_Info smpeg_info;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_getinfo(smpeg, &smpeg_info);

	php_sdl_convert_smpeg_info_to_object(return_value, &smpeg_info TSRMLS_CC);
}
/* }}} */

/* {{{ proto void smpeg_enableaudio(resource smpeg, bool enable)
   Enable or disable audio playback in MPEG stream. */
PHP_FUNCTION(smpeg_enableaudio)
{
	zval *z_smpeg;
	SMPEG *smpeg;
	zend_bool enable = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &z_smpeg, &enable) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_enableaudio(smpeg, enable);
}
/* }}} */

/* {{{ proto void smpeg_enablevideo(resource smpeg, bool enable)
   Enable or disable video playback in MPEG stream. */
PHP_FUNCTION(smpeg_enablevideo)
{
	zval *z_smpeg;
	SMPEG *smpeg;
	zend_bool enable = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &z_smpeg, &enable) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_enablevideo(smpeg, enable);
}
/* }}} */

/* {{{ proto void smpeg_delete(resource smpeg)
   Delete an SMPEG object */
PHP_FUNCTION(smpeg_delete)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_delete(smpeg);

	zend_list_delete(Z_RESVAL_P(z_smpeg));
}
/* }}} */

/* {{{ proto int smpeg_status(resource smpeg)
   Get the current status of an SMPEG object */
PHP_FUNCTION(smpeg_status)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	RETURN_LONG(SMPEG_status(smpeg));
}
/* }}} */

/* {{{ proto void smpeg_setvolume(resource smpeg)
   Set the audio volume of an MPEG stream, in the range 0-100 */
PHP_FUNCTION(smpeg_setvolume)
{
	zval *z_smpeg;
	SMPEG *smpeg;
	long volume;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &z_smpeg, &volume) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_setvolume(smpeg, volume);
}
/* }}} */

void php_sdl_smpeg_update(SDL_Surface *screen, Sint32 x, Sint32 y, Uint32 w, Uint32 h)
{
}

/* {{{ proto bool smpeg_setdisplay(resource smpeg, resource dest_surface, resource surflock_mutex, mixed callback)
   Set the destination surface for MPEG video playback
   'surfLock' is a mutex used to synchronize access to 'dst', and can be NULL.
   'callback' is a function called when an area of 'dst' needs to be updated.
   If 'callback' is NULL, the default function (SDL_UpdateRect) will be used. */
PHP_FUNCTION(smpeg_setdisplay)
{
	zval *z_smpeg, *z_surface, *z_mutex = NULL, *z_callback = NULL, **z_surface_handle;
	SMPEG *smpeg;
	SDL_mutex *mutex = NULL;
	SDL_Surface *surface;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ra|zz",
		&z_smpeg, &z_surface, &z_mutex, &z_callback) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	if (zend_hash_find(Z_ARRVAL_P(z_surface), "handle", sizeof("handle"), (void**)&z_surface_handle) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, z_surface_handle, -1, le_surface_name, le_surface);

	if (z_mutex) {
		if (Z_TYPE_P(z_mutex) == IS_RESOURCE) {
			ZEND_FETCH_RESOURCE(mutex, SDL_mutex *, &z_mutex, -1, le_mutex_name, le_mutex);
		} else {
			if (Z_TYPE_P(z_mutex) != IS_NULL) {
				php_error(E_WARNING, "%s() expected argument 3 to be either NULL or SDL Mutex resource; %s given",
						  get_active_function_name(TSRMLS_C), zend_zval_type_name(z_mutex));
				RETURN_FALSE;
			}
		}
	}

	if (z_callback && Z_TYPE_P(z_callback) != IS_NULL) {
		/* TODO: Invoke the callback function */
		php_error(E_WARNING, "%s() handling callbacks is not yet implemented",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	} else {
		SMPEG_setdisplay(smpeg, surface, mutex, NULL);
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto void smpeg_loop(resource smpeg, int repeat)
   Set or clear looping play on an SMPEG object. */
PHP_FUNCTION(smpeg_loop)
{
	zval *z_smpeg;
	zend_bool repeat = 1;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &z_smpeg, &repeat) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_loop(smpeg, repeat);
}
/* }}} */

/* {{{ proto void smpeg_scalexy(resource smpeg, int width, int height)
   Scale pixel display on an SMPEG object. */
PHP_FUNCTION(smpeg_scalexy)
{
	zval *z_smpeg;
	long width, height;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &z_smpeg, &width, &height) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_scaleXY(smpeg, width, height);
}
/* }}} */

/* {{{ proto void smpeg_scale(resource smpeg, int scale)
   Scale pixel display on an SMPEG object. */
PHP_FUNCTION(smpeg_scale)
{
	zval *z_smpeg;
	long scale;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &z_smpeg, &scale) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_scale(smpeg, scale);
}
/* }}} */

/* {{{ proto void smpeg_double(resuorce smpeg, bool double)
   Scale pixel display on an SMPEG object. */
PHP_FUNCTION(smpeg_double)
{
	zval *z_smpeg;
	zend_bool ddouble = 1;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &z_smpeg, &ddouble) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_double(smpeg, ddouble);
}
/* }}} */

/* {{{ proto void smpeg_move(resource smpeg, int x, int y)
   Move the video display area within the destination surface. */
PHP_FUNCTION(smpeg_move)
{
	zval *z_smpeg;
	long x, y;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &z_smpeg, &x, &y) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_move(smpeg, x, y);
}
/* }}} */

/* {{{ proto void smpeg_setdisplayregion(resource smpeg, int x, int y, int w, int h)
   Set the region of the video to be shown. */
PHP_FUNCTION(smpeg_setdisplayregion)
{
	zval *z_smpeg;
	long x, y, w, h;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllll", &z_smpeg, &x, &y, &w, &h) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_setdisplayregion(smpeg, x, y, w, h);

}
/* }}} */

/* {{{ proto smpeg_play(resource smpeg)
   Play an SMPEG object. */
PHP_FUNCTION(smpeg_play)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_play(smpeg);
}
/* }}} */

/* {{{ proto smpeg_pause(resource smpeg)
   Pause/Resume playback of an SMPEG object. */
PHP_FUNCTION(smpeg_pause)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_pause(smpeg);
}
/* }}} */

/* {{{ proto smpeg_stop(resource smpeg)
   Stop playback of an SMPEG object. */
PHP_FUNCTION(smpeg_stop)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_stop(smpeg);
}
/* }}} */

/* {{{ proto smpeg_rewind(resource smpeg)
   Rewind the play position of an SMPEG object to the beginning of the MPEG. */
PHP_FUNCTION(smpeg_rewind)
{
	zval *z_smpeg;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_rewind(smpeg);
}
/* }}} */

/* {{{ proto smpeg_seek(resource smpeg, int bytes)
   Seek 'bytes' bytes in the MPEG stream. */
PHP_FUNCTION(smpeg_seek)
{
	zval *z_smpeg;
	long bytes;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &z_smpeg, &bytes) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_seek(smpeg, bytes);
}
/* }}} */

/* {{{ proto smpeg_skip(resource smpeg, double seconds)
   Skip 'seconds' seconds in the MPEG stream. */
PHP_FUNCTION(smpeg_skip)
{
	zval *z_smpeg;
	double seconds;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rd", &z_smpeg, &seconds) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_skip(smpeg, (float)seconds);
}
/* }}} */

/* {{{ proto smpeg_renderframe(resource smpeg, int framenum)
   Render a particular frame in the MPEG video. */
PHP_FUNCTION(smpeg_renderframe)
{
	zval *z_smpeg;
	long framenum;
	SMPEG *smpeg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &z_smpeg, &framenum) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	SMPEG_renderFrame(smpeg, framenum);
}
/* }}} */

/* {{{ proto void smpeg_renderfinal(resource smpeg, resoruce dest_surface, int x, int y)
   Render the last frame of an MPEG video. */
PHP_FUNCTION(smpeg_renderfinal)
{
	zval *z_smpeg, *z_surface, *z_surface_handle;
	long x, y;
	SMPEG *smpeg;
	SDL_Surface *surface;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rall", &z_smpeg, &z_surface, &x, &y) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	if (zend_hash_find(Z_ARRVAL_P(z_surface), "handle", sizeof("handle"), (void**)&z_surface_handle) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find surface['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(surface, SDL_Surface *, &z_surface_handle, -1, le_surface_name, le_surface);

	SMPEG_renderFinal(smpeg, surface, x, y);
}
/* }}} */

/* {{{ proto string smpeg_error(resource smpeg)
   Return NULL if there is no error in the MPEG stream, or an error message
   if there was a fatal error in the MPEG stream for the SMPEG object. */
PHP_FUNCTION(smpeg_error)
{
	zval *z_smpeg;
	SMPEG *smpeg;
	char *errmsg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_smpeg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(smpeg, SMPEG *, &z_smpeg, -1, le_smpeg_name, le_smpeg);

	if (errmsg = SMPEG_error(smpeg)) {
		RETURN_STRING(errmsg, 1);
	}
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
