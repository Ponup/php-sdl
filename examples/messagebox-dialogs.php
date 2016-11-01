<?php

require 'bootstrap.php';

SDL_GetVersion($version);

$message = sprintf("Powered by PHP %s, SDL extension %s, SDL2 library %s", phpversion(), phpversion("sdl"), implode('.', $version));

if (false === SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION, "Simple message box", $message
        )) {
    fprintf(STDERR, 'Unable to show simple message box');
    return;
}

$buttons = array(
    new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::RETURNKEY_DEFAULT, 1, "Yes"),
    new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::ESCAPEKEY_DEFAULT, 0, "No"),
);
$colors = array(
    SDL_MessageBoxColor::BACKGROUND => new SDL_MessageBoxColor(0, 0, 0),
    SDL_MessageBoxColor::TEXT => new SDL_MessageBoxColor(255, 255, 255),
    SDL_MessageBoxColor::BUTTON_BORDER => new SDL_MessageBoxColor(255, 0, 0),
    SDL_MessageBoxColor::BUTTON_BACKGROUND => new SDL_MessageBoxColor(0, 255, 0),
    SDL_MessageBoxColor::BUTTON_SELECTED => new SDL_MessageBoxColor(0, 0, 255),
);
$dialog = new SDL_MessageBoxData(
        SDL_MessageBoxData::INFORMATION, "Message box data", 'Select Yes or No', $buttons, $colors
);
$dialog->Show($buttonId);
printf("You press \"%s\"\n", ($buttonId ? "Yes" : "No"));
echo 'Done';
