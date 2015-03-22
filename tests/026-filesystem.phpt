--TEST--
Tests for functions beloning to the filesystem "module".
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
var_dump(SDL_GetPrefPath());
var_dump(SDL_GetBasePath());
?>
+ Done
--EXPECTF--
+ Done
