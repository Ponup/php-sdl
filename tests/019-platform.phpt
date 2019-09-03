--TEST--
SDL_platform test suite
--SKIPIF--
<?php
require 'test-functions.php';
?>
--FILE--
<?php
echo '= Functions', PHP_EOL;
var_dump(is_string($platform = SDL_GetPlatform()));
var_dump(in_array($platform, array('Unknown', 'Windows', 'Mac OS X', 'Linux', 'iOS', 'Android')));

echo '= Done', PHP_EOL;
?>
--EXPECTF--
= Functions
bool(true)
bool(true)
= Done

