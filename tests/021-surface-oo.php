<?php
echo "= Create Palette\n";
$spal = new SDL_Surface(0, 150, 100, 8, 0, 0, 0, 0);
var_dump("$spal");
var_dump($spal->w, $spal->h, $spal->format->palette->ncolors, $spal->pixels);

echo "= Create True colors\n";
$scol = new SDL_Surface(0, 150, 100, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
var_dump("$scol");
var_dump($scol->w, $scol->h, $scol->format->palette, $scol->pixels);

echo "= Lock\n";
var_dump($spal->MustLock(), $spal->locked);
var_dump($spal->Lock(), $spal->locked);
var_dump($spal->Unlock(), $spal->locked);

echo "= ColorKey\n";
var_dump($spal->SetColorKey(1, 127));
var_dump($spal->GetColorKey($key), $key);
var_dump($spal->SetColorKey(0));
var_dump($spal->GetColorKey($key));

echo "= ColorMod\n";
var_dump($scol->SetColorMod(1, 2, 3));
var_dump($scol->GetColorMod($r, $g, $b), $r, $g, $b);

echo "= AlphaMod\n";
var_dump($scol->SetAlphaMod(4));
var_dump($scol->GetAlphaMod($a), $a);

echo "= BlendMode\n";
var_dump($scol->SetBlendMode(SDL_BLENDMODE_ADD));
var_dump($scol->GetBlendMode($a), $a==SDL_BLENDMODE_ADD);

echo "= ClipRect\n";
var_dump($scol->SetClipRect(new SDL_Rect(10,20,30,40)));
var_dump($scol->GetClipRect($rect), $rect);
var_dump($scol->clip_rect);

echo "= Convert\n";
$conv = $spal->Convert($scol->format);
var_dump($scol->format->format == $conv->format->format);
$conv = $spal->ConvertFormat($scol->format->format);
var_dump($scol->format->format == $conv->format->format);

echo "= Free\n";
$scol->Free()
?>
= Done
