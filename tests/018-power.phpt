--TEST--
SDL_power test suite
--SKIPIF--
<?php
extension_loaded('sdl') or die('skip SDL extension not loaded');
?>
--FILE--
<?php
echo '= Constants', PHP_EOL;
var_dump(is_integer(SDL_POWERSTATE_UNKNOWN));
var_dump(is_integer(SDL_POWERSTATE_ON_BATTERY));
var_dump(is_integer(SDL_POWERSTATE_NO_BATTERY));
var_dump(is_integer(SDL_POWERSTATE_CHARGING));
var_dump(is_integer(SDL_POWERSTATE_CHARGED));

echo '= Functions', PHP_EOL;
$secs = $pct = null;
$powerStates = array(SDL_POWERSTATE_UNKNOWN, SDL_POWERSTATE_ON_BATTERY, SDL_POWERSTATE_NO_BATTERY, SDL_POWERSTATE_CHARGING, SDL_POWERSTATE_CHARGED);
var_dump(in_array(SDL_GetPowerInfo(), $powerStates));
var_dump(in_array(SDL_GetPowerInfo($secs, $pct), $powerStates));
var_dump($secs >= -1);
var_dump($pct >= -1 && $pct <= 100);

echo '= Done', PHP_EOL;
?>
--EXPECTF--
= Constants
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
= Functions
bool(true)
bool(true)
bool(true)
bool(true)
= Done
