--TEST--
video group test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "== VideoDriver ==\n";
var_dump($n=SDL_GetNumVideoDrivers());
var_dump($d=SDL_GetVideoDriver(0));
var_dump(SDL_GetVideoDriver($n));
echo "== Video OFF ==\n";
var_dump(SDL_GetCurrentVideoDriver());
var_dump($n=SDL_GetNumVideoDisplays());
echo "== Video ON ==\n";
echo "SDL_VideoInit():"; var_dump(SDL_VideoInit());
echo "SDL_GetCurrentVideoDriver():"; var_dump(SDL_GetCurrentVideoDriver());
echo "SDL_GetNumVideoDisplays():"; var_dump(SDL_GetNumVideoDisplays());
echo "SDL_GetDisplayName(0):"; var_dump(SDL_GetDisplayName(0));
echo "SDL_GetDisplayBounds(0):"; var_dump(SDL_GetDisplayBounds(0,$rect)); var_dump($rect);
echo "SDL_GetNumDisplayModes(0):"; var_dump(SDL_GetNumDisplayModes(0));
echo "SDL_GetDisplayMode(0,0):"; var_dump(SDL_GetDisplayMode(0,0));
echo "SDL_GetDesktopDisplayMode(0):"; var_dump(SDL_GetDesktopDisplayMode(0));
echo "SDL_GetCurrentDisplayMode(0):"; var_dump($x=SDL_GetCurrentDisplayMode(0), "$x");

var_dump(SDL_VideoQuit());
var_dump(SDL_VideoInit($d));
var_dump(SDL_VideoQuit());
var_dump(SDL_VideoInit("foo"));
var_dump(SDL_VideoQuit());
?>
Done
--EXPECTF--
== VideoDriver ==
int(%d)
string(%d) "%s"
bool(false)
== Video OFF ==
bool(false)
int(0)
== Video ON ==
SDL_VideoInit():int(0)
SDL_GetCurrentVideoDriver():string(%d) "%s"
SDL_GetNumVideoDisplays():int(%d)
SDL_GetDisplayName(0):string(9) "Color LCD"
SDL_GetDisplayBounds(0):int(0)
object(SDL_Rect)#1 (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["w"]=>
  int(1680)
  ["h"]=>
  int(1050)
}
SDL_GetNumDisplayModes(0):int(%d)
SDL_GetDisplayMode(0,0):object(SDL_DisplayMode)#2 (4) {
  ["format"]=>
  int(%d)
  ["w"]=>
  int(%d)
  ["h"]=>
  int(%d)
  ["refresh_rate"]=>
  int(%d)
}
SDL_GetDesktopDisplayMode(0):object(SDL_DisplayMode)#2 (4) {
  ["format"]=>
  int(%d)
  ["w"]=>
  int(%d)
  ["h"]=>
  int(%d)
  ["refresh_rate"]=>
  int(%d)
}
SDL_GetCurrentDisplayMode(0):object(SDL_DisplayMode)#2 (4) {
  ["format"]=>
  int(%d)
  ["w"]=>
  int(%d)
  ["h"]=>
  int(%d)
  ["refresh_rate"]=>
  int(%d)
}
string(%d) "SDL_DisplayMode(%s,%d,%d,%d)"
NULL
int(0)
NULL
int(-1)
NULL
Done

