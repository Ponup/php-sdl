<?php
class SDL_Window implements Stringable {
    const FULLSCREEN         = 0x00000001;
    const OPENGL             = 0x00000002;
    const SHOWN              = 0x00000004;
    const HIDDEN             = 0x00000008;
    const BORDERLESS         = 0x00000010;
    const RESIZABLE          = 0x00000020;
    const MINIMIZED          = 0x00000040;
    const MAXIMIZED          = 0x00000080;
    const INPUT_GRABBED      = 0x00000100;
    const INPUT_FOCUS        = 0x00000200;
    const MOUSE_FOCUS        = 0x00000400;
    const FULLSCREEN_DESKTOP = ( SDL_Window::FULLSCREEN | 0x00001000 );
    const FOREIGN            = 0x00000800;
    const ALLOW_HIGHDPI      = 0x00002000;

    public int $event;

    public function __construct(
        public string $title,
        public int $x,
        public int $y,
        public int $w,
        public int $h,
        public int $flags,
    ) {
    }

    public function setTitle(string $title):void {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1166