<?php

require 'bootstrap.php';

$window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);

SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);

SDL_RenderClear($renderer);

SDL_SetRenderDrawColor($renderer, 0, 0, 255, 255);

$rect = new SDL_Rect(50, 50, 50, 50);
SDL_RenderFillRect($renderer, $rect);

SDL_RenderPresent($renderer);

SDL_Delay(5000);

SDL_DestroyWindow($window);
SDL_Quit();

