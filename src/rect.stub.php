<?php

/** @generate-class-entries */

function SDL_PointInRect(SDL_Point $p, SDL_Rect $r): bool {}
function SDL_RectEmpty(SDL_Rect $r): bool {}
function SDL_RectEquals(SDL_Rect $a, SDL_Rect $b): bool {}
function SDL_HasIntersection(SDL_Rect $A, SDL_Rect $B): bool {}
function SDL_IntersectRect(SDL_Rect $A, SDL_Rect $B, ?SDL_Rect &$result): bool {}
function SDL_UnionRect(SDL_Rect $A, SDL_Rect $B, ?SDL_Rect &$result): void {}
function SDL_EnclosePoints(SDL_Point $points, int $count, SDL_Rect $clip, ?SDL_Rect &$result): bool {}
function SDL_IntersectRectAndLine(SDL_Rect $rect, int &$X1, int &$Y1, int &$X2, int &$Y2): bool {}

function SDL_FRectEmpty(SDL_FRect $r): bool {}
function SDL_HasIntersectionF(SDL_FRect $A, SDL_FRect $B): bool {}
function SDL_IntersectFRect(SDL_FRect $A, SDL_FRect $B, ?SDL_FRect &$result): bool {}

class SDL_Point
{
    public int $x;
    public int $y;

    public function __construct(int $x, int $y) {}
    public function __toString(): string {}
}

class SDL_Rect
{
    public int $x;
    public int $y;
    public int $w;
    public int $h;

    public function __construct(int $x, int $y, int $w, int $h) {}
    public function __toString(): string {}

    /** @alias SDL_RectEmpty */
    public function Empty(): bool {}
    /** @alias SDL_RectEquals */
    public function Equal(SDL_Rect $b): bool {}
    /** @alias SDL_HasIntersection */
    public function HasIntersection(SDL_Rect $B): bool {}
    /** @alias SDL_IntersectRect */
    public function Intersect(SDL_Rect $B, ?SDL_Rect &$result): bool {}
    /** @alias SDL_UnionRect */
    public function Union(SDL_Rect $B, ?SDL_Rect &$result): void {}
    /** @alias SDL_IntersectRectAndLine */
    public function IntersectLine(int &$X1, int &$Y1, int &$X2, int &$Y2): bool {}
}

class SDL_FPoint
{
    public float $x;
    public float $y;

    public function __construct(float $x, float $y) {}
    public function __toString(): string {}
}

class SDL_FRect
{
    public float $x;
    public float $y;
    public float $w;
    public float $h;

    public function __construct(float $x, float $y, float $w, float $h) {}
    public function __toString(): string {}

    /** @alias SDL_FRectEmpty */
    public function Empty(): bool {}
    /** @alias SDL_HasIntersectionF */
    public function HasIntersection(SDL_FRect $B): bool {}
    /** @alias SDL_IntersectFRect */
    public function Intersect(SDL_FRect $B, ?SDL_FRect &$result): bool {}
}
