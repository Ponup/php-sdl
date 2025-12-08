<?php
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
// row 1427