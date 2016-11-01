<?php

require 'bootstrap.php';

$event = new SDL_Event();
var_dump($event); // Shows public properties
// Demonstrates how the __toString method works
echo strval($event), PHP_EOL;

