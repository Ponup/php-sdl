--TEST--
Tests for functions beloning to the filesystem "module".
--SKIPIF--
<?php
require 'skipif.php';
skip_test_not_complete();
?>
--FILE--
<?php
$prefPath = SDL_GetPrefPath('my_org', 'my_app');
var_dump(strpos($prefPath, 'my_org') !== false);
var_dump(strpos($prefPath, 'my_app') !== false);
$basePath = SDL_GetBasePath();
var_dump(strpos($basePath, DIRECTORY_SEPARATOR) !== false);
?>
+ Done
--EXPECTF--
bool(true)
bool(true)
bool(true)
+ Done
