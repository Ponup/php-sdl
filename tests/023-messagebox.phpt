--TEST--
SDL_MessageBox test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
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
--EXPECTF--
= SDL_MessageBoxColor
object(SDL_MessageBoxColor)#%d (3) {
  ["r"]=>
  int(1)
  ["g"]=>
  int(2)
  ["b"]=>
  int(3)
}
string(26) "SDL_MessageBoxColor(1,2,3)"
object(SDL_MessageBoxColor)#%d (3) {
  ["r"]=>
  string(3) "123"
  ["g"]=>
  float(345.6)
  ["b"]=>
  int(-5)
}
string(31) "SDL_MessageBoxColor(123,89,251)"
object(SDL_MessageBoxColor)#%d (3) {
  ["r"]=>
  int(123)
  ["g"]=>
  int(89)
  ["b"]=>
  int(251)
}
= SDL_MessageBoxButtonData
object(SDL_MessageBoxButtonData)#%d (3) {
  ["flags"]=>
  int(0)
  ["buttonid"]=>
  int(1)
  ["text"]=>
  string(10) "Foo button"
}
string(42) "SDL_MessageBoxButtonData(0,1,"Foo button")"
= SDL_MessageBoxData
object(SDL_MessageBoxData)#%d (7) {
  ["flags"]=>
  int(0)
  ["title"]=>
  string(11) "Foo title 1"
  ["message"]=>
  string(11) "Foo message"
  ["window"]=>
  bool(false)
  ["numbuttons"]=>
  int(0)
  ["buttons"]=>
  NULL
  ["colors"]=>
  NULL
}
string(33) "SDL_MessageBoxData("Foo title 1")"
object(SDL_MessageBoxData)#%d (7) {
  ["flags"]=>
  int(0)
  ["title"]=>
  string(11) "Foo title 2"
  ["message"]=>
  string(11) "Foo message"
  ["window"]=>
  bool(false)
  ["numbuttons"]=>
  int(2)
  ["buttons"]=>
  array(2) {
    [0]=>
    object(SDL_MessageBoxColor)#%d (6) {
      ["r"]=>
      int(0)
      ["g"]=>
      int(0)
      ["b"]=>
      int(0)
      ["flags"]=>
      int(1)
      ["buttonid"]=>
      int(1)
      ["text"]=>
      string(3) "Yes"
    }
    [1]=>
    object(SDL_MessageBoxColor)#%d (6) {
      ["r"]=>
      int(0)
      ["g"]=>
      int(0)
      ["b"]=>
      int(0)
      ["flags"]=>
      int(2)
      ["buttonid"]=>
      int(0)
      ["text"]=>
      string(2) "No"
    }
  }
  ["colors"]=>
  array(5) {
    [0]=>
    object(SDL_MessageBoxColor)#%d (3) {
      ["r"]=>
      int(0)
      ["g"]=>
      int(0)
      ["b"]=>
      int(0)
    }
    [1]=>
    object(SDL_MessageBoxColor)#%d (3) {
      ["r"]=>
      int(255)
      ["g"]=>
      int(255)
      ["b"]=>
      int(255)
    }
    [2]=>
    object(SDL_MessageBoxColor)#%d (3) {
      ["r"]=>
      int(255)
      ["g"]=>
      int(0)
      ["b"]=>
      int(0)
    }
    [3]=>
    object(SDL_MessageBoxColor)#%d (3) {
      ["r"]=>
      int(0)
      ["g"]=>
      int(255)
      ["b"]=>
      int(0)
    }
    [4]=>
    object(SDL_MessageBoxColor)#%d (3) {
      ["r"]=>
      int(0)
      ["g"]=>
      int(0)
      ["b"]=>
      int(255)
    }
  }
}
string(33) "SDL_MessageBoxData("Foo title 2")"
= Done
