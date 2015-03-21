--TEST--
SDL_RWops test, object mode
--SKIPIF--
<?php
if (!extension_loaded("sdl")) die("skip SDL extension not loaded");
?>
--FILE--
<?php
$p = __DIR__."/tmp.txt";
$memory = "Hello SDL2 world";

echo "= Create file\n";
$rw = SDL_RWFromFile($p, "wb");
var_dump("$rw");
echo "write:"; var_dump($rw->write($memory));
$rw->close();

echo "= Read file\n";
$ro = SDL_RWFromFile($p, "rb");
var_dump("$ro");
echo "size:"; var_dump($ro->size());
echo "seek:"; var_dump($ro->seek(0, RW_SEEK_SET));
echo "tell:"; var_dump($ro->tell());
echo "read:"; var_dump($ro->read($buf, 100), $buf);
$ro->Free();

echo "= Write memory\n";
$wm = SDL_RWFromMem($buffer, 100);
var_dump("$wm");
echo "Buffer:".strlen($buffer)."\n";
echo "write:"; var_dump($l =1*$wm->writeU8(0x90));
echo "write:"; var_dump($l+=2*$wm->writeLE16(0x1234));
echo "write:"; var_dump($l+=2*$wm->writeBE16(0x5678));
echo "write:"; var_dump($l+=4*$wm->writeLE32(0x12345678));
echo "write:"; var_dump($l+=4*$wm->writeBE32(0x12345678));
echo "Buffer:".strlen($buffer)."\n";
echo "Content:".bin2hex(substr($buffer,0,$l))."\n";
$wm->Free();

echo "= Read memory\n";
$rm = SDL_RWFromConstMem($buffer);
var_dump("$rm");
echo "size:"; var_dump($rm->size());
echo "seek:"; var_dump($rm->seek(0, RW_SEEK_SET));
echo "tell:"; var_dump($rm->tell());
printf("read8:    %x\n", $rm->ReadU8());
printf("readLE16: %x\n", $rm->ReadLE16());
printf("readBE16: %x\n", $rm->ReadBE16());
printf("readBE32: %x\n", $rm->ReadLE32());
printf("readBE32: %x\n", $rm->ReadBE32());
$rm->Free();


?>
= Done
--CLEAN--
<?php
@unlink(__DIR__."/tmp.txt");
?>
--EXPECTF--
= Create file
string(23) "SDL_RWops("Stdio file")"
write:int(16)
= Read file
string(23) "SDL_RWops("Stdio file")"
size:int(16)
seek:int(0)
tell:int(0)
read:int(16)
string(16) "Hello SDL2 world"
= Write memory

%s: SDL_RWFromMem(): this function may raised unsupported error with PHP memory in %s/016-rwops-oo.php on line %d
string(26) "SDL_RWops("Memory stream")"
Buffer:100
write:int(1)
write:int(3)
write:int(5)
write:int(9)
write:int(13)
Buffer:100
Content:90341256787856341212345678
= Read memory
string(36) "SDL_RWops("Read only memory stream")"
size:int(100)
seek:int(0)
tell:int(0)
read8:    90
readLE16: 1234
readBE16: 5678
readBE32: 12345678
readBE32: 12345678
= Done
