<?php
class SDL_MessageBoxData implements Stringable {
    const ERROR       = 0x00000010;
    const WARNING     = 0x00000020;
    const INFORMATION = 0x00000040;

    public function __construct(
        public int $flags,
        public string $title,
        public string $message,
        public array $buttons = [],
        public array $colors = [],
        public null|SDL_Window $window = null,
    ) {
    }

    public function Show(int &$id):int {
        return 0;
    }
    
    public function __toString(): string {
        return '';
    }
}
// row 1094