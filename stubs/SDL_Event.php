<?php
class SDL_Event implements Stringable {
    public SDL_Window $window;

    public function __construct() {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1259