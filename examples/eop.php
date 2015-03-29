<?php
/* Check prerequesites */
if (!extension_loaded("sdl")) die("SDL extension not loaded");
if (!extension_loaded("imagick")) die("Imagick extension not loaded");
if (version_compare(phpversion("sdl"), "2.0.0-dev", '<')) die("skip: SDL extension >= 2.0.0 required");

/* Arguments */
if (!isset($_SERVER['argv'][1])) {
	die("Missing image path\n");

} else if (!is_file($path=$_SERVER['argv'][1])) {
	die("Bad path '$path'\n");
}

/* Load/Convert the file using Imagic */
try {
	$image = new Imagick(realpath($path));
	$image->setFormat("bmp");
} catch (Exception $e) {
	die($e->getMessage()."\n");
}

/* Imagic to SDL */
$rwops = SDL_RWFromConstMem($image);
$sdlim = SDL_LoadBMP_RW($rwops, 1);

/* Display */
SDL_VideoInit();
SDL_GetDisplayBounds(0, $max);

/* Compute window size/position */
$ww = $w = $sdlim->w;
$wh = $h = $sdlim->h;

$mw = $max->w * 0.9;
$mh = $max->h * 0.9;
if ($w>$mw || $h>$mh) {
	$tw = $w / $mw;
	$th = $h / $mh;
	if ($tw > $th) {
		$ww = round($w / $tw);
		$wh = round($h / $tw);
	} else {
		$ww = round($w / $th);
		$wh = round($h / $th);
	}
}

/* Load PHP Logo */
$logo = SDL_LoadBMP('compress.zlib://'.__DIR__.'/php.bmp.gz');

/* Display */
$wind = new SDL_Window("EOP - $path - ${w}x{$h}", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, $ww, $wh, SDL_Window::SHOWN);
$wind->SetIcon($logo);
$sdlim->Blit(NULL, $wind->GetSurface());
$wind->UpdateSurface();

SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Eye Of PHP", $msg, $wind);

SDL_VideoQuit();
