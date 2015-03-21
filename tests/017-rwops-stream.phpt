--TEST--
SDL_RWops test, stream mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
if (getenv("SKIP_ONLINE_TESTS")) die("skip test requiring internet connection");
?>
--FILE--
<?php
echo "= Read Stream\n";
$stream = fopen("http://www.libsdl.org/media/SDL_logo.png", "r");
$ro = SDL_RWFromFP($stream);
echo "size:"; var_dump($size=$ro->size());
echo "read:"; var_dump($ro->read($buf, $size)==$size, strlen($buf)==$size);
$ro->Free();
fclose($stream);
?>
= Done
--CLEAN--
<?php
@unlink(__DIR__."/tmp.txt");
?>
--EXPECTF--
= Read Stream
size:int(20932)
read:bool(true)
bool(true)
= Done
