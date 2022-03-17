/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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


#ifndef PHP_SDL_MUTEX_H
#define PHP_SDL_MUTEX_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"

zend_class_entry *get_php_sdl_mutex_ce(void);
zend_bool sdl_mutex_to_zval(SDL_mutex *mutex, zval *z_val, Uint32 flags);
SDL_mutex *zval_to_sdl_mutex(zval *z_val);

zend_class_entry *get_php_sdl_sem_ce(void);
zend_bool sdl_sem_to_zval(SDL_sem *sem, zval *z_val, Uint32 flags);
SDL_sem *zval_to_sdl_sem(zval *z_val);

zend_class_entry *get_php_sdl_cond_ce(void);
zend_bool sdl_cond_to_zval(SDL_cond *cond, zval *z_val, Uint32 flags);
SDL_cond *zval_to_sdl_cond(zval *z_val);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_sem__construct, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SemWaitTimeout, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, semaphore, SDL_sem, 0)
	ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Sem_WaitTimeout, 0, 0, 1)
	ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CondWait, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, condition, SDL_cond, 0)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Cond_Wait, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CondWaitTimeout, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, condition, SDL_cond, 0)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
	ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Cond_WaitTimeout, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
	ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_mutex, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, mutex, SDL_mutex, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_sem, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, semaphore, SDL_sem, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_cond, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, condition, SDL_cond, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_CreateMutex);
PHP_FUNCTION(SDL_LockMutex);
PHP_FUNCTION(SDL_TryLockMutex);
PHP_FUNCTION(SDL_UnlockMutex);
PHP_FUNCTION(SDL_DestroyMutex);
PHP_FUNCTION(SDL_CreateSemaphore);
PHP_FUNCTION(SDL_SemWait);
PHP_FUNCTION(SDL_SemTryWait);
PHP_FUNCTION(SDL_SemPost);
PHP_FUNCTION(SDL_SemValue);
PHP_FUNCTION(SDL_SemWaitTimeout);
PHP_FUNCTION(SDL_DestroySemaphore);
PHP_FUNCTION(SDL_CreateCond);
PHP_FUNCTION(SDL_CondWait);
PHP_FUNCTION(SDL_CondSignal);
PHP_FUNCTION(SDL_CondBroadcast);
PHP_FUNCTION(SDL_CondWaitTimeout);
PHP_FUNCTION(SDL_DestroyCond);

PHP_MINIT_FUNCTION(sdl_mutex);

#ifdef  __cplusplus
} // extern "C"
#endif

#endif /* PHP_SDL_MUTEX_H */

