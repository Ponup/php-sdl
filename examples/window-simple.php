<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);

// Create the window
$wind = new SDL_Window("Foo window 1", 100, 50, 400, 300, SDL_Window::SHOWN | SDL_Window::RESIZABLE);
SDL_Delay(4000);
