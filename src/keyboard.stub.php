<?php


/**
 * Get the window which currently has keyboard focus.
 * @return void
 */
function SDL_GetKeyboardFocus():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Get a snapshot of the current state of the keyboard.
 * @param  null|int   &$numkeys if non-NULL, receives the length of the returned array.
 * @return array<int> An array of key states. Indexes into this array are obtained by using `SDL_Scancode_*` values.
 */
function SDL_GetKeyboardState(null|int &$numkeys):array {
    return [];
}

/**
 * Get the current key modifier state for the keyboard.
 * @return int
 */
function SDL_GetModState():int {
    return 0;
}

/**
 * Set the current key modifier state for the keyboard.
 * 
 * This does not change the keyboard state, only the key modifier flags.
 * @return void
 */
function SDL_SetModState(int $modstate):void {
}

/**
 * Get the key code corresponding to the given scancode according to the current keyboard layout.
 * 
 * See `SDLK_*` constants for details.
 * @param  int $scancode
 * @return int
 */
function SDL_GetKeyFromScancode(int $scancode):int {
    return 0;
}

/**
 * Get the scancode corresponding to the given key code according to the current keyboard layout.
 * 
 * See `SDLK_*` constants for details.
 * @param  int $key
 * @return int
 */
function SDL_GetScancodeFromKey(int $key):int {
    return 0;
}

/**
 * Get a human-readable name for a scancode.
 * 
 * 
 * @param  int    $scancode
 * @return string The name for the scancode.
 *                         If the scancode doesn't have a name, this function returns an empty string ("").
 */
function SDL_GetScancodeName(int $scancode):string {
    return '';
}

/**
 * Get a scancode from a human-readable name
 * @param  string $name
 * @return int    scancode, or `SDL_SCANCODE_UNKNOWN` if the name wasn't recognized
 */
function SDL_GetScancodeFromName(string $name):int {
    return 0;
}

/**
 * Get a human-readable name for a key.
 * @param  int    $key
 * @return string a UTF-8 string that stays valid at least until the next call to this function. If you need it around any longer, you must copy it.  If the key doesn't have a name, this function returns an empty string ("").
 */
function SDL_GetKeyName(int $key):string {
    return '';
}

/**
 * Get a key code from a human-readable name
 * @param  string $name
 * @return int    key code, or SDLK_UNKNOWN if the name wasn't recognized.
 */
function SDL_GetKeyFromName(string $name):int {
    return 0;
}

/**
 * Start accepting Unicode text input events.
 * 
 * This function will show the on-screen keyboard if supported.
 * @return void
 */
function SDL_StartTextInput():void {
}

/**
 * Return whether or not Unicode text input events are enabled.
 * @return bool
 */
function SDL_IsTextInputActive():bool {
    return true;
}

/**
 * Stop receiving any text input events.
 * 
 * This function will hide the on-screen keyboard if supported.
 * @return void
 */
function SDL_StopTextInput():void {
}

/**
 * Set the rectangle used to type Unicode text inputs.
 * 
 * This is used as a hint for IME and on-screen keyboard placement.
 * @param  SDL_Rect $rect
 * @return void
 */
function SDL_SetTextInputRect(
    SDL_Rect $rect
):void {
}

/**
 * Returns whether the platform has some screen keyboard support.
 * 
 * Not all screen keyboard functions are supported on all platforms.
 * @return bool `true` if some keyboard support is available else `false`.
 */
function SDL_HasScreenKeyboardSupport():bool {
    return true;
}

/**
 * Returns whether the screen keyboard is shown for given window.
 * @param  SDL_Window $window The window for which screen keyboard should be queried.
 * @return bool       `true` if screen keyboard is shown else `false`.
 */
function SDL_IsScreenKeyboardShown(
    SDL_Window $window
):bool {
    return true;
}