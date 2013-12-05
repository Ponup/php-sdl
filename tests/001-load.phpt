--TEST--
Check for SDL presence
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php 
echo "SDL version ".phpversion("sdl"). " extension is available\n";
$n = count(get_extension_funcs("sdl"));
echo "$n functions defined\n";
?>
Done
--EXPECTF--
SDL version %s extension is available
%d functions defined
Done
