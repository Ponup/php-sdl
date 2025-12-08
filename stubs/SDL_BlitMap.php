<?php
class SDL_BlitMap {
    public function __construct(
        public SDL_blit $blit,
        public mixed $data,
        public SDL_Surface $dst,
        public int $dst_palette_version,
        public int $identity,
        public SDL_BlitInfo $info,
        public int $src_palette_version,
    ) {
    }
}
// row 1475