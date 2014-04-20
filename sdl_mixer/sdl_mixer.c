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
#include "php_sdl_mixer.h"

#include <SDL/SDL_mixer.h>

/* True global resources - no need for thread safety here */
static int le_sdl_mixer;
static int le_mix_chunk;
static int le_mix_music;

static zend_module_dep sdl_mixer_deps[] = { 
	ZEND_MOD_REQUIRED("sdl")
	ZEND_MOD_END
};

/* {{{ sdl_mixer_functions[]
 *
 * Every user visible function must have an entry in sdl_mixer_functions[].
 */
const zend_function_entry sdl_mixer_functions[] = {
	ZEND_FE(mix_openaudio, NULL)
	ZEND_FE(mix_closeaudio, NULL)
	ZEND_FE(mix_loadmus, NULL)
	ZEND_FE(mix_loadwav, NULL)
	ZEND_FE(mix_playchannel, NULL)
	ZEND_FE(mix_playmusic, NULL)
	ZEND_FE(mix_playingmusic, NULL)

	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_mixer_module_entry
 */
zend_module_entry sdl_mixer_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	sdl_mixer_deps,
	"SDL_mixer",
	sdl_mixer_functions,
	PHP_MINIT(sdl_mixer),
	PHP_MSHUTDOWN(sdl_mixer),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl_mixer),
	PHP_SDL_MIXER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL_MIXER
ZEND_GET_MODULE(sdl_mixer)
#endif

static void _mix_destructor (zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl_mixer)
{
	le_mix_chunk = zend_register_list_destructors_ex(_mix_destructor, NULL, le_mix_chunk_name, module_number);
	le_mix_music = zend_register_list_destructors_ex(_mix_destructor, NULL, le_mix_music_name, module_number);

	REGISTER_LONG_CONSTANT("MIX_DEFAULT_FREQUENCY", MIX_DEFAULT_FREQUENCY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MIX_DEFAULT_FORMAT", MIX_DEFAULT_FORMAT, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl_mixer)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl_mixer)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_mixer support", "enabled");
	php_info_print_table_row(2, "SDL_mixer module version", PHP_SDL_MIXER_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize) */
PHP_FUNCTION(mix_openaudio)
{
	long frequency, format, channels, chunkSize;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &frequency, &format, &channels, &chunkSize) == FAILURE)
	{
		php_error(E_ERROR, "%s(): wrong params");

		RETURN_FALSE;
	}

	if(Mix_OpenAudio(frequency, format, channels, chunkSize) == -1)
	{
		php_error(E_ERROR, "%s(): %s", get_active_function_name(TSRMLS_C), Mix_GetError());

		RETURN_FALSE;
	}

	RETURN_TRUE;
}

PHP_FUNCTION(mix_closeaudio)
{
	Mix_CloseAudio();
}

/* Mix_Music *Mix_LoadMUS(const char *file) */
PHP_FUNCTION(mix_loadmus)
{
	char *musicPath;
	long musicPathLen;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &musicPath, &musicPathLen) == FAILURE)
	{
		php_error(E_ERROR, "%s(): wrong params");

		RETURN_FALSE;
	}

	Mix_Music *music = Mix_LoadMUS(musicPath);
	if(!music)
	{
		php_error(E_ERROR, "%s(): %s", get_active_function_name(TSRMLS_C), Mix_GetError());
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, music, le_mix_music);
}

/* int Mix_PlayMusic(Mix_Music *music, int loops) */
PHP_FUNCTION(mix_playmusic)
{
	zval *musicRes;
	long times;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &musicRes, &times) == FAILURE)
	{
		RETURN_FALSE;
	}

	Mix_Music *music;
        ZEND_FETCH_RESOURCE(music, Mix_Music*, &musicRes, -1, le_mix_music_name, le_mix_music);

	if(Mix_PlayMusic(music, -1) == -1)
	{
		php_error(E_ERROR, "%s(): %s", get_active_function_name(TSRMLS_C), Mix_GetError());
	}
}

PHP_FUNCTION(mix_playingmusic)
{
	if(Mix_PlayingMusic() == 0)
	{
		RETURN_FALSE;
	}
	else
	{
		RETURN_TRUE;
	}
}

PHP_FUNCTION(mix_loadwav)
{
	char *musicPath;
	long musicPathLen;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &musicPath, &musicPathLen) == FAILURE)
	{
		php_error(E_ERROR, "%s(): wrong params");

		RETURN_FALSE;
	}

	Mix_Chunk *music = Mix_LoadWAV(musicPath);
	if(!music)
	{
		php_error(E_ERROR, "%s(): %s", get_active_function_name(TSRMLS_C), Mix_GetError());
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, music, le_mix_chunk);

}

PHP_FUNCTION(mix_playchannel)
{
	zval *musicRes;
	long channel, times;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lrl", &channel, &musicRes, &times) == FAILURE)
	{
		RETURN_FALSE;
	}

	Mix_Chunk *music;
        ZEND_FETCH_RESOURCE(music, Mix_Chunk*, &musicRes, -1, le_mix_chunk_name, le_mix_chunk);

	if(Mix_PlayChannel(channel, music, times) == -1)
	{
		php_error(E_ERROR, "%s(): %s", get_active_function_name(TSRMLS_C), Mix_GetError());
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
