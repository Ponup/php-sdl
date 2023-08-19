<?php
class SDL_WindowShapeMode implements Stringable {
    /** The default mode, a binarized alpha cutoff of 1. */
    const Default = 0;
    
    /** A binarized alpha cutoff with a given integer value. */
    const BinarizeAlpha = 1;

    /** A binarized alpha cutoff with a given integer value, but with the opposite comparison. */
    const ReverseBinarizeAlpha = 2;

    /** A color key is applied. */
    const ColorKey = 3;

    public function __construct(
        private int $mode,
        private mixed $param,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1248