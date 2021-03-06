<?php

declare(strict_types=1);

require 'bootstrap.php';

if (false === SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, 'Message box title', 'This is an example message box')) {
	fprintf(STDERR, 'Unable to show simple message box');
	return;
}

$buttons = [
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::RETURNKEY_DEFAULT, 1, 'Yes'),
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::ESCAPEKEY_DEFAULT, 0, 'No'),
];
$colors = [
	SDL_MessageBoxColor::BACKGROUND => new SDL_MessageBoxColor(0, 0, 0),
	SDL_MessageBoxColor::TEXT => new SDL_MessageBoxColor(255, 255, 255),
	SDL_MessageBoxColor::BUTTON_BORDER => new SDL_MessageBoxColor(255, 0, 0),
	SDL_MessageBoxColor::BUTTON_BACKGROUND => new SDL_MessageBoxColor(0, 255, 0),
	SDL_MessageBoxColor::BUTTON_SELECTED => new SDL_MessageBoxColor(0, 0, 255),
];
$dialog = new SDL_MessageBoxData(SDL_MessageBoxData::INFORMATION, "Message box data", 'Select Yes or No', $buttons, $colors);
$dialog->Show($buttonId);

echo 'Button selection: ', var_export($buttonId), PHP_EOL;
