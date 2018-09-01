<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);
$window = SDL_CreateWindow('Message box example', 300, 100, 1024, 800, SDL_WINDOW_SHOWN);

SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 'Error example', 'An error has occurred (just kidding)', $window);

SDL_DestroyWindow($window);
SDL_Quit();

