<?php

require 'bootstrap.php';

$quit = false;

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow('Window Events', SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
$renderer = SDL_CreateRenderer($window, -1, 0);

SDL_SetRenderDrawColor($renderer, 255, 0, 255, 255);

$event = new SDL_Event;
while (!$quit) {
	while(SDL_PollEvent($event)) {
    	switch ($event->type) {
        	case SDL_QUIT:
            	$quit = true;
            	break;
        	case SDL_WINDOWEVENT:
                $eventText = 'unknown';
                switch ($event->window->event) {
                    case SDL_WINDOWEVENT_SHOWN:
                        $eventText = "Shown";
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        $eventText = "Hidden";
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        $eventText = "Exposed";
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        $eventText = "Moved ({$event->window->data1}, {$event->window->data2})";
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        $eventText = "Resized ({$event->window->data1} x {$event->window->data2})";
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        $eventText = "Size changed";
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        $eventText = "Minimized";
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        $eventText = "Maximized";
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        $eventText = "Restored";
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        $eventText = "Enter";
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        $eventText = "Leave";
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        $eventText = "Focus gained";
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        $eventText = "Focus lost";
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        $eventText = "Close";
                        break;
                    case SDL_WINDOWEVENT_TAKE_FOCUS:
                        $eventText = "Take focus";
                        break;
                    case SDL_WINDOWEVENT_HIT_TEST:
                        $eventText = "Hit test";
                        break;
                }
                $window->setTitle($eventText);
				printf('Event{windowID=%d, timestamp=%s, description=%s}' . PHP_EOL, $event->window->windowID, $event->window->timestamp, $eventText);
            	break;
    	}
	}

    SDL_Delay(5);
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
