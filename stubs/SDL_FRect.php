<?php
class SDL_FRect implements Stringable {
    public function __construct(
        public float $x = 0,
        public float $y = 0,
        public float $w = 0,
        public float $h = 0
    ) {
    }
    public function __toString(): string {
        return '';
    }

    public function Empty(): bool {
        return true;
    }
    
    public function HasIntersection(SDL_FRect $B): bool {
        return true;
    }

    public function Intersect(SDL_FRect $B, ?SDL_FRect &$result): bool {
        return true;
    }
}
// row 1334