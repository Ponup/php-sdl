--TEST--
SDL_Surface test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "= Create Palette\n";
$spal = SDL_CreateRGBSurface(0, 150, 100, 8, 0, 0, 0, 0);
var_dump($spal->w, $spal->h, $spal->format->palette->ncolors);

echo "= Create True colors\n";
$scol = SDL_CreateRGBSurface(0, 150, 100, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
var_dump($scol->w, $scol->h, $scol->format->palette);

echo "= Lock\n";
var_dump(SDL_MustLock($spal), $spal->locked);
var_dump(SDL_LockSurface($spal), $spal->locked);
var_dump(SDL_UnlockSurface($spal), $spal->locked);

echo "= ColorKey\n";
var_dump(SDL_SetColorKey($spal, 1, 127));
var_dump(SDL_GetColorKey($spal, $key), $key);
var_dump(SDL_SetColorKey($spal, 0));
var_dump(SDL_GetColorKey($spal, $key));

echo "= ColorMod\n";
var_dump(SDL_SetSurfaceColorMod($scol, 1, 2, 3));
var_dump(SDL_GetSurfaceColorMod($scol, $r, $g, $b), $r, $g, $b);

echo "= AlphaMod\n";
var_dump(SDL_SetSurfaceAlphaMod($scol, 4));
var_dump(SDL_GetSurfaceAlphaMod($scol, $a), $a);

echo "= BlendMode\n";
var_dump(SDL_SetSurfaceBlendMode($scol, SDL_BLENDMODE_ADD));
var_dump(SDL_GetSurfaceBlendMode($scol, $a), $a==SDL_BLENDMODE_ADD);

echo "= ClipRect\n";
var_dump(SDL_SetClipRect($scol, new SDL_Rect(10,20,30,40)));
var_dump(SDL_GetClipRect($scol, $rect), $rect);

echo "= Convert\n";
$conv = SDL_ConvertSurface($spal, $scol->format);
var_dump($scol->format->format == $conv->format->format);
$conv = SDL_ConvertSurfaceFormat($spal, $scol->format->format);
var_dump($scol->format->format == $conv->format->format);

echo "= ConvertPixels\n";
var_dump(SDL_ConvertPixels(
	150,100,
	$scol->format->format, $scol->pixels, $scol->pitch,
	$conv->format->format, $conv->pixels, $conv->pitch
), SDL_GetError());
echo "= Free\n";
SDL_FreeSurface($spal);
SDL_FreeSurface($scol);
?>
= Done
--EXPECTF--
= Create Palette
int(150)
int(100)
int(256)
= Create True colors
int(150)
int(100)
NULL
= Lock
bool(false)
int(0)
int(0)
int(1)
NULL
int(0)
= ColorKey
int(0)
int(0)
int(127)
int(0)
int(-1)
= ColorMod
int(0)
int(0)
int(1)
int(2)
int(3)
= AlphaMod
int(0)
int(0)
int(4)
= BlendMode
int(0)
int(0)
bool(true)
= ClipRect
bool(true)
NULL
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(10)
  ["y"]=>
  int(20)
  ["w"]=>
  int(30)
  ["h"]=>
  int(40)
}
= Convert
bool(true)
bool(true)
= ConvertPixels
int(0)
string(0) ""
= Free
= Done
