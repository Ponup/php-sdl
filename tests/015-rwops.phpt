--TEST--
SDL_RWops test, procedural mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip: SDL extension not loaded");
?>
--FILE--
<?php
$p = __DIR__."/tmp.txt";

echo "= Create file\n";
$rw = SDL_RWFromFile($p, "wb");
echo "write:"; var_dump(SDL_RWwrite($rw, "Hello SDL2 world"));
SDL_RWclose($rw);

echo "= Read file\n";
$rw = SDL_RWFromFile($p, "rb");
echo "size:"; var_dump(SDL_RWsize($rw));
echo "seek:"; var_dump(SDL_RWseek($rw, 0, RW_SEEK_SET));
echo "tell:"; var_dump(SDL_RWtell($rw));
echo "read:"; var_dump(SDL_RWread($rw, $buf, 100), $buf);
SDL_FreeRW($rw);

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
= Done
