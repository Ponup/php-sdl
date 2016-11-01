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
echo "= Array\n";
var_dump($p2->count());
$p2[0] = new SDL_Color(7,8,9,0);
var_dump($p2[0]);
unset($p2[0]);
var_dump($p2[0]);
echo "= Free\n";
$p2->Free()
?>
= Done
