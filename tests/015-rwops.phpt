--TEST--
SDL_RWops test, procedural mode
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
echo "write:"; var_dump(SDL_RWwrite($rw, $memory));
SDL_RWclose($rw);

echo "= Read file\n";
$ro = SDL_RWFromFile($p, "rb");
echo "size:"; var_dump(SDL_RWsize($ro));
echo "seek:"; var_dump(SDL_RWseek($ro, 0, RW_SEEK_SET));
echo "tell:"; var_dump(SDL_RWtell($ro));
echo "read:"; var_dump(SDL_RWread($ro, $buf, 100), $buf);
SDL_FreeRW($ro);

echo "= Write memory\n";
$wm = SDL_RWFromMem($buffer, 100);
echo "Buffer:".strlen($buffer)."\n";
echo "write:"; var_dump($l =1*SDL_WriteU8($wm, 0x90));
echo "write:"; var_dump($l+=2*SDL_WriteLE16($wm, 0x1234));
echo "write:"; var_dump($l+=2*SDL_WriteBE16($wm, 0x5678));
echo "write:"; var_dump($l+=4*SDL_WriteLE32($wm, 0x12345678));
echo "write:"; var_dump($l+=4*SDL_WriteBE32($wm, 0x12345678));
echo "Buffer:".strlen($buffer)."\n";
echo "Content:".bin2hex(substr($buffer,0,$l))."\n";
SDL_FreeRW($wm);

echo "= Read memory\n";
$rm = SDL_RWFromConstMem($buffer);
echo "size:"; var_dump($rm->size());
echo "seek:"; var_dump($rm->seek(0, RW_SEEK_SET));
echo "tell:"; var_dump($rm->tell());
printf("read8:    %x\n", SDL_ReadU8($rm));
printf("readLE16: %x\n", SDL_ReadLE16($rm));
printf("readBE16: %x\n", SDL_ReadBE16($rm));
printf("readBE32: %x\n", SDL_ReadLE32($rm));
printf("readBE32: %x\n", SDL_ReadBE32($rm));
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
= Write memory

%s: SDL_RWFromMem(): this function may raised unsupported error with PHP memory in %s/015-rwops.php on line %d
Buffer:100
write:int(1)
write:int(3)
write:int(5)
write:int(9)
write:int(13)
Buffer:100
Content:90341256787856341212345678
= Read memory
size:int(100)
seek:int(0)
tell:int(0)
read8:    90
readLE16: 1234
readBE16: 5678
readBE32: 12345678
readBE32: 12345678
= Done
