--TEST--
SDL_Pixels test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--INI--
error_reporting = 32767;
--FILE--
<?php
echo "= Create\n";
try {
	var_dump($pix = new SDL_Pixels(-1, -1));
} catch (Exception $e) {
	echo "Exception: " . $e->getMessage() . "\n";
}
var_dump($pix = new SDL_Pixels(10, 10), "$pix");
echo "= Get/Set\n";
var_dump($pix->GetByte(15,15));
var_dump($pix->SetByte(0,0,1));
var_dump($pix->GetByte(0,0));
var_dump($pix->SetByte(1,1,255));
var_dump($pix->GetByte(1,1));

echo "= Array\n";
var_dump($pix[20], isset($pix[20]), isset($pix[1000]));
var_dump($pix[20]=127);
var_dump($pix[20]);
unset($pix[20]);
var_dump($pix[20]);
?>
= Done
--EXPECTF--
= Create
Exception: Invalid size

Notice: SDL_Pixels::__construct(): Pitch set to 12 in %s%e022-pixels.php on line 8
object(SDL_Pixels)#%d (3) {
  ["pitch"]=>
  int(12)
  ["h"]=>
  int(10)
  ["count"]=>
  int(120)
}
string(17) "SDL_Pixels(12,10)"
= Get/Set

Notice: SDL_Pixels::GetByte(): Invalid position (15,15) in SDL_Pixels (12,10) in %s%e022-pixels.php on line 10
bool(false)
int(0)
int(1)
int(0)
int(255)
= Array
int(0)
bool(true)
bool(false)
int(127)
int(127)
int(0)
= Done
