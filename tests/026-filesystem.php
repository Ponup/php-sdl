<?php
$prefPath = SDL_GetPrefPath('my_org', 'my_app');
var_dump(strpos($prefPath, 'my_org') !== false);
var_dump(strpos($prefPath, 'my_app') !== false);
$basePath = SDL_GetBasePath();
var_dump(strpos($basePath, DIRECTORY_SEPARATOR) !== false);
?>
+ Done
