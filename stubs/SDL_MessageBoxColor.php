<?php
class SDL_MessageBoxColor implements Stringable {
    const BACKGROUND        = 0;
    const TEXT              = 1;
    const BUTTON_BORDER     = 2;
    const BUTTON_BACKGROUND = 3;
    const BUTTON_SELECTED   = 4;
    const MAX               = 5;

    public function __construct(
        public int $r,
        public int $g,
        public int $b,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1114