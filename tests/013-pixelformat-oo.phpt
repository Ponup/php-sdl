--TEST--
SDL_PixelFormat test, object mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "= Palette\n";
$p = new SDL_Palette(16);
var_dump("$p");

echo "= Color\n";
$colors = array();
for ($i=0, $j=0 ; $i<16 ; $i++, $j+=17) {
	$colors[] = new SDL_Color($j, $j, $j, $j);
}
var_dump("".$colors[5]);
echo "= PaletteColors\n";
var_dump($p->SetColors($colors));

echo "= PixelFormat\n";
$f = new SDL_PixelFormat(SDL_PIXELFORMAT_INDEX4LSB);
var_dump("$f");

echo "= PixelFormatPalette\n";
var_dump($f->SetPalette($p));

echo "= Result\n";
var_dump($f);

echo "= RGB\n";
var_dump($f->MapRGB(100,100,100));
var_dump($f->MapRGBA(200,200,200,200));
var_dump($f->GetRGB(5, $r, $g, $b), $r, $g, $b);
var_dump($f->GetRGBA(10, $r, $g, $b, $a), $r, $g, $b, $a);

?>
= Done
--EXPECTF--
= Palette
string(15) "SDL_Palette(16)"
= Color
string(22) "SDL_Color(85,85,85,85)"
= PaletteColors
int(0)
= PixelFormat
string(42) "SDL_PixelFormat(SDL_PIXELFORMAT_INDEX4LSB)"
= PixelFormatPalette
int(0)
= Result
object(SDL_PixelFormat)#%d (16) {
  ["format"]=>
  int(303039488)
  ["BitsPerPixel"]=>
  int(4)
  ["BytesPerPixel"]=>
  int(1)
  ["Rmask"]=>
  int(0)
  ["Gmask"]=>
  int(0)
  ["Bmask"]=>
  int(0)
  ["Amask"]=>
  int(0)
  ["Rloss"]=>
  int(8)
  ["Gloss"]=>
  int(8)
  ["Bloss"]=>
  int(8)
  ["Aloss"]=>
  int(8)
  ["Rshift"]=>
  int(0)
  ["Gshift"]=>
  int(0)
  ["Bshift"]=>
  int(0)
  ["Ashift"]=>
  int(0)
  ["palette"]=>
  object(SDL_Palette)#%d (4) {
    ["ncolors"]=>
    int(16)
    ["version"]=>
    int(2)
    ["refcount"]=>
    int(2)
    ["colors"]=>
    array(16) {
      [0]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(0)
        ["g"]=>
        int(0)
        ["b"]=>
        int(0)
        ["a"]=>
        int(0)
      }
      [1]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(17)
        ["g"]=>
        int(17)
        ["b"]=>
        int(17)
        ["a"]=>
        int(17)
      }
      [2]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(34)
        ["g"]=>
        int(34)
        ["b"]=>
        int(34)
        ["a"]=>
        int(34)
      }
      [3]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(51)
        ["g"]=>
        int(51)
        ["b"]=>
        int(51)
        ["a"]=>
        int(51)
      }
      [4]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(68)
        ["g"]=>
        int(68)
        ["b"]=>
        int(68)
        ["a"]=>
        int(68)
      }
      [5]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(85)
        ["g"]=>
        int(85)
        ["b"]=>
        int(85)
        ["a"]=>
        int(85)
      }
      [6]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(102)
        ["g"]=>
        int(102)
        ["b"]=>
        int(102)
        ["a"]=>
        int(102)
      }
      [7]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(119)
        ["g"]=>
        int(119)
        ["b"]=>
        int(119)
        ["a"]=>
        int(119)
      }
      [8]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(136)
        ["g"]=>
        int(136)
        ["b"]=>
        int(136)
        ["a"]=>
        int(136)
      }
      [9]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(153)
        ["g"]=>
        int(153)
        ["b"]=>
        int(153)
        ["a"]=>
        int(153)
      }
      [10]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(170)
        ["g"]=>
        int(170)
        ["b"]=>
        int(170)
        ["a"]=>
        int(170)
      }
      [11]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(187)
        ["g"]=>
        int(187)
        ["b"]=>
        int(187)
        ["a"]=>
        int(187)
      }
      [12]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(204)
        ["g"]=>
        int(204)
        ["b"]=>
        int(204)
        ["a"]=>
        int(204)
      }
      [13]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(221)
        ["g"]=>
        int(221)
        ["b"]=>
        int(221)
        ["a"]=>
        int(221)
      }
      [14]=>
      object(SDL_Color)#%d (4) {
        ["r"]=>
        int(238)
        ["g"]=>
        int(238)
        ["b"]=>
        int(238)
        ["a"]=>
        int(238)
      }
      [15]=>
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
}
= RGB
int(8)
int(12)
NULL
int(85)
int(85)
int(85)
NULL
int(170)
int(170)
int(170)
int(170)
= Done
