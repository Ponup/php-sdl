<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
if (version_compare(phpversion("sdl"), "2.0.0-dev", '<')) die("skip: SDL extension >= 2.0.0 required");

SDL_GetVersion($version);

$msg = sprintf("Powered by PHP %s, SDL extension %s, SDL2 library %s",
	phpversion(), phpversion("sdl"), implode('.', $version));
echo "\n$msg\n\n";

SDL_ShowSimpleMessageBox(
	SDL_MESSAGEBOX_INFORMATION,
	"SDL_ShowSimpleMessageBox() example",
	$msg
);

$buttons = array(
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::RETURNKEY_DEFAULT, 1, "Yes"),
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::ESCAPEKEY_DEFAULT, 0, "No"),
);
$colors = array(
	SDL_MessageBoxColor::BACKGROUND        => new SDL_MessageBoxColor(0,0,0),
	SDL_MessageBoxColor::TEXT              => new SDL_MessageBoxColor(255,255,255),
	SDL_MessageBoxColor::BUTTON_BORDER     => new SDL_MessageBoxColor(255,0,0),
	SDL_MessageBoxColor::BUTTON_BACKGROUND => new SDL_MessageBoxColor(0,255,0),
	SDL_MessageBoxColor::BUTTON_SELECTED   => new SDL_MessageBoxColor(0,0,255),
);
$d = new SDL_MessageBoxData(
	SDL_MessageBoxData::INFORMATION,
	"SDL_ShowMessageBox() example",
	$msg, 
	$buttons,
	$colors
);
$d->Show($id);
printf("You press \"%s\"\n", ($id ? "Yes" : "No"));

