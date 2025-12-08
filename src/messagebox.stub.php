<?php

class SDL_MessageBoxColor implements Stringable {
    const BACKGROUND        = 0;
    const TEXT              = 1;
    const BUTTON_BORDER     = 2;
    const BUTTON_BACKGROUND = 3;
    const BUTTON_SELECTED   = 4;
    const MAX               = 5;

    public function __construct(
        public int $r,
        public int $g,
        public int $b,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}


/**
 * Create a modal message box.
 * 
 * This function should be called on the thread that created the parent window, or on the main thread if the messagebox has no parent. 
 * It will block execution of that thread until the user clicks a button or closes the messagebox.
 * @param  SDL_MessageBoxData $messageboxdata messageboxdata The SDL_MessageBoxData structure with title, text, etc.
 * @param  int                $buttonid       buttonid The pointer to which user id of hit button should be copied.
 * @return int                -1 on error, otherwise 0 and buttonid contains user id of button hit or -1 if dialog was closed.
 */
function SDL_ShowMessageBox(SDL_MessageBoxData $messageboxdata, int &$buttonid):int {
    return 0;
}