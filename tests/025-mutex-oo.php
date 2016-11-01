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
