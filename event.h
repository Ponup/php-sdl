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

#ifndef PHP_SDL_EVENT_H
#define PHP_SDL_EVENT_H

#ifdef  __cplusplus
extern "C" {
#endif

zend_class_entry *get_php_sdl_event_ce(void);
zend_bool sdl_event_to_zval(SDL_Event *event, zval *value TSRMLS_DC);
zend_bool zval_to_sdl_event(zval *value, SDL_Event *event TSRMLS_DC);

PHP_MINIT_FUNCTION(sdl_event);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_EVENT_H */

