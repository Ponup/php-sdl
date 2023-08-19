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
// row 1348