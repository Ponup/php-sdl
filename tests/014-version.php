<?php
echo '= Constants', PHP_EOL;
var_dump(is_integer(SDL_COMPILEDVERSION));
var_dump(SDL_COMPILEDVERSION > 0);
var_dump(is_integer(SDL_MAJOR_VERSION));
var_dump(SDL_MAJOR_VERSION > 0);
var_dump(is_integer(SDL_MINOR_VERSION));
var_dump(SDL_MINOR_VERSION >= 0);
var_dump(is_integer(SDL_PATCHLEVEL));
var_dump(SDL_PATCHLEVEL >= 0);
var_dump(empty(SDL_REVISION));
var_dump(is_string(SDL_REVISION));

echo '= Functions', PHP_EOL;
SDL_VERSION($version);
var_dump(array_key_exists('major', $version) && array_key_exists('minor', $version) && array_key_exists('patch', $version));
var_dump(12030 === SDL_VERSIONNUM(10,20,30));
var_dump(SDL_VERSION_ATLEAST(2,0,0));
var_dump(SDL_VERSION_ATLEAST(2,0,5));
var_dump(is_string(SDL_GetRevision()));
var_dump(is_integer(SDL_GetRevisionNumber()));

echo '= Done', PHP_EOL;
?>
