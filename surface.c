/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
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

#include "php_sdl.h"
#include "pixels.h"
#include "rect.h"
#include "rwops.h"
#include "surface.h"

static zend_class_entry *php_sdl_surface_ce;
static zend_object_handlers php_sdl_surface_handlers;
struct php_sdl_surface {
	SDL_Surface   *surface;
	Uint32        flags;
	zend_object   zo;
};

zend_class_entry *get_php_sdl_surface_ce(void)
{
	return php_sdl_surface_ce;
}

#define FETCH_SURFACE(__ptr, __id, __check) \
{ \
		zend_object* zox = Z_OBJ_P(__id);\
		intern = (struct php_sdl_surface*)((char*)zox - zox->handlers->offset);\
        __ptr = intern->surface; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_surface_to_zval */
zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *z_val)
{
	if (surface) {
		struct php_sdl_surface *intern;

		object_init_ex(z_val, php_sdl_surface_ce);
		zend_object* zo = Z_OBJ_P(z_val);
		intern = (struct php_sdl_surface*)((char*)zo - zo->handlers->offset);
		intern->surface = surface;
		/* copy flags to be able to check before access to surface */
		intern->flags = surface->flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_surface */
SDL_Surface *zval_to_sdl_surface(zval *z_val)
{
	struct php_sdl_surface *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_surface_ce) {
		zend_object* zo = Z_OBJ_P(z_val);
		intern = (struct php_sdl_surface*)((char*)zo - zo->handlers->offset);
		return intern->surface;
		}
	return NULL;
}
/* }}} */



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
	zend_long flags, width, height, depth, rmask, gmask, bmask, amask;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "llllllll", &flags, &width, &height, &depth, &rmask, &gmask, &bmask, &amask)) {
		return;
	}
	surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	sdl_surface_to_zval(surface, return_value);
}
/* }}} */

/* {{{ proto SDL_Surface SDL_LoadBMP_RW(SDL_RWops src, int freesrc)

 *  Load a surface from a seekable SDL data stream (memory or file).
 *
 *  If \c freesrc is non-zero, the stream will be closed after being read.
 *
 *  The new surface should be freed with SDL_FreeSurface().
 *
 *  \return the new surface, or NULL if there was an error.
 extern DECLSPEC SDL_Surface *SDLCALL SDL_LoadBMP_RW(SDL_RWops * src,
                                                     int freesrc);
 */
PHP_FUNCTION(SDL_LoadBMP_RW)
{
	zval *z_rwops;
	zend_long freesrc;
	SDL_Surface *surface;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Ol", &z_rwops, get_php_sdl_rwops_ce(), &freesrc)) {
		return;
	}
	rwops = zval_to_sdl_rwops(z_rwops);
	surface = SDL_LoadBMP_RW(rwops, 0);
	if (freesrc) {
		/* we close the SDL_RWops ourself, to free the PHP object */
		zval_dtor(z_rwops);
		ZVAL_NULL(z_rwops);
	}
	sdl_surface_to_zval(surface, return_value);
}
/* }}} */



/* {{{ proto SDL_Surface SDL_LoadBMP(string file)

	PHP note: stream are supported

 *  Load a surface from a file.
 *
 *  Convenience macro.
 define SDL_LoadBMP(file)   SDL_LoadBMP_RW(SDL_RWFromFile(file, "rb"), 1)
 */
PHP_FUNCTION(SDL_LoadBMP)
{
	char *path;
	size_t path_len;
	SDL_Surface *surface = NULL;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "s", &path, &path_len)) {
		return;
	}

	surface = SDL_LoadBMP(path);

	sdl_surface_to_zval(surface, return_value);
}
/* }}} */


/* {{{ proto SDL_Surface::__construct(int flags, int width, int height, int depth, int Rmask, int Gmask, int Bmask, int Amask) */
static PHP_METHOD(SDL_Surface, __construct)
{
	struct php_sdl_surface *intern;
	zend_long flags, width, height, depth, rmask, gmask, bmask, amask;
	zend_error_handling error_handling;

	intern = (struct php_sdl_surface *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "llllllll", &flags, &width, &height, &depth, &rmask, &gmask, &bmask, &amask)) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	intern->surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	if (intern->surface) {
		/* copy flags to be able to check before access to surface */
		intern->flags = intern->surface->flags;
	} else {
		zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	}
}
/* }}} */


/* {{{ proto SDL_Surface::__toString() */
static PHP_METHOD(SDL_Surface, __toString)
{
	struct php_sdl_surface *intern;
	char *buf;
    size_t buf_len;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_surface *)Z_OBJ_P(getThis());
	if (intern->surface) {
		buf_len = spprintf(&buf, 100, "SDL_Surface(%u,%d,%d,%u,0x%x,0x%x,0x%x,0x%x)",
			intern->surface->flags, intern->surface->w, intern->surface->h,
			intern->surface->format->BitsPerPixel, intern->surface->format->Rmask,
			intern->surface->format->Gmask, intern->surface->format->Bmask, intern->surface->format->Amask);
		RETVAL_STRINGL(buf, buf_len);
        efree(buf);
	} else {
		RETVAL_STRING("SDL_Surface()");
	}
}
/* }}} */



/* {{{ proto int SDL_SaveBMP_RW(SDL_Surface surface, SDL_RWops &dst, int freedst)

 *  Save a surface to a seekable SDL data stream (memory or file).
 *
 *  If \c freedst is non-zero, the stream will be closed after being written.
 *
 *  \return 0 if successful or -1 if there was an error.
 extern DECLSPEC int SDLCALL SDL_SaveBMP_RW
     (SDL_Surface * surface, SDL_RWops * dst, int freedst);
 */
PHP_FUNCTION(SDL_SaveBMP_RW)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_rwops;
	zend_long freedst = 0;
	SDL_Surface *surface;
	SDL_RWops *rwops;
	int result;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO|l", &z_surface, php_sdl_surface_ce, &z_rwops, get_php_sdl_rwops_ce(), &freedst) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	rwops = zval_to_sdl_rwops(z_rwops);

	if (!rwops) {
		php_error_docref(NULL, E_WARNING, "Invalid SDL_RWops object");
		RETURN_LONG(-1);
	}

	result = SDLCALL SDL_SaveBMP_RW(surface, rwops, 0);

	if (freedst) {
		/* we close the SDL_RWops ourself, to free the PHP object */
		zval_dtor(z_rwops);
		ZVAL_NULL(z_rwops);
	}
	RETURN_LONG(result);
}
/* }}} */



/* {{{ proto int SDL_SaveBMP(SDL_Surface surface, string path)

	PHP note: stream are "partially" supported (only when PHP_STREAM_AS_STDIO)

 define SDL_SaveBMP(surface, file) \
         SDL_SaveBMP_RW(surface, SDL_RWFromFile(file, "wb"), 1)

 */
PHP_FUNCTION(SDL_SaveBMP)
{
	struct php_sdl_surface *intern;
	zval *z_surface, z_rwops;
	char *path;
	SDL_Surface *surface;
	SDL_RWops *rwops;
	size_t path_len;
	int result = -1;
	php_stream *stream;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os", &z_surface, php_sdl_surface_ce, &path, &path_len) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);

	stream = php_stream_open_wrapper(path, "wb", REPORT_ERRORS, NULL);
	php_stream_to_zval_rwops(stream, &z_rwops, 0);

	rwops = zval_to_sdl_rwops(&z_rwops);
	if (rwops) {
		result = SDLCALL SDL_SaveBMP_RW(surface, rwops, 0);
	}
	zval_dtor(&z_rwops);

	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_FreeSurface(SDL_Surface surface)

 *  \brief Destroy a window.
 extern DECLSPEC void SDLCALL SDL_FreeSurface(SDL_Surface * surface);
 */
PHP_FUNCTION(SDL_FreeSurface)
{
	struct php_sdl_surface *intern;
	zval *object;
	SDL_Surface *surface;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object, php_sdl_surface_ce) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, object, 1);

	SDL_FreeSurface(intern->surface);
	intern->surface = NULL;
}
/* }}} */



/* {{{ proto SDL_FillRect(SDL_Surface surface, SDL_Rect rect, int color)

 *  Performs a fast fill of the given rectangle with \c color.
 *
 *  If \c rect is NULL, the whole surface will be filled with \c color.
 *
 *  The color should be a pixel of the format used by the surface, and
 *  can be generated by the SDL_MapRGB() function.
 *
 *  \return 0 on success, or -1 on error.
extern DECLSPEC int SDLCALL SDL_FillRect
    (SDL_Surface * dst, const SDL_Rect * rect, Uint32 color);
 */
PHP_FUNCTION(SDL_FillRect)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_rect;
	zend_long color;
	SDL_Rect rect;
	SDL_Surface *surface;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOl", &z_surface, php_sdl_surface_ce, &z_rect, get_php_sdl_rect_ce(), &color) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	zval_to_sdl_rect(z_rect, &rect);

	RETURN_LONG(SDL_FillRect(surface, &rect, (Uint32)color));
}
/* }}} */


/* {{{ proto int SDL_FillRects(SDL_Surface surface, SDL_Rect rect, int count, int color)

extern DECLSPEC int SDLCALL SDL_FillRects
    (SDL_Surface * dst, const SDL_Rect * rects, int count, Uint32 color);
*/
PHP_FUNCTION(SDL_FillRects)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_rects, *z_rect;
	zend_long color, count;
	int i, nb;
	SDL_Rect *rects;
	SDL_Surface *surface;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oall", &z_surface, php_sdl_surface_ce, &z_rects, &count, &color) == FAILURE) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	if (count<=0) {
		count = zend_hash_next_free_element(Z_ARRVAL_P(z_rects));
	}
	rects = emalloc(sizeof(SDL_Rect)*count);

	for (i=nb=0 ; i<count ; i++) {
		if (!(z_rect = zend_hash_index_find(Z_ARRVAL_P(z_rects), i))) {
			php_error_docref(NULL, E_WARNING, "rects[%d] missing", i);

		} else if (Z_TYPE_P(z_rect) != IS_OBJECT || Z_OBJCE_P(z_rect) != get_php_sdl_rect_ce()) {
			php_error_docref(NULL, E_WARNING, "rects[%d] is not a SDL_Rect object", i);

		} else {
			zval_to_sdl_rect(z_rect, rects+nb);
			nb++;
		}
	}

	if (nb) {
		RETVAL_LONG(SDL_FillRects(surface, rects, nb, (Uint32)color));

	} else {
		php_error_docref(NULL, E_WARNING, "no rect in provided array");
		RETVAL_LONG(-1);
	}
	efree(rects);
}
/* }}} */


/* {{{ proto bool SDL_MUSTLOCK(SDL_Surface surface)

 *  Evaluates to true if the surface needs to be locked before access.
 define SDL_MUSTLOCK(S) (((S)->flags & SDL_RLEACCEL) != 0)
 */
PHP_FUNCTION(SDL_MUSTLOCK)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_surface, php_sdl_surface_ce)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);

	RETURN_BOOL(SDL_MUSTLOCK(surface));
}
/* }}} */


/* {{{ proto int SDL_LockSurface(SDL_Surface surface)

 *  \brief Sets up a surface for directly accessing the pixels.
 *
 *  Between calls to SDL_LockSurface() / SDL_UnlockSurface(), you can write
 *  to and read from \c surface->pixels, using the pixel format stored in
 *  \c surface->format.  Once you are done accessing the surface, you should
 *  use SDL_UnlockSurface() to release it.
 *
 *  Not all surfaces require locking.  If SDL_MUSTLOCK(surface) evaluates
 *  to 0, then you can read and write to the surface at any time, and the
 *  pixel format of the surface will not change.
 *
 *  No operating system or library calls should be made between lock/unlock
 *  pairs, as critical system locks may be held during this time.
 *
 *  SDL_LockSurface() returns 0, or -1 if the surface couldn't be locked.
 *  \sa SDL_UnlockSurface()
 *  \sa SDL_LockSurface()
 extern DECLSPEC int SDLCALL SDL_LockSurface(SDL_Surface * surface);
 */
PHP_FUNCTION(SDL_LockSurface)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_surface, php_sdl_surface_ce)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);

	RETURN_LONG(SDL_LockSurface(surface));
}
/* }}} */


/* {{{ proto void SDL_UnlockSurface(SDL_Surface surface)

extern DECLSPEC void SDLCALL SDL_UnlockSurface(SDL_Surface * surface);
*/
PHP_FUNCTION(SDL_UnlockSurface)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_surface, php_sdl_surface_ce)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);

	SDL_UnlockSurface(surface);
}
/* }}} */


/* {{{ proto void SDL_UpperBlit(SDL_Surface src, SDL_rect &srcrect, SDL_Surface dst [, SDL_rect &dstrect])

 *  Performs a fast blit from the source surface to the destination surface.
 *
 *  This assumes that the source and destination rectangles are
 *  the same size.  If either \c srcrect or \c dstrect are NULL, the entire
 *  surface (\c src or \c dst) is copied.  The final blit rectangles are saved
 *  in \c srcrect and \c dstrect after all clipping is performed.
 *
 *  \return If the blit is successful, it returns 0, otherwise it returns -1.
 *
 *  The blit function should not be called on a locked surface.
 *
 *  The blit semantics for surfaces with and without blending and colorkey
 *  are defined as follows:
 *  \verbatim
    RGBA->RGB:
      Source surface blend mode set to SDL_BLENDMODE_BLEND:
        alpha-blend (using the source alpha-channel and per-surface alpha)
        SDL_SRCCOLORKEY ignored.
      Source surface blend mode set to SDL_BLENDMODE_NONE:
        copy RGB.
        if SDL_SRCCOLORKEY set, only copy the pixels matching the
        RGB values of the source color key, ignoring alpha in the
        comparison.

    RGB->RGBA:
      Source surface blend mode set to SDL_BLENDMODE_BLEND:
        alpha-blend (using the source per-surface alpha)
      Source surface blend mode set to SDL_BLENDMODE_NONE:
        copy RGB, set destination alpha to source per-surface alpha value.
      both:
        if SDL_SRCCOLORKEY set, only copy the pixels matching the
        source color key.

    RGBA->RGBA:
      Source surface blend mode set to SDL_BLENDMODE_BLEND:
        alpha-blend (using the source alpha-channel and per-surface alpha)
        SDL_SRCCOLORKEY ignored.
      Source surface blend mode set to SDL_BLENDMODE_NONE:
        copy all of RGBA to the destination.
        if SDL_SRCCOLORKEY set, only copy the pixels matching the
        RGB values of the source color key, ignoring alpha in the
        comparison.

    RGB->RGB:
      Source surface blend mode set to SDL_BLENDMODE_BLEND:
        alpha-blend (using the source per-surface alpha)
      Source surface blend mode set to SDL_BLENDMODE_NONE:
        copy RGB.
      both:
        if SDL_SRCCOLORKEY set, only copy the pixels matching the
        source color key.
    \endverbatim

 *
 *  You should call SDL_BlitSurface() unless you know exactly how SDL
 *  blitting works internally and how to use the other blit functions.
 define SDL_BlitSurface SDL_UpperBlit

 *  This is the public blit function, SDL_BlitSurface(), and it performs
 *  rectangle validation and clipping before passing it to SDL_LowerBlit()
 extern DECLSPEC int SDLCALL SDL_UpperBlit
     (SDL_Surface * src, const SDL_Rect * srcrect,
      SDL_Surface * dst, SDL_Rect * dstrect);
 */
PHP_FUNCTION(SDL_UpperBlit)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_dst, *z_srect, *z_drect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect srect, drect;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OzO|z", &z_src, php_sdl_surface_ce, &z_srect, &z_dst, php_sdl_surface_ce, &z_drect)) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	FETCH_SURFACE(dst, z_dst, 1);
	if (!(Z_TYPE_P(z_srect)==IS_NULL || zval_to_sdl_rect(z_srect, &srect))) {
		php_error_docref(NULL, E_ERROR, "srcrect is not a SDL_Rect object");
		return;
	}
        /*
	if (z_drect && !(Z_TYPE_P(z_drect)==IS_NULL || zval_to_sdl_rect(z_drect, &drect))) {
		php_error_docref(NULL, E_ERROR, "dstrect is not a SDL_Rect object");
		return;
	} else if (z_drect && Z_TYPE_P(z_drect)==IS_NULL) {
		php_error_docref(NULL, E_NOTICE, "dstrect is not a SDL_Rect object, so is ignored");
	}
         * */

	result = SDL_UpperBlit(src, (Z_TYPE_P(z_srect)==IS_NULL ? NULL : &srect),
	                       dst, (z_drect==NULL || Z_TYPE_P(z_drect)==IS_NULL ? NULL : &drect));

	if (result==0 && z_drect && Z_TYPE_P(z_drect)==IS_OBJECT) {
		sdl_rect_to_zval(&drect, z_drect);
	}
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_LowerBlit(SDL_Surface src, SDL_rect &srcrect, SDL_Surface dst , SDL_rect &dstrect)

 *  This is a semi-private blit function and it performs low-level surface
 *  blitting only.
 extern DECLSPEC int SDLCALL SDL_LowerBlit
     (SDL_Surface * src, SDL_Rect * srcrect,
      SDL_Surface * dst, SDL_Rect * dstrect);
 */
PHP_FUNCTION(SDL_LowerBlit)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_dst, *z_srect, *z_drect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect srect, drect;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOOO", &z_src, php_sdl_surface_ce, &z_srect, get_php_sdl_rect_ce(), &z_dst, php_sdl_surface_ce, &z_drect, get_php_sdl_rect_ce())) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	FETCH_SURFACE(dst, z_dst, 1);
	zval_to_sdl_rect(z_srect, &srect);
	zval_to_sdl_rect(z_srect, &srect);

	result = SDL_LowerBlit(src, &srect, dst, &drect);

	if (result==0) {
		zval_dtor(z_srect);
		sdl_rect_to_zval(&srect, z_srect);
		zval_dtor(z_drect);
		sdl_rect_to_zval(&drect, z_drect);
	}
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_UpperBlitScaled(SDL_Surface src, SDL_rect &srcrect, SDL_Surface dst [, SDL_rect &dstrect])

 *  This is the public scaled blit function, SDL_BlitScaled(), and it performs
 *  rectangle validation and clipping before passing it to SDL_LowerBlitScaled()
 extern DECLSPEC int SDLCALL SDL_UpperBlitScaled
     (SDL_Surface * src, const SDL_Rect * srcrect,
     SDL_Surface * dst, SDL_Rect * dstrect);
 define SDL_BlitScaled SDL_UpperBlitScaled
 */
PHP_FUNCTION(SDL_UpperBlitScaled)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_dst, *z_srect, *z_drect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect srect, drect;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OzO|z", &z_src, php_sdl_surface_ce, &z_srect, &z_dst, php_sdl_surface_ce, &z_drect)) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	FETCH_SURFACE(dst, z_dst, 1);
	if (!(Z_TYPE_P(z_srect)==IS_NULL || zval_to_sdl_rect(z_srect, &srect))) {
		php_error_docref(NULL, E_ERROR, "srcrect is not a SDL_Rect object");
		return;
	}
        /*
	if (z_drect && !(Z_TYPE_P(z_drect)==IS_NULL || zval_to_sdl_rect(z_drect, &drect))) {
		php_error_docref(NULL, E_ERROR, "dstrect is not a SDL_Rect object");
		return;
	} else if (z_drect && Z_TYPE_P(z_drect)==IS_NULL) {
		php_error_docref(NULL, E_NOTICE, "dstrect is not a SDL_Rect object, so is ignored");
	}
         * */

	result = SDL_UpperBlitScaled(src, (Z_TYPE_P(z_srect)==IS_NULL ? NULL : &srect),
	                       dst, (z_drect==NULL || Z_TYPE_P(z_drect)==IS_NULL ? NULL : &drect));

	if (result==0 && z_drect && Z_TYPE_P(z_drect)==IS_OBJECT) {
		sdl_rect_to_zval(&drect, z_drect);
	}
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_LowerBlitScaled(SDL_Surface src, SDL_rect &srcrect, SDL_Surface dst , SDL_rect &dstrect)

 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 extern DECLSPEC int SDLCALL SDL_LowerBlitScaled
     (SDL_Surface * src, SDL_Rect * srcrect,
     SDL_Surface * dst, SDL_Rect * dstrect);
 */
PHP_FUNCTION(SDL_LowerBlitScaled)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_dst, *z_srect, *z_drect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect srect, drect;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OOOO", &z_src, php_sdl_surface_ce, &z_srect, get_php_sdl_rect_ce(), &z_dst, php_sdl_surface_ce, &z_drect, get_php_sdl_rect_ce())) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	FETCH_SURFACE(dst, z_dst, 1);
	zval_to_sdl_rect(z_srect, &srect);
	zval_to_sdl_rect(z_srect, &srect);

	result = SDL_LowerBlitScaled(src, &srect, dst, &drect);

	if (result==0) {
		zval_dtor(z_srect);
		sdl_rect_to_zval(&srect, z_srect);
		zval_dtor(z_drect);
		sdl_rect_to_zval(&drect, z_drect);
	}
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_SoftStretch(SDL_Surface src, SDL_rect srcrect, SDL_Surface dst [, SDL_rect dstrect])

 *  \brief Perform a fast, low quality, stretch blit between two surfaces of the
 *         same pixel format.
 *
 *  \note This function uses a static buffer, and is not thread-safe.
 extern DECLSPEC int SDLCALL SDL_SoftStretch(SDL_Surface * src,
                                             const SDL_Rect * srcrect,
                                             SDL_Surface * dst,
                                             const SDL_Rect * dstrect);

 */
PHP_FUNCTION(SDL_SoftStretch)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_dst, *z_srect, *z_drect = NULL;
	SDL_Surface *src, *dst;
	SDL_Rect srect, drect;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OzO|z", &z_src, php_sdl_surface_ce, &z_srect, &z_dst, php_sdl_surface_ce, &z_drect)) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	FETCH_SURFACE(dst, z_dst, 1);
	if (!(Z_TYPE_P(z_srect)==IS_NULL || zval_to_sdl_rect(z_srect, &srect))) {
		php_error_docref(NULL, E_ERROR, "srcrect is not a SDL_Rect object");
		return;
	}
	if (z_drect && !(Z_TYPE_P(z_drect)==IS_NULL || zval_to_sdl_rect(z_drect, &drect))) {
		php_error_docref(NULL, E_ERROR, "dstrect is not a SDL_Rect object");
		return;
	} else if (z_drect && Z_TYPE_P(z_drect)==IS_NULL) {
		php_error_docref(NULL, E_NOTICE, "dstrect is not a SDL_Rect object, so is ignored");
	}

	result = SDL_SoftStretch(src, (Z_TYPE_P(z_srect)==IS_NULL ? NULL : &srect),
	                         dst, (z_drect==NULL || Z_TYPE_P(z_drect)==IS_NULL ? NULL : &drect));

	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void SDL_SetSurfaceRLE(SDL_Surface src, int flag)

 *  \brief Sets the RLE acceleration hint for a surface.
 *
 *  \return 0 on success, or -1 if the surface is not valid
 *
 *  \note If RLE is enabled, colorkey and alpha blending blits are much faster,
 *        but the surface must be locked before directly accessing the pixels.
 extern DECLSPEC int SDLCALL SDL_SetSurfaceRLE(SDL_Surface * surface,
                                               int flag);
 */
PHP_FUNCTION(SDL_SetSurfaceRLE)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	zend_long flag;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_surface, php_sdl_surface_ce, &flag)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	RETURN_LONG(SDL_SetSurfaceRLE(surface, (int)flag));
}
/* }}} */

/* {{{ proto int SDL_SetColorKey(SDL_Surface src, int flag [, int key ])

 *  \brief Sets the color key (transparent pixel) in a blittable surface.
 *
 *  \param surface The surface to update
 *  \param flag Non-zero to enable colorkey and 0 to disable colorkey
 *  \param key The transparent pixel in the native surface format
 *
 *  \return 0 on success, or -1 if the surface is not valid
 *
 *  You can pass SDL_RLEACCEL to enable RLE accelerated blits.
 extern DECLSPEC int SDLCALL SDL_SetColorKey(SDL_Surface * surface,
                                             int flag, Uint32 key);
 */
PHP_FUNCTION(SDL_SetColorKey)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	zend_long flag, key = 0;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol|l", &z_surface, php_sdl_surface_ce, &flag, &key)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	RETURN_LONG(SDL_SetColorKey(surface, (int)flag, (Uint32)key));
}
/* }}} */

/* {{{ proto int SDL_GetColorKey(SDL_Surface src, int &key)

 *  \brief Gets the color key (transparent pixel) in a blittable surface.
 *
 *  \param surface The surface to update
 *  \param key A pointer filled in with the transparent pixel in the native
 *             surface format
 *
 *  \return 0 on success, or -1 if the surface is not valid or colorkey is not
 *          enabled.
 extern DECLSPEC int SDLCALL SDL_GetColorKey(SDL_Surface * surface,
                                             Uint32 * key);
 */
PHP_FUNCTION(SDL_GetColorKey)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_key;
	Uint32 key;
	SDL_Surface *surface;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz", &z_surface, php_sdl_surface_ce, &z_key)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	result = SDL_GetColorKey(surface, &key);
	if (result == 0) {
		zval_dtor(z_key);
		ZVAL_LONG(z_key, (long)key);
	}
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int SDL_SetSurfaceColorMod(SDL_Surface src, int r, int g, int b)

 *  \brief Set an additional color value used in blit operations.
 *
 *  \param surface The surface to update.
 *  \param r The red color value multiplied into blit operations.
 *  \param g The green color value multiplied into blit operations.
 *  \param b The blue color value multiplied into blit operations.
 *
 *  \return 0 on success, or -1 if the surface is not valid.
 *
 *  \sa SDL_GetSurfaceColorMod()
 extern DECLSPEC int SDLCALL SDL_SetSurfaceColorMod(SDL_Surface * surface,
                                                    Uint8 r, Uint8 g, Uint8 b);
 */
PHP_FUNCTION(SDL_SetSurfaceColorMod)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	zend_long r, g, b;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Olll", &z_surface, php_sdl_surface_ce, &r, &g, &b)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	RETURN_LONG(SDL_SetSurfaceColorMod(surface, (Uint8)r, (Uint8)g, (Uint8)b));
}
/* }}} */

/* {{{ proto int SDL_GetSurfaceColorMod(SDL_Surface src, int &r, int &g, int&b)

 *  \brief Get the additional color value used in blit operations.
 *
 *  \param surface The surface to query.
 *  \param r A pointer filled in with the current red color value.
 *  \param g A pointer filled in with the current green color value.
 *  \param b A pointer filled in with the current blue color value.
 *
 *  \return 0 on success, or -1 if the surface is not valid.
 *
 *  \sa SDL_SetSurfaceColorMod()
 extern DECLSPEC int SDLCALL SDL_GetSurfaceColorMod(SDL_Surface * surface,
                                                    Uint8 * r, Uint8 * g,
                                                    Uint8 * b);
 */
PHP_FUNCTION(SDL_GetSurfaceColorMod)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_r, *z_g, *z_b;
	Uint8 r, g, b;
	SDL_Surface *surface;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ozzz", &z_surface, php_sdl_surface_ce, &z_r, &z_g, &z_b)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	result = SDL_GetSurfaceColorMod(surface, &r, &g, &b);
	if (result == 0) {
		zval_dtor(z_r);
		ZVAL_LONG(z_r, (long)r);
		zval_dtor(z_g);
		ZVAL_LONG(z_g, (long)g);
		zval_dtor(z_b);
		ZVAL_LONG(z_b, (long)b);
	}
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto int SDL_SetSurfaceColorMod(SDL_Surface src, int alpha)

 *  \brief Set an additional alpha value used in blit operations.
 *
 *  \param surface The surface to update.
 *  \param alpha The alpha value multiplied into blit operations.
 *
 *  \return 0 on success, or -1 if the surface is not valid.
 *
 *  \sa SDL_GetSurfaceAlphaMod()
 extern DECLSPEC int SDLCALL SDL_SetSurfaceAlphaMod(SDL_Surface * surface,
                                                    Uint8 alpha);
 */
PHP_FUNCTION(SDL_SetSurfaceAlphaMod)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	zend_long a;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_surface, php_sdl_surface_ce, &a)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	RETURN_LONG(SDL_SetSurfaceAlphaMod(surface, (Uint8)a));
}
/* }}} */

/* {{{ proto int SDL_GetSurfaceAlphaMod(SDL_Surface src, int &a)

 *  \brief Get the additional alpha value used in blit operations.
 *
 *  \param surface The surface to query.
 *  \param alpha A pointer filled in with the current alpha value.
 *
 *  \return 0 on success, or -1 if the surface is not valid.
 *
 *  \sa SDL_SetSurfaceAlphaMod()
 extern DECLSPEC int SDLCALL SDL_GetSurfaceAlphaMod(SDL_Surface * surface,
                                                    Uint8 * alpha);
 */
PHP_FUNCTION(SDL_GetSurfaceAlphaMod)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_a;
	Uint8 a;
	SDL_Surface *surface;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz", &z_surface, php_sdl_surface_ce, &z_a)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	result = SDL_GetSurfaceAlphaMod(surface, &a);
	if (result == 0) {
		zval_dtor(z_a);
		ZVAL_LONG(z_a, (long)a);
	}
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto int SDL_SetSurfaceBlendMode(SDL_Surface src, int blendmode)
 *  \brief Set the blend mode used for blit operations.
 *
 *  \param surface The surface to update.
 *  \param blendMode ::SDL_BlendMode to use for blit blending.
 *
 *  \return 0 on success, or -1 if the parameters are not valid.
 *
 *  \sa SDL_GetSurfaceBlendMode()
 extern DECLSPEC int SDLCALL SDL_SetSurfaceBlendMode(SDL_Surface * surface,
                                                     SDL_BlendMode blendMode);
 */
PHP_FUNCTION(SDL_SetSurfaceBlendMode)
{
	struct php_sdl_surface *intern;
	zval *z_surface;
	zend_long mode;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_surface, php_sdl_surface_ce, &mode)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	RETURN_LONG(SDL_SetSurfaceBlendMode(surface, (SDL_BlendMode)mode));
}
/* }}} */

/* {{{ proto int SDL_GetSurfaceAlphaMod(SDL_Surface src, int &a)

 *  \brief Get the blend mode used for blit operations.
 *
 *  \param surface   The surface to query.
 *  \param blendMode A pointer filled in with the current blend mode.
 *
 *  \return 0 on success, or -1 if the surface is not valid.
 *
 *  \sa SDL_SetSurfaceBlendMode()
 extern DECLSPEC int SDLCALL SDL_GetSurfaceBlendMode(SDL_Surface * surface,
                                                     SDL_BlendMode *blendMode);
 */
PHP_FUNCTION(SDL_GetSurfaceBlendMode)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_mode;
	SDL_BlendMode mode;
	SDL_Surface *surface;
	int result;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz", &z_surface, php_sdl_surface_ce, &z_mode)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	result = SDL_GetSurfaceBlendMode(surface, &mode);
	if (result == 0) {
		zval_dtor(z_mode);
		ZVAL_LONG(z_mode, (long)mode);
	}
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void SDL_SetClipRect(SDL_Surface src, SDL_Rect cliprect)

 *  Sets the clipping rectangle for the destination surface in a blit.
 *
 *  If the clip rectangle is NULL, clipping will be disabled.
 *
 *  If the clip rectangle doesn't intersect the surface, the function will
 *  return SDL_FALSE and blits will be completely clipped.  Otherwise the
 *  function returns SDL_TRUE and blits to the surface will be clipped to
 *  the intersection of the surface area and the clipping rectangle.
 *
 *  Note that blits are automatically clipped to the edges of the source
 *  and destination surfaces.
 extern DECLSPEC SDL_bool SDLCALL SDL_SetClipRect(SDL_Surface * surface,
                                                  const SDL_Rect * rect);
 */
PHP_FUNCTION(SDL_SetClipRect)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_rect;
	SDL_Rect rect;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &z_surface, php_sdl_surface_ce, &z_rect, get_php_sdl_rect_ce())) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	if (zval_to_sdl_rect(z_rect, &rect)) {
		RETURN_BOOL(SDL_SetClipRect(surface, &rect));
	}
	php_error_docref(NULL, E_WARNING, "Invalid SDL_Rect object");
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto void SDL_GetClipRect(SDL_Surface src, SDL_Rect &rect)

 *  Gets the clipping rectangle for the destination surface in a blit.
 *
 *  \c rect must be a pointer to a valid rectangle which will be filled
 *  with the correct values.
 extern DECLSPEC void SDLCALL SDL_GetClipRect(SDL_Surface * surface,
                                              SDL_Rect * rect);
 */
PHP_FUNCTION(SDL_GetClipRect)
{
	struct php_sdl_surface *intern;
	zval *z_surface, *z_rect;
	SDL_Rect rect;
	SDL_Surface *surface;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oz", &z_surface, php_sdl_surface_ce, &z_rect)) {
		return;
	}
	FETCH_SURFACE(surface, z_surface, 1);
	SDL_GetClipRect(surface, &rect);
	zval_dtor(z_rect);
	sdl_rect_to_zval(&rect, z_rect);
}
/* }}} */

/* {{{ proto void SDL_ConvertSurface(SDL_Surface src, SDL_PixelFormat format, int flag)

 *  Creates a new surface of the specified format, and then copies and maps
 *  the given surface to it so the blit of the converted surface will be as
 *  fast as possible.  If this function fails, it returns NULL.
 *
 *  The \c flags parameter is passed to SDL_CreateRGBSurface() and has those
 *  semantics.  You can also pass ::SDL_RLEACCEL in the flags parameter and
 *  SDL will try to RLE accelerate colorkey and alpha blits in the resulting
 *  surface.
 extern DECLSPEC SDL_Surface *SDLCALL SDL_ConvertSurface
     (SDL_Surface * src, const SDL_PixelFormat * fmt, Uint32 flags);
 */
PHP_FUNCTION(SDL_ConvertSurface)
{
	struct php_sdl_surface *intern;
	zval *z_src, *z_format;
	zend_long flags = 0;
	SDL_Surface *src, *dst;
	SDL_PixelFormat *format;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO|l", &z_src, php_sdl_surface_ce, &z_format, get_php_sdl_pixelformat_ce(), &flags)) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	format = zval_to_sdl_pixelformat(z_format);
	if (format) {
		dst = SDL_ConvertSurface(src, format, (Uint32)flags);
		sdl_surface_to_zval(dst, return_value);
	} else {
		RETVAL_NULL();
	}
}
/* }}} */

/* {{{ proto void SDL_ConvertSurfaceFormat(SDL_Surface src, int format [, int flags])

 extern DECLSPEC SDL_Surface *SDLCALL SDL_ConvertSurfaceFormat
     (SDL_Surface * src, Uint32 pixel_format, Uint32 flags);
 */
PHP_FUNCTION(SDL_ConvertSurfaceFormat)
{
	struct php_sdl_surface *intern;
	zval *z_src;
	zend_long format, flags = 0;
	SDL_Surface *src, *dst;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol|l", &z_src, php_sdl_surface_ce, &format, &flags)) {
		return;
	}
	FETCH_SURFACE(src, z_src, 1);
	dst = SDL_ConvertSurfaceFormat(src, (Uint32)format, (Uint32)flags);
	sdl_surface_to_zval(dst, return_value);
}
/* }}} */

/* {{{ proto int SDL_ConvertPixels(int width, int height, int src_format, SDL_Pixels src, int src_pitch, int dst_format, SDL_Pixels dst, int dst_pitch)

 * \brief Copy a block of pixels of one format to another format
 *
 *  \return 0 on success, or -1 if there was an error
 extern DECLSPEC int SDLCALL SDL_ConvertPixels(int width, int height,
                                               Uint32 src_format,
                                               const void * src, int src_pitch,
                                               Uint32 dst_format,
                                               void * dst, int dst_pitch);
 */
PHP_FUNCTION(SDL_ConvertPixels)
{
	zval *z_src, *z_dst;
	zend_long w, h, sf, sp, df, dp;
	SDL_Pixels *src, *dst;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "lllOllOl", &w, &h, &sf, &z_src, get_php_sdl_pixels_ce(), &sp, &df, &z_dst, get_php_sdl_pixels_ce(), &dp)) {
		return;
	}
	if (!(src = zval_to_sdl_pixels(z_src))) {
		php_error_docref(NULL, E_WARNING, "Invalid source SDL_Pixels object");
	}
	if (!(dst = zval_to_sdl_pixels(z_dst))) {
		php_error_docref(NULL, E_WARNING, "Invalid destination SDL_Pixels object");
	}
	if (h < 0 || h > src->h || h > dst->h) {
		h = (src->h > dst->h ? dst->h : src->h);
		php_error_docref(NULL, E_NOTICE, "Bad value for height, will use %ld", h);\
	}
	if (sp != src->pitch) {
		sp = src->pitch;
		php_error_docref(NULL, E_NOTICE, "Bad value for source pitch, will use %ld", sp);\
	}
	if (dp != dst->pitch) {
		dp = dst->pitch;
		php_error_docref(NULL, E_NOTICE, "Bad value for destination pitch, will use %ld", dp);\
	}
	RETVAL_LONG(SDL_ConvertPixels(w, h, sf, src->pixels, sp, df, src->pixels, dp));
}
/* }}} */

/* we need to undefine this macros to avoid substitution in list behind */
#undef SDL_BlitSurface
#undef SDL_BlitScaled

static const zend_function_entry php_sdl_surface_methods[] = {
	PHP_ME(SDL_Surface, __construct, arginfo_SDL_CreateRGBSurface, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Surface, __toString,  arginfo_surface_none,         ZEND_ACC_PUBLIC)

	/* non-static methods */
	PHP_FALIAS(Free,             SDL_FreeSurface,           arginfo_surface_none)
	PHP_FALIAS(FillRect,         SDL_FillRect,              arginfo_SDL_Surface_FillRect)
	PHP_FALIAS(FillRects,        SDL_FillRects,             arginfo_SDL_Surface_FillRects)
	PHP_FALIAS(MustLock,         SDL_MUSTLOCK,              arginfo_surface_none)
	PHP_FALIAS(Lock,             SDL_LockSurface,           arginfo_surface_none)
	PHP_FALIAS(Unlock,           SDL_UnlockSurface,         arginfo_surface_none)
	PHP_FALIAS(Blit,             SDL_UpperBlit,             arginfo_SDL_Surface_UpperBlit)
	PHP_FALIAS(UpperBlit,        SDL_UpperBlit,             arginfo_SDL_Surface_UpperBlit)
	PHP_FALIAS(LowerBlit,        SDL_LowerBlit,             arginfo_SDL_Surface_LowerBlit)
	PHP_FALIAS(BlitScaled,       SDL_UpperBlitScaled,       arginfo_SDL_Surface_UpperBlit)
	PHP_FALIAS(UpperBlitScaled,  SDL_UpperBlitScaled,       arginfo_SDL_Surface_UpperBlit)
	PHP_FALIAS(LowerBlitScaled,  SDL_LowerBlitScaled,       arginfo_SDL_Surface_LowerBlit)
	PHP_FALIAS(SoftStretch,      SDL_SoftStretch,           arginfo_SDL_Surface_UpperBlit)
	PHP_FALIAS(SaveBMP_RW,       SDL_SaveBMP_RW,            arginfo_SDL_Surface_SaveBMP_RW)
	PHP_FALIAS(SaveBMP,          SDL_SaveBMP,               arginfo_SDL_Surface_SaveBMP)
	PHP_FALIAS(SetRLE,           SDL_SetSurfaceRLE,         arginfo_SDL_Surface_SetRLE)
	PHP_FALIAS(SetColorKey,      SDL_SetColorKey,           arginfo_SDL_Surface_SetColorKey)
	PHP_FALIAS(GetColorKey,      SDL_GetColorKey,           arginfo_SDL_Surface_GetColorKey)
	PHP_FALIAS(SetColorMod,      SDL_SetSurfaceColorMod,    arginfo_SDL_Surface_SetColorMod)
	PHP_FALIAS(GetColorMod,      SDL_GetSurfaceColorMod,    arginfo_SDL_Surface_GetColorMod)
	PHP_FALIAS(SetAlphaMod,      SDL_SetSurfaceAlphaMod,    arginfo_SDL_Surface_SetAlphaMod)
	PHP_FALIAS(GetAlphaMod,      SDL_GetSurfaceAlphaMod,    arginfo_SDL_Surface_GetAlphaMod)
	PHP_FALIAS(SetBlendMode,     SDL_SetSurfaceBlendMode,   arginfo_SDL_Surface_SetBlendMode)
	PHP_FALIAS(GetBlendMode,     SDL_GetSurfaceBlendMode,   arginfo_SDL_Surface_GetBlendMode)
	PHP_FALIAS(SetClipRect,      SDL_SetClipRect,           arginfo_SDL_Surface_SetClipRect)
	PHP_FALIAS(GetClipRect,      SDL_GetClipRect,           arginfo_SDL_Surface_GetClipRect)
	PHP_FALIAS(Convert,          SDL_ConvertSurface,        arginfo_SDL_Surface_Convert)
	PHP_FALIAS(ConvertFormat,    SDL_ConvertSurfaceFormat,  arginfo_SDL_Surface_ConvertFormat)

	/* static methods */
	ZEND_FENTRY(LoadRW,    ZEND_FN(SDL_LoadBMP_RW),  arginfo_SDL_LoadBMP_RW,  ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FENTRY(LoadBMP,   ZEND_FN(SDL_LoadBMP),     arginfo_SDL_LoadBMP,     ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	PHP_FE_END
};

/* {{{ php_sdl_surface_free
	 */
static void php_sdl_surface_free(zend_object *object)
{
	struct php_sdl_surface *intern = (struct php_sdl_surface*)((char*)object - object->handlers->offset);
	if (intern->surface) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_FreeSurface(intern->surface);
		}
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

/* {{{ php_sdl_surface_new
 */
static zend_object* php_sdl_surface_new(zend_class_entry *class_type)
{
	struct php_sdl_surface *intern;

	intern = (struct php_sdl_surface*)ecalloc(1, sizeof(struct php_sdl_surface) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->surface = NULL;
	intern->zo.handlers = (zend_object_handlers *) &php_sdl_surface_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ sdl_surface_read_property*/
zval *sdl_surface_read_property(zval *object, zval *member, int type, void** cache_slot, zval *key)
{
	zval tmp_member;
	zend_object* zobject = Z_OBJ_P(object);
	struct php_sdl_surface *intern = (struct php_sdl_surface *)((char*)zobject - zobject->handlers->offset);
	zval *retval = ecalloc(1, sizeof(zval));

 	if (!intern->surface) {
 		return retval;
	}

 	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
	}

 	if (!strcmp(Z_STRVAL_P(member), "flags")) {
		ZVAL_LONG(retval, intern->surface->flags);
 	} else if (!strcmp(Z_STRVAL_P(member), "w")) {
		ZVAL_LONG(retval, intern->surface->w);
 	} else if (!strcmp(Z_STRVAL_P(member), "h")) {
		ZVAL_LONG(retval, intern->surface->h);
 	} else if (!strcmp(Z_STRVAL_P(member), "pitch")) {
		ZVAL_LONG(retval, intern->surface->pitch);
 	} else if (!strcmp(Z_STRVAL_P(member), "locked")) {
		ZVAL_LONG(retval, intern->surface->locked);
 	} else if (!strcmp(Z_STRVAL_P(member), "format")) {
		sdl_pixelformat_to_zval(intern->surface->format, retval, SDL_DONTFREE);
 	} else if (!strcmp(Z_STRVAL_P(member), "clip_rect")) {
		sdl_rect_to_zval(&intern->surface->clip_rect, retval);
 	} else if (!strcmp(Z_STRVAL_P(member), "pixels")) {
		SDL_Pixels pix;
 		pix.pitch  = intern->surface->pitch;
		pix.h      = intern->surface->h;
		pix.pixels = (Uint8 *)intern->surface->pixels;
		sdl_pixels_to_zval(&pix, retval, SDL_DONTFREE);
 	} else {
		return retval;
	}
 	if (member == &tmp_member) {
		zval_dtor(member);
	}
	return retval;
}
/* }}} */

#define REGISTER_SURFACE_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_surface_ce, ZEND_STRL(const_name), value)

#define REGISTER_SURFACE_PROP(name) \
	zend_declare_property_long(php_sdl_surface_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_surface)
{
	zend_class_entry ce_surface;

	INIT_CLASS_ENTRY(ce_surface, "SDL_Surface", php_sdl_surface_methods);
	php_sdl_surface_ce = zend_register_internal_class(&ce_surface);
	php_sdl_surface_ce->create_object = php_sdl_surface_new;
	memcpy(&php_sdl_surface_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_surface_handlers.read_property = sdl_surface_read_property;
	php_sdl_surface_handlers.free_obj = php_sdl_surface_free;
	php_sdl_surface_handlers.offset = XtOffsetOf(struct php_sdl_surface, zo);

	REGISTER_SURFACE_PROP("flags");
	REGISTER_SURFACE_PROP("w");
	REGISTER_SURFACE_PROP("h");
	REGISTER_SURFACE_PROP("pitch");
	zend_declare_property_null(php_sdl_pixelformat_ce, ZEND_STRL("format"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_rect_ce, ZEND_STRL("clip_rect"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_pixels_ce, ZEND_STRL("pixels"), ZEND_ACC_PUBLIC);

	REGISTER_SURFACE_CLASS_CONST_LONG("SWSURFACE",         SDL_SWSURFACE);
	REGISTER_SURFACE_CLASS_CONST_LONG("PREALLOC",          SDL_PREALLOC);
	REGISTER_SURFACE_CLASS_CONST_LONG("RLEACCEL",          SDL_RLEACCEL);
	REGISTER_SURFACE_CLASS_CONST_LONG("DONTFREE",          SDL_DONTFREE);

	return SUCCESS;
}
/* }}} */
