<?php declare(strict_types=1);

require 'bootstrap.php';

if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, 'Message box title', 'This is an example message box') !== 0) {
	fprintf(STDERR, 'Unable to show simple message box');
	exit(1);
}

const BUTTON_ID_YES = 1;
const BUTTON_ID_NO = 0;

$buttons = [
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::RETURNKEY_DEFAULT, BUTTON_ID_YES, 'Yes'),
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::ESCAPEKEY_DEFAULT, BUTTON_ID_NO, 'No'),
];
$colors = [
	SDL_MessageBoxColor::BACKGROUND => new SDL_MessageBoxColor(0, 0, 0),
	SDL_MessageBoxColor::TEXT => new SDL_MessageBoxColor(255, 255, 255),
	SDL_MessageBoxColor::BUTTON_BORDER => new SDL_MessageBoxColor(255, 0, 0),
	SDL_MessageBoxColor::BUTTON_BACKGROUND => new SDL_MessageBoxColor(0, 255, 0),
	SDL_MessageBoxColor::BUTTON_SELECTED => new SDL_MessageBoxColor(0, 0, 255),
];
$dialog = new SDL_MessageBoxData(SDL_MessageBoxData::INFORMATION, "Message box data", 'Select Yes or No', $buttons, $colors);
if(0 === $dialog->Show($buttonId)) {
	echo 'Button selection: ', $buttonId === BUTTON_ID_YES ? 'Yes' : 'No', PHP_EOL;
} else {
	printSdlErrorAndExit();
}
