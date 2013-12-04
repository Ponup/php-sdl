<?php
/**
 * Example of how to capture keyboard events and update the screen accordingly with the PHP-SDL extension.
 *
 * @author Santiago Lizardo <santiagolizardo@php.net>
 */

if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
{
	die( SDL_GetError() );
}

$screen = SDL_SetVideoMode( 640, 480, 8, SDL_HWSURFACE | SDL_DOUBLEBUF );
if( null === $screen )
{
	die( SDL_GetError() );
}

SDL_WM_SetCaption( $title = 'PHP-SDL keyboard events', $title );

$boxColor = SDL_MapRGB( $screen['format'], 0xef, 0xff, 0x87 );
$bgColor = SDL_MapRGB( $screen['format'], 0, 0, 0 );

$x = 35.0;
$y = 35.0;
$speed = 100;
$rect = array(
	'w' => 25,
	'h' => 20,
);

$currentTime = SDL_GetTicks();
while( true )
{
	if( SDL_PollEvent( $event ) )
	{
		if( in_array( $event['type'], [ SDL_MOUSEBUTTONDOWN, SDL_QUIT ] ) ) break;
	}

	$oldTime = $currentTime;
	$currentTime = SDL_GetTicks();
	$deltaTime = ( $currentTime - $oldTime ) / 1000.0;

	// Checks what keys (if any) the user has pressed down.
	$keys = SDL_GetKeyState($numKeys);
	if( $keys[SDLK_LEFT] )
		$x -= $speed * $deltaTime;
	if( $keys[SDLK_RIGHT] )
		$x += $speed * $deltaTime;
	if( $keys[SDLK_DOWN] )
		$y += $speed * $deltaTime;
	if( $keys[SDLK_UP] )
		$y -= $speed * $deltaTime;

	if( $keys[SDLK_ESCAPE] )
		break;

	// Resets the background.
	SDL_FillRect( $screen, null, $bgColor );

	// Draws the yellow box on its new position.
	$rect['x'] = $x;
	$rect['y'] = $y;
	SDL_FillRect( $screen, $rect, $boxColor );

	SDL_Flip( $screen );
}

SDL_Quit();

