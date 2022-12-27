/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

#include "mutex.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_class_entry *php_sdl_mutex_ce;
static zend_object_handlers php_sdl_mutex_handlers;
struct php_sdl_mutex {
	zend_object   zo;
	SDL_mutex    *mutex;
	Uint32        flags;
};

static zend_class_entry *php_sdl_sem_ce;
static zend_object_handlers php_sdl_sem_handlers;
struct php_sdl_sem {
	zend_object   zo;
	SDL_sem      *sem;
	Uint32        flags;
};


static zend_class_entry *php_sdl_cond_ce;
static zend_object_handlers php_sdl_cond_handlers;
struct php_sdl_cond {
	zend_object   zo;
	SDL_cond     *cond;
	Uint32        flags;
};


/* {{{ get_php_sdl_mutex_ce */
zend_class_entry *get_php_sdl_mutex_ce(void)
{
	return php_sdl_mutex_ce;
}
/* }}} */


/* {{{ get_php_sdl_sem_ce */
zend_class_entry *get_php_sdl_sem_ce(void)
{
	return php_sdl_sem_ce;
}
/* }}} */


/* {{{ get_php_sdl_cond_ce */
zend_class_entry *get_php_sdl_cond_ce(void)
{
	return php_sdl_cond_ce;
}
/* }}} */


#define FETCH_MUTEX(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_mutex *)Z_OBJ_P(__id);\
        __ptr = intern->mutex; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}


#define FETCH_SEM(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_sem *)Z_OBJ_P(__id);\
        __ptr = intern->sem; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}


#define FETCH_COND(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_cond *)Z_OBJ_P(__id);\
        __ptr = intern->cond; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}


/* {{{ sdl_mutex_to_zval */
zend_bool sdl_mutex_to_zval(SDL_mutex *mutex, zval *z_val, Uint32 flags)
{
	if (mutex) {
		struct php_sdl_mutex *intern;

		object_init_ex(z_val, php_sdl_mutex_ce);
		intern = (struct php_sdl_mutex *)Z_OBJ_P(z_val);
		intern->mutex = mutex;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ sdl_sem_to_zval */
zend_bool sdl_sem_to_zval(SDL_sem *sem, zval *z_val, Uint32 flags)
{
	if (sem) {
		struct php_sdl_sem *intern;

		object_init_ex(z_val, php_sdl_sem_ce);
		intern = (struct php_sdl_sem *)Z_OBJ_P(z_val);
		intern->sem   = sem;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ sdl_cond_to_zval */
zend_bool sdl_cond_to_zval(SDL_cond *cond, zval *z_val, Uint32 flags)
{
	if (cond) {
		struct php_sdl_cond *intern;

		object_init_ex(z_val, php_sdl_cond_ce);
		intern = (struct php_sdl_cond *)Z_OBJ_P(z_val);
		intern->cond  = cond;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ zval_to_sdl_mutex */
SDL_mutex *zval_to_sdl_mutex(zval *z_val)
{
	struct php_sdl_mutex *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_mutex_ce) {
		intern = (struct php_sdl_mutex *)Z_OBJ_P(z_val);
		return intern->mutex;
	}
	return NULL;
}
/* }}} */


/* {{{ zval_to_sdl_sem */
SDL_sem *zval_to_sdl_sem(zval *z_val)
{
	struct php_sdl_sem *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_sem_ce) {
		intern = (struct php_sdl_sem *)Z_OBJ_P(z_val);
		return intern->sem;
	}
	return NULL;
}
/* }}} */


/* {{{ zval_to_sdl_cond */
SDL_cond *zval_to_sdl_cond(zval *z_val)
{
	struct php_sdl_cond *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_cond_ce) {
		intern = (struct php_sdl_cond *)Z_OBJ_P(z_val);
		return intern->cond;
	}
	return NULL;
}
/* }}} */


/* {{{ php_sdl_mutex_free */
static void php_sdl_mutex_free(zend_object *object)
{
	struct php_sdl_mutex *intern = (struct php_sdl_mutex *) object;

	if (intern->mutex) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_DestroyMutex(intern->mutex);
		}
	}

	zend_object_std_dtor(&intern->zo);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_sem_free */
static void php_sdl_sem_free(zend_object *object)
{
	struct php_sdl_sem *intern = (struct php_sdl_sem *) object;

	if (intern->sem) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_DestroySemaphore(intern->sem);
		}
	}

	zend_object_std_dtor(&intern->zo);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_cond_free */
static void php_sdl_cond_free(zend_object *object)
{
	struct php_sdl_cond *intern = (struct php_sdl_cond *) object;

	if (intern->cond) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_DestroyCond(intern->cond);
		}
	}

	zend_object_std_dtor(&intern->zo);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_mutex_new */
static zend_object* php_sdl_mutex_new(zend_class_entry *class_type)
{
	struct php_sdl_mutex *intern;

	intern = ecalloc(1, sizeof(struct php_sdl_mutex));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->mutex = NULL;
	intern->zo.handlers = (zend_object_handlers *) &php_sdl_mutex_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ php_sdl_sem_new */
static zend_object* php_sdl_sem_new(zend_class_entry *class_type)
{
	struct php_sdl_sem *intern;

	intern = ecalloc(1, sizeof(struct php_sdl_sem));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->sem = NULL;
	intern->zo.handlers = (zend_object_handlers *) &php_sdl_sem_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ php_sdl_cond_new */
static zend_object* php_sdl_cond_new(zend_class_entry *class_type)
{
	struct php_sdl_cond *intern;

	intern = ecalloc(1, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->cond = NULL;
	intern->zo.handlers = (zend_object_handlers *) &php_sdl_cond_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ proto SDL_mutex::__construct(void) */
static PHP_METHOD(SDL_mutex, __construct)
{
	struct php_sdl_mutex *intern;
	zend_error_handling error_handling;

	intern = (struct php_sdl_mutex *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	  intern->mutex = SDL_CreateMutex();
	  if (intern->mutex) {
		  intern->flags = 0;
	  } else {
		  zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	  }
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Mutex___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_mutex::__toString() */
static PHP_METHOD(SDL_mutex, __toString)
{
	struct php_sdl_mutex *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_mutex *)Z_OBJ_P(getThis());
	if (intern->mutex) {
		spprintf(&buf, 100, "SDL_mutex(%lx)", (long)intern->mutex);
		RETVAL_STRING(buf);
	} else {
		RETVAL_STRING("SDL_mutex()");
	}
}
/* }}} */


/* {{{ proto SDL_mutex SDL_CreateMutex(void)

 *  Create a mutex, initialized unlocked.
 extern DECLSPEC SDL_mutex *SDLCALL SDL_CreateMutex(void);
 */
PHP_FUNCTION(SDL_CreateMutex)
{
	SDL_mutex *mutex;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	mutex = SDL_CreateMutex();
	sdl_mutex_to_zval(mutex, return_value, 0);
}
/* }}} */


/* {{{ proto int SDL_LockMutex(SDL_mutex mutex)

 *  Lock the mutex.
 *
 *  \return 0, or -1 on error.
 define SDL_mutexP(m)   SDL_LockMutex(m)
 extern DECLSPEC int SDLCALL SDL_LockMutex(SDL_mutex * mutex);
 */
PHP_FUNCTION(SDL_LockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_MUTEX(mutex, z_mutex, 1);

	RETVAL_LONG(SDL_LockMutex(intern->mutex));
}
/* }}} */


/* {{{ proto int SDL_TryLockMutex(SDL_mutex mutex)

 *  Try to lock the mutex
 *
 *  \return 0, SDL_MUTEX_TIMEDOUT, or -1 on error
 extern DECLSPEC int SDLCALL SDL_TryLockMutex(SDL_mutex * mutex);
 */
PHP_FUNCTION(SDL_TryLockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_MUTEX(mutex, z_mutex, 1);

	RETVAL_LONG(SDL_TryLockMutex(intern->mutex));
}
/* }}} */


/* {{{ proto int SDL_UnlockMutex(SDL_mutex mutex)

 *  Unlock the mutex.
 *
 *  \return 0, or -1 on error.
 *
 *  \warning It is an error to unlock a mutex that has not been locked by
 *           the current thread, and doing so results in undefined behavior.
 define SDL_mutexV(m)   SDL_UnlockMutex(m)
 extern DECLSPEC int SDLCALL SDL_UnlockMutex(SDL_mutex * mutex);
 */
PHP_FUNCTION(SDL_UnlockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_MUTEX(mutex, z_mutex, 1);

	RETVAL_LONG(SDL_UnlockMutex(intern->mutex));
}
/* }}} */


/* {{{ proto void SDL_DestroyMutex(SDL_mutex mutex)

 *  Destroy a mutex.
 extern DECLSPEC void SDLCALL SDL_DestroyMutex(SDL_mutex * mutex);
 */
PHP_FUNCTION(SDL_DestroyMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_MUTEX(mutex, z_mutex, 1);
	SDL_DestroyMutex(mutex);
	intern->mutex = NULL;
}
/* }}} */



/* {{{ proto SDL_sem::__construct(int value) */
static PHP_METHOD(SDL_sem, __construct)
{
	struct php_sdl_sem *intern;
	zend_error_handling error_handling;
	zend_long value;

	intern = (struct php_sdl_sem *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "l", &value)) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	intern->sem = SDL_CreateSemaphore((Uint32)value);
	if (intern->sem) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Sem___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_sem::__toString() */
static PHP_METHOD(SDL_sem, __toString)
{
	struct php_sdl_sem *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_sem *)Z_OBJ_P(getThis());
	if (intern->sem) {
		spprintf(&buf, 100, "SDL_sem(%lx)", (long)intern->sem);
		RETVAL_STRING(buf);
	} else {
		RETVAL_STRING("SDL_sem()");
	}
}
/* }}} */


/* {{{ proto SDL_sem SDL_CreateSemaphore(int value)

 *  Create a semaphore, initialized with value, returns NULL on failure.
 extern DECLSPEC SDL_sem *SDLCALL SDL_CreateSemaphore(Uint32 initial_value);
 */
PHP_FUNCTION(SDL_CreateSemaphore)
{
	SDL_sem *sem;
	zend_long value;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "l", &value)) {
		return;
	}
	sem = SDL_CreateSemaphore((Uint32)value);
	sdl_sem_to_zval(sem, return_value, 0);
}
/* }}} */


/* {{{ proto int SDL_SemWait(SDL_sem sem)

 *  This function suspends the calling thread until the semaphore pointed
 *  to by \c sem has a positive count. It then atomically decreases the
 *  semaphore count.
 extern DECLSPEC int SDLCALL SDL_SemWait(SDL_sem * sem);
 */
PHP_FUNCTION(SDL_SemWait)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_sem, php_sdl_sem_ce) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);

	RETVAL_LONG(SDL_SemWait(intern->sem));
}
/* }}} */


/* {{{ proto int SDL_SemTryWait(SDL_sem sem)

 *  Non-blocking variant of SDL_SemWait().
 *
 *  \return 0 if the wait succeeds, ::SDL_MUTEX_TIMEDOUT if the wait would
 *          block, and -1 on error.
 extern DECLSPEC int SDLCALL SDL_SemTryWait(SDL_sem * sem);
 */
PHP_FUNCTION(SDL_SemTryWait)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_sem, php_sdl_sem_ce) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);

	RETVAL_LONG(SDL_SemTryWait(intern->sem));
}
/* }}} */


/* {{{ proto int SDL_SemPost(SDL_sem sem)

 *  Atomically increases the semaphore's count (not blocking).
 *
 *  \return 0, or -1 on error.
 extern DECLSPEC int SDLCALL SDL_SemPost(SDL_sem * sem);
 */
PHP_FUNCTION(SDL_SemPost)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_sem, php_sdl_sem_ce) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);

	RETVAL_LONG(SDL_SemPost(intern->sem));
}
/* }}} */


/* {{{ proto int SDL_SemValue(SDL_sem sem)

 *  Returns the current count of the semaphore.
 extern DECLSPEC Uint32 SDLCALL SDL_SemValue(SDL_sem * sem);
 */
PHP_FUNCTION(SDL_SemValue)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_sem, php_sdl_sem_ce) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);

	RETVAL_LONG(SDL_SemValue(intern->sem));
}
/* }}} */

/* {{{ proto int SDL_SemWaitTimeout(SDL_sem sem, int ms)

 *  Variant of SDL_SemWait() with a timeout in milliseconds.
 *
 *  \return 0 if the wait succeeds, ::SDL_MUTEX_TIMEDOUT if the wait does not
 *          succeed in the allotted time, and -1 on error.
 *
 *  \warning On some platforms this function is implemented by looping with a
 *           delay of 1 ms, and so should be avoided if possible.
 extern DECLSPEC int SDLCALL SDL_SemWaitTimeout(SDL_sem * sem, Uint32 ms);
 */
PHP_FUNCTION(SDL_SemWaitTimeout)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;
	zend_long ms;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_sem, php_sdl_sem_ce, &ms) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);

	RETVAL_LONG(SDL_SemWaitTimeout(intern->sem, (Uint32)ms));
}
/* }}} */


/* {{{ proto void SDL_DestroySemaphore(SDL_sem sem)

 *  Destroy a semaphore.
 extern DECLSPEC void SDLCALL SDL_DestroySemaphore(SDL_sem * sem);
 */
PHP_FUNCTION(SDL_DestroySemaphore)
{
	struct php_sdl_sem *intern;
	zval *z_sem;
	SDL_sem *sem;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_sem, php_sdl_sem_ce) == FAILURE) {
		return;
	}
	FETCH_SEM(sem, z_sem, 1);
	SDL_DestroySemaphore(sem);
	intern->sem = NULL;
}
/* }}} */


/* {{{ proto SDL_cond::__construct(int value) */
static PHP_METHOD(SDL_cond, __construct)
{
	struct php_sdl_cond *intern;
	zend_error_handling error_handling;

	intern = (struct php_sdl_cond *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	intern->cond = SDL_CreateCond();
	if (intern->cond) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_cond___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_cond::__toString() */
static PHP_METHOD(SDL_cond, __toString)
{
	struct php_sdl_cond *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_cond *)Z_OBJ_P(getThis());
	if (intern->cond) {
		spprintf(&buf, 100, "SDL_cond(%lx)", (long)intern->cond);
		RETVAL_STRING(buf);
	} else {
		RETVAL_STRING("SDL_cond()");
	}
}
/* }}} */


/* {{{ proto SDL_sem SDL_CreateCond(int value)

 *  Create a condition variable.
 *
 *  Typical use of condition variables:
 *
 *  Thread A:
 *    SDL_LockMutex(lock);
 *    while ( ! condition ) {
 *        SDL_CondWait(cond, lock);
 *    }
 *    SDL_UnlockMutex(lock);
 *
 *  Thread B:
 *    SDL_LockMutex(lock);
 *    ...
 *    condition = true;
 *    ...
 *    SDL_CondSignal(cond);
 *    SDL_UnlockMutex(lock);
 *
 *  There is some discussion whether to signal the condition variable
 *  with the mutex locked or not.  There is some potential performance
 *  benefit to unlocking first on some platforms, but there are some
 *  potential race conditions depending on how your code is structured.
 *
 *  In general it's safer to signal the condition variable while the
 *  mutex is locked.
 extern DECLSPEC SDL_cond *SDLCALL SDL_CreateCond(void);
 */
PHP_FUNCTION(SDL_CreateCond)
{
	SDL_cond *cond;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	cond = SDL_CreateCond();
	sdl_cond_to_zval(cond, return_value, 0);
}
/* }}} */


/* {{{ proto int SDL_CondWait(SDL_cond condition, SDL_mutex mutex)

 *  Wait on the condition variable, unlocking the provided mutex.
 *
 *  \warning The mutex must be locked before entering this function!
 *
 *  The mutex is re-locked once the condition variable is signaled.
 *
 *  \return 0 when it is signaled, or -1 on error.
 extern DECLSPEC int SDLCALL SDL_CondWait(SDL_cond * cond, SDL_mutex * mutex);
 */
PHP_FUNCTION(SDL_CondWait)
{
	struct php_sdl_cond *intern;
	zval *z_cond, *z_mutex;
	SDL_cond *cond;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &z_cond, php_sdl_cond_ce, &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_COND(cond, z_cond, 1);
	mutex = zval_to_sdl_mutex(z_mutex);
	if (mutex) {
		RETVAL_LONG(SDL_CondWait(intern->cond, mutex));
	} else {
		php_error_docref(NULL, E_WARNING, "Invalid SDL_mutex object");
	}
}
/* }}} */


/* {{{ proto int SDL_CondSignal(SDL_cond cond)

 *  Restart one of the threads that are waiting on the condition variable.
 *
 *  \return 0 or -1 on error.
 extern DECLSPEC int SDLCALL SDL_CondSignal(SDL_cond * cond);
 */
PHP_FUNCTION(SDL_CondSignal)
{
	struct php_sdl_cond *intern;
	zval *z_cond;
	SDL_cond *cond;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_cond, php_sdl_cond_ce) == FAILURE) {
		return;
	}
	FETCH_COND(cond, z_cond, 1);

	RETVAL_LONG(SDL_CondSignal(intern->cond));
}
/* }}} */


/* {{{ proto int SDL_CondBroadcast(SDL_cond cond)

 *  Restart all threads that are waiting on the condition variable.
 *
 *  \return 0 or -1 on error.
extern DECLSPEC int SDLCALL SDL_CondBroadcast(SDL_cond * cond);
 */
PHP_FUNCTION(SDL_CondBroadcast)
{
	struct php_sdl_cond *intern;
	zval *z_cond;
	SDL_cond *cond;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_cond, php_sdl_cond_ce) == FAILURE) {
		return;
	}
	FETCH_COND(cond, z_cond, 1);

	RETVAL_LONG(SDL_CondBroadcast(intern->cond));
}
/* }}} */


/* {{{ proto int SDL_CondWaitTimeout(SDL_cond cond, SDL_mutex mutex, int ms)

 *  Waits for at most \c ms milliseconds, and returns 0 if the condition
 *  variable is signaled, ::SDL_MUTEX_TIMEDOUT if the condition is not
 *  signaled in the allotted time, and -1 on error.
 *
 *  \warning On some platforms this function is implemented by looping with a
 *           delay of 1 ms, and so should be avoided if possible.
 extern DECLSPEC int SDLCALL SDL_CondWaitTimeout(SDL_cond * cond,
                                                 SDL_mutex * mutex, Uint32 ms);
 */
PHP_FUNCTION(SDL_CondWaitTimeout)
{
	struct php_sdl_cond *intern;
	zval *z_cond, *z_mutex;
	SDL_cond *cond;
	SDL_mutex *mutex;
	zend_long ms;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOl", &z_cond, php_sdl_cond_ce, &z_mutex, php_sdl_mutex_ce, &ms) == FAILURE) {
		return;
	}
	FETCH_COND(cond, z_cond, 1);
	mutex = zval_to_sdl_mutex(z_mutex);
	if (mutex) {
		RETVAL_LONG(SDL_CondWaitTimeout(intern->cond, mutex, (Uint32)ms));
	} else {
		php_error_docref(NULL, E_WARNING, "Invalid SDL_mutex object");
	}
}
/* }}} */


/* {{{ proto void SDL_DestroyCond(SDL_cond cond)

 *  Destroy a condition variable.
 extern DECLSPEC void SDLCALL SDL_DestroyCond(SDL_cond * cond);
 */
PHP_FUNCTION(SDL_DestroyCond)
{
	struct php_sdl_cond *intern;
	zval *z_cond;
	SDL_cond *cond;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_cond, php_sdl_cond_ce) == FAILURE) {
		return;
	}
	FETCH_COND(cond, z_cond, 1);
	SDL_DestroyCond(cond);
	intern->cond = NULL;
}
/* }}} */


/* {{{ sdl_mutex_methods[] */
static const zend_function_entry php_sdl_mutex_methods[] = {
	PHP_ME(SDL_mutex,       __construct,                arginfo_none,          ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_mutex,       __toString,                 arginfo_class_SDL_Mutex___toString,          ZEND_ACC_PUBLIC)

	/* non-static method */
	PHP_FALIAS(Lock,        SDL_LockMutex,              arginfo_none)
	PHP_FALIAS(TryLock,     SDL_TryLockMutex,           arginfo_none)
	PHP_FALIAS(Unlock,      SDL_UnlockMutex,            arginfo_none)
	PHP_FALIAS(Destroy,     SDL_DestroyMutex,           arginfo_none)

	ZEND_FE_END
};
/* }}} */


/* {{{ sdl_sem_methods[] */
static const zend_function_entry php_sdl_sem_methods[] = {
	PHP_ME(SDL_sem,        __construct,                arginfo_SDL_sem__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_sem,        __toString,                 arginfo_class_SDL_Sem___toString,               ZEND_ACC_PUBLIC)

	/* non-static method */
	PHP_FALIAS(Wait,        SDL_SemWait,               arginfo_none)
	PHP_FALIAS(TryWait,     SDL_SemTryWait,            arginfo_none)
	PHP_FALIAS(Post,        SDL_SemPost,               arginfo_none)
	PHP_FALIAS(Value,       SDL_SemValue,              arginfo_none)
	PHP_FALIAS(WaitTimeout, SDL_SemWaitTimeout,        arginfo_SDL_Sem_WaitTimeout)
	PHP_FALIAS(Destroy,     SDL_DestroySemaphore,      arginfo_none)

	ZEND_FE_END
};
/* }}} */


/* {{{ sdl_cond_methods[] */
static const zend_function_entry php_sdl_cond_methods[] = {
	PHP_ME(SDL_cond,        __construct,               arginfo_none, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_cond,        __toString,                arginfo_class_SDL_cond___toString,               ZEND_ACC_PUBLIC)

	/* non-static method */
	PHP_FALIAS(Wait,        SDL_CondWait,              arginfo_SDL_Cond_Wait)
	PHP_FALIAS(Signal,      SDL_CondSignal,            arginfo_none)
	PHP_FALIAS(Broadcast,   SDL_CondBroadcast,         arginfo_none)
	PHP_FALIAS(WaitTimeout, SDL_CondWaitTimeout,       arginfo_SDL_Cond_WaitTimeout)
	PHP_FALIAS(Destroy,     SDL_DestroySemaphore,      arginfo_none)

	ZEND_FE_END
};
/* }}} */

#define REGISTER_MUTEXT_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_MUTEX_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_mutex_ce, ZEND_STRL(const_name), value)

	/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_mutex)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_mutex", php_sdl_mutex_methods);
	ce.create_object = php_sdl_mutex_new;
	php_sdl_mutex_ce = zend_register_internal_class(&ce);
	memcpy(&php_sdl_mutex_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_mutex_handlers.free_obj = php_sdl_mutex_free;

	REGISTER_MUTEXT_CLASS_CONST_LONG("TIMEDOUT", SDL_MUTEX_TIMEDOUT);
	REGISTER_MUTEXT_CLASS_CONST_LONG("MAXWAIT",  SDL_MUTEX_MAXWAIT);

	INIT_CLASS_ENTRY(ce, "SDL_sem", php_sdl_sem_methods);
	ce.create_object = php_sdl_sem_new;
	php_sdl_sem_ce = zend_register_internal_class(&ce);
	memcpy(&php_sdl_sem_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_sem_handlers.free_obj = php_sdl_sem_free;

	INIT_CLASS_ENTRY(ce, "SDL_cond", php_sdl_cond_methods);
	ce.create_object = php_sdl_cond_new;
	php_sdl_cond_ce = zend_register_internal_class(&ce);
	memcpy(&php_sdl_cond_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_cond_handlers.free_obj = php_sdl_cond_free;

	return SUCCESS;
}
/* }}} */
