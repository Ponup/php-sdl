--TEST--
Init/Quit subsystem test
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php 
function check($want) {
	echo "+ shoud be $want\n";
	var_dump(SDL_WasInit());
	var_dump(SDL_WasInit(SDL_INIT_TIMER));
	var_dump(SDL_WasInit(SDL_INIT_AUDIO));
}
echo "Init Audio:";
var_dump(SDL_Init(SDL_INIT_AUDIO));
check(SDL_INIT_AUDIO);

echo "Init Timer:";
var_dump(SDL_InitSubSystem(SDL_INIT_TIMER));
check(SDL_INIT_TIMER+SDL_INIT_AUDIO);

echo "Quit Timer:";
var_dump(SDL_QuitSubSystem(SDL_INIT_TIMER));
check(SDL_INIT_AUDIO);

echo "Quit Video:";
var_dump(SDL_QuitSubSystem(SDL_INIT_VIDEO));

echo "Quit:";
var_dump(SDL_Quit());
check(0);
?>
Done
--EXPECTF--
Init Audio:int(0)
+ shoud be 16
int(16)
int(0)
int(16)
Init Timer:int(0)
+ shoud be 17
int(17)
int(1)
int(16)
Quit Timer:NULL
+ shoud be 16
int(16)
int(0)
int(16)
Quit Video:NULL
Quit:NULL
+ shoud be 0
int(0)
int(0)
int(0)
Done
