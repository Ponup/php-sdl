--TEST--
mutex group test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "+ Create\n";
var_dump($m=SDL_CreateMutex());
echo "+ TryLock/Unlock\n";
var_dump(SDL_TryLockMutex($m));
var_dump(SDL_UnlockMutex($m));
echo "+ Lock/Unlock\n";
var_dump(SDL_LockMutex($m));
var_dump(SDL_UnlockMutex($m));
echo "+ Unlock\n";
var_dump(SDL_UnlockMutex($m));
echo "+ Destroy\n";
var_dump(SDL_DestroyMutex($m), $m);
?>
+ Done
--EXPECTF--
+ Create
object(SDL_mutex)#%d (0) {
}
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
+ Done