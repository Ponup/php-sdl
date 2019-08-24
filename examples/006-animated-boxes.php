<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);

$window = SDL_CreateWindow('Progress bar animation', SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN | SDL_Window::RESIZABLE);
$surf = SDL_GetWindowSurface($window);

$time = 4;
$step = 5;
$color = SDL_MapRGB($surf->format, 0xff, 0x87, 0xef);

// Compute rects
$rects = [];
for ($t = $time * $step; $t; $t--) {
    $rects[$time * $step - $t] = new SDL_Rect(35 + ($time * $step + 1 - $t) * 15, 20, 10, 10);
}
// Display rects in ~white
$surf->FillRects($rects, count($rects), $color);

SDL_UpdateWindowSurface($window);

$cursor = SDL_Cursor::CreateSystem(SDL_Cursor::HAND);
$cursor->Set();

$event = new SDL_Event;

$color = SDL_MapRGB($surf->format, 0xef, 0xff, 0x87);
for($t = $time * $step; $t; $t--) {

    if (!($t % $step)) {
		$secondsLeft = $t / $step;
		SDL_SetWindowTitle($window, "Will be closed in $secondsLeft seconds");
    }

    // Display 1 rect in ~red
    $surf->FillRect($rects[$time * $step - $t], $color);
	SDL_UpdateWindowSurfaceRects($window, array($rects[$time * $step - $t]));

    usleep(1000000 / $step);

	while(SDL_PollEvent($event)) {
		if($event->type == SDL_QUIT) break;
	}
}

SDL_DestroyWindow($window);

