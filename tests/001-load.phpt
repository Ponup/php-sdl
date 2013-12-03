--TEST--
Check for SDL2 presence
--SKIPIF--
<?php
if (!extension_loaded("sdl2")) die("skip: SDL2 extension not loaded");
?>
--FILE--
<?php 
echo "SDL2 version ".phpversion("sdl2"). " extension is available\n";
$n = count(get_extension_funcs("sdl2"));
echo "$n functions defined\n";
// if ($n >= 39) echo "OK\n";
?>
Done
--EXPECTF--
SDL2 version %s extension is available
%d functions defined
Done
