/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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


#ifndef PHP_SDL_MUTEX_H
#define PHP_SDL_MUTEX_H

#ifdef  __cplusplus
extern "C" {
#endif

zend_class_entry *get_php_sdl_mutex_ce(void);
zend_bool sdl_mutex_to_zval(SDL_mutex *mutex, zval *z_val, Uint32 flags TSRMLS_DC);
SDL_mutex *zval_to_sdl_mutex(zval *z_val TSRMLS_DC);

zend_class_entry *get_php_sdl_sem_ce(void);
zend_bool sdl_sem_to_zval(SDL_sem *sem, zval *z_val, Uint32 flags TSRMLS_DC);
SDL_sem *zval_to_sdl_sem(zval *z_val TSRMLS_DC);

zend_class_entry *get_php_sdl_cond_ce(void);
zend_bool sdl_cond_to_zval(SDL_cond *cond, zval *z_val, Uint32 flags TSRMLS_DC);
SDL_cond *zval_to_sdl_cond(zval *z_val TSRMLS_DC);

PHP_MINIT_FUNCTION(sdl_mutex);

#ifdef  __cplusplus
} // extern "C"
#endif

#endif /* PHP_SDL_MUTEX_H */

