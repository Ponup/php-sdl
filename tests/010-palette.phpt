--TEST--
SDL_Palette test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php
echo "= Alloc\n";
$p1 = SDL_AllocPalette(0);
$p2 = SDL_AllocPalette(1);
var_dump($p1, $p2);
echo "= Free\n";
SDL_FreePalette($p2);
?>
= Done
--EXPECTF--
= Alloc
NULL
object(SDL_Palette)#1 (4) {
  ["ncolors"]=>
  int(1)
  ["version"]=>
  int(1)
  ["refcount"]=>
  int(1)
  ["colors"]=>
  array(1) {
    [0]=>
    object(SDL_Color)#2 (4) {
      ["r"]=>
      int(255)
      ["g"]=>
      int(255)
      ["b"]=>
      int(255)
      ["a"]=>
      int(255)
    }
  }
}
= Free
= Done
