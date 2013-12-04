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

#ifndef PHP_SDL_TIME_H
#define PHP_SDL_TIME_H

#include "php.h"

extern int le_timer;
#define le_timer_name "SDL Timer"

void _sdl_timer(zend_rsrc_list_entry *rsrc TSRMLS_DC);

PHP_FUNCTION(sdl_getticks);
PHP_FUNCTION(sdl_delay);
PHP_FUNCTION(sdl_addtimer);
PHP_FUNCTION(sdl_removetimer);

#endif

