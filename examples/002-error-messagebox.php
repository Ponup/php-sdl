<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);

SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 'Error example', 'An error has occurred (just kidding)', null);

SDL_Quit();

