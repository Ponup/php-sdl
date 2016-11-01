<?php
echo "= Palette\n";
$p = SDL_AllocPalette(16);

echo "= Color\n";
$colors = array();
for ($i=0, $j=0 ; $i<16 ; $i++, $j+=17) {
	$colors[] = new SDL_Color($j, $j, $j, $j);
}
echo "= PaletteColors\n";
var_dump(SDL_SetPaletteColors($p, $colors));

echo "= PixelFormat\n";
$f = SDL_AllocFormat(SDL_PIXELFORMAT_INDEX4LSB);

echo "= PixelFormatPalette\n";
var_dump(SDL_SetPixelFormatPalette($f, $p));

echo "= Result\n";
var_dump($f);

echo "= RGB\n";
var_dump(SDL_MapRGB($f, 100,100,100));
var_dump(SDL_MapRGBA($f, 200, 200,200,200));
var_dump(SDL_GetRGB(5, $f, $r, $g, $b), $r, $g, $b);
var_dump(SDL_GetRGBA(10, $f, $r, $g, $b, $a), $r, $g, $b, $a);

echo "= Free\n";
SDL_FreeFormat($f);
SDL_FreePalette($p);
?>
= Done
