--TEST--
error group test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "+ start\n";
var_dump(SDL_GetError());
echo "+ set\n";
var_dump(SDL_SetError("Foo"));
var_dump(SDL_GetError());
echo "+ clear\n";
var_dump(SDL_ClearError());
var_dump(SDL_GetError());
?>
Done
--EXPECTF--
+ start
string(0) ""
+ set
int(-1)
string(3) "Foo"
+ clear
NULL
string(0) ""
Done

