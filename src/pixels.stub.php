<?php
class SDL_Color implements Stringable {
    public function __construct(
        public int $r,
        public int $g,
        public int $b,
        public int $a,
    ) {
    }

    public function __toString(): string {
        return '';
    }
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

class SDL_PixelFormat implements Stringable {
    public function __construct(
        public int $format,
        public SDL_Palette $palette,
        public int $BitsPerPixel,
        public int $BytesPerPixel,
        public int $padding,
        public int $Rmask,
        public int $Gmask,
        public int $Bmask,
        public int $Amask,
        public int $Rloss,
        public int $Gloss,
        public int $Bloss,
        public int $Aloss,
        public int $Rshift,
        public int $Gshift,
        public int $Bshift,
        public int $Ashift,
        public int $refcount,
        public SDL_PixelFormat $next,
    ) {
    }

    public function GetRGB(
        int &$r,
        int &$g,
        int &$b,
    ): void {
    }

    public function GetRGBA(
        int &$r,
        int &$g,
        int &$b,
        int &$a,
    ): void {
    }

    public function __toString(): string {
        return '';
    }
}

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

class SDL_Palette implements Stringable {
    public function __construct(
        public int $ncolors,
    ) {
    }

    
    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|SDL_Color {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        SDL_Color $value
    ): null|false {
        return null;
    }

    public function __toString(): string {
        return '';
    }
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

class SDL_Pixels implements Stringable {
    public function __construct(
        public int $pitch,
        public int $h,
    ) {
    }

    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|int {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        int $value
    ): null|false {
        return null;
    }

    public function GetByte(
        int $x,
        int $y,
    ): false|int {
        return false;
    }

    public function SetByte(
        int $x,
        int $y,
        int $value,
    ): false|int {
        return false;
    }

    public function __toString(): string {
        return '';
    }
}