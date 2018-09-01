/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
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

#include "messagebox.h"
#include "window.h"

static zend_class_entry *php_sdl_messageboxcolor_ce;
static zend_object_handlers php_sdl_messageboxcolor_handlers;
struct php_sdl_messageboxcolor {
	zend_object   zo;
};

static zend_class_entry *php_sdl_messageboxbuttondata_ce;
static zend_object_handlers php_sdl_messageboxbuttondata_handlers;
struct php_sdl_messageboxbuttondata {
	zend_object   zo;
};

static zend_class_entry *php_sdl_messageboxdata_ce;
static zend_object_handlers php_sdl_messageboxdata_handlers;
struct php_sdl_messageboxdata {
	zend_object          zo;
	SDL_MessageBoxData  *data;
	Uint32               flags;
};

/* {{{ get_php_sdl_messageboxcolor_ce */
zend_class_entry *get_php_sdl_messageboxcolor_ce(void)
{
	return php_sdl_messageboxcolor_ce;
}
/* }}} */

/* {{{ get_php_sdl_messageboxbuttondata_ce */
zend_class_entry *get_php_sdl_messageboxbuttondata_ce(void)
{
	return php_sdl_messageboxbuttondata_ce;
}
/* }}} */

/* {{{ get_php_sdl_messageboxdata_ce */
zend_class_entry *get_php_sdl_messageboxdata_ce(void)
{
	return php_sdl_messageboxdata_ce;
}
/* }}} */

/* {{{ sdl_messageboxcolor_to_zval */
zend_bool sdl_messageboxcolor_to_zval(const SDL_MessageBoxColor *color, zval *value TSRMLS_DC)
{
	if (color) {
		object_init_ex(value, php_sdl_messageboxcolor_ce);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "r", 1, color->r TSRMLS_CC);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "g", 1, color->g TSRMLS_CC);
		zend_update_property_long(php_sdl_messageboxcolor_ce, value, "b", 1, color->b TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}
/* }}} */

/* {{{ sdl_messageboxbuttondata_to_zval */
zend_bool sdl_messageboxbuttondata_to_zval(const SDL_MessageBoxButtonData *data, zval *value TSRMLS_DC)
{
	if (data) {
		object_init_ex(value, php_sdl_messageboxbuttondata_ce);
		zend_update_property_long(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("flags"), data->flags TSRMLS_CC);
		zend_update_property_long(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("buttonid"), data->buttonid TSRMLS_CC);
		zend_update_property_string(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("text"), data->text TSRMLS_CC);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}
/* }}} */

/* {{{ sdl_messageboxdata_to_zval */
zend_bool sdl_messageboxdata_to_zval(SDL_MessageBoxData *data, zval *z_val, Uint32 flags TSRMLS_DC)
{
	if (data) {
		struct php_sdl_messageboxdata *intern;

		object_init_ex(z_val, php_sdl_messageboxdata_ce);
		intern = (struct php_sdl_messageboxdata *)Z_OBJ_P(z_val TSRMLS_CC);
		intern->data   = data;
		intern->flags  = flags;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_messageboxcolor( */
zend_bool zval_to_sdl_messageboxcolor(zval *value, SDL_MessageBoxColor *color TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_messageboxcolor_ce) {
		zval *val, rv;

		/* we convert the properties, without copy: yes ! */

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "r", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = color->r = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "g", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = color->g = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxcolor_ce, value, "b", 1, 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = color->b = (Uint8)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty color */
	memset(color, 0, sizeof(SDL_MessageBoxColor));
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_messageboxcolor( */
zend_bool zval_to_sdl_messageboxbuttondata(zval *value, SDL_MessageBoxButtonData *data TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_messageboxbuttondata_ce) {
		zval *val, rv;

		/* we convert the properties, without copy: yes ! */

		val = zend_read_property(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("flags"), 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = data->flags = (Uint32)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("buttonid"), 0, &rv TSRMLS_CC);
		convert_to_long(val);
		Z_LVAL_P(val) = data->buttonid = (int)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_messageboxbuttondata_ce, value, ZEND_STRL("text"), 0, &rv TSRMLS_CC);
		convert_to_string(val);
		data->text = Z_STRVAL_P(val);

		return 1;
	}
	/* create an empty color */
	memset(data, 0, sizeof(SDL_MessageBoxButtonData));
	return 0;
}
/* }}} */

/* {{{ zval_to_sdl_messageboxdata */
SDL_MessageBoxData *zval_to_sdl_messageboxdata(zval *z_val TSRMLS_DC)
{
	if (z_val && Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_messageboxdata_ce) {
		struct php_sdl_messageboxdata *intern;

		intern = (struct php_sdl_messageboxdata *)Z_OBJ_P(z_val TSRMLS_CC);
		return intern->data;
		}
	return NULL;
}
/* }}} */

/* {{{ php_sdl_messageboxdata_free
	 */
static void php_sdl_messageboxdata_free(zend_object *object TSRMLS_DC)
{
	struct php_sdl_messageboxdata *intern = (struct php_sdl_messageboxdata *) object;

	if (intern->data) {
		if (!(intern->flags & SDL_DONTFREE)) {
			efree((void *)intern->data->title);
			efree((void *)intern->data->message);
			if (intern->data->buttons) {
				efree((void *)intern->data->buttons);
			}
			if (intern->data->colorScheme) {
				efree((void *)intern->data->colorScheme);
			}
			efree(intern->data);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
}
/* }}} */

/* {{{ php_sdl_messageboxdata_new
 */
static zend_object* php_sdl_messageboxdata_new(zend_class_entry *class_type TSRMLS_DC)
{
	struct php_sdl_messageboxdata *intern;

	intern = emalloc(sizeof(*intern));
	memset(intern, 0, sizeof(*intern));

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	intern->data = NULL;
	intern->zo.handlers = &php_sdl_messageboxdata_handlers;

	return &intern->zo;
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MessageBoxColor__construct, 0, 0, 3)
       ZEND_ARG_INFO(0, r)
       ZEND_ARG_INFO(0, g)
       ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_MessageBoxColor::__construct(int r, int g, int b, int a)

 * \brief RGB value used in a message box color scheme
typedef struct
{
    Uint8 r, g, b;
} SDL_MessageBoxColor;
*/
static PHP_METHOD(SDL_MessageBoxColor, __construct)
{
	long r, g, b;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &r, &g, &b)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "r", 1, r&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "g", 1, g&255 TSRMLS_CC);
	zend_update_property_long(php_sdl_messageboxcolor_ce, getThis(), "b", 1, b&255 TSRMLS_CC);
}
/* }}} */


/* {{{ proto SDL_MessageBoxColor::__toString() */
static PHP_METHOD(SDL_MessageBoxColor, __toString)
{
	char *buf;
	SDL_MessageBoxColor color;

	//intern = (struct php_sdl_pixelformat *)Z_OBJ_P(__id TSRMLS_CC);
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_messageboxcolor(getThis(), &color TSRMLS_CC);
	spprintf(&buf, 100, "SDL_MessageBoxColor(%u,%u,%u)", color.r, color.g, color.b);
	RETVAL_STRING(buf);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MessageBoxButtonData__construct, 0, 0, 3)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, buttonid)
       ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_MessageBoxButtonData::__construct(int r, int g, int b, int a)

 *  \brief Individual button data.
 typedef struct
 {
     Uint32 flags;       *< ::SDL_MessageBoxButtonFlags *
     int buttonid;       *< User defined button id (value returned via SDL_ShowMessageBox) *
     const char * text;  *< The UTF-8 button text *
 } SDL_MessageBoxButtonData;
*/
static PHP_METHOD(SDL_MessageBoxButtonData, __construct)
{
	long flags, id;
	char *text;
	size_t text_len;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls", &flags, &id, &text, &text_len)) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	zend_update_property_long(php_sdl_messageboxbuttondata_ce, getThis(), ZEND_STRL("flags"), flags TSRMLS_CC);
	zend_update_property_long(php_sdl_messageboxbuttondata_ce, getThis(), ZEND_STRL("buttonid"), (int)id TSRMLS_CC);
	zend_update_property_string(php_sdl_messageboxbuttondata_ce, getThis(), ZEND_STRL("text"), text TSRMLS_CC);
}
/* }}} */


/* {{{ proto SDL_MessageBoxButtonData::__toString()
*/
static PHP_METHOD(SDL_MessageBoxButtonData, __toString)
{
	char *buf;
	SDL_MessageBoxButtonData data;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	zval_to_sdl_messageboxbuttondata(getThis(), &data TSRMLS_CC);
	spprintf(&buf, 1000, "SDL_MessageBoxButtonData(%lu,%d,\"%s\")", (long)data.flags, data.buttonid, data.text);
	RETVAL_STRING(buf);
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MessageBoxData__construct, 0, 0, 3)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, message)
       ZEND_ARG_ARRAY_INFO(0, buttons, 0)
       ZEND_ARG_ARRAY_INFO(0, colors, 0)
       ZEND_ARG_OBJ_INFO(0, parentwindow, SDL_Window, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_MessageBoxData::__construct(int flags, string title, string text [, array buttons [, array colors [, SDL_Window window ]]])

 *  \brief MessageBox structure containing title, text, window, etc.
 typedef struct
 {
     Uint32 flags;                       **< ::SDL_MessageBoxFlags *
     SDL_Window *window;                 **< Parent window, can be NULL *
     const char *title;                  **< UTF-8 title *
     const char *message;                **< UTF-8 message text *

     int numbuttons;
     const SDL_MessageBoxButtonData *buttons;

     const SDL_MessageBoxColorScheme *colorScheme;   **< ::SDL_MessageBoxColorScheme, can be NULL to use system settings *
 } SDL_MessageBoxData;
 */
static PHP_METHOD(SDL_MessageBoxData, __construct)
{
	struct php_sdl_messageboxdata *intern;
	zval *z_window=NULL, *z_buttons=NULL, *z_colors=NULL;
	long flags;
	char *title, *text;
	size_t title_len, text_len;
	int  n, nb;
	zend_error_handling error_handling;

	intern = (struct php_sdl_messageboxdata *)Z_OBJ_P(getThis() TSRMLS_CC);

	zend_replace_error_handling(EH_THROW, NULL, &error_handling TSRMLS_CC);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lss|aaO", &flags, &title, &title_len, &text, &text_len, &z_buttons, &z_colors, &z_window, get_php_sdl_window_ce())) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	intern->flags  = 0;
	intern->data = emalloc(sizeof(SDL_MessageBoxData));
	intern->data->title       = estrdup(title);
	intern->data->message     = estrdup(text);
	intern->data->flags       = (Uint32)flags;
	intern->data->window      = zval_to_sdl_window(z_window TSRMLS_CC);
	intern->data->numbuttons  = 0;
	intern->data->buttons     = NULL;
	intern->data->colorScheme = NULL;

	if (z_buttons) {
		zval *ppzval;
		SDL_MessageBoxButtonData *buttons;

		n  = 0;
		nb = zend_hash_num_elements(Z_ARRVAL_P(z_buttons));
		if (nb) {

			buttons = emalloc(nb * sizeof(SDL_MessageBoxButtonData));

			for (zend_hash_internal_pointer_reset(Z_ARRVAL_P(z_buttons)) ;
				zend_hash_has_more_elements(Z_ARRVAL_P(z_buttons)) == SUCCESS ;
				zend_hash_move_forward(Z_ARRVAL_P(z_buttons))) {
                                        ppzval = zend_hash_get_current_data(Z_ARRVAL_P(z_buttons));
					if (zval_to_sdl_messageboxbuttondata(ppzval, buttons+n TSRMLS_CC)) {
						n++;
					} else {
						php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Ignore button, not a SDL_MessageBoxButtonData object");
					}
			}
			if (n) {
				intern->data->numbuttons = n;
				intern->data->buttons    = buttons;
			} else {
				efree(buttons);
			}
		}
	}

	if (z_colors) {
		zval **ppzval;
		SDL_MessageBoxColorScheme *colors;

		colors = emalloc(sizeof(SDL_MessageBoxColorScheme));
		memset(colors, 0, sizeof(*colors));

		n  = 0;
		for (zend_hash_internal_pointer_reset(Z_ARRVAL_P(z_colors)) ;
			zend_hash_get_current_data(Z_ARRVAL_P(z_colors)) == SUCCESS ;
			zend_hash_move_forward(Z_ARRVAL_P(z_colors))) {
				if (SDL_MESSAGEBOX_COLOR_MAX == n) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Ignore button, only %d accepted", SDL_MESSAGEBOX_COLOR_MAX);
				} else if (zval_to_sdl_messageboxcolor(*ppzval, &colors->colors[n] TSRMLS_CC)) {
					n++;
				} else {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Ignore button, not a SDL_MessageBoxColor object");
				}
		}
		if (n) {
			if (SDL_MESSAGEBOX_COLOR_MAX != n) {
				php_error_docref(NULL TSRMLS_CC, E_NOTICE, "%d SDL_MessageBoxColors expected", SDL_MESSAGEBOX_COLOR_MAX);
			}
			intern->data->colorScheme = colors;
		} else {
			efree(colors);
		}
	}
}
/* }}} */


/* {{{ proto SDL_MessageBoxData::__toString() */
static PHP_METHOD(SDL_MessageBoxData, __toString)
{
	struct php_sdl_messageboxdata *intern;
	char *buf;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = (struct php_sdl_messageboxdata *)Z_OBJ_P(getThis() TSRMLS_CC);
	if (intern->data) {
		spprintf(&buf, 100, "SDL_MessageBoxData(\"%s\")", intern->data->title);
		RETVAL_STRING(buf);
	} else {
		RETVAL_STRING("SDL_MessageBoxData()");
	}
}
/* }}} */

/* {{{ sdl_messageboxdata_read_property */
static zval *sdl_messageboxdata_read_property(zval *object, zval *member, int type, void** cache_slot, zval *rv TSRMLS_DC)
{
	struct php_sdl_messageboxdata *intern = (struct php_sdl_messageboxdata *) zend_objects_get_address(object TSRMLS_CC);
	zval *retval, tmp_member;

	if (!intern->data) {
		return std_object_handlers.read_property(object, member, type, cache_slot, rv TSRMLS_CC);
	}

	if (Z_TYPE_P(member) != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		rv = NULL;
	}

	ALLOC_INIT_ZVAL(retval);
	Z_SET_REFCOUNT_P(retval, 0);

	if (!strcmp(Z_STRVAL_P(member), "flags")) {
		ZVAL_LONG(retval, intern->data->flags);

	} else if (!strcmp(Z_STRVAL_P(member), "title")) {
		ZVAL_STRING(retval, intern->data->title);

	} else if (!strcmp(Z_STRVAL_P(member), "message")) {
		ZVAL_STRING(retval, intern->data->message);

	} else if (!strcmp(Z_STRVAL_P(member), "window")) {
		ZVAL_BOOL(retval, intern->data->window);

	} else if (!strcmp(Z_STRVAL_P(member), "numbuttons")) {
		ZVAL_LONG(retval, intern->data->numbuttons);

	} else if (!strcmp(Z_STRVAL_P(member), "buttons")) {
		if (intern->data->buttons) {
			int i;
			zval z_button;

			array_init(retval);
			for (i=0 ; i<intern->data->numbuttons ; i++) {
				sdl_messageboxbuttondata_to_zval(&intern->data->buttons[i], &z_button TSRMLS_CC);
				add_next_index_zval(retval, &z_button);
			}
		}
	} else if (!strcmp(Z_STRVAL_P(member), "colors")) {
		if (intern->data->colorScheme) {
			int i;
			zval z_color;

			array_init(retval);
			for (i=0 ; i<SDL_MESSAGEBOX_COLOR_MAX ; i++) {
				sdl_messageboxcolor_to_zval(&intern->data->colorScheme->colors[i], &z_color TSRMLS_CC);
				add_next_index_zval(retval, &z_color);
			}
		}
	} else {
		FREE_ZVAL(retval);

		retval = std_object_handlers.read_property(object, member, type, cache_slot, rv TSRMLS_CC);
		if (member == &tmp_member) {
			zval_dtor(member);
		}
		return retval;
	}

	if (member == &tmp_member) {
		zval_dtor(member);
	}
	return retval;
}
/* }}} */


/* {{{ sdl_messageboxdata_get_properties */
static HashTable *sdl_messageboxdata_get_properties(zval *object TSRMLS_DC)
{
	HashTable *props;
	zval zv;
    zend_string* ht_key;
	struct php_sdl_messageboxdata *intern = (struct php_sdl_messageboxdata *) zend_objects_get_address(object TSRMLS_CC);

	props = zend_std_get_properties(object TSRMLS_CC);

	if (intern->data) {
		ZVAL_LONG(&zv, (long)intern->data->flags);
        ht_key = zend_string_init("flags", 5, 0);
		zend_hash_update(props, ht_key, &zv);

		ZVAL_STRING(&zv, intern->data->title);
        ht_key = zend_string_init("title", 5, 0);
		zend_hash_update(props, ht_key, &zv);

		ZVAL_STRING(&zv, intern->data->message);
        ht_key = zend_string_init("message", 8, 0);
		zend_hash_update(props, ht_key, &zv);

		ZVAL_BOOL(&zv, intern->data->window);
        ht_key = zend_string_init("window", 6, 0);
		zend_hash_update(props, ht_key, &zv);

		ZVAL_LONG(&zv, (long)intern->data->numbuttons);
        ht_key = zend_string_init("numbuttons", 11, 0);
		zend_hash_update(props, ht_key, &zv);

		if (intern->data->buttons) {
			int i;
			zval z_button;

			array_init(&zv);
			for (i=0 ; i<intern->data->numbuttons ; i++) {
				sdl_messageboxbuttondata_to_zval(&intern->data->buttons[i], &z_button TSRMLS_CC);
				add_next_index_zval(&zv, &z_button);
			}
		} else {
			ZVAL_NULL(&zv);
		}
        ht_key = zend_string_init("buttons", 7, 0);
		zend_hash_update(props, ht_key, &zv);

		if (intern->data->colorScheme) {
			int i;
			zval z_color;

			array_init(&zv);
			for (i=0 ; i<SDL_MESSAGEBOX_COLOR_MAX ; i++) {
				sdl_messageboxcolor_to_zval(&intern->data->colorScheme->colors[i], &z_color TSRMLS_CC);
				add_next_index_zval(&zv, &z_color);
			}
		} else {
			ZVAL_NULL(&zv);
		}
        ht_key = zend_string_init("colors", 6, 0);
		zend_hash_update(props, ht_key, &zv);
	}
	return props;
}
/* }}} */


/* {{{ sdl_messageboxdata_write_property */
static void sdl_messageboxdata_write_property(zval *object, zval *member, zval *value, zval *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Not supported, SDL_MessageBoxData is read-only");
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_MessageBoxData_Show, 0, 0, 1)
       ZEND_ARG_INFO(1, buttonid)
ZEND_END_ARG_INFO()

#define FETCH_DATA(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_messageboxdata *)Z_OBJ_P(__id TSRMLS_CC);\
        __ptr = intern->data; \
        if (__check && !__ptr) {\
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid %s object", intern->zo.ce->name);\
                RETURN_FALSE;\
        }\
}

/* {{{ proto int SDL_ShowMessageBox(SDL_MessageBoxData messageboxdata, int &buttonid)

 *  \brief Create a modal message box.
 *
 *  \param messageboxdata The SDL_MessageBoxData structure with title, text, etc.
 *  \param buttonid The pointer to which user id of hit button should be copied.
 *
 *  \return -1 on error, otherwise 0 and buttonid contains user id of button
 *          hit or -1 if dialog was closed.
 *
 *  \note This function should be called on the thread that created the parent
 *        window, or on the main thread if the messagebox has no parent.  It will
 *        block execution of that thread until the user clicks a button or
 *        closes the messagebox.
 extern DECLSPEC int SDLCALL SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, int *buttonid);
 */
PHP_FUNCTION(SDL_ShowMessageBox)
{
	struct php_sdl_messageboxdata *intern;
	zval *z_data, *z_id;
	SDL_MessageBoxData *data;
	int id, res;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz/", &z_data, php_sdl_messageboxdata_ce, &z_id) == FAILURE) {
		return;
	}
	FETCH_DATA(data, z_data, 1);

	res = SDL_ShowMessageBox(data, &id);
	if (res==0) {
		zval_dtor(z_id);
		ZVAL_LONG(z_id, (long)id);
	}
}
/* }}} */

/* {{{ proto bool SDL_ShowSimpleMessageBox(int flags, string title, string message, SDL_Window window)

 *  \brief Create a simple modal message box
 *
 *  \param flags    ::SDL_MessageBoxFlags
 *  \param title    UTF-8 title text
 *  \param message  UTF-8 message text
 *  \param window   The parent window, or NULL for no parent
 *
 *  \return 0 on success, -1 on error
 *
 *  \sa SDL_ShowMessageBox
 extern DECLSPEC int SDLCALL SDL_ShowSimpleMessageBox(Uint32 flags, const char *title, const char *message, SDL_Window *window);
 */
PHP_FUNCTION(SDL_ShowSimpleMessageBox)
{
	long flags;
	char *title, *msg;
	size_t title_len, msg_len;
	zval *z_window = NULL;
	SDL_Window *window = NULL;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lss|O!", &flags, &title, &title_len, &msg, &msg_len, &z_window, get_php_sdl_window_ce())) {
		return;
	}

	if( z_window != NULL ) {
		window = zval_to_sdl_window(z_window TSRMLS_CC);
	}
	RETVAL_LONG(SDL_ShowSimpleMessageBox(flags, title, msg, window));
}
/* }}} */


ZEND_BEGIN_ARG_INFO_EX(arginfo_messagebox_none, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ php_sdl_messageboxcolor_methods[] */
static const zend_function_entry php_sdl_messageboxcolor_methods[] = {
	PHP_ME(SDL_MessageBoxColor, __construct, arginfo_SDL_MessageBoxColor__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_MessageBoxColor, __toString,  arginfo_messagebox_none,                ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_messageboxbuttondata_methods[] */
static const zend_function_entry php_sdl_messageboxbuttondata_methods[] = {
	PHP_ME(SDL_MessageBoxButtonData, __construct, arginfo_SDL_MessageBoxButtonData__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_MessageBoxButtonData, __toString,  arginfo_messagebox_none,                     ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ php_sdl_messageboxdata_methods[] */
static const zend_function_entry php_sdl_messageboxdata_methods[] = {
	PHP_ME(SDL_MessageBoxData, __construct, arginfo_SDL_MessageBoxData__construct, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_MessageBoxData, __toString,  arginfo_messagebox_none,               ZEND_ACC_PUBLIC)

	/* non-static methods */
	PHP_FALIAS(Show,         SDL_ShowMessageBox,          arginfo_SDL_MessageBoxData_Show)

	PHP_FE_END
};
/* }}} */

#define REGISTER_MESSAGEBOX_CLASS_CONST_LONG(prefix, const_name, value, ce) \
	REGISTER_LONG_CONSTANT("SDL_MESSAGEBOX_" prefix const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(ce, ZEND_STRL(const_name), value TSRMLS_CC); \

#define REGISTER_MESSAGEBOXCOLOR_PROP(name) \
	zend_declare_property_long(php_sdl_messageboxcolor_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC TSRMLS_CC)

#define REGISTER_MESSAGEBOXBUTTONDATA_PROP(name) \
	zend_declare_property_long(php_sdl_messageboxbuttondata_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC TSRMLS_CC)

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_messagebox)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SDL_MessageBoxColor", php_sdl_messageboxcolor_methods);
	php_sdl_messageboxcolor_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_messageboxcolor_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_MESSAGEBOXCOLOR_PROP("r");
	REGISTER_MESSAGEBOXCOLOR_PROP("g");
	REGISTER_MESSAGEBOXCOLOR_PROP("b");

	INIT_CLASS_ENTRY(ce, "SDL_MessageBoxButtonData", php_sdl_messageboxbuttondata_methods);
	php_sdl_messageboxbuttondata_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_messageboxbuttondata_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_MESSAGEBOXBUTTONDATA_PROP("flags");
	REGISTER_MESSAGEBOXBUTTONDATA_PROP("buttonid");
	REGISTER_MESSAGEBOXBUTTONDATA_PROP("text");

	INIT_CLASS_ENTRY(ce, "SDL_MessageBoxData", php_sdl_messageboxdata_methods);
	ce.create_object = php_sdl_messageboxdata_new;
	php_sdl_messageboxdata_ce = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&php_sdl_messageboxdata_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_messageboxdata_handlers.read_property  = sdl_messageboxdata_read_property;
	php_sdl_messageboxdata_handlers.get_properties = sdl_messageboxdata_get_properties;
	php_sdl_messageboxdata_handlers.write_property = sdl_messageboxdata_write_property;
	php_sdl_messageboxdata_handlers.free_obj = php_sdl_messageboxdata_free;

	zend_declare_property_long(php_sdl_messageboxdata_ce, ZEND_STRL("flags"),      0,  ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_sdl_messageboxdata_ce, ZEND_STRL("title"),          ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_sdl_messageboxdata_ce, ZEND_STRL("message"),        ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_bool(php_sdl_messageboxdata_ce, ZEND_STRL("window"),     0,  ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(php_sdl_messageboxdata_ce, ZEND_STRL("numbuttons"), 0,  ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_sdl_messageboxdata_ce, ZEND_STRL("buttons"),        ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_sdl_messageboxdata_ce, ZEND_STRL("colors"),         ZEND_ACC_PUBLIC TSRMLS_CC);

	/* enum SDL_MessageBoxFlags: If supported will display warning icon, etc. */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("", "ERROR",       SDL_MESSAGEBOX_ERROR,       php_sdl_messageboxdata_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("", "WARNING",     SDL_MESSAGEBOX_WARNING,     php_sdl_messageboxdata_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("", "INFORMATION", SDL_MESSAGEBOX_INFORMATION, php_sdl_messageboxdata_ce);

	/* enum SDL_MessageBoxButtonFlags: Flags for SDL_MessageBoxButtonData. */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("BUTTON_", "RETURNKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, php_sdl_messageboxbuttondata_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("BUTTON_", "ESCAPEKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, php_sdl_messageboxbuttondata_ce);

	/* enum SDL_MessageBoxColorType */
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "BACKGROUND",        SDL_MESSAGEBOX_COLOR_BACKGROUND,        php_sdl_messageboxcolor_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "TEXT",              SDL_MESSAGEBOX_COLOR_TEXT,              php_sdl_messageboxcolor_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "BUTTON_BORDER",     SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,     php_sdl_messageboxcolor_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "BUTTON_BACKGROUND", SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND, php_sdl_messageboxcolor_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "BUTTON_SELECTED",   SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,   php_sdl_messageboxcolor_ce);
	REGISTER_MESSAGEBOX_CLASS_CONST_LONG("COLOR_", "MAX",               SDL_MESSAGEBOX_COLOR_MAX,               php_sdl_messageboxcolor_ce);

	return SUCCESS;
}
/* }}} */
