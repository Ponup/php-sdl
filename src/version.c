/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
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


#include <SDL_revision.h>

/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_version.h                                       |
  +----------------------------------------------------------------------+
*/

#include "php_sdl.h"
#include "version.h"

zend_bool convert_sdl_version_to_php_array(SDL_version *version, zval *version_array) {

	if (version) {
		array_init(version_array);
		add_assoc_long(version_array, "major", version->major);
		add_assoc_long(version_array, "minor", version->minor);
		add_assoc_long(version_array, "patch", version->patch);

		return 1;
	}
	ZVAL_NULL(version_array);
	return 0;
}

/* {{{ proto string SDL_GetRevision()

 *  \brief Get the code revision of SDL that is linked against your program.
 *
 *  Returns an arbitrary string (a hash value) uniquely identifying the
 *  exact revision of the SDL library in use, and is only useful in comparing
 *  against other revisions. It is NOT an incrementing number.
 */
PHP_FUNCTION(SDL_GetRevision)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_STRING(SDL_GetRevision());
}
/* }}} */

#ifdef HAVE_SDL_GETREVISIONNUMBER
/* {{{ proto int SDL_GetRevisionNumber()

 *  \brief Get the revision number of SDL that is linked against your program.
 *
 *  Returns a number uniquely identifying the exact revision of the SDL
 *  library in use. It is an incrementing number based on commits to
 *  hg.libsdl.org.
 */
PHP_FUNCTION(SDL_GetRevisionNumber)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_GetRevisionNumber());
}
/* }}} */
#endif

/* {{{ proto void SDL_GetVersion(array &version)

 *  \brief Get the version of SDL that is linked against your program.
 *
 *  If you are linking to SDL dynamically, then it is possible that the
 *  current version will be different than the version you compiled against.
 *  This function returns the current version, while SDL_VERSION() is a
 *  macro that tells you what version you compiled with.
 *
 *  \code
 *  SDL_version compiled;
 *  SDL_version linked;
 *
 *  SDL_VERSION(&compiled);
 *  SDL_GetVersion(&linked);
 *  printf("We compiled against SDL version %d.%d.%d ...\n",
 *         compiled.major, compiled.minor, compiled.patch);
 *  printf("But we linked against SDL version %d.%d.%d.\n",
 *         linked.major, linked.minor, linked.patch);
 *  \endcode
 *
 *  This function may be called safely at any time, even before SDL_Init().
 *
 *  \sa SDL_VERSION
 */
PHP_FUNCTION(SDL_GetVersion)
{
	SDL_version version;
	zval *version_array;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z/", &version_array) == FAILURE) {
		RETURN_FALSE;
	}

	SDL_GetVersion(&version);
	if(0 == convert_sdl_version_to_php_array(&version, version_array)) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}
/* }}} */

/* {{{ proto void SDL_VERSION(array &version)

 *
 *  \brief Macro to determine SDL version program was compiled against.
 *
 *  This macro fills in a SDL_version structure with the version of the
 *  library you compiled against. This is determined by what header the
 *  compiler uses. Note that if you dynamically linked the library, you might
 *  have a slightly newer or older version at runtime. That version can be
 *  determined with SDL_GetVersion(), which, unlike SDL_VERSION(),
 *  is not a macro.
 *
 *  \param x A pointer to a SDL_version struct to initialize.
 *
 *  \sa SDL_version
 *  \sa SDL_GetVersion
 */
PHP_FUNCTION(SDL_VERSION)
{
	SDL_version version;
	zval *version_array;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z/", &version_array) == FAILURE) {
		RETURN_FALSE;
	}
	SDL_VERSION(&version);
	zval_dtor(version_array);
	convert_sdl_version_to_php_array(&version, version_array);
}
/* }}} */

/* {{{ proto long SDL_VERSIONNUM(int x, int y, int z)

 *  This macro turns the version numbers into a numeric value:
 *  \verbatim
    (1,2,3) -> (1203)
    \endverbatim
 *
 *  This assumes that there will never be more than 100 patchlevels.
 */
PHP_FUNCTION(SDL_VERSIONNUM)
{
	zend_long x, y, z;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &x, &y, &z) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_VERSIONNUM((Uint8)x, (Uint8)y, (Uint8)z));
}
/* }}} */

/* {{{ proto bool SDL_VERSION_ATLEAST(int x, int y, int z)

 *  This macro will evaluate to true if compiled with SDL at least X.Y.Z.
 */
PHP_FUNCTION(SDL_VERSION_ATLEAST)
{
	zend_long x, y, z;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &x, &y, &z) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_BOOL(SDL_VERSION_ATLEAST((Uint8)x, (Uint8)y, (Uint8)z));
}
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_version)
{
	REGISTER_LONG_CONSTANT("SDL_COMPILEDVERSION",	SDL_COMPILEDVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MAJOR_VERSION",	SDL_MAJOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_MINOR_VERSION",	SDL_MINOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_PATCHLEVEL",	SDL_PATCHLEVEL, CONST_CS | CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("SDL_REVISION",	SDL_REVISION, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

