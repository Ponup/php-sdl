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

#include "php_sdl_time.h"

#include "ext/standard/basic_functions.h"

#include <SDL.h>

#include "php_sdl.h"

/* Resources */
int le_timer;

typedef struct php_sdl_timer {
	SDL_TimerID id;
#ifdef ZTS
	THREAD_T caller_thread_id;
#endif
    zend_fcall_info *cb_fci;
} php_sdl_timer_t;

void _sdl_timer(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	int i;
	php_sdl_timer_t *timer_data = (php_sdl_timer_t *)rsrc->ptr;
	for( i = timer_data->cb_fci->param_count - 1; i >= 0; i-- ) {
		efree(timer_data->cb_fci->params[ i ]);
	}
	efree(timer_data->cb_fci->params);
	efree(timer_data->cb_fci);
	efree(timer_data);
}

/* {{{ proto int sdl_getticks(void)
 */
PHP_FUNCTION(sdl_getticks)
{
	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_LONG( SDL_GetTicks() );
}
/* }}} */

/* {{{ void SDL_Delay(Uint32 ms)
 */
PHP_FUNCTION(sdl_delay)
{
	long ms;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ms) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	SDL_Delay((Uint32)ms);
}
/* }}} */

Uint32 php_sdl_timer_callback(Uint32 interval, void *param)
{
	php_sdl_timer_t *timer_data = (php_sdl_timer_t*)param;
#ifdef ZTS
	void ***tsrm_ls = (void ***) ts_resource_ex(0, &(timer_data->caller_thread_id));
#endif
	zval *cb_retval = NULL;

	timer_data->cb_fci->retval_ptr_ptr = &cb_retval;

	if (zend_call_function(timer_data->cb_fci, NULL TSRMLS_CC) == SUCCESS) {
		if (cb_retval) {
			convert_to_long_ex(&cb_retval);
			interval = (Uint32)Z_LVAL_P(cb_retval);
			zval_ptr_dtor(&cb_retval);
		}
	} else {
		php_error(E_WARNING, "%s() calling user callback failed",
				  get_active_function_name(TSRMLS_C));
	}

	return interval;
}

/* {{{ SDL_TimerID SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void* param);
typedef Uint32 (*SDL_NewTimerCallback)(Uint32 interval, void* param);
 */
PHP_FUNCTION(sdl_addtimer)
{
	php_sdl_timer_t *timer_data;
	long interval;
	zval *userdata = NULL;
	zend_bool userdata_isnull;
	zval **args = safe_emalloc(1, sizeof(zval*), 0);

 	timer_data = (php_sdl_timer_t*)emalloc(sizeof(php_sdl_timer_t));
    timer_data->cb_fci = (zend_fcall_info*)emalloc(sizeof(zend_fcall_info));
    zend_fcall_info_cache cb_fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lf|z", &interval, timer_data->cb_fci, &cb_fci_cache, &userdata) == FAILURE) {
		WRONG_PARAM_COUNT;
    }

	userdata_isnull = (userdata == NULL || Z_TYPE_P(userdata) == IS_NULL);

	if(userdata_isnull) {
		timer_data->cb_fci->param_count = 0;
		timer_data->cb_fci->params = NULL;
	}
	else {
		timer_data->cb_fci->param_count = 1;
		timer_data->cb_fci->params = safe_emalloc(1, sizeof(zval**), 0);
		MAKE_STD_ZVAL(args[0]);
		MAKE_COPY_ZVAL(&userdata, args[0]);
		timer_data->cb_fci->params[0] = &args[0];
	}

	// We need the callers thread id for the callback to occur in the right thread
#ifdef ZTS
	timer_data->caller_thread_id = tsrm_thread_id();
#endif
	
	timer_data->id = SDL_AddTimer((Uint32)interval, php_sdl_timer_callback, (void*)timer_data);

	ZEND_REGISTER_RESOURCE(return_value, timer_data, le_timer);
}

/* }}} */

/* {{{ SDL_bool SDL_RemoveTimer(SDL_TimerID id);
 */
PHP_FUNCTION(sdl_removetimer) {
	zval *timer_arg;
	php_sdl_timer_t *timer_data;
	long retval;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &timer_arg) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(timer_data, php_sdl_timer_t *, &timer_arg, -1, le_timer_name, le_timer);
	retval = SDL_RemoveTimer(timer_data->id);

	zend_list_delete(Z_RESVAL_P(timer_arg));

	RETURN_LONG(retval);
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
