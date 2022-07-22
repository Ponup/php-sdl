/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2022 The PHP Group                                |
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

#ifndef PHP_SDL_KEYBOARD_H
#define PHP_SDL_KEYBOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "php_sdl.h"

       ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetKeyboardState, 0, 0, 0)
       ZEND_ARG_TYPE_INFO(ARG_PASS_BY_REF, numkeys, IS_LONG, ARG_ALLOW_NULL)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetModState, 0, 0, 1)
       ZEND_ARG_INFO(0, modstate)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetTextInputRect, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_IsScreenKeyboardShown, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_scancode, 0, 0, 1)
       ZEND_ARG_INFO(0, scancode)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_key, 0, 0, 1)
       ZEND_ARG_INFO(0, key)
       ZEND_END_ARG_INFO()

       ZEND_BEGIN_ARG_INFO_EX(arginfo_name, 0, 0, 1)
       ZEND_ARG_INFO(0, name)
       ZEND_END_ARG_INFO()

       PHP_FUNCTION(SDL_GetKeyboardFocus);
       PHP_FUNCTION(SDL_GetKeyboardState);
       PHP_FUNCTION(SDL_GetModState);
       PHP_FUNCTION(SDL_SetModState);
       PHP_FUNCTION(SDL_GetKeyFromScancode);
       PHP_FUNCTION(SDL_GetScancodeFromKey);
       PHP_FUNCTION(SDL_GetScancodeName);
       PHP_FUNCTION(SDL_GetScancodeFromName);
       PHP_FUNCTION(SDL_GetKeyName);
       PHP_FUNCTION(SDL_GetKeyFromName);
       PHP_FUNCTION(SDL_StartTextInput);
       PHP_FUNCTION(SDL_IsTextInputActive);
       PHP_FUNCTION(SDL_StopTextInput);
       PHP_FUNCTION(SDL_SetTextInputRect);
       PHP_FUNCTION(SDL_HasScreenKeyboardSupport);
       PHP_FUNCTION(SDL_IsScreenKeyboardShown);

       PHP_MINIT_FUNCTION(sdl_keyboard);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_SDL_KEYBOARD_H */
