<?php
echo "+ start\n";
var_dump(SDL_GetError());
echo "+ set\n";
var_dump(SDL_SetError("Foo"));
var_dump(SDL_GetError());
echo "+ clear\n";
var_dump(SDL_ClearError());
var_dump(SDL_GetError());
?>
Done
