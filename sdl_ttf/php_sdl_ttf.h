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

#ifndef PHP_SDL_TTF_H
#define PHP_SDL_TTF_H

#define PHP_SDL_TTF_VERSION "0.9.2"

#define le_ttf_font_name "TTF font"

extern zend_module_entry sdl_ttf_module_entry;
#define phpext_sdl_ttf_ptr &sdl_ttf_module_entry

#ifdef PHP_WIN32
#	define PHP_SDL_TTF_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SDL_TTF_API __attribute__ ((visibility("default")))
#else
#	define PHP_SDL_TTF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(sdl_ttf);
PHP_MSHUTDOWN_FUNCTION(sdl_ttf);
PHP_MINFO_FUNCTION(sdl_ttf);

PHP_FUNCTION(ttf_init);
PHP_FUNCTION(ttf_openfont);

PHP_FUNCTION(ttf_rendertext_solid);
PHP_FUNCTION(ttf_rendertext_blended);

PHP_FUNCTION(ttf_renderutf8_solid);
PHP_FUNCTION(ttf_renderutf8_blended);

PHP_FUNCTION(ttf_renderunicode_solid);
PHP_FUNCTION(ttf_closefont);
PHP_FUNCTION(ttf_fontlineskip);
PHP_FUNCTION(ttf_quit);

/* In every utility function you add that needs to use variables 
   in php_sdl_ttf_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SDL_TTF_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SDL_TTF_G(v) TSRMG(sdl_ttf_globals_id, zend_sdl_ttf_globals *, v)
#else
#define SDL_TTF_G(v) (sdl_ttf_globals.v)
#endif

#endif	/* PHP_SDL_TTF_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
