<?php

declare(strict_types=1);

require 'bootstrap.php';

$window = SDL_CreateWindow('Primitive drawing example', SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_SOFTWARE);
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
SDL_RenderSetLogicalSize($renderer, 640, 480);

SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
SDL_RenderClear($renderer);

$rect = new SDL_Rect(50, 50, 50, 50);
SDL_SetRenderDrawColor($renderer, 0, 0, 255, 255);
SDL_RenderFillRect($renderer, $rect);

$rect = new SDL_Rect(150, 150, 50, 50);
SDL_SetRenderDrawColor($renderer, 0, 0, 0, 255);
SDL_RenderDrawRect($renderer, $rect);

SDL_RenderPresent($renderer);

$quit = false;
$event = new SDL_Event;
while(!$quit) {
	SDL_PollEvent($event);
	SDL_Delay(30);

	while(SDL_PollEvent($event)) {
		if($event->type == SDL_QUIT) $quit = true;
	}
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();

