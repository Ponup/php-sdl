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

/* $ Id: $ */ 

#include "php_sdl.h"
#include "rwops.h"

static zend_class_entry *php_sdl_rwops_ce;
static zend_object_handlers php_sdl_rwops_handlers;
struct php_sdl_rwops {
	zend_object   zo;
	SDL_RWops    *rwops;
	Uint32        flags;
	char         *buf;
};


/* {{{ php_sdl_check_overflow */
int php_sdl_check_overflow(int a, int b)
{
	TSRMLS_FETCH();

	if(a <= 0 || b <= 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "one parameter to a memory allocation multiplication is negative or zero, failing operation gracefully");
		return 1;
	}
	if(a > INT_MAX / b) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "product of memory allocation multiplication would exceed INT_MAX, failing operation gracefully");
		return 1;
	}
	return 0;
}
/* }}} */


/* {{{ get_php_sdl_rwops_ce */
zend_class_entry *get_php_sdl_rwops_ce(void)
{
	return php_sdl_rwops_ce;
}
/* }}} */


#define FETCH_RWOPS(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_rwops *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->rwops; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_rwops_to_zval */
void sdl_rwops_to_zval(SDL_RWops *rwops, zval *z_val, Uint32 flags, char *buf TSRMLS_DC)
{
	struct php_sdl_rwops *intern;
	if (rwops) {
		object_init_ex(z_val, php_sdl_rwops_ce);
		intern = (struct php_sdl_rwops *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->rwops = rwops;
		intern->flags = flags;
		intern->buf   = buf;
	} else {
		ZVAL_NULL(z_val);
	}
}
/* }}} */


/* {{{ zval_to_sdl_rwops */
SDL_RWops *zval_to_sdl_rwops(zval *z_val TSRMLS_DC)
{
	struct php_sdl_rwops *intern;

	intern = (struct php_sdl_rwops *)zend_object_store_get_object(z_val TSRMLS_CC);
	return intern->rwops;
}
/* }}} */


/* {{{ php_sdl_rwops_free
	 */
static void php_sdl_rwops_free(void *object TSRMLS_DC)
{
	struct php_sdl_rwops *intern = (struct php_sdl_rwops *) object;

	if (intern->rwops) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_FreeRW(intern->rwops);
		}
		if (intern->buf) {
			pefree(intern->buf, 1);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */


/* {{{ php_sdl_rwops_new
 */
static zend_object_value php_sdl_rwops_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_rwops *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->rwops = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_rwops_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_rwops_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_rwops_read_property*/
zval *sdl_rwops_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
{
	struct php_sdl_rwops *intern = (struct php_sdl_rwops *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval;

	convert_to_string(member);

	MAKE_STD_ZVAL(retval);
	ZVAL_FALSE(retval);

	if (intern->rwops) {
		if (!strcmp(Z_STRVAL_P(member), "type")) {
			ZVAL_LONG(retval, intern->rwops->type);
		}
	}
	return retval;
}
/* }}} */


/* {{{ sdl_rwops_read_property*/
static HashTable *sdl_rwops_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv;
	struct php_sdl_rwops *intern = (struct php_sdl_rwops *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->rwops) {
		MAKE_STD_ZVAL(zv); \
		ZVAL_LONG(zv, (long)intern->rwops->type); \
		zend_hash_update(props, "type", sizeof("type"), &zv, sizeof(zv), NULL);
	}
	return props;
}
/* }}} */


/* {{{ sdl_rwops_write_property */
void sdl_rwops_write_property(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported, SDL_RWops is read-only");
}
/* }}} */


/* {{{ proto SDL_RWops, __construct(void) */
static PHP_METHOD(SDL_RWops, __construct)
{
	struct php_sdl_rwops *intern;
	zend_error_handling error_handling;

	intern = (struct php_sdl_rwops *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters_none()) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->rwops = SDL_AllocRW();
	if (intern->rwops) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), SDL_GetError(), 0 TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto SDL_RWops SDL_AllocRW(void)

extern DECLSPEC SDL_RWops *SDLCALL SDL_AllocRW(void);
 */
PHP_FUNCTION(SDL_AllocRW)
{
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	rwops = SDL_AllocRW();
	sdl_rwops_to_zval(rwops, return_value, 0, NULL TSRMLS_CC);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWFromFile, 0, 0, 2)
       ZEND_ARG_INFO(0, path)
       ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_RWops SDL_RWFromFile(string path,mode)

 extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromFile(const char *file,
                                                   const char *mode);
 */
PHP_FUNCTION(SDL_RWFromFile)
{
	char *path, *mode;
	int path_len, mode_len;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, ARG_PATH "s", &path, &path_len, &mode, &mode_len)) {
		return;
	}
	rwops = SDL_RWFromFile(path, mode);
	sdl_rwops_to_zval(rwops, return_value, 0, NULL TSRMLS_CC);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWFromConstMem, 0, 0, 1)
       ZEND_ARG_INFO(0, buf)
       ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_RWops SDL_RWFromConstMem(string buf [, int size ])

extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromConstMem(const void *mem,
                                                      int size);
 */
PHP_FUNCTION(SDL_RWFromConstMem)
{
	char *buf, *pbuf;
	int buf_len;
	long size=0;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &buf, &buf_len, &size)) {
		return;
	}
	if (size<=0) {
		size=buf_len;
	} else if (buf_len < size) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "given size reduce to buffer size (%d)", buf_len);
		size = buf_len;
	}

	pbuf=pestrndup(buf, size, 1);

	rwops = SDL_RWFromConstMem(pbuf, size);
	sdl_rwops_to_zval(rwops, return_value, 0, pbuf TSRMLS_CC);
}
/* }}} */

/*
extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromMem(void *mem, int size);
*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWFromFP, 0, 0, 1)
       ZEND_ARG_INFO(0, fp)
       ZEND_ARG_INFO(0, autoclose)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_RWops SDL_RWFromFP(resource fp, bool autoclose)

   PHP change: this function support PHP stream
   * SDL_RWFromFP will be used for real file
   * SDL_RWFromMem will be used for other stream
     (inspired from gd extension)

 extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromFP(FILE * fp,
                                                 SDL_bool autoclose);
 */
PHP_FUNCTION(SDL_RWFromFP)
{
	zval *z_stream;
	SDL_RWops *rwops;
	php_stream *stream;
	long autoclose=0;
	FILE * fp = NULL;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &z_stream, &autoclose)) {
		return;
	}
	php_stream_from_zval(stream, &z_stream);
	if (stream == NULL) {
		RETURN_NULL();
	}
	if (autoclose) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "autoclose can raise unsupported error with PHP stream");
	}

	/* Can we get a FILE * */
	if (php_stream_is(stream, PHP_STREAM_IS_STDIO))	{
		if (FAILURE == php_stream_cast(stream, PHP_STREAM_AS_STDIO, (void**)&fp, REPORT_ERRORS)) {
			RETURN_NULL();
		}
		rwops = SDL_RWFromFP(fp, autoclose);
		sdl_rwops_to_zval(rwops, return_value, 0, NULL TSRMLS_CC);

	/* Map the stream to memory */
	} else {
		char *buff;
		size_t buff_size;

		buff_size = php_stream_copy_to_mem(stream, &buff, PHP_STREAM_COPY_ALL, 1);
		if (!buff_size) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING,"Cannot read data");
			RETURN_NULL();
		}
		rwops = SDL_RWFromMem(buff, (int)buff_size);
		sdl_rwops_to_zval(rwops, return_value, 0, buff TSRMLS_CC);
	}
}
/* }}} */


/* {{{ proto void SDL_FreeRW(SDL_RWops area)

 extern DECLSPEC void SDLCALL SDL_FreeRW(SDL_RWops * area);
 */
PHP_FUNCTION(SDL_FreeRW)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	SDL_FreeRW(intern->rwops);
	if (intern->buf) {
		pefree(intern->buf, 1);
	}
	intern->rwops = NULL;
	intern->buf   = NULL;
}
/* }}} */


/* {{{ proto int SDL_RWsize(SDL_RWops area)

 define SDL_RWsize(ctx)         (ctx)->size(ctx)
 */
PHP_FUNCTION(SDL_RWsize)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWsize(rwops));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWseek, 0, 0, 3)
       ZEND_ARG_INFO(0, RWops)
       ZEND_ARG_INFO(0, offset)
       ZEND_ARG_INFO(0, whence)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWops_seek, 0, 0, 2)
       ZEND_ARG_INFO(0, offset)
       ZEND_ARG_INFO(0, whence)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_RWsize(SDL_RWops area)

 define SDL_RWseek(ctx, offset, whence) (ctx)->seek(ctx, offset, whence)
 */
PHP_FUNCTION(SDL_RWseek)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;
	long offset, whence;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &z_rwops, php_sdl_rwops_ce, &offset, &whence) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWseek(rwops, offset, whence));
}
/* }}} */


/* {{{ proto int SDL_RWtell(SDL_RWops area)

 define SDL_RWtell(ctx)         (ctx)->seek(ctx, 0, RW_SEEK_CUR)
 */
PHP_FUNCTION(SDL_RWtell)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWtell(rwops));
}
/* }}} */


/* {{{ proto int SDL_RWclose(SDL_RWops area)

 define SDL_RWclose(ctx)        (ctx)->close(ctx)
 */
PHP_FUNCTION(SDL_RWclose)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	/* close method also call free */
	intern->rwops = NULL;
	intern->buf   = NULL;

	RETURN_LONG(SDL_RWclose(rwops));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWread, 0, 0, 3)
       ZEND_ARG_INFO(0, RWops)
       ZEND_ARG_INFO(1, buffer)
       ZEND_ARG_INFO(0, size)
       ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWops_read, 0, 0, 2)
       ZEND_ARG_INFO(1, buffer)
       ZEND_ARG_INFO(0, size)
       ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_RWread(SDL_RWops arean string, &buf, [ int size=1 ,] int n)

 define SDL_RWread(ctx, ptr, size, n)   (ctx)->read(ctx, ptr, size, n)
 */
PHP_FUNCTION(SDL_RWread)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops, *z_buf;
	long size, n=0, read;
	SDL_RWops *rwops;
	char *buf;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ozl|l", &z_rwops, php_sdl_rwops_ce, &z_buf, &size, &n) == FAILURE) {
		return;
	}
	if (n<=0) {
		n = size;
		size = 1;
	}
	if (php_sdl_check_overflow(size, n)) {
		return;
	}

	FETCH_RWOPS(rwops, z_rwops, 1);
	buf = emalloc(size * n);
	read = SDL_RWread(rwops, buf, size, n);
	if (read > 0) {
		if (read < n) {
			buf = erealloc(buf, read * size);
		}
		zval_dtor(z_buf);
		ZVAL_STRINGL(z_buf, buf, read * size, 0);
	} else {
		efree(buf);
	}
	RETURN_LONG(read);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWwrite, 0, 0, 2)
       ZEND_ARG_INFO(0, RWops)
       ZEND_ARG_INFO(0, buffer)
       ZEND_ARG_INFO(0, size)
       ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWops_write, 0, 0, 1)
       ZEND_ARG_INFO(0, buffer)
       ZEND_ARG_INFO(0, size)
       ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

/* {{{ proto int SDL_RWwrite(SDL_RWops arean string, buf [[, int size=1 ], int n])

 define SDL_RWwrite(ctx, ptr, size, n)  (ctx)->write(ctx, ptr, size, n)
 */
PHP_FUNCTION(SDL_RWwrite)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	long size=0, n=0, write;
	int buf_len;
	SDL_RWops *rwops;
	char *buf;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|ll", &z_rwops, php_sdl_rwops_ce, &buf, &buf_len, &size, &n) == FAILURE) {
		return;
	}
	if (size<=0) { /* optional arg, default to string length */
		n = buf_len;
		size = 1;
	} else if (n<=0) { /* only length, so consider char (consistency with other php function) */
		n = size;
		size = 1;
	}
	if (php_sdl_check_overflow(size, n)) {
		return;
	}
	if (buf_len < (size * n)) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "given size reduce to buffer size (%d)", buf_len);
		size = 1;
		n = buf_len;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	write = SDL_RWwrite(rwops, buf, size, n);
	RETURN_LONG(write);
}
/* }}} */


/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_rwops_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RWops, 0, 0, 1)
       ZEND_ARG_INFO(0, RWops)
ZEND_END_ARG_INFO()

/* {{{ sdl_rwops_methods[] */
static const zend_function_entry php_sdl_rwops_methods[] = {
	PHP_ME(SDL_RWops,        __construct,       arginfo_rwops_none,    ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(Free,         SDL_FreeRW,        arginfo_rwops_none)
	PHP_FALIAS(Size,         SDL_RWsize,        arginfo_rwops_none)
	PHP_FALIAS(Seek,         SDL_RWseek,        arginfo_SDL_RWops_seek)
	PHP_FALIAS(Tell,         SDL_RWtell,        arginfo_rwops_none)
	PHP_FALIAS(Read,         SDL_RWread,        arginfo_SDL_RWops_read)
	PHP_FALIAS(Write,        SDL_RWwrite,       arginfo_SDL_RWops_write)
	PHP_FALIAS(Close,        SDL_RWclose,       arginfo_rwops_none)

	PHP_FE_END
};
/* }}} */

/* {{{ sdl_rwops_functions[] */
zend_function_entry sdl_rwops_functions[] = {
	ZEND_FE(SDL_AllocRW,                      arginfo_rwops_none)
	ZEND_FE(SDL_FreeRW,                       arginfo_SDL_RWops)
	ZEND_FE(SDL_RWFromFile,                   arginfo_SDL_RWFromFile)
	ZEND_FE(SDL_RWFromFP,                     arginfo_SDL_RWFromFP)
	ZEND_FE(SDL_RWFromConstMem,               arginfo_SDL_RWFromConstMem)
	ZEND_FE(SDL_RWsize,                       arginfo_SDL_RWops)
	ZEND_FE(SDL_RWseek,                       arginfo_SDL_RWseek)
	ZEND_FE(SDL_RWtell,                       arginfo_SDL_RWops)
	ZEND_FE(SDL_RWread,                       arginfo_SDL_RWread)
	ZEND_FE(SDL_RWwrite,                      arginfo_SDL_RWwrite)
	ZEND_FE(SDL_RWclose,                      arginfo_SDL_RWops)
	ZEND_FE_END
};
/* }}} */

#define REGISTER_RWOPS_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_rwops_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC)


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_rwops)
{
	zend_class_entry ce_rwops;

	INIT_CLASS_ENTRY(ce_rwops, "SDL_RWops", php_sdl_rwops_methods);
	ce_rwops.create_object = php_sdl_rwops_new;
	php_sdl_rwops_ce = zend_register_internal_class(&ce_rwops TSRMLS_CC);
	memcpy(&php_sdl_rwops_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_rwops_handlers.read_property  = sdl_rwops_read_property;
	php_sdl_rwops_handlers.get_properties = sdl_rwops_get_properties;
	php_sdl_rwops_handlers.write_property = sdl_rwops_write_property;

	zend_declare_property_long(php_sdl_rwops_ce, "type", sizeof("type")-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	/* RWops Types */
	REGISTER_RWOPS_CLASS_CONST_LONG("UNKNOWN",        SDL_RWOPS_UNKNOWN);
	REGISTER_RWOPS_CLASS_CONST_LONG("WINFILE",        SDL_RWOPS_WINFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("STDFILE",        SDL_RWOPS_STDFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("JNIFILE",        SDL_RWOPS_JNIFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY",         SDL_RWOPS_MEMORY);
	REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY_RO",      SDL_RWOPS_MEMORY_RO);

	REGISTER_LONG_CONSTANT("RW_SEEK_SET",    RW_SEEK_SET, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RW_SEEK_CUR",    RW_SEEK_CUR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RW_SEEK_END",    RW_SEEK_END, CONST_CS | CONST_PERSISTENT);

	return (zend_register_functions(NULL, sdl_rwops_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
