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
echo "= Color\n";
var_dump($p2->colors[0]);
echo "= Free\n";
SDL_FreePalette($p2);
?>
= Done
--EXPECTF--
= Alloc
NULL
object(SDL_Palette)#%d (4) {
  ["ncolors"]=>
  int(1)
  ["version"]=>
  int(1)
  ["refcount"]=>
  int(1)
  ["colors"]=>
  array(1) {
    [0]=>
    object(SDL_Color)#%d (4) {
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
= Color
object(SDL_Color)#%d (4) {
  ["r"]=>
  int(255)
  ["g"]=>
  int(255)
  ["b"]=>
  int(255)
  ["a"]=>
  int(255)
}
= Free
= Done
