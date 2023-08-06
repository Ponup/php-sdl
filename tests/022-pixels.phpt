--TEST--
SDL_Pixels test
--SKIPIF--
<?php
require 'test-functions.php';
--INI--
error_reporting = 32767;
--FILE--
<?php
echo "= Create\n";
try {
	var_dump($pix = new SDL_Pixels(-1, -1));
} catch (Exception $e) {
	echo "Exception: " . $e->getMessage() . "\n";
}
var_dump($pix = new SDL_Pixels(10, 10), "$pix");
?>
= Done
--EXPECTF--
= Create
Exception: Invalid size

Notice: SDL_Pixels::__construct(): Pitch set to 12 in %s%e022-pixels.php on line 8
object(SDL_Pixels)#%d (0) {
}
string(10) "SDL_Pixels"
= Done
