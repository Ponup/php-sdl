/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/


#include "blendmode.h"

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_blendmode)
{
	REGISTER_LONG_CONSTANT("SDL_BLENDMODE_NONE",  SDL_BLENDMODE_NONE,  CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BLENDMODE_BLEND", SDL_BLENDMODE_BLEND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BLENDMODE_ADD",   SDL_BLENDMODE_ADD,   CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_BLENDMODE_MOD",   SDL_BLENDMODE_MOD,   CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */
