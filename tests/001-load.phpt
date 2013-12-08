--TEST--
Check for SDL presence
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php 
echo "SDL version ".phpversion("sdl"). " extension is available\n";
$r = new ReflectionExtension("sdl");

$n = count($r->getFunctions());
echo "$n functions defined (".($n ? 'ok' : 'ko').")\n";

$n = count($r->getClasses());
echo "$n classes defined (".($n ? 'ok' : 'ko').")\n";

$n = count($r->getConstants());
echo "$n constants defined (".($n ? 'ok' : 'ko').")\n";
?>
Done
--EXPECTF--
SDL version %s extension is available
%d functions defined (ok)
%d classes defined (ok)
%d constants defined (ok)
Done
