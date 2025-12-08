<?php
class SDL_sem implements Stringable {
    public function __construct(
        public int $value
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1781