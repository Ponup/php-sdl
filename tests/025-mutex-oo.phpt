--TEST--
mutex group test, object mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
echo "++ Mutex\n";
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

echo "++ Semaphore\n";
echo "+ Create\n";
var_dump($s=new SDL_sem(0), "$s");
echo "+ WaitTimeout\n",
var_dump($s->WaitTimeout(10));
echo "+ Post\n",
var_dump($s->Post());
echo "+ Value\n",
var_dump($s->Value());
echo "+ WaitTimeout\n",
var_dump($s->WaitTimeout(10));
echo "+ TryWait\n",
var_dump($s->TryWait());
echo "+ Post\n",
var_dump($s->Post());
echo "+ Wait\n",
var_dump($s->Wait());
echo "+ Destroy\n";
var_dump(SDL_DestroySemaphore($s), $s, "$s");

?>
+ Done
--EXPECTF--
++ Mutex
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
++ Semaphore
+ Create
object(SDL_sem)#%d (0) {
}
string(21) "SDL_sem(%s)"
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
string(9) "SDL_sem()"
+ Done