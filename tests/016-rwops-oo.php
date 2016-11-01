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
