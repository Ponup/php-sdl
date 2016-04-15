<?php

require 'bootstrap.php';

SDL_Init( SDL_INIT_EVERYTHING  );
$window = SDL_CreateWindow("Message box", 300, 100, 1024, 800, SDL_WINDOW_SHOWN);

SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing file", "File is missing. Please reinstall the program.", $window );

SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

SDL_DestroyWindow($window);
SDL_Quit();

