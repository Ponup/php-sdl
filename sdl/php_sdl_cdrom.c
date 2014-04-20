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

#include "php_sdl_cdrom.h"

#include <SDL.h>

#define GET_CDROM_RESOURCE(cdrom)	{ \
			switch (Z_TYPE_P(cdrom_arg)) { \
				case IS_ARRAY: \
					if (zend_hash_find(Z_ARRVAL_P(cdrom_arg), "handle", sizeof("handle"), (void**)&handle_resource) == FAILURE) { \
						php_error(E_WARNING, "%s() unable to find cdrom['handle'] resource", \
								  get_active_function_name(TSRMLS_C)); \
						RETURN_FALSE; \
					} \
					ZEND_FETCH_RESOURCE(cdrom, SDL_CD *, handle_resource, -1, le_cdrom_name, le_cdrom); \
					break; \
				case IS_RESOURCE: \
					ZEND_FETCH_RESOURCE(cdrom, SDL_CD *, &cdrom_arg, -1, le_cdrom_name, le_cdrom); \
					break; \
				default: \
					php_error(E_WARNING, "%s() argument 1 expected to be CDROM resource or array containing CDROM resource; %s given", \
							  get_active_function_name(TSRMLS_C), zend_zval_type_name(cdrom_arg)); \
					RETURN_FALSE; \
			} \
		}

/* Resources */
int le_cdrom;

void _sdl_cdrom (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}

/* {{{ proto int sdl_cdindrive(int status)
 */
PHP_FUNCTION(sdl_cd_indrive)
{
	long status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &status) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(CD_INDRIVE((int)status));
}
/* }}} */

/* {{{ proto array sdl_frames_to_msf(int f)

 */
PHP_FUNCTION(sdl_frames_to_msf)
{
	long frame;
	int m, s, f;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &frame) == FAILURE)
		return;
	
	FRAMES_TO_MSF(frame, &m, &s, &f);

	array_init(return_value);
	add_next_index_long(return_value, m);
	add_next_index_long(return_value, s);
	add_next_index_long(return_value, f);
}
/* }}} */

/* {{{ proto int sdl_msf_to_frames(int M, int S, int F)
 */
PHP_FUNCTION(sdl_msf_to_frames)
{
	long M, S, F;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &M, &S, &F) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(MSF_TO_FRAMES((int)M, (int)S, (int)F));
}
/* }}} */

/* {{{ proto int sdl_cdnumdrives(void)
 */
PHP_FUNCTION(sdl_cdnumdrives)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG(SDL_CDNumDrives());
}
/* }}} */

/* {{{ proto int sdl_cdname(int drive)
 */
PHP_FUNCTION(sdl_cdname)
{
	long drive;
	char *buf;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &drive) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	buf = (char *)SDL_CDName((int)drive);

	RETURN_STRING(estrndup(buf,strlen(buf)),0);
}
/* }}} */

/* {{{ proto array sdl_cdopen(int drive)
 */
PHP_FUNCTION(sdl_cdopen)
{
	zval *one_track, *track_array;
	int handle, cur_track;
	long drive;
	SDL_CD *cdrom = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &drive) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	cdrom = SDL_CDOpen((int)drive);
	if (!cdrom) {
		
			php_error(E_WARNING, "%s() couldn't open drive: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	/* SDL_CDOpen does not return track informations, but let's initialize the return array first.
	 * Track informations will get populated after SDL_CDStatus() call. */
	MAKE_STD_ZVAL(track_array);
	array_init(track_array);
	for(cur_track=0; cur_track <= SDL_MAX_TRACKS; cur_track++) {
		MAKE_STD_ZVAL(one_track);
		array_init(one_track);
		add_assoc_long(one_track, "id", cdrom->track[cur_track].id);
		add_assoc_long(one_track, "type", cdrom->track[cur_track].type);
		add_assoc_long(one_track, "unused", cdrom->track[cur_track].unused);
		add_assoc_long(one_track, "length", cdrom->track[cur_track].length);
		add_assoc_long(one_track, "offset", cdrom->track[cur_track].offset);
		add_next_index_zval(track_array, one_track);
	}

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 3) || (PHP_MAJOR_VERSION > 5)
	handle = zend_list_insert(cdrom, le_cdrom TSRMLS_CC);
#else
	handle = zend_list_insert(cdrom, le_cdrom);
#endif

	array_init(return_value);
	add_assoc_resource(return_value, "handle", handle);
	zend_list_addref(handle);

	add_assoc_long(return_value, "id", cdrom->id);
	add_assoc_long(return_value, "status", cdrom->status);
	add_assoc_long(return_value, "numtracks", cdrom->numtracks);
	add_assoc_long(return_value, "cur_track", cdrom->cur_track);
	add_assoc_long(return_value, "cur_frame", cdrom->cur_frame);
	add_assoc_zval(return_value, "track", track_array);

}
/* }}} */

/* {{{ proto int sdl_cdstatus(array &cdrom)
 */
PHP_FUNCTION(sdl_cdstatus)
{
	zval *cdrom_arg, **handle_resource, **track_array, **one_track;
	int cdstatus, cur_track;
	SDL_CD *cdrom = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	/* check for parameter being passed by reference */
	if (!PZVAL_IS_REF(cdrom_arg)) {
		php_error(E_WARNING, "%s() parameter cdrom needs to be passed by reference",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (zend_hash_find(Z_ARRVAL_P(cdrom_arg), "handle", sizeof("handle"), (void **)&handle_resource) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find cdrom['handle'] resource",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (zend_hash_find(Z_ARRVAL_P(cdrom_arg), "track", sizeof("track"), (void **)&track_array) == FAILURE) {
		php_error(E_WARNING, "%s() unable to find cdrom['track'] array",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(cdrom, SDL_CD *, handle_resource, -1, le_cdrom_name, le_cdrom);
	cdstatus = SDL_CDStatus(cdrom);

	/* Update array &cdrom according to contents in SDL_CD *cdrom structure */
	add_assoc_long(cdrom_arg, "status", cdrom->status);
	add_assoc_long(cdrom_arg, "numtracks", cdrom->numtracks);
	add_assoc_long(cdrom_arg, "cur_track", cdrom->cur_track);
	add_assoc_long(cdrom_arg, "cur_frame", cdrom->cur_frame);

	for(cur_track=0;cur_track <= cdrom->numtracks; cur_track++) {
		if (zend_hash_index_find(Z_ARRVAL_PP(track_array), cur_track, (void **)&one_track) == FAILURE) {
			php_error(E_WARNING, "%s() unable to find cdrom['track'][%d] array",
				  get_active_function_name(TSRMLS_C), cur_track);
		}

		add_assoc_long((*one_track), "id", cdrom->track[cur_track].id);
		add_assoc_long((*one_track), "type", cdrom->track[cur_track].type);
		add_assoc_long((*one_track), "unused", cdrom->track[cur_track].unused);
		add_assoc_long((*one_track), "length", cdrom->track[cur_track].length);
		add_assoc_long((*one_track), "offset", cdrom->track[cur_track].offset);
	}

	RETURN_LONG(cdstatus);
}
/* }}} */

/* {{{ proto int sdl_cdplay(array cdrom, int start, int length)
 */
PHP_FUNCTION(sdl_cdplay)
{
	zval *cdrom_arg, **handle_resource;
	long start, length;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll", &cdrom_arg, &start, &length) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	RETURN_LONG(SDL_CDPlay(cdrom, (int)start, (int)length));
}
/* }}} */

/* {{{ proto int sdl_cdplaytracks(array cdrom, int start_track, int start_frame, int ntracks, int nframes)
 */
PHP_FUNCTION(sdl_cdplaytracks)
{
	zval *cdrom_arg, **handle_resource;
	long start_track, start_frame, ntracks, nframes, ret;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zllll", &cdrom_arg, &start_track, &start_frame, &ntracks, &nframes) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	if (-1 == (ret = SDL_CDPlayTracks(cdrom, (int)start_track, (int)start_frame, (int)ntracks, (int)nframes))) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(ret);
	}
}
/* }}} */

/* {{{ proto int sdl_cdpause(array cdrom)
 */
PHP_FUNCTION(sdl_cdpause)
{
	zval *cdrom_arg, **handle_resource;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	RETURN_LONG(SDL_CDPause(cdrom));
}
/* }}} */

/* {{{ proto int sdl_cdresume(array cdrom)
 */
PHP_FUNCTION(sdl_cdresume)
{
	zval *cdrom_arg, **handle_resource;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	RETURN_LONG(SDL_CDResume(cdrom));
}
/* }}} */

/* {{{ proto int sdl_cdstop(array cdrom)
 */
PHP_FUNCTION(sdl_cdstop)
{
	zval *cdrom_arg, **handle_resource;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	RETURN_LONG(SDL_CDStop(cdrom));
}
/* }}} */

/* {{{ proto int sdl_cdeject(array cdrom)
 */
PHP_FUNCTION(sdl_cdeject)
{
	zval *cdrom_arg, **handle_resource;
	SDL_CD *cdrom;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);

	RETURN_LONG(SDL_CDEject(cdrom));
}
/* }}} */

/* {{{ proto void sdl_cdclose(array cdrom)
 */
PHP_FUNCTION(sdl_cdclose)
{
	zval *cdrom_arg, **handle_resource;
	int handle;
	SDL_CD *cdrom = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cdrom_arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	GET_CDROM_RESOURCE(cdrom);
	handle = Z_LVAL_PP(handle_resource);
	zend_list_delete(handle);

	SDL_CDClose(cdrom);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
