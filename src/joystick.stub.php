<?php

/**
 * 
 * @return int
 */
function SDL_NumJoysticks():int {
    return 0;
}

/**
 * Get the name of a joystick by index.
 * @param  int         $index joystick index (starts from 0).
 * @return null|string
 */
function SDL_JoystickNameForIndex(int $index):null|string {
    return '';
}

/**
 * Open a joystick connection by index.
 * @param  int               $index joystick index (starts from 0).
 * @return null|SDL_Joystick
 */
function SDL_JoystickOpen(int $index):null|object {
    return null;
}

/**
 * Close a joystick connection.
 * @param  SDL_Joystick $joystick
 * @return void
 */
function SDL_JoystickClose(object $joystick):void {
}

/**
 * Get the name of a joystick.
 * @param  SDL_Joystick $joystick
 * @return void
 */
function SDL_JoystickName(object $joystick):void {
}

/**
 * Get the current value of an axis.
 * @param  SDL_Joystick $joystick
 * @param  int          $axis     `0` is the `x` axis and `1` is the `y` axis.
 * @return int
 */
function SDL_JoystickGetAxis(
    object $joystick,
    int $axis,
):int {
    return 0;
}

/**
 * Get the number of buttons on the joystick.
 * @param  SDL_Joystick $joystick
 * @return int
 */
function SDL_JoystickNumButtons(
    object $joystick,
):int {
    return 0;
}

/**
 * Check if a joystick is used by a videogame by index.
 * @param  int  $index joystick index (starts from 0).
 * @return bool
 */
function SDL_IsGameController(int $index):bool {
    return true;
}