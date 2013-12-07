<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
if (version_compare(phpversion("sdl"), "2.0.0-dev", '<')) die("skip: SDL extension >= 2.0.0 required");

$wind = new SDL_Window("Foo window 1", 100, 50, 350, 300, SDL_Window::SHOWN|SDL_Window::RESIZABLE);
$surf = $wind->GetSurface();

echo "Surface:"; var_dump($surf);
echo "Title:"; var_dump($wind->GetTitle());

echo "\nPowered by PHP ".phpversion().", SDL extension ".phpversion("sdl").", SDL2 library\n";

$time = 4;
$step = 4;
$color = SDL_MapRGB($surf->format, 0xff, 0x87, 0xef);

for ($t=$time*$step ; $t ; $t--) {
	$rects[$time*$step-$t] = new SDL_Rect(($time*$step+1-$t)*15,10,10,10);
}
$surf->FillRects($rects, count($rects), $color);

$color = SDL_MapRGB($surf->format, 0xef, 0xff, 0x87);
for ($t=$time*$step ; $t ; $t--) {

	if (!($t%$step)) {
		$wind->SetTitle("Will be closed in ".($t/$step)."\"");
	}
	
	$surf->FillRect($rects[$time*$step-$t], $color);
	$wind->UpdateSurface();

	usleep(1000000/$step);
}
echo "Done\n";
