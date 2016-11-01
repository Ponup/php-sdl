<?php
echo "+++ Empty (true)\n";
$r = new SDL_Rect(0,0,0,0);
var_dump($r);
var_dump(SDL_RectEmpty($r));

echo "+++ Empty (false)\n";
$r = new SDL_Rect(1,2,3,4);
var_dump($r);
var_dump(SDL_RectEmpty($r));

$r1 = new SDL_Rect(10,10,20,20);
$r2 = new SDL_Rect(10,10,20,20);
$r3 = new SDL_Rect(16,17,22,24);
$r4 = new SDL_Rect(100,10,20,20);

echo "+++ Equal (true)\n";
var_dump(SDL_RectEquals($r1, $r1));
var_dump(SDL_RectEquals($r1, $r2));
echo "+++ Equal (false)\n";
var_dump(SDL_RectEquals($r1, $r3));
var_dump(SDL_RectEquals($r2, $r3));

echo "+++ Inter (true)\n";
var_dump(SDL_HasIntersection($r2, $r3));
var_dump(SDL_IntersectRect($r2, $r3, $x));
var_dump($x); unset($x);

echo "+++ Inter (false)\n";
var_dump(SDL_HasIntersection($r2, $r4));
var_dump(SDL_IntersectRect($r2, $r4, $x));
var_dump($x); unset($x);

echo "+++ Union\n";
var_dump(SDL_UnionRect($r2, $r3, $x));
var_dump($x); unset($x);
var_dump(SDL_UnionRect($r2, $r4, $x));
var_dump($x); unset($x);

echo "+++ InterLine\n";
$x1=0; $y1=10; $x2=40; $y2=30;
var_dump(SDL_IntersectRectAndLine($r1, $x1, $y1, $x2, $y2));
var_dump($x1, $y1, $x2, $y2);
$x1=0; $y1=2; $x2=40; $y2=6;
var_dump($r1->IntersectLine($x1, $y1, $x2, $y2));

echo "+++ EnclosePoints\n";
$pts = array(
	new SDL_Point(20,14),
	new SDL_Point(13,20),
	new SDL_Point(24,20),
	new SDL_Point(20,28),
);
var_dump($pts[0]." ".$pts[1]." ".$pts[2]." ".$pts[3]);
var_dump(SDL_EnclosePoints($pts, 0, $r1, $res1), $res1);
$pts[]="foo";
var_dump(SDL_EnclosePoints($pts, 6, $r4, $res2), $res2);
?>
Done
