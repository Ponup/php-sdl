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
