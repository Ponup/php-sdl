--TEST--
SDL_Palette test, object mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php
echo "= Alloc\n";
try {
	$p1 = new SDL_Palette(0);
} catch (Exception $e) {
	echo $e->getMessage(), "\n";
}
$p2 = new SDL_Palette(1);
var_dump($p2);
echo "= Color\n";
var_dump($p2->colors[0]);
$colors = array(new SDL_Color(1,2,3,4));
var_dump($p2->SetColors($colors, 2));
var_dump($p2->SetColors($colors, 0));
var_dump($p2->colors[0]);
echo "= Free\n";
$p2->Free()
?>
= Done
--EXPECTF--
= Alloc
Parameter 'ncolors' is invalid
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

%s: SDL_Palette::SetColors(): Invalid first color index, 2 >= 1 in %s/011-palette-oo.php on line 13
int(-1)
int(0)
object(SDL_Color)#%d (4) {
  ["r"]=>
  int(1)
  ["g"]=>
  int(2)
  ["b"]=>
  int(3)
  ["a"]=>
  int(4)
}
= Free
= Done
