--TEST--
SDL_RWops test, object mode
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
echo "write:"; var_dump($rw->write($memory));
$rw->close();

echo "= Read file\n";
$ro = SDL_RWFromFile($p, "rb");
echo "size:"; var_dump($ro->size());
echo "seek:"; var_dump($ro->seek(0, RW_SEEK_SET));
echo "tell:"; var_dump($ro->tell());
echo "read:"; var_dump($ro->read($buf, 100), $buf);
$ro->Free();

echo "= Read memory\n";
$rm = SDL_RWFromConstMem($memory);
echo "size:"; var_dump($rm->size());
echo "seek:"; var_dump($rm->seek(0, RW_SEEK_SET));
echo "tell:"; var_dump($rm->tell());
echo "read:"; var_dump($rm->read($buf, 100), $buf);
$rm->Free();

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
