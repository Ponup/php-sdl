<?php 
echo "SDL_GetCPUCount:         "; var_dump(SDL_GetCPUCount());
echo "SDL_GetCPUCacheLineSize: "; var_dump(SDL_GetCPUCacheLineSize());
echo "SDL_HasRDTSC:            "; var_dump(SDL_HasRDTSC());
echo "SDL_HasAltiVec:          "; var_dump(SDL_HasAltiVec());
echo "SDL_HasMMX:              "; var_dump(SDL_HasMMX());
echo "SDL_Has3DNow:            "; var_dump(SDL_Has3DNow());
echo "SDL_HasSSE:              "; var_dump(SDL_HasSSE());
echo "SDL_HasSSE2:             "; var_dump(SDL_HasSSE2());
echo "SDL_HasSSE3:             "; var_dump(SDL_HasSSE3());
echo "SDL_HasSSE41:            "; var_dump(SDL_HasSSE41());
echo "SDL_HasSSE42:            "; var_dump(SDL_HasSSE42());
echo "SDL_GetSystemRAM:        "; var_dump(SDL_GetSystemRAM());
?>
Done
