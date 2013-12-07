--TEST--
rect group test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php
$r = new SDL_Color(1,63,127,255);
var_dump($r);
$r = new SDL_Color(0,-1,256,123456);
var_dump($r);
?>
Done
--EXPECTF--
object(SDL_Color)#1 (4) {
  ["r"]=>
  int(1)
  ["g"]=>
  int(63)
  ["b"]=>
  int(127)
  ["a"]=>
  int(255)
}
object(SDL_Color)#2 (4) {
  ["r"]=>
  int(0)
  ["g"]=>
  int(255)
  ["b"]=>
  int(0)
  ["a"]=>
  int(64)
}
Done
