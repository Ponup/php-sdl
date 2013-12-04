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

#ifndef PHP_SDL_AUDIO_H
#define PHP_SDL_AUDIO_H

#include "php.h"

extern int le_sdl_audiospec;
#define le_sdl_audiospec_name "SDL AudioSpec"

extern int le_sdl_audiocvt;
#define le_sdl_audiocvt_name "SDL AudioCVT"

void _sdl_audiospec(zend_rsrc_list_entry *rsrc TSRMLS_DC);
void _sdl_audiocvt(zend_rsrc_list_entry *rsrc TSRMLS_DC);

PHP_FUNCTION(sdl_openaudio);
PHP_FUNCTION(sdl_pauseaudio);
PHP_FUNCTION(sdl_getaudiostatus);
PHP_FUNCTION(sdl_loadwav);
PHP_FUNCTION(sdl_freewav);
PHP_FUNCTION(sdl_buildaudiocvt);
PHP_FUNCTION(sdl_convertaudio);
PHP_FUNCTION(sdl_mixaudio);
PHP_FUNCTION(sdl_lockaudio);
PHP_FUNCTION(sdl_unlockaudio);
PHP_FUNCTION(sdl_closeaudio);

#endif

