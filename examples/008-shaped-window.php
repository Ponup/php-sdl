<?php

const WINDOW_WIDTH = 640;
const WINDOW_HEIGHT = 640;

require 'bootstrap.php';

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateShapedWindow("Drawing points on screen", 10, 10, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, 0);

$surface = SDL_LoadBMP("p01_shape32alpha.bmp");
if ($surface === null) {
    exit('Unable to load image');
}
$texture = SDL_CreateTextureFromSurface($renderer, $surface);

$mode = new SDL_WindowShapeMode(SDL_WindowShapeMode::BinarizeAlpha, 255);
SDL_SetWindowShape($window, $surface, $mode);

// Clear screen
SDL_SetRenderDrawColor($renderer, 100, 0, 0, 0);
SDL_RenderClear($renderer);
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
$quit = false;
while(!$quit) {
	while(SDL_PollEvent($event)) {
		if($event->type == SDL_QUIT) $quit = true;
		if($event->type == SDL_MOUSEBUTTONDOWN) $quit = true;
	}

    SDL_Delay(20);
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();

