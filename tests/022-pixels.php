<?php
echo "= Create\n";
try {
	var_dump($pix = new SDL_Pixels(-1, -1));
} catch (Exception $e) {
	echo "Exception: " . $e->getMessage() . "\n";
}
var_dump($pix = new SDL_Pixels(10, 10), "$pix");
echo "= Get/Set\n";
var_dump($pix->GetByte(15,15));
var_dump($pix->SetByte(0,0,1));
var_dump($pix->GetByte(0,0));
var_dump($pix->SetByte(1,1,255));
var_dump($pix->GetByte(1,1));

echo "= Array\n";
var_dump($pix[20], isset($pix[20]), isset($pix[1000]));
var_dump($pix[20]=127);
var_dump($pix[20]);
unset($pix[20]);
var_dump($pix[20]);
?>
= Done
