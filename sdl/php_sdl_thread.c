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
  | Author: Santiago Lizardo <santiagolizardo@php.net>                   |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sdl.h"

#include <SDL.h>

/* Resources */
int le_mutex;

void _sdl_mutex (zend_rsrc_list_entry *rsrc TSRMLS_DC) {}

/* {{{ proto resource sdl_createmutex()
   Create a mutex, initialized unlocked. */
PHP_FUNCTION(sdl_createmutex)
{
	SDL_mutex *mutex;
	
	if (zend_parse_parameters_none() == FAILURE)
		return;

	if (NULL == (mutex = SDL_CreateMutex())) {
		
			php_error(E_WARNING, "%s() unable to create mutex: %s",
					  get_active_function_name(TSRMLS_C), SDL_GetError());
		
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, mutex, le_mutex);
}
/* }}} */

/* {{{ proto sdl_destromutex(resource mutex)
   Destroy a mutex. */
PHP_FUNCTION(sdl_destroymutex)
{
	SDL_mutex *mutex;
	zval *z_mutex;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_mutex) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(mutex, SDL_mutex *, &z_mutex, -1, le_mutex_name, le_mutex);

	SDL_DestroyMutex(mutex);

	zend_list_delete(Z_RESVAL_P(z_mutex));
}
/* }}} */

/* {{{ proto bool sdl_mutexp(resource mutex)
   Lock the mutex */
PHP_FUNCTION(sdl_mutexp)
{
	SDL_mutex *mutex;
	zval *z_mutex;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_mutex) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(mutex, SDL_mutex *, &z_mutex, -1, le_mutex_name, le_mutex);

	RETURN_BOOL(!SDL_mutexP(mutex));
}
/* }}} */

/* {{{ proto bool sdl_mutexv(resource mutex)
   Unlock the mutex */
PHP_FUNCTION(sdl_mutexv)
{
	SDL_mutex *mutex;
	zval *z_mutex;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_mutex) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(mutex, SDL_mutex *, &z_mutex, -1, le_mutex_name, le_mutex);

	RETURN_BOOL(!SDL_mutexV(mutex));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
