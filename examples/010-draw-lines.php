<?php

declare(strict_types=1);

require 'bootstrap.php';

const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow("Drawing lines on screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);

// Clear screen
SDL_SetRenderDrawColor($renderer, 100, 0, 0, 0);
SDL_RenderClear($renderer);


// Draw lines
SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
$offset = WINDOW_WIDTH;
$x1 = $y1 = 0;
for ($iteration = 0; $offset > 0; ++$iteration) {
    $side = $iteration % 4;
    $sign = $side < 2 ? 1 : -1;

    $x2 = $side % 2 ? $x1 + $sign * $offset : $x1;
    $y2 = $side % 2 ? $y1 : $y1 + $sign * $offset;

    SDL_RenderDrawLine($renderer, $x1, $y1, $x2, $y2);

    $x1 = $x2;
    $y1 = $y2;
    $offset -= 10;
}
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_QUIT) {
        break;
    }
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
