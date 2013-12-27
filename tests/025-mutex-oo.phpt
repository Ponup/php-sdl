--TEST--
mutex group test, object mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "+ Create\n";
var_dump($m=new SDL_Mutex(), "$m");
echo "+ TryLock/Unlock\n";
var_dump($m->TryLock());
var_dump($m->Unlock());
echo "+ Lock/Unlock\n";
var_dump($m->Lock());
var_dump($m->Unlock());
echo "+ Unlock\n";
var_dump($m->Unlock());
echo "+ Destroy\n";
var_dump($m->Destroy(), $m, "$m");
?>
+ Done
--EXPECTF--
+ Create
object(SDL_mutex)#%d (0) {
}
string(23) "SDL_mutex(%s)"
+ TryLock/Unlock
int(0)
int(0)
+ Lock/Unlock
int(0)
int(0)
+ Unlock
int(0)
+ Destroy
NULL
object(SDL_mutex)#%d (0) {
}
string(11) "SDL_mutex()"
+ Done