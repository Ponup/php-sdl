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
