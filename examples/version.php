<?php

require 'bootstrap.php';

if (SDL_GetVersion($version)) {
    printf('Powered by PHP %s, SDL extension %s, SDL2 library %s' . PHP_EOL, phpversion(), phpversion('sdl'), implode('.', $version));
} else {
    trigger_error('SDL version could not be retrieved', E_USER_NOTICE);
}

var_dump(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);


