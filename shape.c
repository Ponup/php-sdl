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
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

/* $Id$ */ 

/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_shape.h (only SDL_Window)                       |
  +----------------------------------------------------------------------+
  | class SDL_WindowShapeMode                                            |
  +----------------------------------------------------------------------+
*/


#include "php_sdl.h"
#include "shape.h"
#include "window.h"


/* {{{ sdl_shape_functions[] */
zend_function_entry sdl_shape_functions[] = {
	ZEND_FE_END
};
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_shape)
{
	return (zend_register_functions(NULL, sdl_shape_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */
