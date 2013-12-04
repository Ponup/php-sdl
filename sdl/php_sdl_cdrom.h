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

#ifndef PHP_SDL_CDROM_H
#define PHP_SDL_CDROM_H

#include "php.h"

extern int le_cdrom;
#define le_cdrom_name "SDL CD-Rom"

void _sdl_cdrom (zend_rsrc_list_entry *rsrc TSRMLS_DC);

PHP_FUNCTION(sdl_cd_indrive);
PHP_FUNCTION(sdl_frames_to_msf);
PHP_FUNCTION(sdl_msf_to_frames);
PHP_FUNCTION(sdl_cdnumdrives);
PHP_FUNCTION(sdl_cdname);
PHP_FUNCTION(sdl_cdopen);
PHP_FUNCTION(sdl_cdstatus);
PHP_FUNCTION(sdl_cdplay);
PHP_FUNCTION(sdl_cdplaytracks);
PHP_FUNCTION(sdl_cdpause);
PHP_FUNCTION(sdl_cdresume);
PHP_FUNCTION(sdl_cdstop);
PHP_FUNCTION(sdl_cdeject);
PHP_FUNCTION(sdl_cdclose);

#endif

