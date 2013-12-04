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

#ifndef PHP_SDL_EVENT_H
#define PHP_SDL_EVENT_H

#include "php.h"

PHP_FUNCTION(sdl_pumpevents);
PHP_FUNCTION(sdl_peepevents);
PHP_FUNCTION(sdl_pollevent);
PHP_FUNCTION(sdl_waitevent);
PHP_FUNCTION(sdl_pushevent);
PHP_FUNCTION(sdl_seteventfilter);
PHP_FUNCTION(sdl_geteventfilter);
PHP_FUNCTION(sdl_eventstate);

#endif

