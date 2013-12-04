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

#ifndef PHP_SDL_IMAGE_H
#define PHP_SDL_IMAGE_H

#define PHP_SDL_IMAGE_VERSION "0.9.2"

extern zend_module_entry sdl_image_module_entry;
#define phpext_sdl_image_ptr &sdl_image_module_entry

#ifdef PHP_WIN32
#	define PHP_SDL_IMAGE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SDL_IMAGE_API __attribute__ ((visibility("default")))
#else
#	define PHP_SDL_IMAGE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(sdl_image);
PHP_MSHUTDOWN_FUNCTION(sdl_image);
PHP_MINFO_FUNCTION(sdl_image);

PHP_FUNCTION(img_load);
PHP_FUNCTION(img_load_rw);
PHP_FUNCTION(img_loadtyped_rw);
PHP_FUNCTION(img_loadbmp_rw);
PHP_FUNCTION(img_loadpnm_rw);
PHP_FUNCTION(img_loadxpm_rw);
PHP_FUNCTION(img_loadxcf_rw);
PHP_FUNCTION(img_loadpcx_rw);
PHP_FUNCTION(img_loadgif_rw);
PHP_FUNCTION(img_loadjpg_rw);
PHP_FUNCTION(img_loadtif_rw);
PHP_FUNCTION(img_loadpng_rw);
PHP_FUNCTION(img_loadtga_rw);
PHP_FUNCTION(img_loadlbm_rw);
PHP_FUNCTION(img_readxpmfromarray);

PHP_FUNCTION(img_seterror);
PHP_FUNCTION(img_geterror);

PHP_FUNCTION(img_isbmp);
PHP_FUNCTION(img_ispnm);
PHP_FUNCTION(img_isxpm);
PHP_FUNCTION(img_isxcf);
PHP_FUNCTION(img_ispcx);
PHP_FUNCTION(img_isgif);
PHP_FUNCTION(img_isjpg);
PHP_FUNCTION(img_istif);
PHP_FUNCTION(img_ispng);
PHP_FUNCTION(img_islbm);

/* In every utility function you add that needs to use variables 
   in php_sdl_image_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SDL_IMAGE_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SDL_IMAGE_G(v) TSRMG(sdl_image_globals_id, zend_sdl_image_globals *, v)
#else
#define SDL_IMAGE_G(v) (sdl_image_globals.v)
#endif

#endif	/* PHP_SDL_IMAGE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
