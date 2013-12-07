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
#include "rect.h"

zend_class_entry *php_sdl_surface_ce;
static zend_object_handlers php_sdl_surface_handlers;
struct php_sdl_surface {
	zend_object   zo;
	SDL_Surface   *surface;
	Uint32        flags;
};

#define FETCH_SURFACE(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_surface *)zend_object_store_get_object(__id TSRMLS_CC);\
        __ptr = intern->surface; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_surface_to_zval */
zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *z_val TSRMLS_DC)
{
	struct php_sdl_surface *intern;
	if (surface) {
		object_init_ex(z_val, php_sdl_surface_ce);
		intern = (struct php_sdl_surface *)zend_object_store_get_object(z_val TSRMLS_CC);
		intern->surface = surface;
		/* copy flags to be able to check before access to surface */
		intern->flags = surface->flags;

		return SUCCESS;
	}
	return FAILURE;
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateRGBSurface, 0, 0, 6)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, depth)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_Surface SDL_CreateRGBSurface(int flags, int width, int height, int depth, int Rmask, int Gmask, int Bmask, int Amask)

 *  Allocate and free an RGB surface.
 *
 *  If the depth is 4 or 8 bits, an empty palette is allocated for the surface.
 *  If the depth is greater than 8 bits, the pixel format is set using the
 *  flags '[RGB]mask'.
 *
 *  If the function runs out of memory, it will return NULL.
 *
 *  \param flags The \c flags are obsolete and should be set to 0.
 *  \param width The width in pixels of the surface to create.
 *  \param height The height in pixels of the surface to create.
 *  \param depth The depth in bits of the surface to create.
 *  \param Rmask The red mask of the surface to create.
 *  \param Gmask The green mask of the surface to create.
 *  \param Bmask The blue mask of the surface to create.
 *  \param Amask The alpha mask of the surface to create.
 extern DECLSPEC SDL_Surface *SDLCALL SDL_CreateRGBSurface
     (Uint32 flags, int width, int height, int depth,
      Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
*/
PHP_FUNCTION(SDL_CreateRGBSurface)
{
	long flags, width, height, depth, rmask, gmask, bmask, amask;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllllll", &flags, &width, &height, &depth, &rmask, &gmask, &bmask, &amask)) {
		return;
	}
	surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	sdl_surface_to_zval(surface, return_value TSRMLS_CC);
}
/* }}} */

/* {{{ proto SDL_Surface, __construct(int flags, int width, int height, int depth, int Rmask, int Gmask, int Bmask, int Amask)
 */
static PHP_METHOD(SDL_Surface, __construct)
{
	struct php_sdl_surface *intern;
	long flags, width, height, depth, rmask, gmask, bmask, amask;
	zend_error_handling error_handling;

	intern = (struct php_sdl_surface *)zend_object_store_get_object(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllllll", &flags, &width, &height, &depth, &rmask, &gmask, &bmask, &amask)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	if (intern->surface) {
		/* copy flags to be able to check before access to surface */
		intern->flags = intern->surface->flags;
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), SDL_GetError(), 0 TSRMLS_CC);
	}
}
/* }}} */


/* {{{ proto SDL_FreeSurface(SDL_Surface surface)

 *  \brief Destroy a window.
 extern DECLSPEC void SDLCALL SDL_FreeSurface(SDL_Surface * surface);
 */
PHP_FUNCTION(SDL_FreeSurface)
{
	struct php_sdl_surface *intern;
	zval *object;
	SDL_Surface *surface;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &object, php_sdl_surface_ce) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, object, 1);

	SDL_FreeSurface(intern->surface);
	intern->surface = NULL;
}
/* }}} */


/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_surface_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface, 0, 0, 1)
       ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()


/* {{{ sdl_surface_functions[] */
zend_function_entry sdl_surface_functions[] = {
	ZEND_FE(SDL_CreateRGBSurface,			arginfo_SDL_CreateRGBSurface)
	ZEND_FE(SDL_FreeSurface,				arginfo_SDL_Surface)
	ZEND_FE_END
};
/* }}} */

static const zend_function_entry php_sdl_surface_methods[] = {
	PHP_ME(SDL_Surface, __construct, arginfo_SDL_CreateRGBSurface, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)

	PHP_FALIAS(Free,             SDL_FreeSurface,           arginfo_surface_none)

	PHP_FE_END
};

/* {{{ php_sdl_surface_free
	 */
static void php_sdl_surface_free(void *object TSRMLS_DC)
{
	struct php_sdl_surface *intern = (struct php_sdl_surface *) object;

	if (intern->surface) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_FreeSurface(intern->surface);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ php_sdl_surface_new
 */
static zend_object_value php_sdl_surface_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;
	struct php_sdl_surface *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->surface = NULL;

	retval.handle = zend_objects_store_put(intern, NULL, php_sdl_surface_free, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &php_sdl_surface_handlers;

	return retval;
}
/* }}} */


/* {{{ sdl_surface_read_property*/
zval *sdl_surface_read_property(zval *object, zval *member, int type, const zend_literal *key TSRMLS_DC)
{
	struct php_sdl_surface *intern = (struct php_sdl_surface *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval;

	convert_to_string(member);

	MAKE_STD_ZVAL(retval);
	ZVAL_FALSE(retval);

	if (intern->surface) {
		if (!strcmp(Z_STRVAL_P(member), "flags")) {
			ZVAL_LONG(retval, intern->surface->flags);

		} else if (!strcmp(Z_STRVAL_P(member), "w")) {
			ZVAL_LONG(retval, intern->surface->w);

		} else if (!strcmp(Z_STRVAL_P(member), "h")) {
			ZVAL_LONG(retval, intern->surface->h);

		} else if (!strcmp(Z_STRVAL_P(member), "pitch")) {
			ZVAL_LONG(retval, intern->surface->w);
		}
	}
	return retval;
}
/* }}} */

#define SDL_SURFACE_ADD_PROPERTY(n,f) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_LONG(zv, (long)f); \
	zend_hash_update(props, n, sizeof(n), &zv, sizeof(zv), NULL)

/* {{{ sdl_surface_read_property*/
static HashTable *sdl_surface_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval *zv;
	struct php_sdl_surface *intern = (struct php_sdl_surface *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->surface) {
		SDL_SURFACE_ADD_PROPERTY("flags", intern->surface->flags);
		SDL_SURFACE_ADD_PROPERTY("w",     intern->surface->w);
		SDL_SURFACE_ADD_PROPERTY("h",     intern->surface->h);
		SDL_SURFACE_ADD_PROPERTY("pitch", intern->surface->pitch);
	}
	return props;
}
/* }}} */


#define REGISTER_SURFACE_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_surface_ce, const_name, sizeof(const_name)-1, value TSRMLS_CC)

#define REGISTER_SURFACE_PROP(name) \
	zend_declare_property_long(php_sdl_surface_ce, name, sizeof(name)-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_surface)
{
	zend_class_entry ce_surface;

	INIT_CLASS_ENTRY(ce_surface, "SDL_Surface", php_sdl_surface_methods);
	ce_surface.create_object = php_sdl_surface_new;
	php_sdl_surface_ce = zend_register_internal_class(&ce_surface TSRMLS_CC);
	memcpy(&php_sdl_surface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_surface_handlers.read_property  = sdl_surface_read_property;
	php_sdl_surface_handlers.get_properties = sdl_surface_get_properties;

	REGISTER_SURFACE_PROP("flags");
	REGISTER_SURFACE_PROP("w");
	REGISTER_SURFACE_PROP("h");
	REGISTER_SURFACE_PROP("pitch");

	REGISTER_SURFACE_CLASS_CONST_LONG("SWSURFACE",         SDL_SWSURFACE);
	REGISTER_SURFACE_CLASS_CONST_LONG("PREALLOC",          SDL_PREALLOC);
	REGISTER_SURFACE_CLASS_CONST_LONG("RLEACCEL",          SDL_RLEACCEL);
	REGISTER_SURFACE_CLASS_CONST_LONG("DONTFREE",          SDL_DONTFREE);

	return (zend_register_functions(NULL, sdl_surface_functions, NULL, MODULE_PERSISTENT TSRMLS_CC));
}
