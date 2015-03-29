<?php

SDL_GetVersion( $version );

printf( 'Powered by PHP %s, SDL extension %s, SDL2 library %s' . PHP_EOL,
	phpversion(), phpversion( 'sdl' ), implode( '.', $version ) );


