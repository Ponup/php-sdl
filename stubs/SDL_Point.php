<?php
class SDL_Point implements Stringable {
    public function __construct(
        public int $x,
        public int $y
    ) {
    }
    public function __toString(): string {
        return '';
    }
}
// row 1271