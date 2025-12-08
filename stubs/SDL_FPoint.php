<?php
class SDL_FPoint implements Stringable {
    public function __construct(
        public float $x,
        public float $y
    ) {
    }
    public function __toString(): string {
        return '';
    }
}
// row 1309