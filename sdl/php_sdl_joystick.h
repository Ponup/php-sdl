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

#ifndef PHP_SDL_JOYSTICK_H
#define PHP_SDL_JOYSTICK_H

#include "php.h"

extern int le_joystick;
#define le_joystick_name "SDL Joystick"

void _sdl_joystick(zend_rsrc_list_entry *rsrc TSRMLS_DC);

PHP_FUNCTION(sdl_numjoysticks);
PHP_FUNCTION(sdl_joystickname);
PHP_FUNCTION(sdl_joystickopen);
PHP_FUNCTION(sdl_joystickopened);
PHP_FUNCTION(sdl_joystickindex);
PHP_FUNCTION(sdl_joysticknumaxes);
PHP_FUNCTION(sdl_joysticknumballs);
PHP_FUNCTION(sdl_joysticknumhats);
PHP_FUNCTION(sdl_joysticknumbuttons);
PHP_FUNCTION(sdl_joystickupdate);
PHP_FUNCTION(sdl_joystickeventstate);
PHP_FUNCTION(sdl_joystickgetaxis);
PHP_FUNCTION(sdl_joystickgethat);
PHP_FUNCTION(sdl_joystickgetball);
PHP_FUNCTION(sdl_joystickgetbutton);
PHP_FUNCTION(sdl_joystickclose);

#endif

