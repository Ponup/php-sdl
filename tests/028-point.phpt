--TEST--
SDL_Point test suite
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
SUITE: Start
<?php
echo 'TEST: Subclasses of SDL_Point can be converted properly', PHP_EOL;
class CustomPoint extends \SDL_Point {}
$customPoint = new CustomPoint(10, 20);
echo strval($customPoint), PHP_EOL;
?>
SUITE: End
--EXPECTF--
SUITE: Start
TEST: Subclasses of SDL_Point can be converted properly
SDL_Point(10,20)
SUITE: End
