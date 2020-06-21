<?php

declare(strict_types=1);

require 'bootstrap.php';

$quit = false;

SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
$joystick = SDL_JoystickOpen(0);
$joystickFound = !is_null($joystick);
if (!$joystickFound) {
	trigger_error('A joystick could not be found.', E_USER_NOTICE);
}

$window = SDL_CreateWindow("Input handling example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, -1, 0);

$image = SDL_LoadBMP("spaceship.bmp");
if ($image === null) {
	exit('Unable to load image');
}
$windowSurface = SDL_GetWindowSurface($window);
$color = SDL_MapRGB($windowSurface->format, 0xff, 0xff, 0xff);
SDL_SetColorKey($image, true, $color);

$texture = SDL_CreateTextureFromSurface($renderer, $image);
$drect = $image->clip_rect;
SDL_FreeSurface($image);

SDL_SetRenderDrawColor($renderer, 255, 0, 255, 255);
SDL_RenderClear($renderer);
SDL_RenderPresent($renderer);
$rotCenter = new SDL_Point(10, 10);
$event = new SDL_Event;
$destRect = new SDL_Rect;
$destRect->x = $x = 100;
$destRect->y = $y = 100;
$destRect->w = 64;
$destRect->h = 64;
$update = true;
while (!$quit) {
	if ($joystickFound) {
		$xJoystickMotion = SDL_JoystickGetAxis($joystick, 0);
		if ($xJoystickMotion !== 0) {
			$x += ceil($xJoystickMotion / 32767) * 5;
			$update = true;
		}
		$yJoystickMotion = SDL_JoystickGetAxis($joystick, 1);
		if ($yJoystickMotion !== 0) {
			$y += ceil($yJoystickMotion / 32767) * 5;
			$update = true;
		}
	}

	while (SDL_PollEvent($event)) {
		switch ($event->type) {
			case SDL_QUIT:
				$quit = true;
				break;
			case SDL_MOUSEMOTION:
				$x = $event->motion->x;
				$y = $event->motion->y;
				$update = true;
				break;
			case SDL_JOYAXISMOTION:
				break;
		}
	}

	if ($update) {
		SDL_RenderClear($renderer);
		$destRect->x = $x;
		$destRect->y = $y;

		if (SDL_RenderCopyEx($renderer, $texture, NULL, $destRect, 90, $rotCenter, SDL_FLIP_NONE) != 0) {
			echo SDL_GetError(), PHP_EOL;
		}
		SDL_RenderPresent($renderer);
		$update = false;
	}

	SDL_Delay(25);
}

if ($joystickFound) {
	SDL_JoystickClose($joystick);
}

SDL_DestroyTexture($texture);
SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
