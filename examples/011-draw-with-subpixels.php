<?php

declare(strict_types=1);

require 'bootstrap.php';

const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;
const SQUARE = WINDOW_WIDTH / 2 - 20;

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow("Drawing lines on screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);

$image = SDL_LoadBMP(__DIR__."/spaceship.bmp");
if ($image === null) {
	exit('Unable to load image');
}

$texture = SDL_CreateTextureFromSurface($renderer, $image);
$drect = $image->clip_rect;
$drect->y = 500;
$dfrect = new SDL_FRect($drect->x, $drect->y, $drect->w, $drect->h);

// Draw lines
function line($iteration, $renderer)
{
    $x1 = 40.0;
    $y1 = 40.0 + $iteration;
    $x2 = SQUARE;
    $y2 = SQUARE - $iteration;

    SDL_RenderDrawLineF($renderer, $x1, $y1, $x2, $y2);
}

// Draw rects
function rect($iteration, $renderer)
{
    $x1 = SQUARE + 20 + $iteration/2;
    $y1 = SQUARE + $iteration/2 + 20;
    $w = SQUARE - 10 - $iteration;
    $h = SQUARE - 10 - $iteration;
    $rect1 = new SDL_FRect($x1, $y1, $w, $h);
    $rect2 = new SDL_FRect($x1 + 50, $y1 + 50, $w - 100 , $h - 100);
    SDL_RenderDrawRectF($renderer, $rect1);
    SDL_RenderFillRectF($renderer, $rect2);
}

// Draw points
function points($iteration, $renderer)
{
    for ($x = SQUARE + 80; $x < WINDOW_WIDTH - 60; $x++) {
        $y = sin($x*6/SQUARE + $iteration/10) * 120 + 250;
        SDL_RenderDrawPointF($renderer, (float) $x, $y);
    }
}

// Draw sprites
function sprites($iteration, $renderer, $destRect, $destFRect, $texture)
{
    $destFRect->x = $iteration;
    $destRect->x = (int) $destFRect->x + 100;
    if (SDL_RenderCopyEx($renderer, $texture, null, $destRect, $iteration, null, SDL_FLIP_NONE) != 0) {
        echo SDL_GetError(), PHP_EOL;
    }
    if (SDL_RenderCopyExF($renderer, $texture, null, $destFRect, $iteration, null, SDL_FLIP_NONE) != 0) {
        echo SDL_GetError(), PHP_EOL;
    }

    $destRect2 = clone $destRect;
    $destFRect2 = clone $destFRect;
    $destRect2->y += 100;
    $destFRect2->y += 100;
    if (SDL_RenderCopy($renderer, $texture, null, $destRect2) != 0) {
        echo SDL_GetError(), PHP_EOL;
    }
    if (SDL_RenderCopyF($renderer, $texture, null, $destFRect2) != 0) {
        echo SDL_GetError(), PHP_EOL;
    }
}

function getIncrement($i, $increment)
{
    if ($i > SQUARE) {
        return -0.20;
    }

    if ($i < 20.0) {
        return 0.20;
    }

    return $increment;
}

// Wait for quit event
$event = new SDL_Event;
$i = .0;
$increment = 0.20;

while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_QUIT) {
        break;
    }
    // Clear screen
    SDL_SetRenderDrawColor($renderer, 47, 79, 79, 255);
    SDL_RenderClear($renderer);

    SDL_SetRenderDrawColor($renderer, 230, 230, 230, 255);
    $increment = getIncrement($i, $increment);
    $i += $increment;
    line($i, $renderer);
    rect($i, $renderer);
    points($i, $renderer);
    sprites($i, $renderer, $drect, $dfrect, $texture);

    SDL_RenderPresent($renderer);
    SDL_Delay(5);
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
