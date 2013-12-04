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
#include "php_sdl_image.h"

#include <SDL_image.h>

/* True global resources - no need for thread safety here */
static int le_sdl_image;

static zend_module_dep sdl_image_deps[] = { 
	ZEND_MOD_REQUIRED("sdl")
	ZEND_MOD_END
};

/* {{{ sdl_image_functions[]
 *
 * Every user visible function must have an entry in sdl_image_functions[].
 */
const zend_function_entry sdl_image_functions[] = {
	ZEND_FE(img_load, NULL)
	ZEND_FE(img_load_rw, NULL)
	ZEND_FE(img_loadtyped_rw, NULL)
	ZEND_FE(img_loadbmp_rw, NULL)
	ZEND_FE(img_loadpnm_rw, NULL)
	ZEND_FE(img_loadxpm_rw, NULL)
	ZEND_FE(img_loadxcf_rw, NULL)
	ZEND_FE(img_loadpcx_rw, NULL)
	ZEND_FE(img_loadgif_rw, NULL)
	ZEND_FE(img_loadjpg_rw, NULL)
	ZEND_FE(img_loadtif_rw, NULL)
	ZEND_FE(img_loadpng_rw, NULL)
	ZEND_FE(img_loadtga_rw, NULL)
	ZEND_FE(img_loadlbm_rw, NULL)
	ZEND_FE(img_readxpmfromarray, NULL)

	ZEND_FE(img_seterror, NULL)
	ZEND_FE(img_geterror, NULL)

	ZEND_FE(img_isbmp, NULL)
	ZEND_FE(img_ispnm, NULL)
	ZEND_FE(img_isxpm, NULL)
	ZEND_FE(img_isxcf, NULL)
	ZEND_FE(img_ispcx, NULL)
	ZEND_FE(img_isgif, NULL)
	ZEND_FE(img_isjpg, NULL)
	ZEND_FE(img_istif, NULL)
	ZEND_FE(img_ispng, NULL)
	ZEND_FE(img_islbm, NULL)

	ZEND_FE_END
};
/* }}} */

/* {{{ sdl_image_module_entry
 */
zend_module_entry sdl_image_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	sdl_image_deps,
	"SDL_image",
	sdl_image_functions,
	PHP_MINIT(sdl_image),
	PHP_MSHUTDOWN(sdl_image),
	/* RINIT, RSHUTDOWN */
	NULL, NULL,
	PHP_MINFO(sdl_image),
	PHP_SDL_IMAGE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SDL_IMAGE
ZEND_GET_MODULE(sdl_image)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sdl_image)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sdl_image)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sdl_image)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sdl_image)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_image support", "enabled");
	php_info_print_table_row(2, "SDL_image module version", PHP_SDL_IMAGE_VERSION);
	php_info_print_table_end();
}
/* }}} */

PHP_FUNCTION(img_load)
{
	char *filename;
	int filename_len;
	SDL_Surface *image;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE)
		RETURN_FALSE;

	if (NULL == (image = IMG_Load(filename))) {
		
			php_error(E_WARNING, "%s() could not load image '%s': %s",
					  get_active_function_name(TSRMLS_C), filename, SDL_GetError());
		
		RETURN_FALSE;
	}

	php_sdl_surface_to_array(image, return_value TSRMLS_CC);
}

PHP_FUNCTION(img_load_rw) {}
PHP_FUNCTION(img_loadtyped_rw) {}
PHP_FUNCTION(img_loadbmp_rw) {}
PHP_FUNCTION(img_loadpnm_rw) {}
PHP_FUNCTION(img_loadxpm_rw) {}
PHP_FUNCTION(img_loadxcf_rw) {}
PHP_FUNCTION(img_loadpcx_rw) {}
PHP_FUNCTION(img_loadgif_rw) {}
PHP_FUNCTION(img_loadjpg_rw) {}
PHP_FUNCTION(img_loadtif_rw) {}
PHP_FUNCTION(img_loadpng_rw) {}
PHP_FUNCTION(img_loadtga_rw) {}
PHP_FUNCTION(img_loadlbm_rw) {}
PHP_FUNCTION(img_readxpmfromarray) {}

PHP_FUNCTION(img_seterror) {}
PHP_FUNCTION(img_geterror) {}

PHP_FUNCTION(img_isbmp) {}
PHP_FUNCTION(img_ispnm) {}
PHP_FUNCTION(img_isxpm) {}
PHP_FUNCTION(img_isxcf) {}
PHP_FUNCTION(img_ispcx) {}
PHP_FUNCTION(img_isgif) {}
PHP_FUNCTION(img_isjpg) {}
PHP_FUNCTION(img_istif) {}
PHP_FUNCTION(img_ispng) {}
PHP_FUNCTION(img_islbm) {}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
