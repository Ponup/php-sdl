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
