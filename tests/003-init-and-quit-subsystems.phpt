--TEST--
Subsystems can be init and shutdown.
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
<?php
require 'test-functions.php';
assertEquals(SDL_WasInit(), 0, 'before calling SDL_Init nothing is initialised');

SDL_InitSubSystem(SDL_INIT_AUDIO);
assertEquals(SDL_WasInit(), SDL_INIT_AUDIO, 'init first subsystem works');

SDL_InitSubSystem(SDL_INIT_TIMER);
assertEquals(SDL_WasInit(), SDL_INIT_AUDIO + SDL_INIT_TIMER, 'init two subsystems works');

SDL_QuitSubSystem(SDL_INIT_AUDIO);
assertEquals(SDL_WasInit(), SDL_INIT_TIMER, 'quitting one subsystem works');

SDL_Quit();
assertEquals(SDL_WasInit(), 0, 'quitting everything works');
--EXPECTF--
PASS: before calling SDL_Init nothing is initialised.
PASS: init first subsystem works.
PASS: init two subsystems works.
PASS: quitting one subsystem works.
PASS: quitting everything works.
