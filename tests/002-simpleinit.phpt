--TEST--
Simple init
--SKIPIF--
<?php
require 'skipif.php';
skip_test_not_complete();
?>
--FILE--
<?php 
var_dump(SDL_Init());
var_dump(SDL_WasInit());
var_dump(SDL_Quit());
?>
Done
--EXPECTF--
int(0)
int(29233)
NULL
Done
