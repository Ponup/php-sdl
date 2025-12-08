<?php
class SDL_Cursor implements Stringable {
    const ARROW     = 0;
    const IBEAM     = 1;
    const WAIT      = 2;
    const CROSSHAIR = 3;
    const WAITARROW = 4;
    const SIZENWSE  = 5;
    const SIZENESW  = 6;
    const SIZEWE    = 7;
    const SIZENS    = 8;
    const SIZEALL   = 9;
    const NO        = 10;
    const HAND      = 11;

    /**
     * Create a system cursor.
     * @param  int        $id one of the `SDL_Cursor::*` constants.
     * @return SDL_Cursor
     */
    public static function CreateSystem(int $id):SDL_Cursor {
        return new self(
            '',
            0,
            0,
            0,
            0,
            0,
        );
    }

    public function __construct(
        public string $data,
        public int $mask,
        public int $w,
        public int $h,
        public int $x,
        public int $y,
    ) {
    }

    /**
     * Frees a cursor created with `SDL_CreateCursor()`.
     * @return void
     */
    public function Free():void {
    }

    /**
     * @return void
     */
    public function Set():void {
    }

    public function __toString(): string {
        return '';
    }
}
// row 1224