<?php
class SDL_DisplayMode implements Stringable {
    public function __construct(
        public int $format,
        public int $w,
        public int $h,
        public int $refresh_rate,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1856