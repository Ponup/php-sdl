--TEST--
Extension can init and shutdown.
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
<?php 
require 'test-functions.php';

assertEquals(SDL_WasInit(), 0, 'nothings is initialised');
SDL_Init();
assertEquals(SDL_WasInit(), SDL_INIT_EVERYTHING, 'everything is initialised');
SDL_Quit();
assertEquals(SDL_WasInit(), 0, 'everything is shutdown');
--EXPECTF--
PASS: nothings is initialised.
PASS: everything is initialised.
PASS: everything is shutdown.