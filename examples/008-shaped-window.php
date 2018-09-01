<?php

const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

require 'bootstrap.php';

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateShapedWindow("Drawing points on screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);


//$surface = SDL_LoadBMP("p01_shape24.bmp");
$surface = SDL_LoadBMP("p01_shape32alpha.bmp");
if ($surface === null) {
    exit('Unable to load image');
}
$texture = SDL_CreateTextureFromSurface($renderer, $surface);

$mode = new SDL_WindowShapeMode(SDL_WindowShapeMode::BinarizeAlpha, 255);
//$color = new SDL_Color(0,0,0,255);
//$mode = new SDL_WindowShapeMode(SDL_WindowShapeMode::ColorKey, $color);
SDL_SetWindowShape($window, $surface, $mode);

// Clear screen
SDL_SetRenderDrawColor($renderer, 100, 0, 0, 0);
SDL_RenderClear($renderer);
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
while(true) {
    if(SDL_PollEvent($event) && $event->type == SDL_QUIT) {
        break;
	}
    SDL_Delay(20);
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();

