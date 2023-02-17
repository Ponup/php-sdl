<?php
class SDL_mutex implements Stringable {
    public function __toString(): string {
        return '';
    }
}


/**
 * Create a mutex, initialized unlocked.
 * @return SDL_mutex
 */
function SDL_CreateMutex():SDL_mutex {
    return new SDL_mutex;
}

/**
 * Lock the mutex.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_LockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Try to lock the mutex
 * @param  SDL_mutex $mutex
 * @return int       0, SDL_MUTEX_TIMEDOUT, or -1 on error
 */
function SDL_TryLockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Unlock the mutex.
 * 
 * WARNING: It is an error to unlock a mutex that has not been locked by the current thread, and doing so results in undefined behavior.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_UnlockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Destroy a mutex.
 * @param  SDL_mutex $mutex
 * @return void
 */
function SDL_DestroyMutex(SDL_mutex $mutex):void {
}

class SDL_sem implements Stringable {
    public function __construct(
        public int $value
    ) {
    }

    public function __toString(): string {
        return '';
    }
}


/**
 * Create a semaphore, initialized with value, returns NULL on failure.
 * @param  int          $value
 * @return null|SDL_sem
 */
function SDL_CreateSemaphore(int $value): null|SDL_sem {
    return null;
}

/**
 * This function suspends the calling thread until the semaphore pointed to by `$sem` has a positive count.
 * It then atomically decreases the semaphore count.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemWait(SDL_sem $sem):int {
    return 0;
}


/**
 * Non-blocking variant of SDL_SemWait().
 * @param  SDL_sem $sem
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait would block, and -1 on error.
 */
function SDL_SemTryWait(SDL_sem $sem):int {
    return 0;
}

/**
 * Atomically increases the semaphore's count (not blocking).
 * @param  SDL_sem $sem
 * @return int     0, or -1 on error.
 */
function SDL_SemPost(SDL_sem $sem):int {
    return 0;
}

/**
 * Returns the current count of the semaphore.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemValue(SDL_sem $sem):int {
    return 0;
}

/**
 * Variant of SDL_SemWait() with a timeout in milliseconds.
 * 
 * On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_sem $sem
 * @param  int     $ms
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait does not succeed in the allotted time, and -1 on error.
 */
function SDL_SemWaitTimeout(SDL_sem $sem, int $ms):int {
    return 0;
}

/**
 * Destroy a semaphore.
 * @param  SDL_sem $sem
 * @return void
 */
function SDL_DestroySemaphore(SDL_sem $sem):void {
}

class SDL_cond implements Stringable {
    public function __construct(
        public int $value
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

/**
 * Create a condition variable.
 * 
 * Typical use of condition variables:
 *
 * Thread A:
 * ```c
 * SDL_LockMutex(lock);
 * while ( ! condition ) {
 *     SDL_CondWait(cond, lock);
 * }
 * SDL_UnlockMutex(lock);
 * ```
 *
 * Thread B:
 * ```c
 * SDL_LockMutex(lock);
 * ...
 * condition = true;
 * ...
 * SDL_CondSignal(cond);
 * SDL_UnlockMutex(lock);
 * ```
 *
 * There is some discussion whether to signal the condition variable
 * with the mutex locked or not.  There is some potential performance
 * benefit to unlocking first on some platforms, but there are some
 * potential race conditions depending on how your code is structured.
 * 
 * In general it's safer to signal the condition variable while the
 * mutex is locked.
 * @param  int      $value
 * @return SDL_cond
 */
function SDL_CreateCond(int $value):SDL_cond {
    return new SDL_cond(0);
}

/**
 * Wait on the condition variable, unlocking the provided mutex.
 * 
 * WARNING: The mutex must be locked before entering this function!
 * 
 * The mutex is re-locked once the condition variable is signaled.
 * @param  SDL_cond  $condition
 * @param  SDL_mutex $mutex
 * @return int       0 when it is signaled, or -1 on error.
 */
function SDL_CondWait(
    SDL_cond $condition,
    SDL_mutex $mutex
):int {
    return 0;
}

/**
 * Restart one of the threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondSignal(SDL_cond $cond):int {
    return 0;
}

/**
 * Restart all threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondBroadcast(SDL_cond $cond):int {
    return 0;
}

/**
 * Waits for at most \c ms milliseconds, and returns 0 if the condition variable is signaled, `SDL_MUTEX_TIMEDOUT` if the condition is not signaled in the allotted time, and -1 on error.
 * 
 * WARNING: On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_cond  $cond
 * @param  SDL_mutex $mutex
 * @param  int       $ms
 * @return int
 */
function SDL_CondWaitTimeout(SDL_cond $cond, SDL_mutex $mutex, int $ms):int {
    return 0;
}

/**
 * Destroy a condition variable.
 * @param  SDL_cond $cond
 * @return void
 */
function SDL_DestroyCond(SDL_cond $cond):void {
}