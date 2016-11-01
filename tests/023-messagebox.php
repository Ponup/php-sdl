<?php
echo "= SDL_MessageBoxColor\n";
$c = new SDL_MessageBoxColor(1,2,3);
var_dump($c, "$c");
$c->r = "123";
$c->g = 345.6;
$c->b = -5;
var_dump($c); /* string, float, int */
var_dump("$c");
var_dump($c); /* 3 int */

echo "= SDL_MessageBoxButtonData\n";
$b = new SDL_MessageBoxButtonData(0,1,"Foo button");
var_dump($b, "$b");

echo "= SDL_MessageBoxData\n";
$d = new SDL_MessageBoxData(0,"Foo title 1","Foo message");
var_dump($d, "$d");

$buttons = array(
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::RETURNKEY_DEFAULT, 1, "Yes"),
	new SDL_MessageBoxButtonData(SDL_MessageBoxButtonData::ESCAPEKEY_DEFAULT, 0, "No"),
);
$colors = array(
	SDL_MessageBoxColor::BACKGROUND        => new SDL_MessageBoxColor(0,0,0),
	SDL_MessageBoxColor::TEXT              => new SDL_MessageBoxColor(255,255,255),
	SDL_MessageBoxColor::BUTTON_BORDER     => new SDL_MessageBoxColor(255,0,0),
	SDL_MessageBoxColor::BUTTON_BACKGROUND => new SDL_MessageBoxColor(0,255,0),
	SDL_MessageBoxColor::BUTTON_SELECTED   => new SDL_MessageBoxColor(0,0,255),
);
$d = new SDL_MessageBoxData(0,"Foo title 2","Foo message", $buttons, $colors);
var_dump($d, "$d");
?>
= Done
