<?php

require 'bootstrap.php';

if(SDL_GetVersion($version)) {
    printf('Powered by PHP %s, SDL extension %s and SDL2 library %s.' . PHP_EOL, phpversion(), phpversion('sdl'), implode('.', $version));
} else {
    trigger_error('SDL version could not be retrieved', E_USER_NOTICE);
}

printf('SDL version components are %d (SDL_MAJOR_VERSION), %d (SDL_MINOR_VERSION) and %d (SDL_PATCHLEVEL).', SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

