<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
if (version_compare(phpversion("sdl"), "2.0.0-dev", '<')) die("skip: SDL extension >= 2.0.0 required");

$wind = new SDL_Window("Foo window 1", 100, 50, 350, 300, SDL_Window::SHOWN|SDL_Window::RESIZABLE);
$surf = $wind->GetSurface();

echo "Surface:"; var_dump($surf);
echo "Title:"; var_dump($wind->GetTitle());

echo "\nPowered by PHP ".phpversion().", SDL extension ".phpversion("sdl").", SDL2 library\n";

$color = SDL_MapRGB($surf->format, 0xef, 0xff, 0x87);
for ($t=12 ; $t ; $t--) {
	$rect = new SDL_Rect((13-$t)*15,10,10,10);

	if (!($t&3)) {
		$wind->SetTitle("Will be closed in ".($t/4)."\"");
	}
	
	$surf->FillRect($rect, $color);
	$wind->UpdateSurface();

	usleep(250000);
}
echo "Done\n";
