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

#include "php_sdl_audio.h"

#include <SDL.h>

/* Resources */
int le_sdl_audiospec;
int le_sdl_audiocvt;

void _sdl_audiospec(zend_rsrc_list_entry *rsrc TSRMLS_DC) {}
void _sdl_audiocvt(zend_rsrc_list_entry *rsrc TSRMLS_DC) {}

SDL_AudioSpec* convert_zval_to_sdl_audiospec( zval **zv_var ) {
	zval **zv_value = NULL;
	SDL_AudioSpec *converted_audiospec = (SDL_AudioSpec*)emalloc( sizeof( SDL_AudioSpec ) );

	if(zend_hash_find(Z_ARRVAL_PP(zv_var), "freq", sizeof("freq"), (void **)&zv_value) != FAILURE) {
		convert_to_long_ex(zv_value);
		converted_audiospec->freq = (Sint16)Z_LVAL_PP(zv_value);
	}
	if(zend_hash_find(Z_ARRVAL_PP(zv_var), "format", sizeof("format"), (void **)&zv_value) != FAILURE) {
		convert_to_long_ex(zv_value);
		converted_audiospec->format = (Sint16)Z_LVAL_PP(zv_value);
	}
	if(zend_hash_find(Z_ARRVAL_PP(zv_var), "channels", sizeof("channels"), (void **)&zv_value) != FAILURE) {
		convert_to_long_ex(zv_value);
		converted_audiospec->channels = (Sint16)Z_LVAL_PP(zv_value);
	}
	if(zend_hash_find(Z_ARRVAL_PP(zv_var), "samples", sizeof("samples"), (void **)&zv_value) != FAILURE) {
		convert_to_long_ex(zv_value);
		converted_audiospec->samples = (Sint16)Z_LVAL_PP(zv_value);
	}

	return converted_audiospec;
}

zval* convert_sdl_audiospec_to_zval( SDL_AudioSpec *spec ) {
	zval *zv_spec = NULL;

	if (NULL == spec)
		return NULL;

	MAKE_STD_ZVAL( zv_spec );
	array_init( zv_spec );
	add_assoc_long( zv_spec, "freq", spec->freq );
	add_assoc_long( zv_spec, "format", spec->format );
	add_assoc_long( zv_spec, "channels", spec->channels );
	add_assoc_long( zv_spec, "samples", spec->samples );

	return zv_spec;
}

void convert_sdl_audiospec_to_existing_zval( SDL_AudioSpec *spec, zval *zv_spec ) {
	if (NULL == spec)
		return;

	array_init( zv_spec );
	add_assoc_long( zv_spec, "freq", spec->freq );
	add_assoc_long( zv_spec, "format", spec->format );
	add_assoc_long( zv_spec, "channels", spec->channels );
	add_assoc_long( zv_spec, "samples", spec->samples );
}

Uint8* convert_zval_to_uint8( zval *zv_var ) {
	Uint8 *var = NULL;
	zval *zv_value = NULL;
	unsigned int i = 0, var_count = 0, var_len = 0;

	var_count = zend_hash_next_free_element(Z_ARRVAL_PP(&zv_var));
	var_len = sizeof(Uint8) * var_count;
	var = (Uint8*)emalloc( var_len );
	memset( var, '\0', var_len );

	for( ; i < var_count; i++ ) {
		if (zend_hash_index_find(Z_ARRVAL_PP(&zv_var), i, (void **)&zv_value) != FAILURE) {
			ZVAL_LONG( zv_value, var[ i ] );
		}
	}

	return var;
}

zval* convert_uint8_to_zval( Uint8 *var ) {
	zval *zv_var = NULL;
	unsigned int i = 0;

	MAKE_STD_ZVAL( zv_var );
	array_init( zv_var );

	for( ; var[ i ]; i++ ) {
		add_index_long( zv_var, i, var[ i ] );
	}

	return zv_var;
}

void convert_uint8_to_existing_zval( Uint8 *var, zval *zv_var ) {
	unsigned int i = 0;

	array_init( zv_var );
	for( ; var[ i ]; i++ ) {
		add_index_long( zv_var, i, var[ i ] );
	}
}

int sound_pos = 0;
Uint8 *audio_buf = NULL;
Uint32 audio_len;

/**
 * This callback is invoked every time we load audio with SDL_LoadWAV and SDL_PauseAudio(0).
 * @todo Move this callback to userland so that users can do fancy things with the sound.
 */
void callback(void *userdata, Uint8 *stream, int length) {
	Uint8 *wave = NULL;
	wave = audio_buf + sound_pos;
 	SDL_memcpy( stream, wave, length );
	sound_pos += length;
	if (sound_pos >= audio_len - length)
		SDL_PauseAudio(1);
}

/* {{{ proto int sdl_openaudio(array desired, array &obtained)

 int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
 */
PHP_FUNCTION(sdl_openaudio)
{
	zval *zv_desired = NULL, *zv_obtained = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &zv_desired, &zv_obtained) == FAILURE)
		return;

	SDL_AudioSpec *desired = convert_zval_to_sdl_audiospec( &zv_desired );
	desired->callback = callback;
	desired->userdata = NULL;
	SDL_AudioSpec obtained;

	int result = SDL_OpenAudio( desired, &obtained );

	convert_sdl_audiospec_to_existing_zval( &obtained, zv_obtained );

	RETURN_LONG( result );
}
/* }}} */

/* {{{ proto void sdl_pauseaudio(int pause_on)

 void SDL_PauseAudio(int pause_on);
 */
PHP_FUNCTION(sdl_pauseaudio)
{
	long pause_on;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &pause_on) == FAILURE)
		return;

	SDL_PauseAudio( pause_on );
}
/* }}} */

/* {{{ proto int sdl_getaudiostatus(void)

 SDL_audiostatus SDL_GetAudioStatus(void);
 */
PHP_FUNCTION(sdl_getaudiostatus)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG( SDL_GetAudioStatus() );
}
/* }}} */

/* {{{ proto array sdl_loadwav(string file, array &spec, array &buf, long &len)

 SDL_AudioSpec *SDL_LoadWAV(const char *file, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
 */
PHP_FUNCTION(sdl_loadwav)
{
	char *file = NULL;
	int file_len;
	zval *zv_spec = NULL, *zv_audio_buff = NULL, *zv_audio_len = NULL;
	SDL_AudioSpec *returned_spec = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "szzz", &file, &file_len, &zv_spec, &zv_audio_buff, &zv_audio_len) == FAILURE)
		return;

	SDL_AudioSpec *spec = (SDL_AudioSpec*)emalloc(sizeof(SDL_AudioSpec));

	returned_spec = SDL_LoadWAV( file, spec, &audio_buf, &audio_len );
	if (NULL == returned_spec)
		RETURN_NULL();

	convert_uint8_to_existing_zval( audio_buf, zv_audio_buff );

	ZVAL_LONG( zv_audio_len, audio_len );

	zval *returned_zval = convert_sdl_audiospec_to_zval( returned_spec );
	convert_sdl_audiospec_to_existing_zval( returned_spec, zv_spec );
	RETURN_ZVAL( returned_zval, 1, 0 );
/*
	int handle = zend_list_insert( returned_spec, le_sdl_audiospec TSRMLS_CC );
	array_init( return_value );
	add_assoc_resource( return_value, "handle", handle );
	*/
}
/* }}} */

/* void SDL_FreeWAV(Uint8 *audio_buf) */
PHP_FUNCTION(sdl_freewav)
{
	/* TODO: Implement */
	RETURN_NULL();
}

/* int SDL_BuildAudioCVT(SDL_AudioCVT *cvt, Uint16 src_format, Uint8 src_channels, int src_rate, Uint16 dst_format, Uint8 dst_channels, int dst_rate) */
PHP_FUNCTION(sdl_buildaudiocvt)
{
	RETURN_NULL();
}

/* int SDL_ConvertAudio(SDL_AudioCVT *cvt) */
PHP_FUNCTION(sdl_convertaudio)
{
	RETURN_NULL();
}

/* void SDL_MixAudio(Uint8 *dst, Uint8 *src, Uint32 len, int volume) */
PHP_FUNCTION(sdl_mixaudio)
{
	zval *zv_dst = NULL, *zv_src = NULL;
	long len, volume;
	Uint8 *dst = NULL, *src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzll", &zv_dst, &zv_src, &len, &volume) == FAILURE)
		return;

	dst = convert_zval_to_uint8( zv_dst );
	src = convert_zval_to_uint8( zv_src );

	SDL_MixAudio( dst, src, len, volume );
}

/* {{{ proto void sdl_lockaudio(void)

 void SDL_LockAudio(void);
 */
PHP_FUNCTION(sdl_lockaudio)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_LockAudio();
}
/* }}} */

/* {{{ proto void sdl_lockaudio(void)

 void SDL_UnlockAudio(void);
 */
PHP_FUNCTION(sdl_unlockaudio)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_UnlockAudio();
}
/* }}} */

/* {{{ proto void sdl_closeaudio(void)

 void SDL_CloseAudio(void);
 */
PHP_FUNCTION(sdl_closeaudio)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	SDL_CloseAudio();
}
/* }}} */

