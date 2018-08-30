--TEST--
Extension is loaded.
Check for SDL presence
--SKIPIF--
<?php
require 'skipif.php';
--FILE--
<?php
echo 'SDL extension version: ', phpversion('sdl'), PHP_EOL;

$ext = new ReflectionExtension('sdl');

$numFunctions = count($ext->getFunctions());
if($numFunctions)
	echo "$numFunctions functions defined", PHP_EOL;
else
	echo 'no functions defined', PHP_EOL;

$numClasses = count($ext->getClasses());
if($numClasses)
	echo "$numClasses classes defined", PHP_EOL;
else
	echo 'no functions defined', PHP_EOL;

$numConstants = count($ext->getConstants());
if($numConstants)
	echo "$numConstants constants defined", PHP_EOL;
else
	echo 'no constants defined', PHP_EOL;
--EXPECTF--
SDL extension version: %s
%d functions defined
%d classes defined
%d constants defined
