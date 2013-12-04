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

#ifndef PHP_SDL_SMPEG_H
#define PHP_SDL_SMPEG_H

#define PHP_SDL_SMPEG_VERSION "0.9.2"

#define	   le_smpeg_name		"SMPEG"

extern zend_module_entry sdl_smpeg_module_entry;
#define phpext_sdl_smpeg_ptr &sdl_smpeg_module_entry

#ifdef PHP_WIN32
#	define PHP_SDL_SMPEG_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SDL_SMPEG_API __attribute__ ((visibility("default")))
#else
#	define PHP_SDL_SMPEG_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(sdl_smpeg);
PHP_MSHUTDOWN_FUNCTION(sdl_smpeg);
PHP_MINFO_FUNCTION(sdl_smpeg);

PHP_FUNCTION(smpeg_new);
PHP_FUNCTION(smpeg_new_descr);
PHP_FUNCTION(smpeg_new_data);
PHP_FUNCTION(smpeg_new_rwops);
PHP_FUNCTION(smpeg_getinfo);
PHP_FUNCTION(smpeg_enableaudio);
PHP_FUNCTION(smpeg_enablevideo);
PHP_FUNCTION(smpeg_delete);
PHP_FUNCTION(smpeg_status);
PHP_FUNCTION(smpeg_setvolume);
PHP_FUNCTION(smpeg_setdisplay);
PHP_FUNCTION(smpeg_loop);
PHP_FUNCTION(smpeg_scalexy);
PHP_FUNCTION(smpeg_scale);
PHP_FUNCTION(smpeg_double);
PHP_FUNCTION(smpeg_move);
PHP_FUNCTION(smpeg_setdisplayregion);
PHP_FUNCTION(smpeg_play);
PHP_FUNCTION(smpeg_pause);
PHP_FUNCTION(smpeg_stop);
PHP_FUNCTION(smpeg_rewind);
PHP_FUNCTION(smpeg_seek);
PHP_FUNCTION(smpeg_skip);
PHP_FUNCTION(smpeg_renderframe);
PHP_FUNCTION(smpeg_renderfinal);
PHP_FUNCTION(smpeg_filter);
PHP_FUNCTION(smpeg_error);
PHP_FUNCTION(smpeg_playaudio);
PHP_FUNCTION(smpeg_playaudiosdl);
PHP_FUNCTION(smpeg_wantedspec);
PHP_FUNCTION(smpeg_actualspec);

/* In every utility function you add that needs to use variables 
   in php_sdl_smpeg_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SDL_SMPEG_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

ZEND_BEGIN_MODULE_GLOBALS(sdl_smpeg)
	zval *smpeg_update_callback;
	pthread_t smpeg_update_caller;
ZEND_END_MODULE_GLOBALS(sdl_smpeg)

#ifdef ZTS
#define SDL_SMPEG_G(v) TSRMG(sdl_smpeg_globals_id, zend_sdl_smpeg_globals *, v)
#else
#define SDL_SMPEG_G(v) (sdl_smpeg_globals.v)
#endif

#endif	/* PHP_SDL_SMPEG_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
