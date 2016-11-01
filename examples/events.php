<?php

require 'bootstrap.php';

$quit = false;
$x = 288;
$y = 208;

// init SDL

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow("SDL2 Keyboard/Mouse events", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_ALLOW_HIGHDPI);
$renderer = SDL_CreateRenderer($window, -1, 0);

$image = SDL_LoadBMP("spaceship.bmp");
if ($image === null) {
    exit('Unable to load image');
}
$texture = SDL_CreateTextureFromSurface($renderer, $image);
$drect = $image->clip_rect;
SDL_FreeSurface($image);

SDL_SetRenderDrawColor($renderer, 255, 0, 255, 255);

$event = new SDL_Event;
while (!$quit) {
    SDL_WaitEvent($event);
    switch ($event->type) {
        case SDL_QUIT:
            $quit = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_RenderClear($renderer);
            $destRect = new SDL_Rect;
            $destRect->x = $event->motion->x;
            $destRect->y = $event->motion->y;
            $destRect->w = $drect->w;
            $destRect->h = $drect->h;
            if (SDL_RenderCopy($renderer, $texture, NULL, $destRect) != 0) {
                echo SDL_GetError(), PHP_EOL;
            }
            SDL_RenderPresent($renderer);

            break;
    }

    SDL_Delay(5);
}

// cleanup SDL
SDL_DestroyTexture($texture);
SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();

