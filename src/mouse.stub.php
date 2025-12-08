<?php
class SDL_Cursor implements Stringable {
    const ARROW     = 0;
    const IBEAM     = 1;
    const WAIT      = 2;
    const CROSSHAIR = 3;
    const WAITARROW = 4;
    const SIZENWSE  = 5;
    const SIZENESW  = 6;
    const SIZEWE    = 7;
    const SIZENS    = 8;
    const SIZEALL   = 9;
    const NO        = 10;
    const HAND      = 11;

    /**
     * Create a system cursor.
     * @param  int        $id one of the `SDL_Cursor::*` constants.
     * @return SDL_Cursor
     */
    public static function CreateSystem(int $id):SDL_Cursor {
        return new self(
            '',
            0,
            0,
            0,
            0,
            0,
        );
    }

    public function __construct(
        public string $data,
        public int $mask,
        public int $w,
        public int $h,
        public int $x,
        public int $y,
    ) {
    }

    /**
     * Frees a cursor created with `SDL_CreateCursor()`.
     * @return void
     */
    public function Free():void {
    }

    /**
     * @return void
     */
    public function Set():void {
    }

    public function __toString(): string {
        return '';
    }
}


/**
 * Create a cursor, using the specified bitmap data and mask (in MSB format).
 * 
 * The cursor width must be a multiple of 8 bits.
 * 
 * The cursor is created in black and white according to the following:
 * 
 * | data | mask | resulting pixel on screen                 |
 * |------|------|-------------------------------------------|
 * | 0    | 1    | White                                     |
 * | 1    | 1    | Black                                     |
 * | 0    | 0    | Transparent                               |
 * | 1    | 0    | Inverted color if possible, black if not. |
 * 
 * @param  string          $data
 * @param  string          $mask
 * @param  int             $w
 * @param  int             $h
 * @param  int             $hot_x
 * @param  int             $hot_y
 * @return null|SDL_Cursor
 */
function SDL_CreateCursor(
    string $data,
    string $mask,
    int $w,
    int $h,
    int $hot_x,
    int $hot_y
): null|SDL_Cursor {
    return null;
}

/**
 * Create a system cursor.
 * @param  int        $id one of the `SDL_Cursor::*` constants.
 * @return SDL_Cursor
 */
function SDL_CreateSystemCursor(int $id):SDL_Cursor {
    return new self(
        '',
        0,
        0,
        0,
        0,
        0,
    );
}

/**
 * Create a color cursor.
 * @param  SDL_Surface     $surface
 * @param  int             $x
 * @param  int             $y
 * @return null|SDL_Cursor
 */
function SDL_CreateColorCursor(
    SDL_Surface $surface,
    int $x,
    int $y,
): null|SDL_Cursor {
    return null;
}

/**
 * Frees a cursor created with `SDL_CreateCursor()`.
 * @param  SDL_Cursor $cursor
 * @return void
 */
function SDL_FreeCursor(SDL_Cursor $cursor):void {
}

/**
 * Set the active cursor.
 * @param  SDL_Cursor $cursor
 * @return void
 */
function SDL_SetCursor(
    SDL_Cursor $cursor,
):void {
}

/**
 * Return the active cursor.
 * @return SDL_Cursor
 */
function SDL_GetCursor():SDL_Cursor {
    return new SDL_Cursor('', 0, 0, 0, 0, 0);
}


/**
 * Return the default cursor.
 * @return SDL_Cursor
 */
function SDL_GetDefaultCursor():SDL_Cursor {
    return new SDL_Cursor('', 0, 0, 0, 0, 0);
}

/**
 * Toggle whether or not the cursor is shown.
 * 
 * @param  bool $toggle toggle 1 to show the cursor, 0 to hide it, -1 to query the current state.
 * @return bool `true` if the cursor is shown, or `false` if the cursor is hidden.
 */
function SDL_ShowCursor(bool $toggle):bool {
    return true;
}

/**
 * Get the window which currently has mouse focus.
 * @return SDL_Window
 */
function SDL_GetMouseFocus():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Retrieve the current state of the mouse.
 * 
 * The current button state is returned as a button bitmask, which can be tested using the `SDL_BUTTON(X)` macros (check the `C` documentation), and x and y are set to the mouse cursor position relative to the focus window for the currently selected mouse. 
 * You can pass `NULL` for either x or y.
 * @param  null|int $x
 * @param  null|int $y
 * @return int
 */
function SDL_GetMouseState(
    null|int &$x = null,
    null|int &$y = null,
):int {
    return 0;
}

/**
 * Retrieve the relative state of the mouse.
 * 
 * The current button state is returned as a button bitmask, which can be tested using the `SDL_BUTTON(X)` macros (cehck the `C` documentation), and x and y are set to the mouse deltas since the last call to SDL_GetRelativeMouseState().
 * @param  null|int $x
 * @param  null|int $y
 * @return int
 */
function SDL_GetRelativeMouseState(
    null|int &$x = null,
    null|int &$y = null,
):int {
    return 0;
}

/**
 * Moves the mouse to the given position within the window.
 * @param  SDL_Window $window The window to move the mouse into, or NULL for the current mouse focus.
 * @param  int        $x      The x coordinate within the window.
 * @param  int        $y      The y coordinate within the window.
 * @return void
 */
function SDL_WarpMouseInWindow(
    SDL_Window $window,
    int $x,
    int $y
):void {
}

/**
 * Set relative mouse mode.
 * 
 * While the mouse is in relative mode, the cursor is hidden, and the driver will try to report continuous motion in the current window. 
 * Only relative motion events will be delivered, the mouse position will not change.
 * 
 * This function will flush any pending mouse motion.
 * 
 * @param  bool $enabled Whether or not to enable relative mode.
 * @return int  0 on success, or -1 if relative mode is not supported.
 */
function SDL_SetRelativeMouseMode(bool $enabled):int {
    return 0;
}

/**
 * Query whether relative mouse mode is enabled.
 * @return bool
 */
function SDL_GetRelativeMouseMode():bool {
    return true;
}