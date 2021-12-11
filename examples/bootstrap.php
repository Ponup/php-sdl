<?php declare(strict_types=1);

error_reporting(E_ALL);

if (!extension_loaded('sdl')) {
    fprintf(STDERR, "The sdl extension is not loaded. Make sure it is in the system and there is a line for it on the php.ini file (eg \"extension=sdl.so\")");
    exit(1);
}

function initSDLOrExit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) !== 0) {
		printSdlErrorAndExit();
	}
}

function printSdlErrorAndExit() {
	fprintf(STDERR, "ERROR: %s\n", SDL_GetError());
	exit(1);
}

