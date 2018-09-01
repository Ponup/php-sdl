<?php

require 'bootstrap.php';

$window = SDL_CreateWindow('Primitive drawing example', SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_SOFTWARE);

SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
SDL_RenderClear($renderer);

$rect = new SDL_Rect(50, 50, 50, 50);
SDL_SetRenderDrawColor($renderer, 0, 0, 255, 255);
SDL_RenderFillRect($renderer, $rect);

SDL_RenderPresent($renderer);

$iniTime = time();
$event = new SDL_Event;
while(true) {
	SDL_PollEvent($event);
	SDL_Delay(30);

	// Stop after 5 seconds
	if(time() - $iniTime > 5) break;
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();

