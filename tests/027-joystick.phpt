--TEST--
Joystick test suite.
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
<?php
var_dump(0 === SDL_Init(SDL_INIT_JOYSTICK));
var_dump(is_long(SDL_NumJoysticks()));
var_dump(SDL_JoystickNameForIndex(PHP_INT_MAX));
var_dump(SDL_IsGameController(PHP_INT_MAX));
var_dump(SDL_JoystickOpen(PHP_INT_MAX));
--EXPECTF--
bool(true)
bool(true)
NULL
bool(false)
NULL
