<?php
echo "= Alloc\n";
$p1 = SDL_AllocPalette(0);
$p2 = SDL_AllocPalette(1);
var_dump($p1, $p2);
echo "= Color\n";
var_dump($p2->colors[0]);
$colors = array(new SDL_Color(1,2,3,4));
var_dump(SDL_SetPaletteColors($p2, $colors, 2));
var_dump(SDL_SetPaletteColors($p2, $colors, 0));
var_dump($p2->colors[0]);
echo "= Free\n";
SDL_FreePalette($p2);
?>
= Done
