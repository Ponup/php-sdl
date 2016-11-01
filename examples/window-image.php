<?php

require 'bootstrap.php';

SDL_Init(SDL_INIT_EVERYTHING);

// Create the window
$wind = new SDL_Window("Foo window 1", 100, 50, 400, 300, SDL_Window::SHOWN | SDL_Window::RESIZABLE);
$surf = $wind->GetSurface();

// Load the PHP Logo from a stream
$logo = SDL_LoadBMP('spaceship.bmp');

SDL_GetVersion($version);

printf("Window:  $wind\n");
printf("Surface: %dx%d\n", $surf->clip_rect->w, $surf->clip_rect->h);
printf("Title:   %s\n", $wind->GetTitle());
printf("Logo:    %dx%d\n", $logo->clip_rect->w, $logo->clip_rect->h);
printf("\nPowered by PHP %s, SDL extension %s, SDL2 library %s\n", phpversion(), phpversion("sdl"), implode('.', $version));

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

$wind->UpdateSurface();

$cursor = SDL_Cursor::CreateSystem(SDL_Cursor::WAITARROW);
$cursor->Set();

$color = SDL_MapRGB($surf->format, 0xef, 0xff, 0x87);
for ($t = $time * $step; $t; $t--) {

    if (!($t % $step)) {
        $wind->SetTitle("Will be closed in " . ($t / $step) . "\"");
    }

    // Display 1 rect in ~red
    $surf->FillRect($rects[$time * $step - $t], $color);
    $wind->UpdateSurfaceRects(array($rects[$time * $step - $t]));

    usleep(1000000 / $step);
}
echo "Done\n";

