/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Santiago Lizardo <santiagolizardo@php.net>                   |
  | Author: Remi Collet <remi@php.net>                                   |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SDL_JOYSTICK_H
#define PHP_SDL_JOYSTICK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "php_sdl.h"

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_NumJoysticks, 0, 0, 0)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_NumJoysticks);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickOpen, 0, 0, 1)
  ZEND_ARG_TYPE_INFO(ARG_NOT_PASS_BY_REF, index, IS_LONG, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickOpen);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickClose, 0, 0, 1)
  ZEND_ARG_OBJ_INFO(ARG_NOT_PASS_BY_REF, joystick, SDL_Joystick, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickClose);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickName, 0, 0, 1)
  ZEND_ARG_OBJ_INFO(ARG_NOT_PASS_BY_REF, joystick, SDL_Joystick, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickName);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickGetAxis, 0, 0, 2)
  ZEND_ARG_OBJ_INFO(ARG_NOT_PASS_BY_REF, joystick, SDL_Joystick, ARG_NOT_ALLOW_NULL)
  ZEND_ARG_TYPE_INFO(ARG_NOT_PASS_BY_REF, axis, IS_LONG, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickGetAxis);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickNameForIndex, 0, 0, 1)
  ZEND_ARG_TYPE_INFO(ARG_NOT_PASS_BY_REF, index, IS_LONG, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickNameForIndex);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_JoystickNumButtons, 0, 0, 1)
  ZEND_ARG_OBJ_INFO(ARG_NOT_PASS_BY_REF, joystick, SDL_Joystick, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_JoystickNumButtons);

  ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_IsGameController, 0, 0, 1)
  ZEND_ARG_TYPE_INFO(ARG_NOT_PASS_BY_REF, index, IS_LONG, ARG_NOT_ALLOW_NULL)
  ZEND_END_ARG_INFO()
  PHP_FUNCTION(SDL_IsGameController);

  PHP_MINIT_FUNCTION(sdl_joystick);

#ifdef __cplusplus
}
#endif

#endif
