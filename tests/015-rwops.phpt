--TEST--
SDL_RWops test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php
$p = __DIR__."/tmp.txt";
$memory = "Hello SDL2 world";

echo "= Create file\n";
$rw = SDL_RWFromFile($p, "wb");
echo "write:"; var_dump(SDL_RWwrite($rw, $memory));
SDL_RWclose($rw);

echo "= Read file\n";
$ro = SDL_RWFromFile($p, "rb");
echo "size:"; var_dump(SDL_RWsize($ro));
echo "seek:"; var_dump(SDL_RWseek($ro, 0, RW_SEEK_SET));
echo "tell:"; var_dump(SDL_RWtell($ro));
echo "read:"; var_dump(SDL_RWread($ro, $buf, 100), $buf);
SDL_FreeRW($ro);

echo "= Read memory\n";
$rm = SDL_RWFromConstMem($memory);
echo "size:"; var_dump(SDL_RWsize($rm));
echo "seek:"; var_dump(SDL_RWseek($rm, 0, RW_SEEK_SET));
echo "tell:"; var_dump(SDL_RWtell($rm));
echo "read:"; var_dump(SDL_RWread($rm, $buf, 100), $buf);
SDL_FreeRW($rm);

?>
= Done
--CLEAN--
<?php
@unlink(__DIR__."/tmp.txt");
?>
--EXPECTF--
= Create file
write:int(16)
= Read file
size:int(16)
seek:int(0)
tell:int(0)
read:int(16)
string(16) "Hello SDL2 world"
= Read memory
size:int(16)
seek:int(0)
tell:int(0)
read:int(16)
string(16) "Hello SDL2 world"
= Done
