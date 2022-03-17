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

#include "joystick.h"

#include <SDL_joystick.h>

static zend_class_entry *php_sdl_joystick_ce;
static zend_object_handlers php_sdl_joystick_handlers;

struct php_sdl_joystick
{
    SDL_Joystick *intern;
    zend_object zo;
};
typedef struct php_sdl_joystick php_sdl_joystick_t;

static zend_object *php_sdl_joystick_create_object(zend_class_entry *ce)
{
    php_sdl_joystick_t *php_joystick;

    php_joystick = (php_sdl_joystick_t *)ecalloc(1, sizeof(php_sdl_joystick_t) + zend_object_properties_size(ce));

    zend_object_std_init(&php_joystick->zo, ce);
    object_properties_init(&php_joystick->zo, ce);

    php_joystick->intern = NULL;
    php_joystick->zo.handlers = (zend_object_handlers *)&php_sdl_joystick_handlers;

    return &php_joystick->zo;
}

static void php_sdl_joystick_free_object(zend_object *zo)
{
    php_sdl_joystick_t *php_joystick = (php_sdl_joystick_t *)((char *)zo - zo->handlers->offset);
    zend_object_std_dtor(&php_joystick->zo);
}

static inline SDL_Joystick *sdl_joystick_from_zval(zval *zjoystick)
{
    zend_object *zo = Z_OBJ_P(zjoystick);
    php_sdl_joystick_t *php_joystick = (php_sdl_joystick_t *)((char *)zo - zo->handlers->offset);
    return php_joystick->intern;
}

static inline void sdl_joystick_to_zval(SDL_Joystick *joystick, zval *zvalue)
{
    object_init_ex(zvalue, php_sdl_joystick_ce);
    zend_object *zo = Z_OBJ_P(zvalue);
    php_sdl_joystick_t *php_joystick = (php_sdl_joystick_t *)((char *)zo - zo->handlers->offset);
    php_joystick->intern = joystick;
}

PHP_FUNCTION(SDL_NumJoysticks)
{
    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(SDL_NumJoysticks());
}

PHP_FUNCTION(SDL_JoystickNameForIndex)
{
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    const char *name = SDL_JoystickNameForIndex(index);
    if (name)
    {
        RETURN_STRING(name);
    }

    RETURN_NULL();
}

PHP_FUNCTION(SDL_JoystickOpen)
{
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    SDL_Joystick *joystick = SDL_JoystickOpen(index);
    if (joystick)
    {
        sdl_joystick_to_zval(joystick, return_value);
        return;
    }

    RETURN_NULL();
}

PHP_FUNCTION(SDL_JoystickClose)
{
    zval *zjoystick;
    SDL_Joystick *joystick;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_OBJECT_OF_CLASS(zjoystick, php_sdl_joystick_ce)
    ZEND_PARSE_PARAMETERS_END();

    joystick = sdl_joystick_from_zval(zjoystick);

    SDL_JoystickClose(joystick);
}

PHP_FUNCTION(SDL_JoystickName)
{
    zval *zjoystick;
    SDL_Joystick *joystick;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_OBJECT_OF_CLASS(zjoystick, php_sdl_joystick_ce)
    ZEND_PARSE_PARAMETERS_END();

    joystick = sdl_joystick_from_zval(zjoystick);

    RETURN_STRING(SDL_JoystickName(joystick));
}

PHP_FUNCTION(SDL_JoystickGetAxis)
{
    zval *zjoystick;
    zend_long axis;
    SDL_Joystick *joystick;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_OBJECT_OF_CLASS(zjoystick, php_sdl_joystick_ce)
    Z_PARAM_LONG(axis)
    ZEND_PARSE_PARAMETERS_END();

    joystick = sdl_joystick_from_zval(zjoystick);

    RETURN_LONG(SDL_JoystickGetAxis(joystick, axis));
}

PHP_FUNCTION(SDL_JoystickNumButtons)
{
    zval *zjoystick;
    SDL_Joystick *joystick;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_OBJECT_OF_CLASS(zjoystick, php_sdl_joystick_ce)
    ZEND_PARSE_PARAMETERS_END();

    joystick = sdl_joystick_from_zval(zjoystick);

    RETURN_LONG(SDL_JoystickNumButtons(joystick));
}

PHP_FUNCTION(SDL_IsGameController)
{
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(SDL_IsGameController(index) == SDL_TRUE);
}

PHP_MINIT_FUNCTION(sdl_joystick)
{
    zend_class_entry sdl_joystick_ce;
    INIT_CLASS_ENTRY(sdl_joystick_ce, "SDL_Joystick", NULL);

    php_sdl_joystick_ce = zend_register_internal_class(&sdl_joystick_ce);
    php_sdl_joystick_ce->create_object = php_sdl_joystick_create_object;

    memcpy(&php_sdl_joystick_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_sdl_joystick_handlers.free_obj = php_sdl_joystick_free_object;
    php_sdl_joystick_handlers.offset = XtOffsetOf(php_sdl_joystick_t, zo);

    return SUCCESS;
}
