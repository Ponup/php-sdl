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
