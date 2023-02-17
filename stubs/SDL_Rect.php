<?php
class SDL_Rect implements Stringable {
    public function __construct(
        public int $x = 0,
        public int $y = 0,
        public int $w = 0,
        public int $h = 0,
    ) {
    }

    
    public function Empty(): bool {
        return true;
    }
    
    public function HasIntersection(SDL_Rect $B): bool {
        return true;
    }
    
    public function Intersect(SDL_Rect $B, ?SDL_Rect &$result): bool {
        return true;
    }

    public function __toString(): string {
        return '';
    }
}
// row 1298