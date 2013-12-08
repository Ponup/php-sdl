--TEST--
SDL_Color test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "Color\n";
$r = new SDL_Color(1,63,127,255);
var_dump($r);
$r = new SDL_Color(0,-1,256,123456);
var_dump($r);
echo "Name\n";
var_dump(SDL_GetPixelFormatName(0));
var_dump(SDL_GetPixelFormatName(SDL_PIXELFORMAT_RGBA4444));
var_dump(SDL_GetPixelFormatName(SDL_PIXELFORMAT_YVYU));
var_dump(SDL_GetPixelFormatName(-1));
echo "Mask\n";
var_dump(SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_RGBA4444, $bpp, $r, $g, $b, $a), SDL_PIXELFORMAT_RGBA4444, $bpp, $r, $g, $b, $a);
var_dump($f=SDL_MasksToPixelFormatEnum($bpp, $r, $g, $b, $a));
var_dump(SDL_GetPixelFormatName($f));
var_dump($f=SDL_MasksToPixelFormatEnum(32, 0xff000000, 0xff0000, 0xff00, 0xff));
var_dump(SDL_GetPixelFormatName($f));
?>
Done
--EXPECTF--
Color
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
Name
string(23) "SDL_PIXELFORMAT_UNKNOWN"
string(24) "SDL_PIXELFORMAT_RGBA4444"
string(20) "SDL_PIXELFORMAT_YVYU"
string(23) "SDL_PIXELFORMAT_UNKNOWN"
Mask
bool(true)
int(356651010)
int(16)
int(61440)
int(3840)
int(240)
int(15)
int(356651010)
string(24) "SDL_PIXELFORMAT_RGBA4444"
int(373694468)
string(24) "SDL_PIXELFORMAT_RGBA8888"
Done
