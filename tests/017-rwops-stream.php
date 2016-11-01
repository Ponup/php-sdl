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
