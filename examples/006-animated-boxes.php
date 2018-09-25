<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);

$window = SDL_CreateWindow('Progress bar animation', SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN | SDL_Window::RESIZABLE);
$surf = SDL_GetWindowSurface($window);

// Load the PHP Logo from a stream
$logo = SDL_LoadBMP('spaceship.bmp');
if($logo == null) {
	exit('Unable to load image');
}

$time = 4;
$step = 5;
$color = SDL_MapRGB($surf->format, 0xff, 0x87, 0xef);

// Compute rects
$rects = [];
for ($t = $time * $step; $t; $t--) {
    $rects[$time * $step - $t] = new SDL_Rect(35 + ($time * $step + 1 - $t) * 15, $logo->h + 20, 10, 10);
}
// Display rects in ~white
$surf->FillRects($rects, count($rects), $color);

// Display the logo
$drect = $logo->clip_rect;
$drect->x = ($surf->clip_rect->w - $logo->w ) / 2;
$drect->y = 10;
$logo->Blit(NULL, $surf, $drect);

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

