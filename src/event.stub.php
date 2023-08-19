<?php

class SDL_Event implements Stringable {
    public SDL_Window $window;

    public function __construct() {
    }

    public function __toString(): string {
        return '';
    }
}

/**
 * Polls for currently pending events.
 * @param null|resource If not NULL, the next event is removed from the queue and stored in that area.
 * @return int 1 if there are any pending events, or 0 if there are none available.
 */
function SDL_PollEvent(
    mixed $event
):int {
    return 0;
}

/**
 * 
 * @param  SDL_Event $event
 * @return int
 */
function SDL_WaitEvent(SDL_Event $event):int {
    return 0;
}