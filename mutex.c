/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_mutex.h                                         |
  +----------------------------------------------------------------------+
  | SDL_mutex                                                            |
  +----------------------------------------------------------------------+
*/


#include "php_sdl.h"
#include "mutex.h"

static zend_class_entry *php_sdl_mutex_ce;
static zend_object_handlers php_sdl_mutex_handlers;
struct php_sdl_mutex {
	zend_object   zo;
	SDL_mutex    *mutex;
	Uint32        flags;
};


/* {{{ get_php_sdl_mutex_ce */
zend_class_entry *get_php_sdl_mutex_ce(void)
{
	return php_sdl_mutex_ce;
}
/* }}} */


#define FETCH_MUTEX(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_mutex *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->mutex; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_mutex_to_zval */
zend_bool sdl_mutex_to_zval(SDL_mutex *mutex, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (mutex) {
		struct php_sdl_mutex *intern;

		object_init_ex(z_val, php_sdl_mutex_ce);
		intern = (struct php_sdl_mutex *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->mutex = mutex;
		intern->flags = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ zval_to_sdl_mutex */
SDL_mutex *zval_to_sdl_mutex(zval *z_val TSRMLS_DC)
{
	struct php_sdl_mutex *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_mutex_ce) {
		intern = (struct php_sdl_mutex *)zend_object_store_get_object(z_val TSRMLS_CC);
		return intern->mutex;
	}
	return NULL;
}
/* }}} */


/* {{{ php_sdl_mutex_free
	 */
static void php_sdl_mutex_free(void *object TSRMLS_DC)
{
	struct php_sdl_mutex *intern = (struct php_sdl_mutex *) object;

	if (intern->mutex) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_DestroyMutex(intern->mutex);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_mutex_new
 */
static zend_object_value php_sdl_mutex_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_mutex *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->mutex = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_mutex_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_mutex_handlers;

	return retval;
}
/* }}} */


/* {{{ proto SDL_mutex::__construct(void) */
static PHP_METHOD(SDL_mutex, __construct)
{
	struct php_sdl_mutex *intern;
	zend_error_handling error_handling;

	intern = (struct php_sdl_mutex *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (zend_parse_parameters_none() == FAILURE) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	  intern->mutex = SDL_CreateMutex();
	  if (intern->mutex) {
		  intern->flags = 0;
	  } else {
		  zend_throw_exception(zend_exception_get_default(TSRMLS_C), SDL_GetError(), 0 TSRMLS_CC);
	  }
}
/* }}} */


/* {{{ proto SDL_mutex::__toString() */
static PHP_METHOD(SDL_mutex, __toString)
{
	struct php_sdl_mutex *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_mutex *)zend_object_store_get_object(getThis() TSRMLS_CC);
	if (intern->mutex) {
		spprintf(&buf, 100, "SDL_mutex(%lx)", (long)intern->mutex);
		RETVAL_STRING(buf, 0);
	} else {
		RETVAL_STRING("SDL_mutex()", 1);
	}
}
/* }}} */


/* {{{ proto SDL_mutex SDL_CreateMutex(void)

 *  Create a mutex, initialized unlocked.
 extern DECLSPEC SDL_mutex *SDLCALL SDL_CreateMutex(void);
 */
PHP_FUNCTION(SDL_CreateMutex)
{
	SDL_mutex *context;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	context = SDL_CreateMutex();
	sdl_mutex_to_zval(context, return_value, 0 TSRMLS_CC);
}
/* }}} */


/* {{{ proto int SDL_LockMutex(SDL_mutex mutex)

 *  Lock the mutex.
 *
 *  \return 0, or -1 on error.
 define SDL_mutexP(m)   SDL_LockMutex(m)
 extern DECLSPEC int SDLCALL SDL_LockMutex(SDL_mutex * mutex);
 */
static PHP_FUNCTION(SDL_LockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_TryLockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_UnlockMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
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
static PHP_FUNCTION(SDL_DestroyMutex)
{
	struct php_sdl_mutex *intern;
	zval *z_mutex;
	SDL_mutex *mutex;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_mutex, php_sdl_mutex_ce) == FAILURE) {
		return;
	}
	FETCH_MUTEX(mutex, z_mutex, 1);
	SDL_DestroyMutex(mutex);
	intern->mutex = NULL;
}
/* }}} */


/* generic arginfo */

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_mutex, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
ZEND_END_ARG_INFO()


/* {{{ sdl_mutex_methods[] */
static const zend_function_entry php_sdl_mutex_methods[] = {
	PHP_ME(SDL_mutex,       __construct,                arginfo_none,          ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_mutex,       __toString,                 arginfo_none,          ZEND_ACC_PUBLIC)

	/* non-static method */
	PHP_FALIAS(Lock,        SDL_LockMutex,              arginfo_none)
	PHP_FALIAS(TryLock,     SDL_TryLockMutex,           arginfo_none)
	PHP_FALIAS(Unlock,      SDL_UnlockMutex,            arginfo_none)
	PHP_FALIAS(Destroy,     SDL_DestroyMutex,            arginfo_none)

	ZEND_FE_END
};
/* }}} */


/* {{{ sdl_mutex_functions[] */
static zend_function_entry sdl_mutex_functions[] = {
	ZEND_FE(SDL_CreateMutex,                        arginfo_none)
	ZEND_FE(SDL_LockMutex,                          arginfo_SDL_mutex)
	ZEND_FE(SDL_TryLockMutex,                       arginfo_SDL_mutex)
	ZEND_FE(SDL_UnlockMutex,                        arginfo_SDL_mutex)
	ZEND_FE(SDL_DestroyMutex,                       arginfo_SDL_mutex)

	/* aliases */
	PHP_FALIAS(SDL_mutexP,      SDL_LockMutex,      arginfo_SDL_mutex)
	PHP_FALIAS(SDL_mutexV,      SDL_UnlockMutex,    arginfo_SDL_mutex)

	ZEND_FE_END
};
/* }}} */


#define REGISTER_MUTEXT_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_MUTEX_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_mutex_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC)

	/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_mutex)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_mutex", php_sdl_mutex_methods);
	ce.create_object = php_sdl_mutex_new;
	php_sdl_mutex_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_mutex_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_MUTEXT_CLASS_CONST_LONG("TIMEDOUT", SDL_MUTEX_TIMEDOUT);
	REGISTER_MUTEXT_CLASS_CONST_LONG("MAXWAIT",  SDL_MUTEX_MAXWAIT);

	return (zend_register_functions(NULL, sdl_mutex_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
/* }}} */
