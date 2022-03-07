--TEST--
rect group test, object mode
--SKIPIF--
<?php
require 'test-functions.php';
--FILE--
<?php
echo "+++ Empty (true)\n";
$r = new SDL_Rect(0,0,0,0);
var_dump($r, "$r");
var_dump($r->Empty());

$r = new SDL_FRect(.0,.0,.0,.0);
var_dump($r);
var_dump($r->Empty());

echo "+++ Empty (false)\n";
$r = new SDL_Rect(1,2,3,4);
var_dump($r, "$r");
var_dump($r->Empty());

$r = new SDL_FRect(1.1, 2.2, 3.3, 4.4);
var_dump($r, "$r");
var_dump($r->Empty());

$r1 = new SDL_Rect(10,10,20,20);
$r2 = new SDL_Rect(10,10,20,20);
$r3 = new SDL_Rect(16,17,22,24);
$r4 = new SDL_Rect(100,10,20,20);

$fr2 = new SDL_FRect(10.1, 10.1, 20.1, 20.1);
$fr3 = new SDL_FRect(16.1, 17.1, 22.1, 24.1);
$fr4 = new SDL_FRect(100.1, 10.1, 20.1, 20.1);

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

var_dump($fr2->HasIntersection($fr3));
var_dump($fr2->Intersect($fr3, $x));
var_dump($x); unset($x);

echo "+++ Inter (false)\n";
var_dump($r2->HasIntersection($r4));
var_dump($r2->Intersect($r4, $x));
var_dump($x); unset($x);

var_dump($fr2->HasIntersection($fr4));
var_dump($fr2->Intersect($fr4, $x));
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

echo '+++ Test subclasses of SDL_Rect can be passed to SDL functions', PHP_EOL;
class CustomRect extends \SDL_Rect {}
$customRect = new CustomRect(10, 20, 30, 40);
var_dump(SDL_RectEmpty($customRect));
?>
Done
--EXPECTF--
+++ Empty (true)
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["w"]=>
  int(0)
  ["h"]=>
  int(0)
}
string(17) "SDL_Rect(0,0,0,0)"
bool(true)
object(SDL_FRect)#%d (4) {
  ["x"]=>
  float(0)
  ["y"]=>
  float(0)
  ["w"]=>
  float(0)
  ["h"]=>
  float(0)
}
bool(true)
+++ Empty (false)
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(1)
  ["y"]=>
  int(2)
  ["w"]=>
  int(3)
  ["h"]=>
  int(4)
}
string(17) "SDL_Rect(1,2,3,4)"
bool(false)
object(SDL_FRect)#%d (4) {
  ["x"]=>
  float(1.100000023841858)
  ["y"]=>
  float(2.200000047683716)
  ["w"]=>
  float(3.299999952316284)
  ["h"]=>
  float(4.400000095367432)
}
string(46) "SDL_FRect(1.100000,2.200000,3.300000,4.400000)"
bool(false)
+++ Equal (true)
bool(true)
bool(true)
+++ Equal (false)
bool(false)
bool(false)
+++ Inter (true)
bool(true)
bool(true)
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(16)
  ["y"]=>
  int(17)
  ["w"]=>
  int(14)
  ["h"]=>
  int(13)
}
bool(true)
bool(true)
object(SDL_FRect)#%d (4) {
  ["x"]=>
  float(16.100000381469727)
  ["y"]=>
  float(17.100000381469727)
  ["w"]=>
  float(14.100000381469727)
  ["h"]=>
  float(13.100000381469727)
}
+++ Inter (false)
bool(false)
bool(false)
NULL
bool(false)
bool(false)
NULL
+++ Uninon
NULL
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(10)
  ["y"]=>
  int(10)
  ["w"]=>
  int(28)
  ["h"]=>
  int(31)
}
NULL
object(SDL_Rect)#%d (4) {
  ["x"]=>
  int(10)
  ["y"]=>
  int(10)
  ["w"]=>
  int(110)
  ["h"]=>
  int(20)
}
+++ InterLine
bool(true)
int(10)
int(15)
int(29)
int(24)
bool(false)
+++ Test subclasses of SDL_Rect can be passed to SDL functions
bool(false)
Done