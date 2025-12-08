<?php
class SDL_Pixels implements Stringable {
    public function __construct(
        public int $pitch,
        public int $h,
    ) {
    }

    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|int {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        int $value
    ): null|false {
        return null;
    }

    public function GetByte(
        int $x,
        int $y,
    ): false|int {
        return false;
    }

    public function SetByte(
        int $x,
        int $y,
        int $value,
    ): false|int {
        return false;
    }

    public function __toString(): string {
        return '';
    }
}
// row 1842