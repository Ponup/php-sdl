<?php
class SDL_blit {
    public function __construct(
        public SDL_Surface &$src,
        public SDL_Rect &$srcrect,
        public SDL_Surface &$dst,
        public SDL_Rect &$dstrect,
    ) {
    }
}
// row 1462