<?php
const SDL_INIT_TIMER          = 0x00000001;
const SDL_INIT_AUDIO          = 0x00000010;
const SDL_INIT_VIDEO          = 0x00000020;
const SDL_INIT_JOYSTICK       = 0x00000200;
const SDL_INIT_HAPTIC         = 0x00001000;
const SDL_INIT_GAMECONTROLLER = 0x00002000;
const SDL_INIT_EVENTS         = 0x00004000;
const SDL_INIT_SENSOR         = 0x00008000;
const SDL_INIT_NOPARACHUTE    = 0x00100000;
const SDL_INIT_EVERYTHING     = SDL_INIT_TIMER 
                        | SDL_INIT_AUDIO 
                        | SDL_INIT_VIDEO 
                        | SDL_INIT_EVENTS 
                        | SDL_INIT_JOYSTICK 
                        | SDL_INIT_HAPTIC 
                        | SDL_INIT_GAMECONTROLLER 
                        | SDL_INIT_SENSOR;
/** fullscreen window */
const SDL_WINDOW_FULLSCREEN = 0x00000001;
/** fullscreen window at the current desktop resolution */
const SDL_WINDOW_FULLSCREEN_DESKTOP = ( SDL_WINDOW_FULLSCREEN | 0x00001000 );
/** window usable with OpenGL context */
const SDL_WINDOW_OPENGL = 0x00000002;
/** window is visible */
const SDL_WINDOW_SHOWN = 0x00000004;
/** window is not visible */
const SDL_WINDOW_HIDDEN = 0x00000008;
/** no window decoration */
const SDL_WINDOW_BORDERLESS = 0x00000010;
/** window can be resized */
const SDL_WINDOW_RESIZABLE = 0x00000020;
/** window is minimized */
const SDL_WINDOW_MINIMIZED = 0x00000040;
/** window is maximized */
const SDL_WINDOW_MAXIMIZED = 0x00000080;
/** window has grabbed input focus */
const SDL_WINDOW_INPUT_GRABBED = 0x00000100;
/** window has input focus */
const SDL_WINDOW_INPUT_FOCUS = 0x00000200;
/** window has mouse focus */
const SDL_WINDOW_MOUSE_FOCUS = 0x00000400;
/** window not created by SDL */
const SDL_WINDOW_FOREIGN = 0x00000800;
/** window should be created in high-DPI mode if supported (>= SDL 2.0.1) */
const SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000;
/** window has mouse captured (unrelated to INPUT_GRABBED, >= SDL 2.0.4) */
const SDL_WINDOW_MOUSE_CAPTURE = 0x00004000;
/** window should always be above others (X11 only, >= SDL 2.0.5) */
const SDL_WINDOW_ALWAYS_ON_TOP = 0x00008000;
/** window should not be added to the taskbar (X11 only, >= SDL 2.0.5) */
const SDL_WINDOW_SKIP_TASKBAR = 0x00010000;
/** window should be treated as a utility window (X11 only, >= SDL 2.0.5) */
const SDL_WINDOW_UTILITY = 0x00020000;
/** window should be treated as a tooltip (X11 only, >= SDL 2.0.5) */
const SDL_WINDOW_TOOLTIP = 0x00040000;
/** window should be treated as a popup menu (X11 only, >= SDL 2.0.5) */
const SDL_WINDOW_POPUP_MENU = 0x00080000;
/** window usable with a Vulkan instance */
const SDL_WINDOW_VULKAN = 0x10000000;
/** The renderer is a software fallback */
const SDL_RENDERER_SOFTWARE = 0x00000001;
/** The renderer uses hardware acceleration */
const SDL_RENDERER_ACCELERATED = 0x00000002;
/** Present is synchronized with the refresh rate */
const SDL_RENDERER_PRESENTVSYNC = 0x00000004;
/** The renderer supports rendering to texture */
const SDL_RENDERER_TARGETTEXTURE = 0x00000008;

const SDL_PIXELTYPE_UNKNOWN  = 0;
const SDL_PIXELTYPE_INDEX1   = 1;
const SDL_PIXELTYPE_INDEX4   = 2;
const SDL_PIXELTYPE_INDEX8   = 3;
const SDL_PIXELTYPE_PACKED8  = 4;
const SDL_PIXELTYPE_PACKED16 = 5;
const SDL_PIXELTYPE_PACKED32 = 6;
const SDL_PIXELTYPE_ARRAYU8  = 7;
const SDL_PIXELTYPE_ARRAYU16 = 8;
const SDL_PIXELTYPE_ARRAYU32 = 9;
const SDL_PIXELTYPE_ARRAYF16 = 10;
const SDL_PIXELTYPE_ARRAYF32 = 11;


const SDL_BITMAPORDER_NONE = 0;
const SDL_BITMAPORDER_4321 = 1;
const SDL_BITMAPORDER_1234 = 2;

const SDL_PACKEDORDER_NONE = 0;
const SDL_PACKEDORDER_XRGB = 1;
const SDL_PACKEDORDER_RGBX = 2;
const SDL_PACKEDORDER_ARGB = 3;
const SDL_PACKEDORDER_RGBA = 4;
const SDL_PACKEDORDER_XBGR = 5;
const SDL_PACKEDORDER_BGRX = 6;
const SDL_PACKEDORDER_ABGR = 7;
const SDL_PACKEDORDER_BGRA = 8;


const SDL_ARRAYORDER_NONE = 0;
const SDL_ARRAYORDER_RGB  = 1;
const SDL_ARRAYORDER_RGBA = 2;
const SDL_ARRAYORDER_ARGB = 3;
const SDL_ARRAYORDER_BGR  = 4;
const SDL_ARRAYORDER_BGRA = 5;
const SDL_ARRAYORDER_ABGR = 6;


const SDL_PACKEDLAYOUT_NONE    = 0;
const SDL_PACKEDLAYOUT_332     = 1;
const SDL_PACKEDLAYOUT_4444    = 2;
const SDL_PACKEDLAYOUT_1555    = 3;
const SDL_PACKEDLAYOUT_5551    = 4;
const SDL_PACKEDLAYOUT_565     = 5;
const SDL_PACKEDLAYOUT_8888    = 6;
const SDL_PACKEDLAYOUT_2101010 = 7;
const SDL_PACKEDLAYOUT_1010102 = 8;
const SDL_WINDOWPOS_UNDEFINED  = 0x1FFF0000;

const SDL_FLIP_NONE       = 0x00000000;
const SDL_FLIP_HORIZONTAL = 0x00000001;
const SDL_FLIP_VERTICAL   = 0x00000002;

const SDL_FIRSTEVENT = 0;
/** User-requested quit */
const SDL_QUIT = 0x100;
/** The application is being terminated by the OS Called on iOS in applicationWillTerminate() Called on Android in onDestroy() */
const SDL_APP_TERMINATING = 0x101;
/** The application is low on memory, free memory if possible. Called on iOS in applicationDidReceiveMemoryWarning() Called on Android in onLowMemory() */
const SDL_APP_LOWMEMORY = 0x102;
/** The application is about to enter the background Called on iOS in applicationWillResignActive() Called on Android in onPause() */
const SDL_APP_WILLENTERBACKGROUND = 0x103;
/** The application did enter the background and may not get CPU for some time Called on iOS in applicationDidEnterBackground() Called on Android in onPause() */
const SDL_APP_DIDENTERBACKGROUND = 0x104;
/** The application is about to enter the foreground Called on iOS in applicationWillEnterForeground() Called on Android in onResume() */
const SDL_APP_WILLENTERFOREGROUND = 0x105;
/** The application is now interactive Called on iOS in applicationDidBecomeActive() Called on Android in onResume() */
const SDL_APP_DIDENTERFOREGROUND = 0x106;
/** Display state change event data (event.display.*) */
const SDL_DISPLAYEVENT = 0x150;
/** Window state change event data (event.window.*) */
const SDL_WINDOWEVENT = 0x200;
/** A video driver dependent system event (event.syswm.*) This event is disabled by default, you can enable it with `SDL_EventState()` */
const SDL_SYSWMEVENT = 0x201;
/** Key pressed */
const SDL_KEYDOWN = 0x300;
/** Key released */
const SDL_KEYUP = 0x301;
/** Keyboard text editing (composition) */
const SDL_TEXTEDITING = 0x302;
/** Keymap changed due to a system event such as an input language or keyboard layout  */
const SDL_TEXTINPUT = 0x303;
/** change. */
const SDL_KEYMAPCHANGED = 0x304;
/** Mouse moved */
const SDL_MOUSEMOTION = 0x400;
/** Mouse button pressed */
const SDL_MOUSEBUTTONDOWN = 0x401;
/** Mouse button released */
const SDL_MOUSEBUTTONUP = 0x402;
/** Mouse wheel motion */
const SDL_MOUSEWHEEL = 0x403;
/** Joystick axis motion */
const SDL_JOYAXISMOTION = 0x600;
/** Joystick trackball motion */
const SDL_JOYBALLMOTION = 0x601;
/** Joystick hat position change */
const SDL_JOYHATMOTION = 0x602;
/** Joystick button pressed */
const SDL_JOYBUTTONDOWN = 0x603;
/** Joystick button released */
const SDL_JOYBUTTONUP = 0x604;
/** A new joystick has been inserted into the system */
const SDL_JOYDEVICEADDED = 0x605;
/** An opened joystick has been removed */
const SDL_JOYDEVICEREMOVED = 0x606;
/** Game controller axis motion */
const SDL_CONTROLLERAXISMOTION = 0x650;
/** Game controller button pressed */
const SDL_CONTROLLERBUTTONDOWN = 0x651;
/** Game controller button released */
const SDL_CONTROLLERBUTTONUP = 0x652;
/** A new Game controller has been inserted into the system */
const SDL_CONTROLLERDEVICEADDED = 0x653;
/** An opened Game controller has been removed */
const SDL_CONTROLLERDEVICEREMOVED = 0x654;
/** The controller mapping was updated */
const SDL_CONTROLLERDEVICEREMAPPED = 0x655;
/** Finger pressed */
const SDL_FINGERDOWN = 0x700;
/** Finger released */
const SDL_FINGERUP = 0x701;
/** Finger moved */
const SDL_FINGERMOTION = 0x702;
/** Finger gesture */
const SDL_DOLLARGESTURE = 0x800;
const SDL_DOLLARRECORD  = 0x801;
/** Finger multi gesture */
const SDL_MULTIGESTURE = 0x802;
/** The clipboard changed */
const SDL_CLIPBOARDUPDATE = 0x900;
/** The system requests a file open */
const SDL_DROPFILE = 0x1000;
/** text/plain drag-and-drop event */
const SDL_DROPTEXT = 0x1001;
/** A new set of drops is beginning (NULL filename) */
const SDL_DROPBEGIN = 0x1002;
/** Current set of drops is now complete (NULL filename) */
const SDL_DROPCOMPLETE = 0x1003;
/** A new audio device is available */
const SDL_AUDIODEVICEADDED = 0x1100;
/** An audio device has been removed. */
const SDL_AUDIODEVICEREMOVED = 0x1101;
/** A sensor was updated */
const SDL_SENSORUPDATE = 0x1200;
/** The render targets have been reset and their contents need to be updated */
const SDL_RENDER_TARGETS_RESET = 0x2000;
/** The device has been reset and all textures need to be recreated */
const SDL_RENDER_DEVICE_RESET = 0x2001;
/** Events  */
const SDL_USEREVENT = 0x8000;
/** This last event is only for bounding internal arrays */
const SDL_LASTEVENT = 0xFFFF;


const SDL_SCANCODE_UNKNOWN      = 0;
const SDL_SCANCODE_A            = 4;
const SDL_SCANCODE_B            = 5;
const SDL_SCANCODE_C            = 6;
const SDL_SCANCODE_D            = 7;
const SDL_SCANCODE_E            = 8;
const SDL_SCANCODE_F            = 9;
const SDL_SCANCODE_G            = 10;
const SDL_SCANCODE_H            = 11;
const SDL_SCANCODE_I            = 12;
const SDL_SCANCODE_J            = 13;
const SDL_SCANCODE_K            = 14;
const SDL_SCANCODE_L            = 15;
const SDL_SCANCODE_M            = 16;
const SDL_SCANCODE_N            = 17;
const SDL_SCANCODE_O            = 18;
const SDL_SCANCODE_P            = 19;
const SDL_SCANCODE_Q            = 20;
const SDL_SCANCODE_R            = 21;
const SDL_SCANCODE_S            = 22;
const SDL_SCANCODE_T            = 23;
const SDL_SCANCODE_U            = 24;
const SDL_SCANCODE_V            = 25;
const SDL_SCANCODE_W            = 26;
const SDL_SCANCODE_X            = 27;
const SDL_SCANCODE_Y            = 28;
const SDL_SCANCODE_Z            = 29;
const SDL_SCANCODE_1            = 30;
const SDL_SCANCODE_2            = 31;
const SDL_SCANCODE_3            = 32;
const SDL_SCANCODE_4            = 33;
const SDL_SCANCODE_5            = 34;
const SDL_SCANCODE_6            = 35;
const SDL_SCANCODE_7            = 36;
const SDL_SCANCODE_8            = 37;
const SDL_SCANCODE_9            = 38;
const SDL_SCANCODE_0            = 39;
const SDL_SCANCODE_RETURN       = 40;
const SDL_SCANCODE_ESCAPE       = 41;
const SDL_SCANCODE_BACKSPACE    = 42;
const SDL_SCANCODE_TAB          = 43;
const SDL_SCANCODE_SPACE        = 44;
const SDL_SCANCODE_MINUS        = 45;
const SDL_SCANCODE_EQUALS       = 46;
const SDL_SCANCODE_LEFTBRACKET  = 47;
const SDL_SCANCODE_RIGHTBRACKET = 48;
/**
 * Located at the lower left of the return key on ISO keyboards and at the right end of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a French Windows layout.
 */
const SDL_SCANCODE_BACKSLASH = 49;
/**
 * ISO USB keyboards actually use this code instead of 49 for the same key, but all OSes I've seen treat the two codes identically. So, as an implementor, unless your keyboard generates both of those codes and your OS treats them differently, you should generate `SDL_SCANCODE_BACKSLASH` instead of this code. As a user, you should not rely on this code because SDL will never generate it with most (all?) keyboards.
 */
const SDL_SCANCODE_NONUSHASH  = 50;
const SDL_SCANCODE_SEMICOLON  = 51;
const SDL_SCANCODE_APOSTROPHE = 52;
/**
 * Located in the top left corner (on both ANSI and ISO keyboards). Produces GRAVE ACCENT and TILDE in a US Windows layout and in US and UK Mac layouts on ANSI keyboards, GRAVE ACCENT and NOT SIGN in a UK Windows layout, SECTION SIGN and PLUS-MINUS SIGN in US and UK Mac layouts on ISO keyboards, SECTION SIGN and DEGREE SIGN in a Swiss German layout (Mac: only on ISO keyboards), CIRCUMFLEX ACCENT and DEGREE SIGN in a German layout (Mac: only on ISO keyboards), SUPERSCRIPT TWO and TILDE in a French Windows layout, COMMERCIAL AT and NUMBER SIGN in a French Mac layout on ISO keyboards, and LESS-THAN SIGN and GREATER-THAN SIGN in a Swiss German, German, or French Mac layout on ANSI keyboards.
 */
const SDL_SCANCODE_GRAVE       = 53;
const SDL_SCANCODE_COMMA       = 54;
const SDL_SCANCODE_PERIOD      = 55;
const SDL_SCANCODE_SLASH       = 56;
const SDL_SCANCODE_CAPSLOCK    = 57;
const SDL_SCANCODE_F1          = 58;
const SDL_SCANCODE_F2          = 59;
const SDL_SCANCODE_F3          = 60;
const SDL_SCANCODE_F4          = 61;
const SDL_SCANCODE_F5          = 62;
const SDL_SCANCODE_F6          = 63;
const SDL_SCANCODE_F7          = 64;
const SDL_SCANCODE_F8          = 65;
const SDL_SCANCODE_F9          = 66;
const SDL_SCANCODE_F10         = 67;
const SDL_SCANCODE_F11         = 68;
const SDL_SCANCODE_F12         = 69;
const SDL_SCANCODE_PRINTSCREEN = 70;
const SDL_SCANCODE_SCROLLLOCK  = 71;
const SDL_SCANCODE_PAUSE       = 72;
/** insert on PC, help on some Mac keyboards (but does send code 73, not 117) */
const SDL_SCANCODE_INSERT   = 73;
const SDL_SCANCODE_HOME     = 74;
const SDL_SCANCODE_PAGEUP   = 75;
const SDL_SCANCODE_DELETE   = 76;
const SDL_SCANCODE_END      = 77;
const SDL_SCANCODE_PAGEDOWN = 78;
const SDL_SCANCODE_RIGHT    = 79;
const SDL_SCANCODE_LEFT     = 80;
const SDL_SCANCODE_DOWN     = 81;
const SDL_SCANCODE_UP       = 82;
/** num lock on PC, clear on Mac keyboards */
const SDL_SCANCODE_NUMLOCKCLEAR = 83;
const SDL_SCANCODE_KP_DIVIDE    = 84;
const SDL_SCANCODE_KP_MULTIPLY  = 85;
const SDL_SCANCODE_KP_MINUS     = 86;
const SDL_SCANCODE_KP_PLUS      = 87;
const SDL_SCANCODE_KP_ENTER     = 88;
const SDL_SCANCODE_KP_1         = 89;
const SDL_SCANCODE_KP_2         = 90;
const SDL_SCANCODE_KP_3         = 91;
const SDL_SCANCODE_KP_4         = 92;
const SDL_SCANCODE_KP_5         = 93;
const SDL_SCANCODE_KP_6         = 94;
const SDL_SCANCODE_KP_7         = 95;
const SDL_SCANCODE_KP_8         = 96;
const SDL_SCANCODE_KP_9         = 97;
const SDL_SCANCODE_KP_0         = 98;
const SDL_SCANCODE_KP_PERIOD    = 99;
/** This is the additional key that ISO keyboards have over ANSI ones, located between left shift and Y. Produces GRAVE ACCENT and TILDE in a US or UK Mac layout, REVERSE SOLIDUS (backslash) and VERTICAL LINE in a US or UK Windows layout, and LESS-THAN SIGN and GREATER-THAN SIGN in a Swiss German, German, or French layout. */
const SDL_SCANCODE_NONUSBACKSLASH = 100;
/** windows contextual menu, compose */
const SDL_SCANCODE_APPLICATION = 101;
/** The USB document says this is a status flag, not a physical key - but some Mac keyboards do have a power key. */
const SDL_SCANCODE_POWER     = 102;
const SDL_SCANCODE_KP_EQUALS = 103;
const SDL_SCANCODE_F13       = 104;
const SDL_SCANCODE_F14       = 105;
const SDL_SCANCODE_F15       = 106;
const SDL_SCANCODE_F16       = 107;
const SDL_SCANCODE_F17       = 108;
const SDL_SCANCODE_F18       = 109;
const SDL_SCANCODE_F19       = 110;
const SDL_SCANCODE_F20       = 111;
const SDL_SCANCODE_F21       = 112;
const SDL_SCANCODE_F22       = 113;
const SDL_SCANCODE_F23       = 114;
const SDL_SCANCODE_F24       = 115;
const SDL_SCANCODE_EXECUTE   = 116;
const SDL_SCANCODE_HELP      = 117;
const SDL_SCANCODE_MENU      = 118;
const SDL_SCANCODE_SELECT    = 119;
const SDL_SCANCODE_STOP      = 120;
/** redo */
const SDL_SCANCODE_AGAIN             = 121;
const SDL_SCANCODE_UNDO              = 122;
const SDL_SCANCODE_CUT               = 123;
const SDL_SCANCODE_COPY              = 124;
const SDL_SCANCODE_PASTE             = 125;
const SDL_SCANCODE_FIND              = 126;
const SDL_SCANCODE_MUTE              = 127;
const SDL_SCANCODE_VOLUMEUP          = 128;
const SDL_SCANCODE_VOLUMEDOWN        = 129;
const SDL_SCANCODE_LOCKINGCAPSLOCK   = 130;
const SDL_SCANCODE_LOCKINGNUMLOCK    = 131;
const SDL_SCANCODE_LOCKINGSCROLLLOCK = 132;
const SDL_SCANCODE_KP_COMMA          = 133;
const SDL_SCANCODE_KP_EQUALSAS400    = 134;
/** used on Asian keyboards, see footnotes in USB doc */
const SDL_SCANCODE_INTERNATIONAL1 = 135;
const SDL_SCANCODE_INTERNATIONAL2 = 136;
/** Yen */
const SDL_SCANCODE_INTERNATIONAL3 = 137;
const SDL_SCANCODE_INTERNATIONAL4 = 138;
const SDL_SCANCODE_INTERNATIONAL5 = 139;
const SDL_SCANCODE_INTERNATIONAL6 = 140;
const SDL_SCANCODE_INTERNATIONAL7 = 141;
const SDL_SCANCODE_INTERNATIONAL8 = 142;
const SDL_SCANCODE_INTERNATIONAL9 = 143;
/** Hangul/English toggle */
const SDL_SCANCODE_LANG1 = 144;
/** Hanja conversion */
const SDL_SCANCODE_LANG2 = 145;
/** Katakana */
const SDL_SCANCODE_LANG3 = 146;
/** Hiragana */
const SDL_SCANCODE_LANG4 = 147;
/** Zenkaku/Hankaku */
const SDL_SCANCODE_LANG5 = 148;
/** reserved */
const SDL_SCANCODE_LANG6 = 149;
/** reserved */
const SDL_SCANCODE_LANG7 = 150;
/** reserved */
const SDL_SCANCODE_LANG8 = 151;
/** reserved */
const SDL_SCANCODE_LANG9 = 152;
/** Erase-Eaze */
const SDL_SCANCODE_ALTERASE           = 153;
const SDL_SCANCODE_SYSREQ             = 154;
const SDL_SCANCODE_CANCEL             = 155;
const SDL_SCANCODE_CLEAR              = 156;
const SDL_SCANCODE_PRIOR              = 157;
const SDL_SCANCODE_RETURN2            = 158;
const SDL_SCANCODE_SEPARATOR          = 159;
const SDL_SCANCODE_OUT                = 160;
const SDL_SCANCODE_OPER               = 161;
const SDL_SCANCODE_CLEARAGAIN         = 162;
const SDL_SCANCODE_CRSEL              = 163;
const SDL_SCANCODE_EXSEL              = 164;
const SDL_SCANCODE_KP_00              = 176;
const SDL_SCANCODE_KP_000             = 177;
const SDL_SCANCODE_THOUSANDSSEPARATOR = 178;
const SDL_SCANCODE_DECIMALSEPARATOR   = 179;
const SDL_SCANCODE_CURRENCYUNIT       = 180;
const SDL_SCANCODE_CURRENCYSUBUNIT    = 181;
const SDL_SCANCODE_KP_LEFTPAREN       = 182;
const SDL_SCANCODE_KP_RIGHTPAREN      = 183;
const SDL_SCANCODE_KP_LEFTBRACE       = 184;
const SDL_SCANCODE_KP_RIGHTBRACE      = 185;
const SDL_SCANCODE_KP_TAB             = 186;
const SDL_SCANCODE_KP_BACKSPACE       = 187;
const SDL_SCANCODE_KP_A               = 188;
const SDL_SCANCODE_KP_B               = 189;
const SDL_SCANCODE_KP_C               = 190;
const SDL_SCANCODE_KP_D               = 191;
const SDL_SCANCODE_KP_E               = 192;
const SDL_SCANCODE_KP_F               = 193;
const SDL_SCANCODE_KP_XOR             = 194;
const SDL_SCANCODE_KP_POWER           = 195;
const SDL_SCANCODE_KP_PERCENT         = 196;
const SDL_SCANCODE_KP_LESS            = 197;
const SDL_SCANCODE_KP_GREATER         = 198;
const SDL_SCANCODE_KP_AMPERSAND       = 199;
const SDL_SCANCODE_KP_DBLAMPERSAND    = 200;
const SDL_SCANCODE_KP_VERTICALBAR     = 201;
const SDL_SCANCODE_KP_DBLVERTICALBAR  = 202;
const SDL_SCANCODE_KP_COLON           = 203;
const SDL_SCANCODE_KP_HASH            = 204;
const SDL_SCANCODE_KP_SPACE           = 205;
const SDL_SCANCODE_KP_AT              = 206;
const SDL_SCANCODE_KP_EXCLAM          = 207;
const SDL_SCANCODE_KP_MEMSTORE        = 208;
const SDL_SCANCODE_KP_MEMRECALL       = 209;
const SDL_SCANCODE_KP_MEMCLEAR        = 210;
const SDL_SCANCODE_KP_MEMADD          = 211;
const SDL_SCANCODE_KP_MEMSUBTRACT     = 212;
const SDL_SCANCODE_KP_MEMMULTIPLY     = 213;
const SDL_SCANCODE_KP_MEMDIVIDE       = 214;
const SDL_SCANCODE_KP_PLUSMINUS       = 215;
const SDL_SCANCODE_KP_CLEAR           = 216;
const SDL_SCANCODE_KP_CLEARENTRY      = 217;
const SDL_SCANCODE_KP_BINARY          = 218;
const SDL_SCANCODE_KP_OCTAL           = 219;
const SDL_SCANCODE_KP_DECIMAL         = 220;
const SDL_SCANCODE_KP_HEXADECIMAL     = 221;
const SDL_SCANCODE_LCTRL              = 224;
const SDL_SCANCODE_LSHIFT             = 225;
/** alt, option */
const SDL_SCANCODE_LALT = 226;
/** windows, command (apple), meta */
const SDL_SCANCODE_LGUI   = 227;
const SDL_SCANCODE_RCTRL  = 228;
const SDL_SCANCODE_RSHIFT = 229;
/** alt gr, option */
const SDL_SCANCODE_RALT = 230;
/** windows, command (apple), meta */
const SDL_SCANCODE_RGUI = 231;
/** I'm not sure if this is really not covered by any of the above, but since there's a special KMOD_MODE for it I'm adding it here */
const SDL_SCANCODE_MODE           = 257;
const SDL_SCANCODE_AUDIONEXT      = 258;
const SDL_SCANCODE_AUDIOPREV      = 259;
const SDL_SCANCODE_AUDIOSTOP      = 260;
const SDL_SCANCODE_AUDIOPLAY      = 261;
const SDL_SCANCODE_AUDIOMUTE      = 262;
const SDL_SCANCODE_MEDIASELECT    = 263;
const SDL_SCANCODE_WWW            = 264;
const SDL_SCANCODE_MAIL           = 265;
const SDL_SCANCODE_CALCULATOR     = 266;
const SDL_SCANCODE_COMPUTER       = 267;
const SDL_SCANCODE_AC_SEARCH      = 268;
const SDL_SCANCODE_AC_HOME        = 269;
const SDL_SCANCODE_AC_BACK        = 270;
const SDL_SCANCODE_AC_FORWARD     = 271;
const SDL_SCANCODE_AC_STOP        = 272;
const SDL_SCANCODE_AC_REFRESH     = 273;
const SDL_SCANCODE_AC_BOOKMARKS   = 274;
const SDL_SCANCODE_BRIGHTNESSDOWN = 275;
const SDL_SCANCODE_BRIGHTNESSUP   = 276;
/** display mirroring/dual display switch, video mode switch */
const SDL_SCANCODE_DISPLAYSWITCH    = 277;
const SDL_SCANCODE_KBDILLUMTOGGLE   = 278;
const SDL_SCANCODE_KBDILLUMDOWN     = 279;
const SDL_SCANCODE_KBDILLUMUP       = 280;
const SDL_SCANCODE_EJECT            = 281;
const SDL_SCANCODE_SLEEP            = 282;
const SDL_SCANCODE_APP1             = 283;
const SDL_SCANCODE_APP2             = 284;
const SDL_SCANCODE_AUDIOREWIND      = 285;
const SDL_SCANCODE_AUDIOFASTFORWARD = 286;
/** not a key, just marks the number of scancodes for array bounds */
const SDL_NUM_SCANCODES = 512;


/** Never used */
const SDL_WINDOWEVENT_NONE = 0;
/** Window has been shown */
const SDL_WINDOWEVENT_SHOWN = 0;
/** Window has been hidden */
const SDL_WINDOWEVENT_HIDDEN = 0;
/** Window has been exposed and should be redrawn */
const SDL_WINDOWEVENT_EXPOSED = 0;
/** Window has been moved to data1, data2 */
const SDL_WINDOWEVENT_MOVED = 0;
/** Window has been resized to data1xdata2 */
const SDL_WINDOWEVENT_RESIZED = 0;
/** The window size has changed, either as a result of an API call or through the system or user changing the window size. */
const SDL_WINDOWEVENT_SIZE_CHANGED = 0;
/** Window has been minimized */
const SDL_WINDOWEVENT_MINIMIZED = 0;
/** Window has been maximized */
const  SDL_WINDOWEVENT_MAXIMIZED = 0;
/** Window has been restored to normal size and position */
const SDL_WINDOWEVENT_RESTORED = 0;
/** Window has gained mouse focus */
const SDL_WINDOWEVENT_ENTER = 0;
/** Window has lost mouse focus */
const SDL_WINDOWEVENT_LEAVE = 0;
/** Window has gained keyboard focus */
const SDL_WINDOWEVENT_FOCUS_GAINED = 0;
/** Window has lost keyboard focus */
const SDL_WINDOWEVENT_FOCUS_LOST = 0;
/** The window manager requests that the window be closed */
const SDL_WINDOWEVENT_CLOSE = 0;
/** Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
const SDL_WINDOWEVENT_TAKE_FOCUS = 0;
/** Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
const SDL_WINDOWEVENT_HIT_TEST = 0;

const KMOD_NONE     = 0x0000;
const KMOD_LSHIFT   = 0x0001;
const KMOD_RSHIFT   = 0x0002;
const KMOD_LCTRL    = 0x0040;
const KMOD_RCTRL    = 0x0080;
const KMOD_LALT     = 0x0100;
const KMOD_RALT     = 0x0200;
const KMOD_LGUI     = 0x0400;
const KMOD_RGUI     = 0x0800;
const KMOD_NUM      = 0x1000;
const KMOD_CAPS     = 0x2000;
const KMOD_MODE     = 0x4000;
const KMOD_RESERVED = 0x8000;

const SDLK_UNKNOWN            = 0;
const SDLK_RETURN             = "\r";
const SDLK_ESCAPE             = "\033";
const SDLK_BACKSPACE          = "\b";
const SDLK_TAB                = "\t";
const SDLK_SPACE              = " ";
const SDLK_EXCLAIM            = "!";
const SDLK_QUOTEDBL           = "\"";
const SDLK_HASH               = "#";
const SDLK_PERCENT            = "%";
const SDLK_DOLLAR             = "$";
const SDLK_AMPERSAND          = "&";
const SDLK_QUOTE              = "\"";
const SDLK_LEFTPAREN          = "(";
const SDLK_RIGHTPAREN         = ")";
const SDLK_ASTERISK           = "*";
const SDLK_PLUS               = "+";
const SDLK_COMMA              = ",";
const SDLK_MINUS              = "-";
const SDLK_PERIOD             = ".";
const SDLK_SLASH              = "/";
const SDLK_0                  = "0";
const SDLK_1                  = "1";
const SDLK_2                  = "2";
const SDLK_3                  = "3";
const SDLK_4                  = "4";
const SDLK_5                  = "5";
const SDLK_6                  = "6";
const SDLK_7                  = "7";
const SDLK_8                  = "8";
const SDLK_9                  = "9";
const SDLK_COLON              = ":";
const SDLK_SEMICOLON          = ";";
const SDLK_LESS               = "<";
const SDLK_EQUALS             = "=";
const SDLK_GREATER            = ">";
const SDLK_QUESTION           = "?";
const SDLK_AT                 = "@";
const SDLK_LEFTBRACKET        = "[";
const SDLK_BACKSLASH          = "\\";
const SDLK_RIGHTBRACKET       = "]";
const SDLK_CARET              = "^";
const SDLK_UNDERSCORE         = "_";
const SDLK_BACKQUOTE          = "`";
const SDLK_a                  = "a";
const SDLK_b                  = "b";
const SDLK_c                  = "c";
const SDLK_d                  = "d";
const SDLK_e                  = "e";
const SDLK_f                  = "f";
const SDLK_g                  = "g";
const SDLK_h                  = "h";
const SDLK_i                  = "i";
const SDLK_j                  = "j";
const SDLK_k                  = "k";
const SDLK_l                  = "l";
const SDLK_m                  = "m";
const SDLK_n                  = "n";
const SDLK_o                  = "o";
const SDLK_p                  = "p";
const SDLK_q                  = "q";
const SDLK_r                  = "r";
const SDLK_s                  = "s";
const SDLK_t                  = "t";
const SDLK_u                  = "u";
const SDLK_v                  = "v";
const SDLK_w                  = "w";
const SDLK_x                  = "x";
const SDLK_y                  = "y";
const SDLK_z                  = "z";
const SDLK_CAPSLOCK           = SDL_SCANCODE_CAPSLOCK    | (1 << 30);
const SDLK_F1                 = SDL_SCANCODE_F1          | (1 << 30);
const SDLK_F2                 = SDL_SCANCODE_F2          | (1 << 30);
const SDLK_F3                 = SDL_SCANCODE_F3          | (1 << 30);
const SDLK_F4                 = SDL_SCANCODE_F4          | (1 << 30);
const SDLK_F5                 = SDL_SCANCODE_F5          | (1 << 30);
const SDLK_F6                 = SDL_SCANCODE_F6          | (1 << 30);
const SDLK_F7                 = SDL_SCANCODE_F7          | (1 << 30);
const SDLK_F8                 = SDL_SCANCODE_F8          | (1 << 30);
const SDLK_F9                 = SDL_SCANCODE_F9          | (1 << 30);
const SDLK_F10                = SDL_SCANCODE_F10         | (1 << 30);
const SDLK_F11                = SDL_SCANCODE_F11         | (1 << 30);
const SDLK_F12                = SDL_SCANCODE_F12         | (1 << 30);
const SDLK_PRINTSCREEN        = SDL_SCANCODE_PRINTSCREEN | (1 << 30);
const SDLK_SCROLLLOCK         = SDL_SCANCODE_SCROLLLOCK  | (1 << 30);
const SDLK_PAUSE              = SDL_SCANCODE_PAUSE       | (1 << 30);
const SDLK_INSERT             = SDL_SCANCODE_INSERT      | (1 << 30);
const SDLK_HOME               = SDL_SCANCODE_HOME        | (1 << 30);
const SDLK_PAGEUP             = SDL_SCANCODE_PAGEUP      | (1 << 30);
const SDLK_DELETE             = "\177";
const SDLK_END                = SDL_SCANCODE_END                | (1 << 30);
const SDLK_PAGEDOWN           = SDL_SCANCODE_PAGEDOWN           | (1 << 30);
const SDLK_RIGHT              = SDL_SCANCODE_RIGHT              | (1 << 30);
const SDLK_LEFT               = SDL_SCANCODE_LEFT               | (1 << 30);
const SDLK_DOWN               = SDL_SCANCODE_DOWN               | (1 << 30);
const SDLK_UP                 = SDL_SCANCODE_UP                 | (1 << 30);
const SDLK_NUMLOCKCLEAR       = SDL_SCANCODE_NUMLOCKCLEAR       | (1 << 30);
const SDLK_KP_DIVIDE          = SDL_SCANCODE_KP_DIVIDE          | (1 << 30);
const SDLK_KP_MULTIPLY        = SDL_SCANCODE_KP_MULTIPLY        | (1 << 30);
const SDLK_KP_MINUS           = SDL_SCANCODE_KP_MINUS           | (1 << 30);
const SDLK_KP_PLUS            = SDL_SCANCODE_KP_PLUS            | (1 << 30);
const SDLK_KP_ENTER           = SDL_SCANCODE_KP_ENTER           | (1 << 30);
const SDLK_KP_1               = SDL_SCANCODE_KP_1               | (1 << 30);
const SDLK_KP_2               = SDL_SCANCODE_KP_2               | (1 << 30);
const SDLK_KP_3               = SDL_SCANCODE_KP_3               | (1 << 30);
const SDLK_KP_4               = SDL_SCANCODE_KP_4               | (1 << 30);
const SDLK_KP_5               = SDL_SCANCODE_KP_5               | (1 << 30);
const SDLK_KP_6               = SDL_SCANCODE_KP_6               | (1 << 30);
const SDLK_KP_7               = SDL_SCANCODE_KP_7               | (1 << 30);
const SDLK_KP_8               = SDL_SCANCODE_KP_8               | (1 << 30);
const SDLK_KP_9               = SDL_SCANCODE_KP_9               | (1 << 30);
const SDLK_KP_0               = SDL_SCANCODE_KP_0               | (1 << 30);
const SDLK_KP_PERIOD          = SDL_SCANCODE_KP_PERIOD          | (1 << 30);
const SDLK_APPLICATION        = SDL_SCANCODE_APPLICATION        | (1 << 30);
const SDLK_POWER              = SDL_SCANCODE_POWER              | (1 << 30);
const SDLK_KP_EQUALS          = SDL_SCANCODE_KP_EQUALS          | (1 << 30);
const SDLK_F13                = SDL_SCANCODE_F13                | (1 << 30);
const SDLK_F14                = SDL_SCANCODE_F14                | (1 << 30);
const SDLK_F15                = SDL_SCANCODE_F15                | (1 << 30);
const SDLK_F16                = SDL_SCANCODE_F16                | (1 << 30);
const SDLK_F17                = SDL_SCANCODE_F17                | (1 << 30);
const SDLK_F18                = SDL_SCANCODE_F18                | (1 << 30);
const SDLK_F19                = SDL_SCANCODE_F19                | (1 << 30);
const SDLK_F20                = SDL_SCANCODE_F20                | (1 << 30);
const SDLK_F21                = SDL_SCANCODE_F21                | (1 << 30);
const SDLK_F22                = SDL_SCANCODE_F22                | (1 << 30);
const SDLK_F23                = SDL_SCANCODE_F23                | (1 << 30);
const SDLK_F24                = SDL_SCANCODE_F24                | (1 << 30);
const SDLK_EXECUTE            = SDL_SCANCODE_EXECUTE            | (1 << 30);
const SDLK_HELP               = SDL_SCANCODE_HELP               | (1 << 30);
const SDLK_MENU               = SDL_SCANCODE_MENU               | (1 << 30);
const SDLK_SELECT             = SDL_SCANCODE_SELECT             | (1 << 30);
const SDLK_STOP               = SDL_SCANCODE_STOP               | (1 << 30);
const SDLK_AGAIN              = SDL_SCANCODE_AGAIN              | (1 << 30);
const SDLK_UNDO               = SDL_SCANCODE_UNDO               | (1 << 30);
const SDLK_CUT                = SDL_SCANCODE_CUT                | (1 << 30);
const SDLK_COPY               = SDL_SCANCODE_COPY               | (1 << 30);
const SDLK_PASTE              = SDL_SCANCODE_PASTE              | (1 << 30);
const SDLK_FIND               = SDL_SCANCODE_FIND               | (1 << 30);
const SDLK_MUTE               = SDL_SCANCODE_MUTE               | (1 << 30);
const SDLK_VOLUMEUP           = SDL_SCANCODE_VOLUMEUP           | (1 << 30);
const SDLK_VOLUMEDOWN         = SDL_SCANCODE_VOLUMEDOWN         | (1 << 30);
const SDLK_KP_COMMA           = SDL_SCANCODE_KP_COMMA           | (1 << 30);
const SDLK_KP_EQUALSAS400     = SDL_SCANCODE_KP_EQUALSAS400     | (1 << 30);
const SDLK_ALTERASE           = SDL_SCANCODE_ALTERASE           | (1 << 30);
const SDLK_SYSREQ             = SDL_SCANCODE_SYSREQ             | (1 << 30);
const SDLK_CANCEL             = SDL_SCANCODE_CANCEL             | (1 << 30);
const SDLK_CLEAR              = SDL_SCANCODE_CLEAR              | (1 << 30);
const SDLK_PRIOR              = SDL_SCANCODE_PRIOR              | (1 << 30);
const SDLK_RETURN2            = SDL_SCANCODE_RETURN2            | (1 << 30);
const SDLK_SEPARATOR          = SDL_SCANCODE_SEPARATOR          | (1 << 30);
const SDLK_OUT                = SDL_SCANCODE_OUT                | (1 << 30);
const SDLK_OPER               = SDL_SCANCODE_OPER               | (1 << 30);
const SDLK_CLEARAGAIN         = SDL_SCANCODE_CLEARAGAIN         | (1 << 30);
const SDLK_CRSEL              = SDL_SCANCODE_CRSEL              | (1 << 30);
const SDLK_EXSEL              = SDL_SCANCODE_EXSEL              | (1 << 30);
const SDLK_KP_00              = SDL_SCANCODE_KP_00              | (1 << 30);
const SDLK_KP_000             = SDL_SCANCODE_KP_000             | (1 << 30);
const SDLK_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR | (1 << 30);
const SDLK_DECIMALSEPARATOR   = SDL_SCANCODE_DECIMALSEPARATOR   | (1 << 30);
const SDLK_CURRENCYUNIT       = SDL_SCANCODE_CURRENCYUNIT       | (1 << 30);
const SDLK_CURRENCYSUBUNIT    = SDL_SCANCODE_CURRENCYSUBUNIT    | (1 << 30);
const SDLK_KP_LEFTPAREN       = SDL_SCANCODE_KP_LEFTPAREN       | (1 << 30);
const SDLK_KP_RIGHTPAREN      = SDL_SCANCODE_KP_RIGHTPAREN      | (1 << 30);
const SDLK_KP_LEFTBRACE       = SDL_SCANCODE_KP_LEFTBRACE       | (1 << 30);
const SDLK_KP_RIGHTBRACE      = SDL_SCANCODE_KP_RIGHTBRACE      | (1 << 30);
const SDLK_KP_TAB             = SDL_SCANCODE_KP_TAB             | (1 << 30);
const SDLK_KP_BACKSPACE       = SDL_SCANCODE_KP_BACKSPACE       | (1 << 30);
const SDLK_KP_A               = SDL_SCANCODE_KP_A               | (1 << 30);
const SDLK_KP_B               = SDL_SCANCODE_KP_B               | (1 << 30);
const SDLK_KP_C               = SDL_SCANCODE_KP_C               | (1 << 30);
const SDLK_KP_D               = SDL_SCANCODE_KP_D               | (1 << 30);
const SDLK_KP_E               = SDL_SCANCODE_KP_E               | (1 << 30);
const SDLK_KP_F               = SDL_SCANCODE_KP_F               | (1 << 30);
const SDLK_KP_XOR             = SDL_SCANCODE_KP_XOR             | (1 << 30);
const SDLK_KP_POWER           = SDL_SCANCODE_KP_POWER           | (1 << 30);
const SDLK_KP_PERCENT         = SDL_SCANCODE_KP_PERCENT         | (1 << 30);
const SDLK_KP_LESS            = SDL_SCANCODE_KP_LESS            | (1 << 30);
const SDLK_KP_GREATER         = SDL_SCANCODE_KP_GREATER         | (1 << 30);
const SDLK_KP_AMPERSAND       = SDL_SCANCODE_KP_AMPERSAND       | (1 << 30);
const SDLK_KP_DBLAMPERSAND    = SDL_SCANCODE_KP_DBLAMPERSAND    | (1 << 30);
const SDLK_KP_VERTICALBAR     = SDL_SCANCODE_KP_VERTICALBAR     | (1 << 30);
const SDLK_KP_DBLVERTICALBAR  = SDL_SCANCODE_KP_DBLVERTICALBAR  | (1 << 30);
const SDLK_KP_COLON           = SDL_SCANCODE_KP_COLON           | (1 << 30);
const SDLK_KP_HASH            = SDL_SCANCODE_KP_HASH            | (1 << 30);
const SDLK_KP_SPACE           = SDL_SCANCODE_KP_SPACE           | (1 << 30);
const SDLK_KP_AT              = SDL_SCANCODE_KP_AT              | (1 << 30);
const SDLK_KP_EXCLAM          = SDL_SCANCODE_KP_EXCLAM          | (1 << 30);
const SDLK_KP_MEMSTORE        = SDL_SCANCODE_KP_MEMSTORE        | (1 << 30);
const SDLK_KP_MEMRECALL       = SDL_SCANCODE_KP_MEMRECALL       | (1 << 30);
const SDLK_KP_MEMCLEAR        = SDL_SCANCODE_KP_MEMCLEAR        | (1 << 30);
const SDLK_KP_MEMADD          = SDL_SCANCODE_KP_MEMADD          | (1 << 30);
const SDLK_KP_MEMSUBTRACT     = SDL_SCANCODE_KP_MEMSUBTRACT     | (1 << 30);
const SDLK_KP_MEMMULTIPLY     = SDL_SCANCODE_KP_MEMMULTIPLY     | (1 << 30);
const SDLK_KP_MEMDIVIDE       = SDL_SCANCODE_KP_MEMDIVIDE       | (1 << 30);
const SDLK_KP_PLUSMINUS       = SDL_SCANCODE_KP_PLUSMINUS       | (1 << 30);
const SDLK_KP_CLEAR           = SDL_SCANCODE_KP_CLEAR           | (1 << 30);
const SDLK_KP_CLEARENTRY      = SDL_SCANCODE_KP_CLEARENTRY      | (1 << 30);
const SDLK_KP_BINARY          = SDL_SCANCODE_KP_BINARY          | (1 << 30);
const SDLK_KP_OCTAL           = SDL_SCANCODE_KP_OCTAL           | (1 << 30);
const SDLK_KP_DECIMAL         = SDL_SCANCODE_KP_DECIMAL         | (1 << 30);
const SDLK_KP_HEXADECIMAL     = SDL_SCANCODE_KP_HEXADECIMAL     | (1 << 30);
const SDLK_LCTRL              = SDL_SCANCODE_LCTRL              | (1 << 30);
const SDLK_LSHIFT             = SDL_SCANCODE_LSHIFT             | (1 << 30);
const SDLK_LALT               = SDL_SCANCODE_LALT               | (1 << 30);
const SDLK_LGUI               = SDL_SCANCODE_LGUI               | (1 << 30);
const SDLK_RCTRL              = SDL_SCANCODE_RCTRL              | (1 << 30);
const SDLK_RSHIFT             = SDL_SCANCODE_RSHIFT             | (1 << 30);
const SDLK_RALT               = SDL_SCANCODE_RALT               | (1 << 30);
const SDLK_RGUI               = SDL_SCANCODE_RGUI               | (1 << 30);
const SDLK_MODE               = SDL_SCANCODE_MODE               | (1 << 30);
const SDLK_AUDIONEXT          = SDL_SCANCODE_AUDIONEXT          | (1 << 30);
const SDLK_AUDIOPREV          = SDL_SCANCODE_AUDIOPREV          | (1 << 30);
const SDLK_AUDIOSTOP          = SDL_SCANCODE_AUDIOSTOP          | (1 << 30);
const SDLK_AUDIOPLAY          = SDL_SCANCODE_AUDIOPLAY          | (1 << 30);
const SDLK_AUDIOMUTE          = SDL_SCANCODE_AUDIOMUTE          | (1 << 30);
const SDLK_MEDIASELECT        = SDL_SCANCODE_MEDIASELECT        | (1 << 30);
const SDLK_WWW                = SDL_SCANCODE_WWW                | (1 << 30);
const SDLK_MAIL               = SDL_SCANCODE_MAIL               | (1 << 30);
const SDLK_CALCULATOR         = SDL_SCANCODE_CALCULATOR         | (1 << 30);
const SDLK_COMPUTER           = SDL_SCANCODE_COMPUTER           | (1 << 30);
const SDLK_AC_SEARCH          = SDL_SCANCODE_AC_SEARCH          | (1 << 30);
const SDLK_AC_HOME            = SDL_SCANCODE_AC_HOME            | (1 << 30);
const SDLK_AC_BACK            = SDL_SCANCODE_AC_BACK            | (1 << 30);
const SDLK_AC_FORWARD         = SDL_SCANCODE_AC_FORWARD         | (1 << 30);
const SDLK_AC_STOP            = SDL_SCANCODE_AC_STOP            | (1 << 30);
const SDLK_AC_REFRESH         = SDL_SCANCODE_AC_REFRESH         | (1 << 30);
const SDLK_AC_BOOKMARKS       = SDL_SCANCODE_AC_BOOKMARKS       | (1 << 30);
const SDLK_BRIGHTNESSDOWN     = SDL_SCANCODE_BRIGHTNESSDOWN     | (1 << 30);
const SDLK_BRIGHTNESSUP       = SDL_SCANCODE_BRIGHTNESSUP       | (1 << 30);
const SDLK_DISPLAYSWITCH      = SDL_SCANCODE_DISPLAYSWITCH      | (1 << 30);
const SDLK_KBDILLUMTOGGLE     = SDL_SCANCODE_KBDILLUMTOGGLE     | (1 << 30);
const SDLK_KBDILLUMDOWN       = SDL_SCANCODE_KBDILLUMDOWN       | (1 << 30);
const SDLK_KBDILLUMUP         = SDL_SCANCODE_KBDILLUMUP         | (1 << 30);
const SDLK_EJECT              = SDL_SCANCODE_EJECT              | (1 << 30);
const SDLK_SLEEP              = SDL_SCANCODE_SLEEP              | (1 << 30);
const SDLK_APP1               = SDL_SCANCODE_APP1               | (1 << 30);
const SDLK_APP2               = SDL_SCANCODE_APP2               | (1 << 30);
const SDLK_AUDIOREWIND        = SDL_SCANCODE_AUDIOREWIND        | (1 << 30);
const SDLK_AUDIOFASTFORWARD   = SDL_SCANCODE_AUDIOFASTFORWARD   | (1 << 30);

const SDL_MUTEX_TIMEDOUT = 0;

const SDL_PIXELFORMAT_UNKNOWN   = 0;
const SDL_PIXELFORMAT_INDEX1LSB = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_INDEX1) << 24) 
    | ((SDL_BITMAPORDER_4321) << 20) 
    | ((0) << 16) 
    | ((1) << 8) 
    | ((0) << 0)
);

const SDL_PIXELFORMAT_INDEX1MSB = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_INDEX1) << 24) 
    | ((SDL_BITMAPORDER_1234) << 20) 
    | ((0) << 16) 
    | ((1) << 8) 
    | ((0) << 0)
);

const SDL_PIXELFORMAT_INDEX4LSB = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_INDEX4) << 24) 
    | ((SDL_BITMAPORDER_4321) << 20) 
    | ((0) << 16) 
    | ((4) << 8) 
    | ((0) << 0)
);

const SDL_PIXELFORMAT_INDEX4MSB = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_INDEX4) << 24) 
    | ((SDL_BITMAPORDER_1234) << 20) 
    | ((0) << 16) 
    | ((4) << 8) 
    | ((0) << 0)
);
const SDL_PIXELFORMAT_INDEX8 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_INDEX8) << 24) 
    | ((0) << 20) 
    | ((0) << 16) 
    | ((8) << 8) 
    | ((1) << 0)
);
const SDL_PIXELFORMAT_RGB332 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED8) << 24) 
    | ((SDL_PACKEDORDER_XRGB) << 20) 
    | ((SDL_PACKEDLAYOUT_332) << 16) 
    | ((8) << 8) 
    | ((1) << 0)
);
const SDL_PIXELFORMAT_RGB444 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_XRGB) << 20) 
    | ((SDL_PACKEDLAYOUT_4444) << 16) 
    | ((12) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_RGB555 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_XRGB) << 20) 
    | ((SDL_PACKEDLAYOUT_1555) << 16) 
    | ((15) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_BGR555 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_XBGR) << 20) 
    | ((SDL_PACKEDLAYOUT_1555) << 16) 
    | ((15) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_ARGB4444 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_ARGB) << 20) 
    | ((SDL_PACKEDLAYOUT_4444) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_RGBA4444 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_RGBA) << 20) 
    | ((SDL_PACKEDLAYOUT_4444) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_ABGR4444 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_ABGR) << 20) 
    | ((SDL_PACKEDLAYOUT_4444) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_BGRA4444 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_BGRA) << 20) 
    | ((SDL_PACKEDLAYOUT_4444) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_ARGB1555 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_ARGB) << 20) 
    | ((SDL_PACKEDLAYOUT_1555) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_RGBA5551 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_RGBA) << 20) 
    | ((SDL_PACKEDLAYOUT_5551) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_ABGR1555 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_ABGR) << 20) 
    | ((SDL_PACKEDLAYOUT_1555) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_BGRA5551 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_BGRA) << 20) 
    | ((SDL_PACKEDLAYOUT_5551) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_RGB565 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_XRGB) << 20) 
    | ((SDL_PACKEDLAYOUT_565) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_BGR565 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED16) << 24) 
    | ((SDL_PACKEDORDER_XBGR) << 20) 
    | ((SDL_PACKEDLAYOUT_565) << 16) 
    | ((16) << 8) 
    | ((2) << 0)
);
const SDL_PIXELFORMAT_RGB24 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_ARRAYU8) << 24) 
    | ((SDL_ARRAYORDER_RGB) << 20) 
    | ((0) << 16) 
    | ((24) << 8) 
    | ((3) << 0)
);
const SDL_PIXELFORMAT_BGR24 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_ARRAYU8) << 24) 
    | ((SDL_ARRAYORDER_BGR) << 20) 
    | ((0) << 16) 
    | ((24) << 8) 
    | ((3) << 0)
);
const SDL_PIXELFORMAT_RGB888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_XRGB) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((24) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_RGBX8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_RGBX) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((24) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_BGR888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_XBGR) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((24) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_BGRX8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_BGRX) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((24) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_ARGB8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_ARGB) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((32) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_RGBA8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_RGBA) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((32) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_ABGR8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_ABGR) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((32) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_BGRA8888 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_BGRA) << 20) 
    | ((SDL_PACKEDLAYOUT_8888) << 16) 
    | ((32) << 8) 
    | ((4) << 0)
);
const SDL_PIXELFORMAT_ARGB2101010 = (
    (1 << 28) 
    | ((SDL_PIXELTYPE_PACKED32) << 24) 
    | ((SDL_PACKEDORDER_ARGB) << 20) 
    | ((SDL_PACKEDLAYOUT_2101010) << 16) 
    | ((32) << 8) 
    | ((4) << 0)
);

const SDL_PIXELFORMAT_YV12         = (((int)((string)'Y')) << 0) | (((int)((string)'V')) << 8) | (((int)((string)'1')) << 16) | (((int)((string)'2')) << 24);
const SDL_PIXELFORMAT_IYUV         = (((int)((string)'I')) << 0) | (((int)((string)'Y')) << 8) | (((int)((string)'U')) << 16) | (((int)((string)'V')) << 24);
const SDL_PIXELFORMAT_YUY2         = (((int)((string)'Y')) << 0) | (((int)((string)'U')) << 8) | (((int)((string)'Y')) << 16) | (((int)((string)'2')) << 24);
const SDL_PIXELFORMAT_UYVY         = (((int)((string)'U')) << 0) | (((int)((string)'Y')) << 8) | (((int)((string)'V')) << 16) | (((int)((string)'Y')) << 24);
const SDL_PIXELFORMAT_YVYU         = (((int)((string)'Y')) << 0) | (((int)((string)'V')) << 8) | (((int)((string)'Y')) << 16) | (((int)((string)'U')) << 24);
const SDL_PIXELFORMAT_NV12         = (((int)((string)'N')) << 0) | (((int)((string)'V')) << 8) | (((int)((string)'1')) << 16) | (((int)((string)'2')) << 24);
const SDL_PIXELFORMAT_NV21         = (((int)((string)'N')) << 0) | (((int)((string)'V')) << 8) | (((int)((string)'2')) << 16) | (((int)((string)'1')) << 24);
const SDL_PIXELFORMAT_EXTERNAL_OES = (((int)((string)'O')) << 0) | (((int)((string)'E')) << 8) | (((int)((string)'S')) << 16) | (((int)((string)' ')) << 24);


const RW_SEEK_SET = 0;
const RW_SEEK_CUR = 1;
const RW_SEEK_END = 2;


const SDL_MESSAGEBOX_COLOR_BACKGROUND        = 0;
const SDL_MESSAGEBOX_COLOR_TEXT              = 1;
const SDL_MESSAGEBOX_COLOR_BUTTON_BORDER     = 2;
const SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND = 3;
const SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED   = 4;
const SDL_MESSAGEBOX_COLOR_MAX               = 5;

const SDL_MESSAGEBOX_ERROR       = 0x00000010;
const SDL_MESSAGEBOX_WARNING     = 0x00000020;
const SDL_MESSAGEBOX_INFORMATION = 0x00000040;
// row 1070