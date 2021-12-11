--TEST--
SDL_PointInRect test suite
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
SUITE: Start
<?php
var_dump(SDL_PointInRect(new SDL_Point(10, 20), new SDL_Rect(100, 200, 50, 50)));
var_dump(SDL_PointInRect(new SDL_Point(10, 20), new SDL_Rect(0, 10, 50, 50)));
?>
SUITE: End
--EXPECTF--
SUITE: Start
bool(false)
bool(true)
SUITE: End
