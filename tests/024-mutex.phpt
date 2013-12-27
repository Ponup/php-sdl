--TEST--
mutex group test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "++ Mutex\n";
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

echo "++ Semaphore\n";
echo "+ Create\n";
var_dump($s=SDL_CreateSemaphore(0));
echo "+ WaitTimeout\n",
var_dump(SDL_SemWaitTimeout($s, 10));
echo "+ Post\n",
var_dump(SDL_SemPost($s));
echo "+ Value\n",
var_dump(SDL_SemValue($s));
echo "+ WaitTimeout\n",
var_dump(SDL_SemWaitTimeout($s, 10));
echo "+ TryWait\n",
var_dump(SDL_SemTryWait($s));
echo "+ Post\n",
var_dump(SDL_SemPost($s));
echo "+ Wait\n",
var_dump(SDL_SemWait($s));
echo "+ Destroy\n";
var_dump(SDL_DestroySemaphore($s), $s);


?>
+ Done
--EXPECTF--
++ Mutex
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
++ Semaphore
+ Create
object(SDL_sem)#%d (0) {
}
+ WaitTimeout
int(1)
+ Post
int(0)
+ Value
int(1)
+ WaitTimeout
int(0)
+ TryWait
int(1)
+ Post
int(0)
+ Wait
int(0)
+ Destroy
NULL
object(SDL_sem)#%d (0) {
}
+ Done