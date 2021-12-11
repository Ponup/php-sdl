<?php declare(strict_types=1);

require 'bootstrap.php';

initSDLOrExit();

if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 'Error example', 'An error has occurred (just kidding)', null) !== 0) {
	printSdlErrorAndExit();
}

SDL_Quit();
