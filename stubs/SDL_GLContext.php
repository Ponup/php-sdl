<?php
class SDL_GLContext implements Stringable {
    public function __construct(
        public SDL_Window $window,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1764