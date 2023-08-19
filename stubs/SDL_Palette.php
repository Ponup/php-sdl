<?php
class SDL_Palette implements Stringable {
    public function __construct(
        public int $ncolors,
    ) {
    }

    
    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|SDL_Color {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        SDL_Color $value
    ): null|false {
        return null;
    }

    public function __toString(): string {
        return '';
    }
}
// row 1383