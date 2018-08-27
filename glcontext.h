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

#ifndef PHP_SDL_GLCONTEXT_H
#define PHP_SDL_GLCONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GLContext, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, GLcontext, SDL_GLContext, 0)
ZEND_END_ARG_INFO()

zend_class_entry *get_php_sdl_glcontext_ce(void);
zend_bool  sdl_glcontext_to_zval(SDL_GLContext glcontext, zval *z_val, Uint32 flags TSRMLS_DC);
SDL_GLContext zval_to_sdl_glcontext(zval *z_val TSRMLS_DC);

PHP_FUNCTION(SDL_GL_CreateContext);
PHP_FUNCTION(SDL_GL_MakeCurrent);
PHP_FUNCTION(SDL_GL_GetCurrentWindow);
#if SDL_VERSION_ATLEAST(2,0,1)
PHP_FUNCTION(SDL_GL_GetDrawableSize);
#endif
PHP_FUNCTION(SDL_GL_SwapWindow);

PHP_MINIT_FUNCTION(sdl_glcontext);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_GLCONTEXT_H */

