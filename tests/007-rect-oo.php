<?php
echo "+++ Empty (true)\n";
$r = new SDL_Rect(0,0,0,0);
var_dump($r, "$r");
var_dump(SDL_RectEmpty($r));

echo "+++ Empty (false)\n";
$r = new SDL_Rect(1,2,3,4);
var_dump($r, "$r");
var_dump($r->Empty());

$r1 = new SDL_Rect(10,10,20,20);
$r2 = new SDL_Rect(10,10,20,20);
$r3 = new SDL_Rect(16,17,22,24);
$r4 = new SDL_Rect(100,10,20,20);

echo "+++ Equal (true)\n";
var_dump($r1->Equal($r1));
var_dump($r1->Equal($r2));
echo "+++ Equal (false)\n";
var_dump($r1->Equal($r3));
var_dump($r2->Equal($r3));

echo "+++ Inter (true)\n";
var_dump($r2->HasIntersection($r3));
var_dump($r2->Intersect($r3, $x));
var_dump($x); unset($x);

echo "+++ Inter (false)\n";
var_dump($r2->HasIntersection($r4));
var_dump($r2->Intersect($r4, $x));
var_dump($x); unset($x);

echo "+++ Uninon\n";
var_dump($r2->Union($r3, $x));
var_dump($x); unset($x);
var_dump($r2->Union($r4, $x));
var_dump($x); unset($x);

echo "+++ InterLine\n";
$x1=0; $y1=10; $x2=40; $y2=30;
var_dump($r1->IntersectLine($x1, $y1, $x2, $y2));
var_dump($x1, $y1, $x2, $y2);
$x1=0; $y1=2; $x2=40; $y2=6;
var_dump($r1->IntersectLine($x1, $y1, $x2, $y2));
?>
Done
