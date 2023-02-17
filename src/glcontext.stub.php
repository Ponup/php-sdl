<?php

class SDL_GLContext implements Stringable {
    public function __construct(
        public SDL_Window $window,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

/**
 * Return true if an OpenGL extension is supported for the current context.
 * @param  string $ext
 * @return bool
 */
function SDL_GL_ExtensionSupported(string $ext):bool {
    return true;
}

/**
 * Set an OpenGL window attribute before window creation.
 * @param  int $attr
 * @param  int $value
 * @return int
 */
function SDL_GL_SetAttribute(
    int $attr,
    int $value,
):int {
    return 0;
}

/**
 * Get the actual value for an attribute from the current context.
 * @param  int $attr
 * @param  int &$value
 * @return int
 */
function SDL_GL_GetAttribute(
    int $attr,
    int &$value,
):int {
    return 0;
}

/**
 * Create an OpenGL context for use with an OpenGL window, and make it current.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_GL_CreateContext(SDL_Window $window):void {
}

/**
 * Delete an OpenGL context.
 * @param  SDL_GLContext $context
 * @return void
 */
function SDL_GL_DeleteContext(
    SDL_GLContext $context
):void {
}

/**
 * Set up an OpenGL context for rendering into an OpenGL window.
 * 
 * The context must have been created with a compatible window.
 * @param  SDL_Window    $window
 * @param  SDL_GLContext $context
 * @return null|int
 */
function SDL_GL_MakeCurrent(
    SDL_Window $window,
    SDL_GLContext $context,
):null|int {
    return null;
}

/**
 * Get the currently active OpenGL window.
 * @return SDL_Window
 */
function SDL_GL_GetCurrentWindow():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Get the currently active OpenGL context.
 * @return SDL_GLContext
 */
function SDL_GL_GetCurrentContext():SDL_GLContext {
    /** @var SDL_GLContext $o */
    return $o;
}

/**
 * Get the size of a window's underlying drawable (for use with glViewport).
 * 
 * This may differ from SDL_GetWindowSize if we're rendering to a high-DPI drawable, i.e. the window was created with SDL_WINDOW_ALLOW_HIGHDPI on a platform with high-DPI support (Apple calls this "Retina"), and not disabled by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
 * @param  SDL_Window $window Window from which the drawable size should be queried
 * @param  int        $w      Pointer to variable for storing the width, may be NULL
 * @param  int        $h      Pointer to variable for storing the height, may be NULL
 * @return void
 */
function SDL_GL_GetDrawableSize(
    SDL_Window $window,
    int &$w,
    int &$h,
):void {
}

/**
 * Swap the OpenGL buffers for a window, if double-buffering is supported.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_GL_SwapWindow(
    SDL_Window $window
):void {
}

/**
 * Set the swap interval for the current OpenGL context.
 * @param  int $interval 0 for immediate updates, 1 for updates synchronized with the vertical retrace. If the system supports it, you may specify -1 to allow late swaps to happen immediately instead of waiting for the next retrace.
 * @return int 0 on success, or -1 if setting the swap interval is not supported.
 */
function SDL_GL_SetSwapInterval(int $interval):int {
    return 0;
}

/**
 * Get the swap interval for the current OpenGL context.
 * @return int 0 if there is no vertical retrace synchronization, 1 if the buffer swap is synchronized with the vertical retrace, and -1 if late swaps happen immediately instead of waiting for the next retrace. If the system can't determine the swap interval, or there isn't a valid current context, this will return 0 as a safe default.
 */
function SDL_GL_GetSwapInterval():int {
    return 0;
}