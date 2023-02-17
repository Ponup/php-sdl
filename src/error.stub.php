<?php

/**
 * 
 * @param  string $error
 * @return int    unconditionally returns -1.
 */
function SDL_SetError(string $error):int {
    return 0;
}

/**
 * 
 * @return string
 */
function SDL_GetError():string {
    return '';
}

/**
 * 
 * @return string
 */
function SDL_ClearError():string {
    return '';
}