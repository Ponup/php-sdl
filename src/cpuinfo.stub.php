<?php

/**
 * This function returns the number of CPU cores available.
 * @return int
 */
function SDL_GetCPUCount():int {
    return 0;
}

/**
 * This function returns the L1 cache line size of the CPU
 *
 * This is useful for determining multi-threaded structure padding or SIMD prefetch sizes.
 * @return int
 */
function SDL_GetCPUCacheLineSize():int {
    return 0;
}


/**
 * This function returns true if the CPU has the RDTSC instruction.
 * @return int
 */
function SDL_HasRDTSC():int {
    return 0;
}

/**
 * This function returns true if the CPU has AltiVec features.
 * @return int
 */
function SDL_HasAltiVec():int {
    return 0;
}

/**
 * This function returns true if the CPU has MMX features.
 * @return int
 */
function SDL_HasMMX():int {
    return 0;
}

/**
 * This function returns true if the CPU has 3DNow! features.
 * @return int
 */
function SDL_Has3DNow():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE features.
 * @return int
 */
function SDL_HasSSE():int {
    return 0;
}

/**
 * This function returns true if the CPU has HasSSE2 features.
 * @return int
 */
function SDL_HasSSE2():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE3 features.
 * @return int
 */
function SDL_HasSSE3():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.1 features.
 * @return int
 */
function SDL_HasSSE41():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.2 features.
 * @return int
 */
function SDL_HasSSE42():int {
    return 0;
}

/**
 * This function returns the amount of RAM configured in the system, in MB.
 * @return int
 */
function SDL_GetSystemRAM():int {
    return 0;
}