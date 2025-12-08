<?php
class SDL_BlitInfo {
    public function __construct(
        public int $a,
        public int $b,
        public int $colorkey,
        public int $dst,
        public SDL_PixelFormat $dst_fmt,
        public int $dst_h,
        public int $dst_pitch,
        public int $dst_skip,
        public int $dst_w,
        public int $flags,
        public int $g,
        public int $r,
        public int $src,
        public SDL_PixelFormat $src_fmt,
        public int $src_h,
        public int $src_pitch,
        public int $src_skip,
        public int $src_w,
        public int $table,
    ) {
    }
}
// row 1452