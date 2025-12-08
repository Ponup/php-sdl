<?php
class SDL_MessageBoxButtonData implements Stringable {
    const RETURNKEY_DEFAULT = 0x00000001;
    const ESCAPEKEY_DEFAULT = 0x00000002;

    public function __construct(
        public int $flags,
        public int $id,
        public string $text,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1130