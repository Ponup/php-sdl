<?php

/**
 * Initialize SDL module.
 * @param  int $flag Check `SDL_INIT_*` constants
 * @return int
 */
function SDL_Init(int $flag):int {
    return 0;
}

/**
 * Create a window that can be shaped with the specified position, dimensions, and flags.
 * @param  string          $title The title of the window, in UTF-8 encoding.
 * @param  int             $x     The x position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int             $y     The y position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int             $w     The width of the window.
 * @param  int             $h     The height of the window.
 * @param  int             $flags The flags for the window, a mask of `SDL_WINDOW_BORDERLESS` with any of the following: `SDL_WINDOW_OPENGL`, `SDL_WINDOW_INPUT_GRABBED`, `SDL_WINDOW_HIDDEN`, `SDL_WINDOW_RESIZABLE`, ::SDL_WINDOW_MAXIMIZED,  `SDL_WINDOW_MINIMIZED`, `SDL_WINDOW_BORDERLESS` is always set, and `SDL_WINDOW_FULLSCREEN` is always unset.
 * @return null|SDL_Window The window created, or NULL if window creation failed. 
 */
function SDL_CreateWindow(
    string $title,
    int $x,
    int $y,
    int $w,
    int $h,
    int $flags
):null|SDL_Window {
    return null;
}

/**
 * Create a window that can be shaped with the specified position, dimensions, and flags.
 * @param  string        $title The title of the window, in UTF-8 encoding.
 * @param  int           $x     The x position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int           $y     The y position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int           $w     The width of the window.
 * @param  int           $h     The height of the window.
 * @param  int           $flags The flags for the window, a mask of `SDL_WINDOW_BORDERLESS` with any of the following: `SDL_WINDOW_OPENGL`, `SDL_WINDOW_INPUT_GRABBED`, `SDL_WINDOW_HIDDEN`, `SDL_WINDOW_RESIZABLE`, ::SDL_WINDOW_MAXIMIZED,  `SDL_WINDOW_MINIMIZED`, `SDL_WINDOW_BORDERLESS` is always set, and `SDL_WINDOW_FULLSCREEN` is always unset.
 * @return null|resource The window created, or NULL if window creation failed. 
 */
function SDL_CreateShapedWindow(
    string $title,
    int $x,
    int $y,
    int $w,
    int $h,
    int $flags
):mixed {
}

/**
 * 
 * @param  SDL_Window    $window The window where rendering is displayed.
 * @param  int           $index  The index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags.
 * @param  int           $flags  Check `SDL_RENDERER_*` constants.
 * @return null|resource A valid rendering context or NULL if there was an error.
 */
function SDL_CreateRenderer(
    SDL_Window $window,
    int $index,
    int $flags
):mixed {
}

/**
 * Create a texture from an existing surface.
 * 
 * The surface is not modified or freed by this function.
 * @param  resource      $renderer
 * @param  SDL_Surface   $surface
 * @return null|resource
 */
function SDL_CreateTextureFromSurface(
    mixed $renderer,
    SDL_Surface $surface,
):mixed {
}


const SDL_NONSHAPEABLE_WINDOW    = -1;
const SDL_INVALID_SHAPE_ARGUMENT = -2;
const SDL_WINDOW_LACKS_SHAPE     = -3;

/**
 * Set the shape and parameters of a shaped window.
 * @param  SDL_Window          $window     The shaped window whose parameters should be set.
 * @param  SDL_Surface         $shape      A surface encoding the desired shape for the window.
 * @param  SDL_WindowShapeMode $shape_mode The parameters to set for the shaped window.
 * @return int                 0 on success, `SDL_INVALID_SHAPE_ARGUMENT` on invalid an invalid shape argument, or `SDL_NONSHAPEABLE_WINDOW` if the `SDL_Window*` given does not reference a valid shaped window.
 */
function SDL_SetWindowShape(
    SDL_Window $window,
    SDL_Surface $shape,
    SDL_WindowShapeMode $shape_mode
):int {
    return 0;
}


/**
 * Set the color used for drawing operations (Rect, Line and Clear).
 * @param  resource $renderer The renderer for which drawing color should be set.
 * @param  int      $r        The red value used to draw on the rendering target.
 * @param  int      $g        The green value used to draw on the rendering target.
 * @param  int      $b        The blue value used to draw on the rendering target.
 * @param  int      $a        The alpha value used to draw on the rendering target, usually `SDL_ALPHA_OPAQUE` (255).
 * @return int      0 on success, or -1 on error.
 */
function SDL_SetRenderDrawColor(
    mixed $renderer,
    int $r,
    int $g,
    int $b,
    int $a,
):int {
    return 0;
}

/**
 * Clear the current rendering target with the drawing color.
 *
 * This function clears the entire rendering target, ignoring the viewport and the clip rectangle.
 * @param  resource $rederer
 * @return int
 */
function SDL_RenderClear(mixed $rederer):int {
    return 0;
}

/**
 * Update the screen with rendering performed.
 * @param  resource $rederer
 * @return int
 */
function SDL_RenderPresent(mixed $rederer):int {
    return 0;
}


/**
 * Polls for currently pending events.
 * @param null|resource If not NULL, the next event is removed from the queue and stored in that area.
 * @return int 1 if there are any pending events, or 0 if there are none available.
 */
function SDL_PollEvent(
    mixed $event
):int {
    return 0;
}

/**
 * 
 * @param  SDL_Event $event
 * @return int
 */
function SDL_WaitEvent(SDL_Event $event):int {
    return 0;
}

/**
 * Wait a specified number of milliseconds before returning.
 * @param  int  $ms
 * @return void
 */
function SDL_Delay(int $ms):void {
}

/**
 * Destroy a renderer.
 * @param  resource $renderer
 * @return void
 */
function SDL_DestroyRenderer(mixed $renderer):void {
}

/**
 * Destroy a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_DestroyWindow(SDL_Window $window):void {
}

/**
 * This function cleans up all initialized subsystems.
 * 
 * You should call it upon all exit conditions.
 * @return void
 */
function SDL_Quit() {
}

/**
 * Get the version of SDL that is linked against your program.
 *
 * If you are linking to SDL dynamically, then it is possible that the
 * current version will be different than the version you compiled against.
 * This function returns the current version, while SDL_VERSION() is a
 * macro that tells you what version you compiled with.
 * @param  array $version
 * @return void
 */
function SDL_GetVersion(array &$version):void {
}

/**
 * Create a simple modal message box.
 * @param  int             $flags   Check `SDL_MESSAGEBOX_*` constants.
 * @param  string          $title   UTF-8 title text.
 * @param  string          $message UTF-8 message text.
 * @param  null|SDL_Window $window  The parent window, or NULL for no parent.
 * @return bool
 */
function SDL_ShowSimpleMessageBox(
    int $flags,
    string $title,
    string $message,
    null|SDL_Window $window = null
):bool {
    return true;
}

/**
 * Draw a point on the current rendering target.
 * @param  resource $renderer The renderer which should draw a point.
 * @param  int      $x        The x coordinate of the point.
 * @param  int      $y        The y coordinate of the point.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawPoint(
    mixed $renderer,
    int $x,
    int $y,
) {
    return 0;
}

/**
 * Draw a point on the current rendering target.
 * @param  resource $renderer The renderer which should draw a point.
 * @param  int      $x        The x coordinate of the point.
 * @param  int      $y        The y coordinate of the point.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawPointF(
    mixed $renderer,
    int $x,
    int $y,
) {
    return 0;
}

function SDL_PointInRect(
    SDL_Point $p,
    SDL_Rect $r
): bool {
    return true;
}

/**
 * Returns true if the rectangle has no area.
 * @param  SDL_Rect $r
 * @return bool
 */
function SDL_RectEmpty(SDL_Rect $r): bool {
    return true;
}
/**
 * Returns true if the two rectangles are equal.
 * @param  SDL_Rect $a
 * @param  SDL_Rect $b
 * @return bool
 */
function SDL_RectEquals(
    SDL_Rect $a,
    SDL_Rect $b
): bool {
    return true;
}
/**
 * Determine whether two rectangles intersect.
 * @param  SDL_Rect $A
 * @param  SDL_Rect $B
 * @return bool     `true` if there is an intersection, `false`` otherwise.
 */
function SDL_HasIntersection(
    SDL_Rect $A,
    SDL_Rect $B
): bool {
    return true;
}
/**
 * Calculate the intersection of two rectangles.
 * @param  SDL_Rect      $A
 * @param  SDL_Rect      $B
 * @param  null|SDL_Rect $result
 * @return bool          `true` if there is an intersection, `false` otherwise.
 */
function SDL_IntersectRect(
    SDL_Rect $A,
    SDL_Rect $B,
    ?SDL_Rect &$result
): bool {
    return true;
}
/**
 * Calculate the union of two rectangles.
 * @param  SDL_Rect      $A
 * @param  SDL_Rect      $B
 * @param  null|SDL_Rect $result
 * @return void
 */
function SDL_UnionRect(SDL_Rect $A, SDL_Rect $B, ?SDL_Rect &$result): void {
}
/**
 * Calculate a minimal rectangle enclosing a set of points
 * @param  SDL_Point       $points
 * @param  int             $count
 * @param  SDL_Rect        $clip
 * @param  null|SDL_Rect   $result
 * @return null|false|bool `true` if any points were within the clipping rect
 */
function SDL_EnclosePoints(
    SDL_Point $points,
    int $count,
    SDL_Rect $clip,
    ?SDL_Rect &$result
): null|bool {
    return true;
}

/**
 * Calculate the intersection of a rectangle and line segment.
 * @param  SDL_Rect $rect
 * @param  int      $X1
 * @param  int      $Y1
 * @param  int      $X2
 * @param  int      $Y2
 * @return bool
 */
function SDL_IntersectRectAndLine(
    SDL_Rect $rect,
    int &$X1,
    int &$Y1,
    int &$X2,
    int &$Y2
): bool {
    return true;
}

function SDL_FRectEmpty(SDL_FRect $r): bool {
    return true;
}
function SDL_HasIntersectionF(SDL_FRect $A, SDL_FRect $B): bool {
    return true;
}
function SDL_IntersectFRect(SDL_FRect $A, SDL_FRect $B, ?SDL_FRect &$result): bool {
    return true;
}


/**
 * Fill a rectangle on the current rendering target with the drawing color.
 * @param  resource $renderer The renderer which should fill a rectangle.
 * @param  SDL_Rect $rect     A pointer to the destination rectangle, or NULL for the entire rendering target.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderFillRect(
    mixed $renderer,
    SDL_Rect $rect,
):int {
    return 0;
}


/**
 * Draw a rectangle on the current rendering target.
 * @param  resource $renderer The renderer which should draw a rectangle.
 * @param  SDL_Rect $rect     A pointer to the destination rectangle, or NULL to outline the entire rendering target.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawRect(
    mixed $renderer,
    SDL_Rect $rect,
):int {
    return 0;
}


/**
 * Fill a rectangle on the current rendering target with the drawing color.
 * @param  resource  $renderer The renderer which should fill a rectangle.
 * @param  SDL_FRect $rect     A pointer to the destination rectangle, or NULL for the entire rendering target.
 * @return int       0 on success, or -1 on error.
 */
function SDL_RenderFillRectF(
    mixed $renderer,
    SDL_FRect $rect,
):int {
    return 0;
}

/**
 * Draw a rectangle on the current rendering target.
 * @param  resource  $renderer The renderer which should draw a rectangle.
 * @param  SDL_FRect $rect     A pointer to the destination rectangle, or NULL to outline the entire rendering target.
 * @return int       0 on success, or -1 on error.
 */
function SDL_RenderDrawRectF(
    mixed $renderer,
    SDL_FRect $rect,
):int {
    return 0;
}


/**
 * Get the SDL surface associated with the window.
 * 
 * You may not combine this with 3D or the rendering API on this window.
 * @param  SDL_Window       $window
 * @return null|SDL_Surface The window's framebuffer surface, or NULL on error.
 *                                 A new surface will be created with the optimal format for the window,
 *                                 if necessary. This surface will be freed when the window is destroyed.
 */
function SDL_GetWindowSurface(SDL_Window $window):null|SDL_Surface {
    return null;
}

/**
 * Destroy a window.
 * @param  SDL_Surface $src
 * @return void
 */
function SDL_FreeSurface(SDL_Surface $src):void {
}
/**
 * Performs a fast fill of the given rectangle with `$color`.
 *
 * If `$rect` is `NULL`, the whole surface will be filled with  `$color`.
 *
 * The color should be a pixel of the format used by the surface, and can be generated by the `SDL_MapRGB()` function.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $rect
 * @param  int         $color
 * @return void        0 on success, or -1 on error.
 */
function SDL_FillRect(
    SDL_Surface $src,
    SDL_Rect $rect,
    int $color
):int {
    return 0;
}

/**
 * 
 * @param  SDL_Surface     $src
 * @param  array<SDL_Rect> $rect
 * @param  int             $count
 * @param  int             $color
 * @return int
 */
function SDL_FillRects(
    SDL_Surface $src,
    array $rect,
    int $count,
    int $color
):int {
    return 0;
}

/**
 * Evaluates to true if the surface needs to be locked before access.
 * define SDL_MUSTLOCK(S) (((S)->flags & SDL_RLEACCEL) != 0)
 * @param  SDL_Surface $src
 * @return bool
 */
function SDL_MUSTLOCK(SDL_Surface $src):bool {
    return true;
}

/**
 * Sets up a surface for directly accessing the pixels.
 *
 * Between calls to `SDL_LockSurface()` / `SDL_UnlockSurface()`, you can write
 * to and read from `$surface->pixels`, using the pixel format stored in
 * `$surface->format`.  Once you are done accessing the surface, you should
 * use `SDL_UnlockSurface()` to release it.
 *
 * Not all surfaces require locking.  If `SDL_MUSTLOCK($surface)` evaluates
 * to 0, then you can read and write to the surface at any time, and the
 * pixel format of the surface will not change.
 *
 * No operating system or library calls should be made between lock/unlock
 * pairs, as critical system locks may be held during this time.
 * @param  SDL_Surface $src
 * @return int         0, or -1 if the surface couldn't be locked.
 */
function SDL_LockSurface(SDL_Surface $src):int {
    return 0;
}

function SDL_UnlockSurface(SDL_Surface $src):void {
}

/**
 * Performs a fast blit from the source surface to the destination surface.
 *
 *  This assumes that the source and destination rectangles are
 *  the same size.  If either `$srcrect` or `$dstrect` are `NULL`, the entire
 *  surface (`$src` or `$dst`) is copied.  The final blit rectangles are saved
 *  in `$srcrect` and `$dstrect` after all clipping is performed.
 *
 *  The blit function should not be called on a locked surface.
 * @param  SDL_Surface   $src
 * @param  SDL_Rect      $srcrect
 * @param  SDL_Surface   $dst
 * @param  SDL_Rect|null $dstrect
 * @return void          returns 0, otherwise it returns -1.
 */
function SDL_UpperBlit(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect = null,
):void {
}

/**
 * This is a semi-private blit function and it performs low-level surface blitting only.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_LowerBlit(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect,
):void {
}

/**
 * This is the public scaled blit function, `SDL_BlitScaled()`, and it performs rectangle validation and clipping before passing it to `SDL_LowerBlitScaled()`.
 * @param  SDL_Surface   $src
 * @param  SDL_Rect      $srcrect
 * @param  SDL_Surface   $dst
 * @param  SDL_Rect|null $dstrect
 * @return void
 */
function SDL_UpperBlitScaled(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect = null
):void {
}

/**
 * This is a semi-private blit function and it performs low-level surface scaled blitting only.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_LowerBlitScaled(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect,
):void {
}

/**
 * Perform a fast, low quality, stretch blit between two surfaces of the same pixel format.
 * 
 * This function uses a static buffer, and is not thread-safe.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_SoftStretch(
    SDL_Surface $src,
    SDL_rect $srcrect,
    SDL_Surface $dst,
    SDL_rect $dstrect
):void {
}

/**
 * Save a surface to a seekable SDL data stream (memory or file).
 *
 * If `$freedst` is non-zero, the stream will be closed after being written.
 * @param  SDL_Surface $src
 * @param  SDL_RWops   $dst
 * @param  int         $freedst
 * @return int         0 if successful or -1 if there was an error.
 */
function SDL_SaveBMP_RW(
    SDL_Surface $src,
    SDL_RWops &$dst,
    int $freedst
):int {
    return 0;
}

/**
 * stream are "partially" supported (only when `PHP_STREAM_AS_STDIO`).
 * @param  SDL_Surface $src
 * @param  string      $path
 * @return int
 */
function SDL_SaveBMP(
    SDL_Surface $src,
    string $path
):int {
    return 0;
}

/**
 * Sets the RLE acceleration hint for a surface.
 * 
 * If RLE is enabled, colorkey and alpha blending blits are much faster, but the surface must be locked before directly accessing the pixels.
 * @param  SDL_Surface $src
 * @param  int         $flag
 * @return void        0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceRLE(
    SDL_Surface $src,
    int $flag
):void {
}

/**
 * Sets the color key (transparent pixel) in a blittable surface.
 * 
 * You can pass SDL_RLEACCEL to enable RLE accelerated blits.
 * @param  SDL_Surface $src  The surface to update. 
 * @param  int         $flag Non-zero to enable colorkey and 0 to disable colorkey.
 * @param  int         $key  key The transparent pixel in the native surface format.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetColorKey(
    SDL_Surface $src,
    int $flag,
    int $key = 0
):int {
    return 0;
}

/**
 * Gets the color key (transparent pixel) in a blittable surface.
 * @param  SDL_Surface $src The surface to update. 
 * @param  int         $key A pointer filled in with the transparent pixel in the native surface format.
 * @return int         0 on success, or -1 if the surface is not valid or colorkey is not enabled.
 */
function SDL_GetColorKey(
    SDL_Surface $src,
    int &$key
):int {
    return 0;
}

/**
 * Set an additional color value used in blit operations.
 * @param  SDL_Surface $src The surface to update.
 * @param  int         $r   The red color value multiplied into blit operations.
 * @param  int         $g   The green color value multiplied into blit operations.
 * @param  int         $b   The blue color value multiplied into blit operations.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceColorMod(
    SDL_Surface $src,
    int $r,
    int $g,
    int $b
):int {
    return 0;
}

/**
 * Get the additional color value used in blit operations.
 * @param  SDL_Surface $src The surface to query.
 * @param  int         $r   A pointer filled in with the current red color value.
 * @param  int         $g   A pointer filled in with the current green color value.
 * @param  int         $b   A pointer filled in with the current blue color value.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_GetSurfaceColorMod(
    SDL_Surface $src,
    int &$r,
    int &$g,
    int &$b
):int {
    return 0;
}

/**
 * Set an additional alpha value used in blit operations.
 * @param  SDL_Surface $src   The surface to update.
 * @param  int         $alpha The alpha value multiplied into blit operations.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceAlphaMod(
    SDL_Surface $src,
    int $alpha
):int {
    return 0;
}

/**
 * Get the additional alpha value used in blit operations.
 * @param  SDL_Surface $src The surface to query.
 * @param  int         $a   A pointer filled in with the current alpha value.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_GetSurfaceAlphaMod(
    SDL_Surface $src,
    int &$a
):int {
    return 0;
}

/**
 * Set the blend mode used for blit operations.
 * @param  SDL_Surface $src       The surface to update.
 * @param  int         $blendmode ::SDL_BlendMode to use for blit blending.
 * @return int         0 on success, or -1 if the parameters are not valid.
 */
function SDL_SetSurfaceBlendMode(
    SDL_Surface $src,
    int $blendmode,
):int {
    return 0;
}

/**
 * Set the blend mode used for blit operations.
 * @param  SDL_Surface $src       The surface to update.
 * @param  int         $blendmode ::SDL_BlendMode to use for blit blending.
 * @return int         0 on success, or -1 if the parameters are not valid.
 */
function SDL_GetSurfaceBlendMode(
    SDL_Surface $src,
    int $blendmode,
):int {
    return 0;
}

/**
 * Sets the clipping rectangle for the destination surface in a blit.
 *
 * If the clip rectangle is NULL, clipping will be disabled.
 *
 * If the clip rectangle doesn't intersect the surface, the function will
 * return SDL_FALSE and blits will be completely clipped.  Otherwise the
 * function returns SDL_TRUE and blits to the surface will be clipped to
 * the intersection of the surface area and the clipping rectangle.
 *
 * Note that blits are automatically clipped to the edges of the source
 * and destination surfaces.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $cliprect
 * @return void
 */
function SDL_SetClipRect(
    SDL_Surface $src,
    SDL_Rect $cliprect,
):void {
}

/**
 * Gets the clipping rectangle for the destination surface in a blit.
 *
 * `$rect` must be a pointer to a valid rectangle which will be filled with the correct values.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $rect
 * @return void
 */
function SDL_GetClipRect(
    SDL_Surface $src,
    SDL_Rect &$rect
):void {
}

/**
 * Creates a new surface of the specified format, and then copies and maps
 * the given surface to it so the blit of the converted surface will be as
 * fast as possible.  If this function fails, it returns `NULL`.
 *
 * The `$flags` parameter is passed to `SDL_CreateRGBSurface()` and has those
 * semantics.  You can also pass `::SDL_RLEACCEL` in the flags parameter and
 * SDL will try to RLE accelerate colorkey and alpha blits in the resulting
 * surface.
 * @param  SDL_Surface     $src
 * @param  SDL_PixelFormat $format
 * @param  int             $flag
 * @return void
 */
function SDL_ConvertSurface(
    SDL_Surface $src,
    SDL_PixelFormat $format,
    int $flag
):void {
}

/**
 * 
 * @param  SDL_Surface $src
 * @param  int         $format
 * @param  int         $flags
 * @return void
 */
function SDL_ConvertSurfaceFormat(
    SDL_Surface $src,
    int $format,
    int $flags = 0
):void {
}

/**
 * Load a surface from a seekable SDL data stream (memory or file).
 *
 * If `$freesrc` is non-zero, the stream will be closed after being read.
 *
 * The new surface should be freed with `SDL_FreeSurface()`.
 * @param  SDL_RWops        $src
 * @param  int              $freesrc
 * @return null|SDL_Surface the new surface, or NULL if there was an error.
 */
function SDL_LoadBMP_RW(SDL_RWops $src, int $freesrc):null|SDL_Surface {
    return null;
}

/**
 * Load a surface from a file.
 * 
 * stream are supported.
 * @param  string|resource  $file
 * @return null|SDL_Surface
 */
function SDL_LoadBMP(string $file):null|SDL_Surface {
    return null;
}


/**
 * Copy a number of rectangles on the window surface to the screen.
 * @param  SDL_Window $window
 * @param  array      $rects
 * @param  int        $numrect
 * @return int        0 on success, or -1 on error.
 */
function SDL_UpdateWindowSurfaceRects(
    SDL_Window $window,
    array $rects,
    int $numrect = 0
):int {
    return 0;
}

/**
 * Copy the window surface to the screen.
 * @param  SDL_Window $window
 * @return int        0 on success, or -1 on error.
 */
function SDL_UpdateWindowSurface(SDL_Window $window):int {
    return 0;
}

/**
 * Set the title of a window, in UTF-8 format.
 * @param  SDL_Window $window
 * @param  string     $title
 * @return void
 */
function SDL_SetWindowTitle(
    SDL_Window $window,
    string $title,
):void {
}

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

/**
 * 
 * @param  mixed          $renderer
 * @param  mixed          $texture
 * @param  null|SDL_Rect  $srcrect
 * @param  null|SDL_Rect  $dstrect
 * @param  float          $angle
 * @param  null|SDL_Point $center
 * @param  int            $flip
 * @return int
 */
function SDL_RenderCopyEx(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_Rect $dstrect = null,
    float $angle,
    null|SDL_Point $center = null,
    int $flip,
):int {
    return 0;
}

/**
 * 
 * @param  mixed           $renderer
 * @param  mixed           $texture
 * @param  null|SDL_Rect   $srcrect
 * @param  null|SDL_FRect  $dstrect
 * @param  float           $angle
 * @param  null|SDL_FPoint $center
 * @param  int             $flip
 * @return int
 */
function SDL_RenderCopyExF(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect|SDL_FRect $srcrect = null,
    null|SDL_FRect $dstrect = null,
    float $angle,
    null|SDL_FPoint $center = null,
    int $flip,
):int {
    return 0;
}

/**
 * Destroy a texture.
 * @param  resource $texture
 * @return void
 */
function SDL_DestroyTexture(mixed $texture):void {
}

/**
 * Draw a line between two points.
 * @param  resource $renderer
 * @param  int      $x1
 * @param  int      $y1
 * @param  int      $x2
 * @param  int      $y2
 * @return int
 */
function SDL_RenderDrawLine(
    mixed $renderer,
    int $x1,
    int $y1,
    int $x2,
    int $y2,
):int {
    return 0;
}

/**
 * Draw a line between two points.
 * @param  resource $renderer
 * @param  float    $x1
 * @param  float    $y1
 * @param  float    $x2
 * @param  float    $y2
 * @return int
 */
function SDL_RenderDrawLineF(
    mixed $renderer,
    float $x1,
    float $y1,
    float $x2,
    float $y2,
):int {
    return 0;
}

/**
 * 
 * @param  resource      $renderer
 * @param  resource      $texture
 * @param  null|SDL_Rect $srcrect
 * @param  null|SDL_Rect $dstrect
 * @return int
 */
function SDL_RenderCopy(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_Rect $dstrect = null,
):int {
    return 0;
}

/**
 * 
 * @param  resource       $renderer
 * @param  resource       $texture
 * @param  null|SDL_Rect  $srcrect
 * @param  null|SDL_FRect $dstrect
 * @return int
 */
function SDL_RenderCopyF(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_FRect $dstrect = null,
):int {
    return 0;
}

/**
 * This function returns the number of CPU cores available.
 * @return int
 */
function SDL_GetCPUCount():int {
    return 0;
}

/**
 * This function returns the L1 cache line size of the CPU
 *
 * This is useful for determining multi-threaded structure padding or SIMD prefetch sizes.
 * @return int
 */
function SDL_GetCPUCacheLineSize():int {
    return 0;
}

/**
 * This function returns true if the CPU has the RDTSC instruction.
 * @return int
 */
function SDL_HasRDTSC():int {
    return 0;
}

/**
 * This function returns true if the CPU has AltiVec features.
 * @return int
 */
function SDL_HasAltiVec():int {
    return 0;
}

/**
 * This function returns true if the CPU has MMX features.
 * @return int
 */
function SDL_HasMMX():int {
    return 0;
}

/**
 * This function returns true if the CPU has 3DNow! features.
 * @return int
 */
function SDL_Has3DNow():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE features.
 * @return int
 */
function SDL_HasSSE():int {
    return 0;
}

/**
 * This function returns true if the CPU has HasSSE2 features.
 * @return int
 */
function SDL_HasSSE2():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE3 features.
 * @return int
 */
function SDL_HasSSE3():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.1 features.
 * @return int
 */
function SDL_HasSSE41():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.2 features.
 * @return int
 */
function SDL_HasSSE42():int {
    return 0;
}

/**
 * This function returns the amount of RAM configured in the system, in MB.
 * @return int
 */
function SDL_GetSystemRAM():int {
    return 0;
}

/**
 * 
 * @param  string $error
 * @return int    unconditionally returns -1.
 */
function SDL_SetError(string $error):int {
    return 0;
}

/**
 * 
 * @return string
 */
function SDL_GetError():string {
    return '';
}


/**
 * 
 * @return string
 */
function SDL_ClearError():string {
    return '';
}


/**
 * Get the path where the application resides.
 *
 * Get the "base path". This is the directory where the application was run from, which is probably the installation directory, and may or may not be the process's current working directory.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call SDL_free() on the pointer when you are done with it, or it will be a memory leak. This is not necessarily a fast call, though, so you should call this once near startup and save the string if you need it.
 *
 * Some platforms can't determine the application's path, and on other platforms, this might be meaningless. In such cases, this function will return NULL.
 * 
 * @param  string            $org
 * @param  string            $app
 * @return null|false|string String of base dir in UTF-8 encoding, or NULL on error.
 */
function SDL_GetPrefPath(
    string $org,
    string $app,
):null|false|string {
    return null;
}

/**
 * Get the user-and-app-specific path where files can be written.
 *
 * Get the "pref dir". This is meant to be where users can write personal files (preferences and save games, etc) that are specific to your application. This directory is unique per user, per application.
 *
 * This function will decide the appropriate location in the native filesystem, create the directory if necessary, and return a string of the absolute path to the directory in UTF-8 encoding.
 *
 * On Windows, the string might look like: "C:\\Users\\bob\\AppData\\Roaming\\My Company\\My Program Name\\"
 *
 * On Linux, the string might look like: "/home/bob/.local/share/My Program Name/"
 *
 * On Mac OS X, the string might look like: "/Users/bob/Library/Application Support/My Program Name/"
 *
 * (etc.)
 *
 * You specify the name of your organization (if it's not a real organization, your name or an Internet domain you own might do) and the name of your application. These should be untranslated proper names.
 *
 * Both the org and app strings may become part of a directory name, so please follow these rules:
 *
 *    - Try to use the same org string (including case-sensitivity) for
 *      all your applications that use this function.
 *    - Always use a unique app string for each one, and make sure it never
 *      changes for an app once you've decided on it.
 *    - Unicode characters are legal, as long as it's UTF-8 encoded, but...
 *    - ...only use letters, numbers, and spaces. Avoid punctuation like
 *      "Game Name 2: Bad Guy's Revenge!" ... "Game Name 2" is sufficient.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call SDL_free() on the pointer when you are done with it, or it will be a memory leak. This is not necessarily a fast call, though, so you should call this once near startup and save the string if you need it.
 *
 * You should assume the path returned by this function is the only safe place to write files (and that SDL_GetBasePath(), while it might be writable, or even the parent of the returned path, aren't where you should be writing things).
 *
 * Some platforms can't determine the pref path, and on other platforms, this might be meaningless. In such cases, this function will return NULL.
 * @return null|string UTF-8 string of user dir in platform-dependent notation. NULL if there's a problem (creating directory failed, etc).
 */
function SDL_GetBasePath():null|string {
    return null;
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


/**
 * Create a modal message box.
 * 
 * This function should be called on the thread that created the parent window, or on the main thread if the messagebox has no parent. 
 * It will block execution of that thread until the user clicks a button or closes the messagebox.
 * @param  SDL_MessageBoxData $messageboxdata messageboxdata The SDL_MessageBoxData structure with title, text, etc.
 * @param  int                $buttonid       buttonid The pointer to which user id of hit button should be copied.
 * @return int                -1 on error, otherwise 0 and buttonid contains user id of button hit or -1 if dialog was closed.
 */
function SDL_ShowMessageBox(SDL_MessageBoxData $messageboxdata, int &$buttonid):int {
    return 0;
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


/**
 * Create a mutex, initialized unlocked.
 * @return SDL_mutex
 */
function SDL_CreateMutex():SDL_mutex {
    return new SDL_mutex;
}

/**
 * Lock the mutex.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_LockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Try to lock the mutex
 * @param  SDL_mutex $mutex
 * @return int       0, SDL_MUTEX_TIMEDOUT, or -1 on error
 */
function SDL_TryLockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Unlock the mutex.
 * 
 * WARNING: It is an error to unlock a mutex that has not been locked by the current thread, and doing so results in undefined behavior.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_UnlockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Destroy a mutex.
 * @param  SDL_mutex $mutex
 * @return void
 */
function SDL_DestroyMutex(SDL_mutex $mutex):void {
}

/**
 * Create a semaphore, initialized with value, returns NULL on failure.
 * @param  int          $value
 * @return null|SDL_sem
 */
function SDL_CreateSemaphore(int $value): null|SDL_sem {
    return null;
}

/**
 * This function suspends the calling thread until the semaphore pointed to by `$sem` has a positive count.
 * It then atomically decreases the semaphore count.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemWait(SDL_sem $sem):int {
    return 0;
}


/**
 * Non-blocking variant of SDL_SemWait().
 * @param  SDL_sem $sem
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait would block, and -1 on error.
 */
function SDL_SemTryWait(SDL_sem $sem):int {
    return 0;
}

/**
 * Atomically increases the semaphore's count (not blocking).
 * @param  SDL_sem $sem
 * @return int     0, or -1 on error.
 */
function SDL_SemPost(SDL_sem $sem):int {
    return 0;
}

/**
 * Returns the current count of the semaphore.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemValue(SDL_sem $sem):int {
    return 0;
}

/**
 * Variant of SDL_SemWait() with a timeout in milliseconds.
 * 
 * On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_sem $sem
 * @param  int     $ms
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait does not succeed in the allotted time, and -1 on error.
 */
function SDL_SemWaitTimeout(SDL_sem $sem, int $ms):int {
    return 0;
}

/**
 * Destroy a semaphore.
 * @param  SDL_sem $sem
 * @return void
 */
function SDL_DestroySemaphore(SDL_sem $sem):void {
}

/**
 * Create a condition variable.
 * 
 * Typical use of condition variables:
 *
 * Thread A:
 * ```c
 * SDL_LockMutex(lock);
 * while ( ! condition ) {
 *     SDL_CondWait(cond, lock);
 * }
 * SDL_UnlockMutex(lock);
 * ```
 *
 * Thread B:
 * ```c
 * SDL_LockMutex(lock);
 * ...
 * condition = true;
 * ...
 * SDL_CondSignal(cond);
 * SDL_UnlockMutex(lock);
 * ```
 *
 * There is some discussion whether to signal the condition variable
 * with the mutex locked or not.  There is some potential performance
 * benefit to unlocking first on some platforms, but there are some
 * potential race conditions depending on how your code is structured.
 * 
 * In general it's safer to signal the condition variable while the
 * mutex is locked.
 * @param  int      $value
 * @return SDL_cond
 */
function SDL_CreateCond(int $value):SDL_cond {
    return new SDL_cond(0);
}

/**
 * Wait on the condition variable, unlocking the provided mutex.
 * 
 * WARNING: The mutex must be locked before entering this function!
 * 
 * The mutex is re-locked once the condition variable is signaled.
 * @param  SDL_cond  $condition
 * @param  SDL_mutex $mutex
 * @return int       0 when it is signaled, or -1 on error.
 */
function SDL_CondWait(
    SDL_cond $condition,
    SDL_mutex $mutex
):int {
    return 0;
}

/**
 * Restart one of the threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondSignal(SDL_cond $cond):int {
    return 0;
}

/**
 * Restart all threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondBroadcast(SDL_cond $cond):int {
    return 0;
}

/**
 * Waits for at most \c ms milliseconds, and returns 0 if the condition variable is signaled, `SDL_MUTEX_TIMEDOUT` if the condition is not signaled in the allotted time, and -1 on error.
 * 
 * WARNING: On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_cond  $cond
 * @param  SDL_mutex $mutex
 * @param  int       $ms
 * @return int
 */
function SDL_CondWaitTimeout(SDL_cond $cond, SDL_mutex $mutex, int $ms):int {
    return 0;
}

/**
 * Destroy a condition variable.
 * @param  SDL_cond $cond
 * @return void
 */
function SDL_DestroyCond(SDL_cond $cond):void {
}

/**
 * Get the human readable name of a pixel format.
 * @param  int    $format
 * @return string
 */
function SDL_GetPixelFormatName(int $format):string {
    return '';
}

/**
 * Convert one of the enumerated pixel formats to a bpp and RGBA masks.
 * @param  int  $format
 * @param  int  $bpp
 * @param  int  $Rmask
 * @param  int  $Gmask
 * @param  int  $Bmask
 * @param  int  $Amask
 * @return bool `true`, or `false` if the conversion wasn't possible.
 */
function SDL_PixelFormatEnumToMasks(
    int $format,
    int &$bpp,
    int &$Rmask,
    int &$Gmask,
    int &$Bmask,
    int &$Amask
):bool {
    return true;
}

/**
 * Convert a bpp and RGBA masks to an enumerated pixel format.
 * @param  int  $format
 * @param  int  $bpp
 * @param  int  $Rmask
 * @param  int  $Gmask
 * @param  int  $Bmask
 * @param  int  $Amask
 * @return bool The pixel format, or `SDL_PIXELFORMAT_UNKNOWN` if the conversion wasn't possible.
 */
function SDL_MasksToPixelFormatEnum(
    int $format,
    int $bpp,
    int $Rmask,
    int $Gmask,
    int $Bmask,
    int $Amask
):bool {
    return true;
}

/**
 * Create an SDL_PixelFormat structure from a pixel format enum.
 * @param  int             $ncolors
 * @return SDL_PixelFormat
 */
function SDL_AllocFormat(int $ncolors):SDL_PixelFormat {
    /** @var SDL_PixelFormat $o*/
    $o = new stdClass;
    return $o;
}

/**
 * Free an SDL_PixelFormat structure.
 * @param  SDL_PixelFormat             $format
 * @return void
 */
function SDL_FreeFormat(SDL_PixelFormat $format):void {}

/**
 * Create a palette structure with the specified number of color entries.
 * 
 * The palette entries are initialized to white.
 * @param  int             $ncolors
 * @return ?SDL_Palette A new palette, or NULL if there wasn't enough memory.
 */
function SDL_AllocPalette(int $ncolors):SDL_Palette {
    /** @var SDL_Palette $o*/
    $o = new stdClass;
    return $o;
}

/**
 * Set the palette for a pixel format structure.
 * @param  SDL_PixelFormat $format
 * @param  SDL_Palette     $palette
 * @return int
 */
function SDL_SetPixelFormatPalette(
    SDL_PixelFormat $format,
    SDL_Palette $palette
):int {
    return 0;
}

/**
 * Set a range of colors in a palette.
 * @param  SDL_Palette $palette The palette to modify.
 * @param  array       $colors  An array of colors to copy into the palette.
 * @param  int         $first   The index of the first palette entry to modify.
 * @param  int         $ncolors The number of entries to modify.
 * @return int         0 on success, or -1 if not all of the colors could be set.
 */
function SDL_SetPaletteColors(
    SDL_Palette $palette,
    array $colors,
    int $first,
    int $ncolors
):int {
    return 0;
}

/**
 * Free a palette created with `SDL_AllocPalette()`.
 * @see SDL_AllocPalette()
 * @param SDL_Palette $palette
 * @return void
 */
function SDL_FreePalette(SDL_Palette $palette):void {}

/**
 * Maps an RGB triple to an opaque pixel value for a given pixel format.
 * @param  SDL_PixelFormat $pixelformat
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @return int
 */
function SDL_MapRGB(
    SDL_PixelFormat $pixelformat,
    int $r,
    int $g,
    int $b,
):int {
    return 0;
}

/**
 * Maps an RGBA quadruple to a pixel value for a given pixel format.
 * @param  SDL_PixelFormat $pixelformat
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @param  int             $a
 * @return int
 */
function SDL_MapRGBA(
    SDL_PixelFormat $pixelformat,
    int $r,
    int $g,
    int $b,
    int $a,
):int {
    return 0;
}

/**
 * Get the RGB components from a pixel of the specified format.
 * @param  int             $pixel
 * @param  SDL_PixelFormat $format
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @return void
 */
function SDL_GetRGB(
    int $pixel,
    SDL_PixelFormat $format,
    int &$r,
    int &$g,
    int &$b
):void {
}

/**
 * Get the RGBA components from a pixel of the specified format.
 * @param  int             $pixel
 * @param  SDL_PixelFormat $format
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @param  int             $a
 * @return void
 */
function SDL_GetRGBA(
    int $pixel,
    SDL_PixelFormat $format,
    int &$r,
    int &$g,
    int &$b,
    int &$a
):void {
}

/**
 * Calculate a 256 entry gamma ramp for a gamma value.
 * @param  float $gamma
 * @param  array $ramp
 * @return void
 */
function SDL_CalculateGammaRamp(float $gamma, array &$ramp):void {
}

/**
 * Gets the name of the platform.
 * @return string
 */
function SDL_GetPlatform():string {
    return '';
}

/**
 * Get the current power supply details.
 * @param  null|int $sec Seconds of battery life left. You can pass a `NULL` here if
 *                       you don't care. Will return -1 if we can't determine a
 *                       value, or we're not running on a battery.
 * @param  null|int $pct Percentage of battery life left, between 0 and 100. You can
 *                       pass a NULL here if you don't care. Will return -1 if we
 *                       can't determine a value, or we're not running on a battery.
 * @return string   The state of the battery (if any).
 */
function SDL_GetPowerInfo(null|int &$sec = null, null|int &$pct = null):string {
    return '';
}

/**
 * 
 * @param  resource      $renderer
 * @param  int           $format
 * @param  int           $access
 * @param  int           $w
 * @param  int           $h
 * @return null|resource
 */
function SDL_CreateTexture(
    mixed $renderer,
    int $format,
    int $access,
    int $w,
    int $h,
):mixed {
}

/**
 * 
 * @param  resource $renderer
 * @param  resource $texture
 * @return null|int
 */
function SDL_SetRenderTarget(
    mixed $renderer,
    mixed $texture,
):null|int {
    return null;
}

/**
 * 
 * @param  resource $renderer
 * @param  null|int $width
 * @param  null|int $height
 * @return resource
 */
function SDL_GetRendererOutputSize(
    mixed $renderer,
    null|int &$width = null,
    null|int &$height = null,
):mixed {
}


/**
 * 
 * @param  resource $texture
 * @param  null|int $format
 * @param  null|int $access
 * @param  null|int $width
 * @param  null|int $height
 * @return int
 */
function SDL_QueryTexture(
    mixed $texture,
    null|int &$format = null,
    null|int &$access = null,
    null|int &$width = null,
    null|int &$height = null,
):int {
    return 0;
}

/**
 * 
 * @return SDL_RWops
 */
function SDL_AllocRW():SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  string    $path
 * @param  string    $mode
 * @return SDL_RWops
 */
function SDL_RWFromFile(
    string $path,
    string $mode,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  string    $buf
 * @param  int       $size
 * @return SDL_RWops
 */
function SDL_RWFromConstMem(
    string $buf,
    int $size,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}


/**
 * 
 * @param  string    $buf
 * @param  int       $size
 * @return SDL_RWops
 */
function SDL_RWFromMem(
    string &$buf,
    int $size
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * PHP change: this function support PHP stream
 * SDL_RWFromFP will be used for real file
 * SDL_RWFromMem will be used for other stream
 * (inspired from gd extension)
 * @param  resource  $fp
 * @param  bool      $autoclose
 * @return SDL_RWops
 */
function SDL_RWFromFP(
    mixed $fp,
    bool $autoclose,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return void
 */
function SDL_FreeRW(SDL_RWops $area):void {
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWsize(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $offset
 * @param  int       $whence
 * @return int
 */
function SDL_RWseek(
    SDL_RWops $area,
    int $offset,
    int $whence
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWtell(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWclose(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  string    $string
 * @param  mixed     $buf
 * @param  int       $size
 * @param  int       $n
 * @return int
 */
function SDL_RWread(
    SDL_RWops $area,
    string &$buf,
    int $size = 1,
    int $n = 0
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  string    $buf
 * @param  int       $size
 * @param  int       $n
 * @return int
 */
function SDL_RWwrite(
    SDL_RWops $area,
    string $buf,
    int $size = 0,
    int $n = 0
): int {
    return 0;
}

/**
 * Read endian functions.
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadU8(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadLE16(SDL_RWops $area): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE16(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadLE32(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE32(SDL_RWops $area):int {
    return 0;
}

function SDL_ReadLE64(SDL_RWops $area): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE64(SDL_RWops $area):int {
    return 0;
}

/**
 * Write endian functions.
 * 
 * Write an item of native format to the specified endianness.
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteU8(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE16(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE16(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE32(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE32(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE64(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE64(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * This function cleans up all initialized subsystems. 
 * You should call it upon all exit conditions.
 * @param  int $flags
 * @return int
 */
function SDL_InitSubSystem(int $flags):int {
    return 0;
}

/**
 * This function cleans up specific SDL subsystems.
 * @param  int $flags
 * @return int
 */
function SDL_QuitSubSystem(int $flags):int {
    return 0;
}

/**
 * This function returns a mask of the specified subsystems which have previously been initialized.
 * 
 * If `$flags` is 0, it returns a mask of all initialized subsystems.
 * @param  int $flags
 * @return int
 */
function SDL_WasInit(int $flags):int {
    return 0;
}

/**
 * Copy a block of pixels of one format to another format.
 * @param  int        $width
 * @param  int        $height
 * @param  int        $src_format
 * @param  SDL_Pixels $src
 * @param  int        $src_pitch
 * @param  int        $dst_format
 * @param  SDL_Pixels $dst
 * @param  int        $dst_pitch
 * @return int        0 on success, or -1 if there was an error.
 */
function SDL_ConvertPixels(
    int $width,
    int $height,
    int $src_format,
    SDL_Pixels $src,
    int $src_pitch,
    int $dst_format,
    SDL_Pixels $dst,
    int $dst_pitch
):int {
    return 0;
}

/**
 * Get the code revision of SDL that is linked against your program.
 * 
 * Returns an arbitrary string (a hash value) uniquely identifying the
 * exact revision of the SDL library in use, and is only useful in comparing
 * against other revisions. It is NOT an incrementing number.
 * @return string
 */
function SDL_GetRevision():string {
    return '';
}

/**
 * Get the revision number of SDL that is linked against your program.
 * 
 * Returns a number uniquely identifying the exact revision of the SDL
 * library in use. It is an incrementing number based on commits to
 * hg.libsdl.org.
 * @return int
 */
function SDL_GetRevisionNumber():int {
    return 0;
}

/**
 * Macro to determine SDL version program was compiled against.
 * 
 * This macro fills in a SDL_version structure with the version of the
 * library you compiled against. This is determined by what header the
 * compiler uses. Note that if you dynamically linked the library, you might
 * have a slightly newer or older version at runtime. That version can be
 * determined with SDL_GetVersion(), which, unlike SDL_VERSION(),
 * is not a macro.
 * @param  array $version a SDL_version struct to initialize.
 * @return void
 */
function SDL_VERSION(array &$version):void {
}

/**
 * This macro turns the version numbers into a numeric value: (1,2,3) -> (1203)
 * 
 * This assumes that there will never be more than 100 patchlevels.
 * @param  int $x
 * @param  int $y
 * @param  int $z
 * @return int
 */
function SDL_VERSIONNUM(
    int $x,
    int $y,
    int $z
):int {
    return 0;
}

/**
 * This macro will evaluate to true if compiled with SDL at least X.Y.Z.
 * @param  int  $x
 * @param  int  $y
 * @param  int  $z
 * @return bool
 */
function SDL_VERSION_ATLEAST(
    int $x,
    int $y,
    int $z
):bool {
    return true;
}

/**
 * Get the number of video drivers compiled into SDL.
 * @return int
 */
function SDL_GetNumVideoDrivers():int {
    return 0;
}


/**
 * Get the name of a built in video driver.
 * 
 * The video drivers are presented in the order in which they are normally checked during initialization.
 * @param  int    $driverIndex
 * @return string
 */
function SDL_GetVideoDriver(int $driverIndex): string {
    return '';
}

/**
 * Initialize the video subsystem, optionally specifying a video driver.
 * 
 * This function initializes the video subsystem; setting up a connection
 * to the window manager, etc, and determines the available display modes
 * and pixel formats, but does not initialize a window or graphics mode.
 * @param  null|string $driver Initialize a specific driver by name, or NULL for the default video driver.
 * @return string      0 on success, -1 on error.
 */
function SDL_VideoInit(null|string $driver = null):int {
    return 0;
}

/**
 * Shuts down the video subsystem.
 * 
 * This function closes all windows, and restores the original video mode.
 * @return void
 */
function SDL_VideoQuit():void {
}

/**
 * Returns the name of the currently initialized video driver.
 * @return string The name of the current video driver or NULL if no driver has been initialized.
 */
function SDL_GetCurrentVideoDriver():string {
    return '';
}

/**
 * Returns the number of available video displays.
 * @return int
 */
function SDL_GetNumVideoDisplays():int {
    return 0;
}

/**
 * Get the name of a display in UTF-8 encoding.
 * @param  int    $displayIndex
 * @return string The name of a display, or NULL for an invalid display index.
 */
function SDL_GetDisplayName(int $displayIndex):string {
    return '';
}

/**
 * Get the desktop area represented by a display, with the primary display located at 0,0.
 * @param  int      $displayIndex
 * @param  SDL_Rect $rect
 * @return array    0 on success, or -1 if the index is out of range.
 */
function SDL_GetDisplayBounds(
    int $displayIndex,
    SDL_Rect &$rect
):array {
    return [];
}

/**
 * Returns the number of available display modes.
 * @param  int $displayIndex
 * @return int
 */
function SDL_GetNumDisplayModes(int $displayIndex):int {
    return 0;
}

/**
 * Fill in information about a specific display mode.
 * 
 * The display modes are sorted in this priority:
 *    - bits per pixel -> more colors to fewer colors
 *    - width -> largest to smallest
 *    - height -> largest to smallest
 *    - refresh rate -> highest to lowest
 * @param  int   $displayIndex
 * @param  int   $modeIndex
 * @return array
 */
function SDL_GetDisplayMode(
    int $displayIndex,
    int $modeIndex
):array {
    return [];
}

/**
 * Fill in information about the desktop display mode.
 * @param  int   $displayIndex
 * @return array
 */
function SDL_GetDesktopDisplayMode(int $displayIndex):array {
    return [];
}

/**
 * Fill in information about the current display mode.
 * @param  int   $displayIndex
 * @return array
 */
function SDL_GetCurrentDisplayMode(int $displayIndex):array {
    return[];
}

/**
 * Get the closest match to the requested display mode.
 * 
 * The available display modes are scanned, and `$closest` is filled in with the
 * closest mode matching the requested mode and returned.  The mode format and
 * refresh_rate default to the desktop mode if they are 0.  The modes are
 * scanned with size being first priority, format being second priority, and
 * finally checking the refresh_rate.  If all the available modes are too
 * small, then `NULL` is returned.
 * @param  int                  $displayIndex The index of display from which mode should be queried.
 * @param  SDL_DisplayMode      $mode         The desired display mode.
 * @param  SDL_DisplayMode      $closest      A pointer to a display mode to be filled in with the closest match of the available display modes.
 * @return null|SDL_DisplayMode The passed in value `$closest`, or `NULL` if no matching video mode was available.
 */
function SDL_GetClosestDisplayMode(
    int $displayIndex,
    SDL_DisplayMode $mode,
    SDL_DisplayMode $closest
):null|SDL_DisplayMode {
    return null;
}

/**
 * Returns whether the screensaver is currently enabled (default on).
 * @return bool
 */
function SDL_IsScreenSaverEnabled():bool {
    return true;
}

/**
 * Allow the screen to be blanked by a screensaver.
 * @return void
 */
function SDL_EnableScreenSaver():void {
}

/**
 * Prevent the screen from being blanked by a screensaver.
 * @return void
 */
function SDL_DisableScreenSaver():void {
}

/**
 * Get the display index associated with a window.
 * @param  SDL_Window $window
 * @return void       The display index of the display containing the center of the window, or -1 on error.
 */
function SDL_GetWindowDisplayIndex(SDL_Window $window):void {
}

/**
 * Set the display mode used when a fullscreen window is visible.
 * 
 * By default the window's dimensions and the desktop format and refresh rate
 *  are used.
 * @param  SDL_Window      $window The window for which the display mode should be set.
 * @param  SDL_DisplayMode $mode   The mode to use, or NULL for the default mode.
 * @return int             0 on success, or -1 if setting the display mode failed.
 */
function SDL_SetWindowDisplayMode(
    SDL_Window $window,
    SDL_DisplayMode $mode
):int {
    return 0;
}

/**
 * Fill in information about the display mode used when a fullscreen window is visible.
 * @param  SDL_Window      $window
 * @param  SDL_DisplayMode $mode
 * @return int
 */
function SDL_GetWindowDisplayMode(
    SDL_Window $window,
    SDL_DisplayMode $mode
):int {
    return 0;
}

/**
 * Get the pixel format associated with the window.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowPixelFormat(SDL_Window $window):int {
    return 0;
}

/**
 * Get the numeric ID of a window, for logging purposes.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowID(SDL_Window $window): int {
    return 0;
}

/**
 * Get the window flags.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowFlags(SDL_Window $window):int {
    return 0;
}

/**
 * Set the icon for a window.
 * @param  SDL_Window  $window The window for which the icon should be set.
 * @param  SDL_Surface $icon   The icon for the window.
 * @return void
 */
function SDL_SetWindowIcon(
    SDL_Window $window,
    SDL_Surface $icon
):void {
}

/**
 * Set the position of a window.
 * 
 * The window coordinate origin is the upper left of the display.
 * @param  SDL_Window $window The window to reposition.
 * @param  int        $x      The x coordinate of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int        $y      The y coordinate of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @return void
 */
function SDL_SetWindowPosition(
    SDL_Window $window,
    int $x,
    int $y
):void {
}

/**
 * 
 * @param  int $display
 * @return int
 */
function SDL_WINDOWPOS_CENTERED_DISPLAY(int $display):int {
    return 0;
}

/**
 * 
 * @param  int $display
 * @return int
 */
function SDL_WINDOWPOS_UNDEFINED_DISPLAY(int $display):int {
    return 0;
}

/**
 * Get the position of a window.
 * 
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the x position, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the y position, may be `NULL`.
 * @return void
 */
function SDL_GetWindowPosition(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the size of a window's client area.
 * You can't change the size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to resize.
 * @param  int        $x      The width of the window, must be >0.
 * @param  int        $y      The height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the minimum size of a window's client area.
 * 
 * You can't change the minimum size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to set a new minimum size.
 * @param  int        $x      The minimum width of the window, must be >0.
 * @param  int        $y      The minimum height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowMinimumSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the minimum size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the minimum width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the minimum height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowMinimumSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the maximum size of a window's client area.
 * 
 * You can't change the maximum size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to set a new maximum size.
 * @param  int        $x      The maximum width of the window, must be >0.
 * @param  int        $y      The maximum height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowMaximumSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the maximum size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the maximum width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the maximum height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowMaximumSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the border state of a window.
 * 
 * This will add or remove the window's `SDL_WINDOW_BORDERLESS` flag and
 * add or remove the border from the actual window. This is a no-op if the
 * window's border already matches the requested state.
 * 
 * You can't change the border state of a fullscreen window.
 * @param  SDL_Window $window   The window of which to change the border state.
 * @param  bool       $bordered SDL_FALSE to remove border, SDL_TRUE to add border.
 * @return void
 */
function SDL_SetWindowBordered(
    SDL_Window $window,
    bool $bordered
):void {
}

/**
 * Show a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_ShowWindow(SDL_Window $window):void {
}

/**
 * Hide a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_HideWindow(SDL_Window $window):void {
}

/**
 * Raise a window above other windows and set the input focus.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_RaiseWindow(SDL_Window $window):void {
}

/**
 * Make a window as large as possible.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_MaximizeWindow(SDL_Window $window):void {
}

/**
 * Minimize a window to an iconic representation.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_MinimizeWindow(SDL_Window $window):void {
}

/**
 * Restore the size and position of a minimized or maximized window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_RestoreWindow(SDL_Window $window):void {
}

/**
 * Set a window's fullscreen state.
 * @param  SDL_Window $window
 * @param  int        $flags
 * @return void       0 on success, or -1 if setting the display mode failed.
 */
function SDL_SetWindowFullscreen(
    SDL_Window $window,
    int $flags
):void {
}

/**
 * Set a window's input grab mode.
 * @param  SDL_Window $window  The window for which the input grab mode should be set.
 * @param  bool       $grabbed This is SDL_TRUE to grab input, and SDL_FALSE to release input.
 * @return void
 */
function SDL_SetWindowGrab(
    SDL_Window $window,
    bool $grabbed
):void {
}

/**
 * Get a window's input grab mode.
 * @param  SDL_Window $window
 * @return bool       This returns SDL_TRUE if input is grabbed, and SDL_FALSE otherwise.
 */
function SDL_GetWindowGrab(SDL_Window $window):bool {
    return true;
}

/**
 * Set the brightness (gamma correction) for a window.
 * @param  SDL_Window $window
 * @param  float      $brightness
 * @return int        0 on success, or -1 if setting the brightness isn't supported.
 */
function SDL_SetWindowBrightness(
    SDL_Window $window,
    float $brightness
):int {
    return 0;
}

/**
 * Get the brightness (gamma correction) for a window.
 * @param  SDL_Window $window
 * @return void       The last brightness value passed to `SDL_SetWindowBrightness()`.
 */
function SDL_GetWindowBrightness(SDL_Window $window):void {
}

/**
 * Get the gamma ramp for a window.
 * @param  SDL_Window $window The window from which the gamma ramp should be queried.
 * @param  array      $red    A pointer to a 256 element array of 16-bit quantities to hold the translation table for the red channel, or `NULL`.
 * @param  array      $green  A pointer to a 256 element array of 16-bit quantities to hold the translation table for the green channel, or `NULL`.
 * @param  array      $blue   A pointer to a 256 element array of 16-bit quantities to hold the translation table for the blue channel, or `NULL`.
 * @return int        0 on success, or -1 if gamma ramps are unsupported.
 */
function SDL_GetWindowGammaRamp(
    SDL_Window $window,
    array &$red,
    array &$green,
    array &$blue
):int {
    return 0;
}

/**
 * Get the title of a window, in UTF-8 format.
 * @param  SDL_Window $window
 * @return string
 */
function SDL_GetWindowTitle(SDL_Window $window):string {
    return '';
}

/**
 * Return whether the given window is a shaped window.
 * @param  SDL_Window $window The window to query for being shaped.
 * @return null|bool  `true` if the window is a window that can be shaped, `false` if the window is unshaped or `NULL`.
 */
function SDL_IsShapedWindow(SDL_Window $window):null|bool {
    return null;
}

/**
 * Get the shape parameters of a shaped window.
 * @param  SDL_Window          $window     The shaped window whose parameters should be retrieved.
 * @param  SDL_WindowShapeMode $shape_mode An empty shape-mode structure to fill, 
 *                                         or `NULL` to check whether the window has a shape.
 * @return int                 0 if the window has a shape and, provided shape_mode was not `NULL`, 
 *                                        shape_mode has been filled with the mode data, `SDL_NONSHAPEABLE_WINDOW` if 
 *                                        the `SDL_Window` given is not a shaped window, or `SDL_WINDOW_LACKS_SHAPE` if 
 *                                        the `SDL_Window*` given is a shapeable window currently lacking a shape.
 */
function SDL_GetShapedWindowMode(
    SDL_Window $window,
    SDL_WindowShapeMode &$shape_mode
):int {
    return 0;
}