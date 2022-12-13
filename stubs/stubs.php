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

class SDL_MessageBoxData implements Stringable {
    const ERROR       = 0x00000010;
    const WARNING     = 0x00000020;
    const INFORMATION = 0x00000040;

    public function __construct(
        public int $flags,
        public string $title,
        public string $message,
        public array $buttons = [],
        public array $colors = [],
        public null|SDL_Window $window = null,
    ) {
    }

    public function Show(int &$id):int {
        return 0;
    }
    
    public function __toString(): string {
        return '';
    }
}

class SDL_MessageBoxColor implements Stringable {
    const BACKGROUND        = 0;
    const TEXT              = 1;
    const BUTTON_BORDER     = 2;
    const BUTTON_BACKGROUND = 3;
    const BUTTON_SELECTED   = 4;
    const MAX               = 5;

    public function __construct(
        public int $r,
        public int $g,
        public int $b,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_MessageBoxButtonData implements Stringable {
    const RETURNKEY_DEFAULT = 0x00000001;
    const ESCAPEKEY_DEFAULT = 0x00000002;

    public function __construct(
        public int $flags,
        public int $id,
        public string $text,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_Window implements Stringable {
    const FULLSCREEN         = 0x00000001;
    const OPENGL             = 0x00000002;
    const SHOWN              = 0x00000004;
    const HIDDEN             = 0x00000008;
    const BORDERLESS         = 0x00000010;
    const RESIZABLE          = 0x00000020;
    const MINIMIZED          = 0x00000040;
    const MAXIMIZED          = 0x00000080;
    const INPUT_GRABBED      = 0x00000100;
    const INPUT_FOCUS        = 0x00000200;
    const MOUSE_FOCUS        = 0x00000400;
    const FULLSCREEN_DESKTOP = ( SDL_Window::FULLSCREEN | 0x00001000 );
    const FOREIGN            = 0x00000800;
    const ALLOW_HIGHDPI      = 0x00002000;

    public int $event;

    public function __construct(
        public string $title,
        public int $x,
        public int $y,
        public int $w,
        public int $h,
        public int $flags,
    ) {
    }

    public function setTitle(string $title):void {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_Cursor implements Stringable {
    const ARROW     = 0;
    const IBEAM     = 1;
    const WAIT      = 2;
    const CROSSHAIR = 3;
    const WAITARROW = 4;
    const SIZENWSE  = 5;
    const SIZENESW  = 6;
    const SIZEWE    = 7;
    const SIZENS    = 8;
    const SIZEALL   = 9;
    const NO        = 10;
    const HAND      = 11;

    /**
     * Create a system cursor.
     * @param  int        $id one of the `SDL_Cursor::*` constants.
     * @return SDL_Cursor
     */
    public static function CreateSystem(int $id):SDL_Cursor {
        return new self(
            '',
            0,
            0,
            0,
            0,
            0,
        );
    }

    public function __construct(
        public string $data,
        public int $mask,
        public int $w,
        public int $h,
        public int $x,
        public int $y,
    ) {
    }

    /**
     * Frees a cursor created with `SDL_CreateCursor()`.
     * @return void
     */
    public function Free():void {
    }

    /**
     * @return void
     */
    public function Set():void {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_WindowShapeMode implements Stringable {
    /** The default mode, a binarized alpha cutoff of 1. */
    const Default = 0;
    
    /** A binarized alpha cutoff with a given integer value. */
    const BinarizeAlpha = 1;

    /** A binarized alpha cutoff with a given integer value, but with the opposite comparison. */
    const ReverseBinarizeAlpha = 2;

    /** A color key is applied. */
    const ColorKey = 3;

    public function __construct(
        private int $mode,
        private mixed $param,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_Event implements Stringable {
    public SDL_Window $window;

    public function __construct() {
    }

    public function __toString(): string {
        return '';
    }
}


class SDL_Point implements Stringable {
    public function __construct(
        public int $x,
        public int $y
    ) {
    }
    public function __toString(): string {
        return '';
    }
}

class SDL_Rect implements Stringable {
    public function __construct(
        public int $x = 0,
        public int $y = 0,
        public int $w = 0,
        public int $h = 0,
    ) {
    }

    
    public function Empty(): bool {
        return true;
    }
    
    public function HasIntersection(SDL_Rect $B): bool {
        return true;
    }
    
    public function Intersect(SDL_Rect $B, ?SDL_Rect &$result): bool {
        return true;
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_FPoint implements Stringable {
    public function __construct(
        public float $x,
        public float $y
    ) {
    }
    public function __toString(): string {
        return '';
    }
}

class SDL_FRect implements Stringable {
    public function __construct(
        public float $x = 0,
        public float $y = 0,
        public float $w = 0,
        public float $h = 0
    ) {
    }
    public function __toString(): string {
        return '';
    }

    public function Empty(): bool {
        return true;
    }
    
    public function HasIntersection(SDL_FRect $B): bool {
        return true;
    }

    public function Intersect(SDL_FRect $B, ?SDL_FRect &$result): bool {
        return true;
    }
}

class SDL_Color implements Stringable {
    public function __construct(
        public int $r,
        public int $g,
        public int $b,
        public int $a,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_Palette implements Stringable {
    public function __construct(
        public int $ncolors,
    ) {
    }

    
    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|SDL_Color {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        SDL_Color $value
    ): null|false {
        return null;
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_PixelFormat implements Stringable {
    public function __construct(
        public int $format,
        public SDL_Palette $palette,
        public int $BitsPerPixel,
        public int $BytesPerPixel,
        public int $padding,
        public int $Rmask,
        public int $Gmask,
        public int $Bmask,
        public int $Amask,
        public int $Rloss,
        public int $Gloss,
        public int $Bloss,
        public int $Aloss,
        public int $Rshift,
        public int $Gshift,
        public int $Bshift,
        public int $Ashift,
        public int $refcount,
        public SDL_PixelFormat $next,
    ) {
    }

    public function GetRGB(
        int &$r,
        int &$g,
        int &$b,
    ): void {
    }

    public function GetRGBA(
        int &$r,
        int &$g,
        int &$b,
        int &$a,
    ): void {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_BlitInfo {
    public function __construct(
        public int $a,
        public int $b,
        public int $colorkey,
        public int $dst,
        public SDL_PixelFormat $dst_fmt,
        public int $dst_h,
        public int $dst_pitch,
        public int $dst_skip,
        public int $dst_w,
        public int $flags,
        public int $g,
        public int $r,
        public int $src,
        public SDL_PixelFormat $src_fmt,
        public int $src_h,
        public int $src_pitch,
        public int $src_skip,
        public int $src_w,
        public int $table,
    ) {
    }
}

class SDL_blit {
    public function __construct(
        public SDL_Surface &$src,
        public SDL_Rect &$srcrect,
        public SDL_Surface &$dst,
        public SDL_Rect &$dstrect,
    ) {
    }
}

class SDL_BlitMap {
    public function __construct(
        public SDL_blit $blit,
        public mixed $data,
        public SDL_Surface $dst,
        public int $dst_palette_version,
        public int $identity,
        public SDL_BlitInfo $info,
        public int $src_palette_version,
    ) {
    }
}

class SDL_RWops implements Stringable {
    public function __toString(): string {
        return '';
    }
}

class SDL_Surface implements Stringable {
    public function __construct(
        public int $flags,
        public SDL_PixelFormat $format,
        public int $w,
        public int $h,
        public int $pitch,
        public mixed $pixels,
        public mixed $userdata,
        public int $locked,
        public mixed $lock_data,
        public SDL_Rect $clip_rect,
        public SDL_BlitMap $map,
        public int $refcount,
    ) {
    }

    /**
     * Load a /usr/share/code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.htmlsurface from a file.
     * 
     * stream are supported.
     * @param  string|resource  $file
     * @return null|SDL_Surface
     */
    public static function LoadBMP(string $file):null|SDL_Surface {
        return null;
    }

    /**
     * Performs a fast fill of the given rectangle with `$color`.
     *
     * If `$rect` is `NULL`, the whole surface will be filled with  `$color`.
     *
     * The color should be a pixel of the format used by the surface, and can be generated by the `SDL_MapRGB()` function.
     * @param  SDL_Rect $rect
     * @param  int      $color
     * @return void     0 on success, or -1 on error.
     */
    public function FillRect(
        SDL_Rect $rect,
        int $color
    ):int {
        return 0;
    }

    /**
     * 
     * @param  array<SDL_Rect> $rects
     * @param  int             $count
     * @param  int             $color
     * @return int
     */
    public function FillRects(
        array $rects,
        int $count,
        int $color
    ):int {
        return 0;
    }

    /**
     * Evaluates to true if the surface needs to be locked before access.
     * define SDL_MUSTLOCK(S) (((S)->flags & SDL_RLEACCEL) != 0)
     * @return bool
     */
    public function MUSTLOCK():bool {
        return true;
    }

    /**
     * Performs a fast blit from the source surface to the destination surface.
     *
     * This assumes that the source and destination rectangles are
     * the same size.  If either `$srcrect` or `$dstrect` are `NULL`, the entire
     * surface (`$src` or `$dst`) is copied.  The final blit rectangles are saved
     * in `$srcrect` and `$dstrect` after all clipping is performed.
     *
     * The blit function should not be called on a locked surface.
     * @param  SDL_Rect      $srcrect
     * @param  SDL_Surface   $dst
     * @param  SDL_Rect|null $dstrect
     * @return void          returns 0, otherwise it returns -1.
     */
    public function Blit(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect = null,
    ):void {
    }

    /**
     * Performs a fast blit from the source surface to the destination surface.
     *
     * This assumes that the source and destination rectangles are
     * the same size.  If either `$srcrect` or `$dstrect` are `NULL`, the entire
     * surface (`$src` or `$dst`) is copied.  The final blit rectangles are saved
     * in `$srcrect` and `$dstrect` after all clipping is performed.
     *
     * The blit function should not be called on a locked surface.
     * @param  SDL_Rect      $srcrect
     * @param  SDL_Surface   $dst
     * @param  SDL_Rect|null $dstrect
     * @return void          returns 0, otherwise it returns -1.
     */
    public function UpperBlit(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect = null,
    ):void {
    }

    /**
     * This is a semi-private blit function and it performs low-level surface blitting only.
     * @param  SDL_Rect    $srcrect
     * @param  SDL_Surface $dst
     * @param  SDL_Rect    $dstrect
     * @return void
     */
    public function LowerBlit(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect,
    ):void {
    }

    /**
     * This is the public scaled blit function, `SDL_BlitScaled()`, and it performs rectangle validation and clipping before passing it to `SDL_LowerBlitScaled()`.
     * @param  SDL_Rect      $srcrect
     * @param  SDL_Surface   $dst
     * @param  SDL_Rect|null $dstrect
     * @return void
     */
    public function BlitScaled(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect = null
    ):void {
    }

    /**
     * This is the public scaled blit function, `SDL_BlitScaled()`, and it performs rectangle validation and clipping before passing it to `SDL_LowerBlitScaled()`.
     * @param  SDL_Rect      $srcrect
     * @param  SDL_Surface   $dst
     * @param  SDL_Rect|null $dstrect
     * @return void
     */
    public function UpperBlitScaled(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect = null
    ):void {
    }

    /**
     * This is a semi-private blit function and it performs low-level surface scaled blitting only.
     * @param  SDL_Rect    $srcrect
     * @param  SDL_Surface $dst
     * @param  SDL_Rect    $dstrect
     * @return void
     */
    public function LowerBlitScaled(
        SDL_rect &$srcrect,
        SDL_Surface $dst,
        SDL_rect &$dstrect,
    ):void {
    }

    /**
     * Perform a fast, low quality, stretch blit between two surfaces of the same pixel format.
     * 
     * This function uses a static buffer, and is not thread-safe.
     * @param  SDL_Rect    $srcrect
     * @param  SDL_Surface $dst
     * @param  SDL_Rect    $dstrect
     * @return void
     */
    public function SoftStretch(
        SDL_rect $srcrect,
        SDL_Surface $dst,
        SDL_rect $dstrect
    ):void {
    }

    /**
     * Save a surface to a seekable SDL data stream (memory or file).
     *
     * If `$freedst` is non-zero, the stream will be closed after being written.
     * @param  SDL_RWops $dst
     * @param  int       $freedst
     * @return int       0 if successful or -1 if there was an error.
     */
    public function SaveBMP_RW(
        SDL_RWops &$dst,
        int $freedst
    ):int {
        return 0;
    }

    /**
     * stream are "partially" supported (only when `PHP_STREAM_AS_STDIO`).
     * @param  string $path
     * @return int
     */
    public function SaveBMP(
        string $path
    ):int {
        return 0;
    }

    /**
     * Sets the color key (transparent pixel) in a blittable surface.
     * 
     * You can pass SDL_RLEACCEL to enable RLE accelerated blits.
     * @param  int $flag Non-zero to enable colorkey and 0 to disable colorkey.
     * @param  int $key  key The transparent pixel in the native surface format.
     * @return int 0 on success, or -1 if the surface is not valid.
     */
    public function SetColorKey(
        int $flag,
        int $key = 0
    ):int {
        return 0;
    }

    /**
     * Gets the color key (transparent pixel) in a blittable surface.
     * @param  int $key A pointer filled in with the transparent pixel in the native surface format.
     * @return int 0 on success, or -1 if the surface is not valid or colorkey is not enabled.
     */
    public function GetColorKey(
        int &$key
    ):int {
        return 0;
    }

    /**
     * Sets the clipping rectangle for the destination surface in a blit.
     *
     * If the clip rectangle is NULL, clipping will be disabled.
     *
     * If the clip rectangle doesn't intersect the surface, the function will
     * return SDL_FALSE and blits will be completely clipped.  Otherwise the
     * function returns SDL_TRUE and blits to the surface will be clipped to
     * the intersection of the surface area and the clipping rectangle.
     *
     * Note that blits are automatically clipped to the edges of the source
     * and destination surfaces.
     * @param  SDL_Rect $cliprect
     * @return void
     */
    public function SetClipRect(
        SDL_Rect $cliprect,
    ):void {
    }

    /**
     * Gets the clipping rectangle for the destination surface in a blit.
     *
     * `$rect` must be a pointer to a valid rectangle which will be filled with the correct values.
     * @param  SDL_Rect $rect
     * @return void
     */
    public function GetClipRect(
        SDL_Rect &$rect
    ):void {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_GLContext implements Stringable {
    public function __construct(
        public SDL_Window $window,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_mutex implements Stringable {
    public function __toString(): string {
        return '';
    }
}

class SDL_sem implements Stringable {
    public function __construct(
        public int $value
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
class SDL_cond implements Stringable {
    public function __construct(
        public int $value
    ) {
    }

    public function __toString(): string {
        return '';
    }
}
class SDL_Pixels implements Stringable {
    public function __construct(
        public int $pitch,
        public int $h,
    ) {
    }

    public function count():int {
        return 0;
    }

    public function offsetExists(int $offset): bool {
        return true;
    }

    public function offsetGet(int $offset): false|int {
        return false;
    }

    public function offsetUnset(int $offset): null|false {
        return null;
    }

    public function offsetSet(
        int $offset,
        int $value
    ): null|false {
        return null;
    }

    public function GetByte(
        int $x,
        int $y,
    ): false|int {
        return false;
    }

    public function SetByte(
        int $x,
        int $y,
        int $value,
    ): false|int {
        return false;
    }

    public function __toString(): string {
        return '';
    }
}

class SDL_DisplayMode implements Stringable {
    public function __construct(
        public int $format,
        public int $w,
        public int $h,
        public int $refresh_rate,
    ) {
    }

    public function __toString(): string {
        return '';
    }
}

/**
 * Initialize SDL module.
 * @param  int $flag Check `SDL_INIT_*` constants
 * @return int
 */
function SDL_Init(int $flag):int {
    return 0;
}

/**
 * Create a window that can be shaped with the specified position, dimensions, and flags.
 * @param  string          $title The title of the window, in UTF-8 encoding.
 * @param  int             $x     The x position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int             $y     The y position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int             $w     The width of the window.
 * @param  int             $h     The height of the window.
 * @param  int             $flags The flags for the window, a mask of `SDL_WINDOW_BORDERLESS` with any of the following: `SDL_WINDOW_OPENGL`, `SDL_WINDOW_INPUT_GRABBED`, `SDL_WINDOW_HIDDEN`, `SDL_WINDOW_RESIZABLE`, ::SDL_WINDOW_MAXIMIZED,  `SDL_WINDOW_MINIMIZED`, `SDL_WINDOW_BORDERLESS` is always set, and `SDL_WINDOW_FULLSCREEN` is always unset.
 * @return null|SDL_Window The window created, or NULL if window creation failed. 
 */
function SDL_CreateWindow(
    string $title,
    int $x,
    int $y,
    int $w,
    int $h,
    int $flags
):null|SDL_Window {
    return null;
}

/**
 * Create a window that can be shaped with the specified position, dimensions, and flags.
 * @param  string        $title The title of the window, in UTF-8 encoding.
 * @param  int           $x     The x position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int           $y     The y position of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int           $w     The width of the window.
 * @param  int           $h     The height of the window.
 * @param  int           $flags The flags for the window, a mask of `SDL_WINDOW_BORDERLESS` with any of the following: `SDL_WINDOW_OPENGL`, `SDL_WINDOW_INPUT_GRABBED`, `SDL_WINDOW_HIDDEN`, `SDL_WINDOW_RESIZABLE`, ::SDL_WINDOW_MAXIMIZED,  `SDL_WINDOW_MINIMIZED`, `SDL_WINDOW_BORDERLESS` is always set, and `SDL_WINDOW_FULLSCREEN` is always unset.
 * @return null|resource The window created, or NULL if window creation failed. 
 */
function SDL_CreateShapedWindow(
    string $title,
    int $x,
    int $y,
    int $w,
    int $h,
    int $flags
):mixed {
}

/**
 * 
 * @param  SDL_Window    $window The window where rendering is displayed.
 * @param  int           $index  The index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags.
 * @param  int           $flags  Check `SDL_RENDERER_*` constants.
 * @return null|resource A valid rendering context or NULL if there was an error.
 */
function SDL_CreateRenderer(
    SDL_Window $window,
    int $index,
    int $flags
):mixed {
}

/**
 * Create a texture from an existing surface.
 * 
 * The surface is not modified or freed by this function.
 * @param  resource      $renderer
 * @param  SDL_Surface   $surface
 * @return null|resource
 */
function SDL_CreateTextureFromSurface(
    mixed $renderer,
    SDL_Surface $surface,
):mixed {
}


const SDL_NONSHAPEABLE_WINDOW    = -1;
const SDL_INVALID_SHAPE_ARGUMENT = -2;
const SDL_WINDOW_LACKS_SHAPE     = -3;

/**
 * Set the shape and parameters of a shaped window.
 * @param  SDL_Window          $window     The shaped window whose parameters should be set.
 * @param  SDL_Surface         $shape      A surface encoding the desired shape for the window.
 * @param  SDL_WindowShapeMode $shape_mode The parameters to set for the shaped window.
 * @return int                 0 on success, `SDL_INVALID_SHAPE_ARGUMENT` on invalid an invalid shape argument, or `SDL_NONSHAPEABLE_WINDOW` if the `SDL_Window*` given does not reference a valid shaped window.
 */
function SDL_SetWindowShape(
    SDL_Window $window,
    SDL_Surface $shape,
    SDL_WindowShapeMode $shape_mode
):int {
    return 0;
}


/**
 * Set the color used for drawing operations (Rect, Line and Clear).
 * @param  resource $renderer The renderer for which drawing color should be set.
 * @param  int      $r        The red value used to draw on the rendering target.
 * @param  int      $g        The green value used to draw on the rendering target.
 * @param  int      $b        The blue value used to draw on the rendering target.
 * @param  int      $a        The alpha value used to draw on the rendering target, usually `SDL_ALPHA_OPAQUE` (255).
 * @return int      0 on success, or -1 on error.
 */
function SDL_SetRenderDrawColor(
    mixed $renderer,
    int $r,
    int $g,
    int $b,
    int $a,
):int {
    return 0;
}

/**
 * Clear the current rendering target with the drawing color.
 *
 * This function clears the entire rendering target, ignoring the viewport and the clip rectangle.
 * @param  resource $rederer
 * @return int
 */
function SDL_RenderClear(mixed $rederer):int {
    return 0;
}

/**
 * Update the screen with rendering performed.
 * @param  resource $rederer
 * @return int
 */
function SDL_RenderPresent(mixed $rederer):int {
    return 0;
}


/**
 * Polls for currently pending events.
 * @param null|resource If not NULL, the next event is removed from the queue and stored in that area.
 * @return int 1 if there are any pending events, or 0 if there are none available.
 */
function SDL_PollEvent(
    mixed $event
):int {
    return 0;
}

/**
 * Wait a specified number of milliseconds before returning.
 * @param  int  $ms
 * @return void
 */
function SDL_Delay(int $ms):void {
}

/**
 * Destroy a renderer.
 * @param  resource $renderer
 * @return void
 */
function SDL_DestroyRenderer(mixed $renderer):void {
}

/**
 * Destroy a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_DestroyWindow(SDL_Window $window):void {
}

/**
 * This function cleans up all initialized subsystems.
 * 
 * You should call it upon all exit conditions.
 * @return void
 */
function SDL_Quit() {
}

/**
 * Get the version of SDL that is linked against your program.
 *
 * If you are linking to SDL dynamically, then it is possible that the
 * current version will be different than the version you compiled against.
 * This function returns the current version, while SDL_VERSION() is a
 * macro that tells you what version you compiled with.
 * @param  array $version
 * @return void
 */
function SDL_GetVersion(array &$version):void {
}

/**
 * Create a simple modal message box.
 * @param  int             $flags   Check `SDL_MESSAGEBOX_*` constants.
 * @param  string          $title   UTF-8 title text.
 * @param  string          $message UTF-8 message text.
 * @param  null|SDL_Window $window  The parent window, or NULL for no parent.
 * @return bool
 */
function SDL_ShowSimpleMessageBox(
    int $flags,
    string $title,
    string $message,
    null|SDL_Window $window = null
):bool {
    return true;
}

/**
 * Draw a point on the current rendering target.
 * @param  resource $renderer The renderer which should draw a point.
 * @param  int      $x        The x coordinate of the point.
 * @param  int      $y        The y coordinate of the point.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawPoint(
    mixed $renderer,
    int $x,
    int $y,
) {
    return 0;
}

/**
 * Draw a point on the current rendering target.
 * @param  resource $renderer The renderer which should draw a point.
 * @param  int      $x        The x coordinate of the point.
 * @param  int      $y        The y coordinate of the point.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawPointF(
    mixed $renderer,
    int $x,
    int $y,
) {
    return 0;
}

function SDL_PointInRect(
    SDL_Point $p,
    SDL_Rect $r
): bool {
    return true;
}

/**
 * Returns true if the rectangle has no area.
 * @param  SDL_Rect $r
 * @return bool
 */
function SDL_RectEmpty(SDL_Rect $r): bool {
    return true;
}
/**
 * Returns true if the two rectangles are equal.
 * @param  SDL_Rect $a
 * @param  SDL_Rect $b
 * @return bool
 */
function SDL_RectEquals(
    SDL_Rect $a,
    SDL_Rect $b
): bool {
    return true;
}
/**
 * Determine whether two rectangles intersect.
 * @param  SDL_Rect $A
 * @param  SDL_Rect $B
 * @return bool     `true` if there is an intersection, `false`` otherwise.
 */
function SDL_HasIntersection(
    SDL_Rect $A,
    SDL_Rect $B
): bool {
    return true;
}
/**
 * Calculate the intersection of two rectangles.
 * @param  SDL_Rect      $A
 * @param  SDL_Rect      $B
 * @param  null|SDL_Rect $result
 * @return bool          `true` if there is an intersection, `false` otherwise.
 */
function SDL_IntersectRect(
    SDL_Rect $A,
    SDL_Rect $B,
    ?SDL_Rect &$result
): bool {
    return true;
}
/**
 * Calculate the union of two rectangles.
 * @param  SDL_Rect      $A
 * @param  SDL_Rect      $B
 * @param  null|SDL_Rect $result
 * @return void
 */
function SDL_UnionRect(SDL_Rect $A, SDL_Rect $B, ?SDL_Rect &$result): void {
}
/**
 * Calculate a minimal rectangle enclosing a set of points
 * @param  SDL_Point       $points
 * @param  int             $count
 * @param  SDL_Rect        $clip
 * @param  null|SDL_Rect   $result
 * @return null|false|bool `true` if any points were within the clipping rect
 */
function SDL_EnclosePoints(
    SDL_Point $points,
    int $count,
    SDL_Rect $clip,
    ?SDL_Rect &$result
): null|bool {
    return true;
}

/**
 * Calculate the intersection of a rectangle and line segment.
 * @param  SDL_Rect $rect
 * @param  int      $X1
 * @param  int      $Y1
 * @param  int      $X2
 * @param  int      $Y2
 * @return bool
 */
function SDL_IntersectRectAndLine(
    SDL_Rect $rect,
    int &$X1,
    int &$Y1,
    int &$X2,
    int &$Y2
): bool {
    return true;
}

function SDL_FRectEmpty(SDL_FRect $r): bool {
    return true;
}
function SDL_HasIntersectionF(SDL_FRect $A, SDL_FRect $B): bool {
    return true;
}
function SDL_IntersectFRect(SDL_FRect $A, SDL_FRect $B, ?SDL_FRect &$result): bool {
    return true;
}


/**
 * Fill a rectangle on the current rendering target with the drawing color.
 * @param  resource $renderer The renderer which should fill a rectangle.
 * @param  SDL_Rect $rect     A pointer to the destination rectangle, or NULL for the entire rendering target.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderFillRect(
    mixed $renderer,
    SDL_Rect $rect,
):int {
    return 0;
}


/**
 * Draw a rectangle on the current rendering target.
 * @param  resource $renderer The renderer which should draw a rectangle.
 * @param  SDL_Rect $rect     A pointer to the destination rectangle, or NULL to outline the entire rendering target.
 * @return int      0 on success, or -1 on error.
 */
function SDL_RenderDrawRect(
    mixed $renderer,
    SDL_Rect $rect,
):int {
    return 0;
}


/**
 * Fill a rectangle on the current rendering target with the drawing color.
 * @param  resource  $renderer The renderer which should fill a rectangle.
 * @param  SDL_FRect $rect     A pointer to the destination rectangle, or NULL for the entire rendering target.
 * @return int       0 on success, or -1 on error.
 */
function SDL_RenderFillRectF(
    mixed $renderer,
    SDL_FRect $rect,
):int {
    return 0;
}

/**
 * Draw a rectangle on the current rendering target.
 * @param  resource  $renderer The renderer which should draw a rectangle.
 * @param  SDL_FRect $rect     A pointer to the destination rectangle, or NULL to outline the entire rendering target.
 * @return int       0 on success, or -1 on error.
 */
function SDL_RenderDrawRectF(
    mixed $renderer,
    SDL_FRect $rect,
):int {
    return 0;
}


/**
 * Get the SDL surface associated with the window.
 * 
 * You may not combine this with 3D or the rendering API on this window.
 * @param  SDL_Window       $window
 * @return null|SDL_Surface The window's framebuffer surface, or NULL on error.
 *                                 A new surface will be created with the optimal format for the window,
 *                                 if necessary. This surface will be freed when the window is destroyed.
 */
function SDL_GetWindowSurface(SDL_Window $window):null|SDL_Surface {
    return null;
}

/**
 * Maps an RGB triple to an opaque pixel value for a given pixel format.
 * @param  SDL_PixelFormat $pixelformat
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @return int
 */
function SDL_MapRGB(
    SDL_PixelFormat $pixelformat,
    int $r,
    int $g,
    int $b,
):int {
    return 0;
}

/**
 * Maps an RGBA quadruple to a pixel value for a given pixel format.
 * @param  SDL_PixelFormat $pixelformat
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @param  int             $a
 * @return int
 */
function SDL_MapRGBA(
    SDL_PixelFormat $pixelformat,
    int $r,
    int $g,
    int $b,
    int $a,
):int {
    return 0;
}

/**
 * Destroy a window.
 * @param  SDL_Surface $src
 * @return void
 */
function SDL_FreeSurface(SDL_Surface $src):void {
}
/**
 * Performs a fast fill of the given rectangle with `$color`.
 *
 * If `$rect` is `NULL`, the whole surface will be filled with  `$color`.
 *
 * The color should be a pixel of the format used by the surface, and can be generated by the `SDL_MapRGB()` function.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $rect
 * @param  int         $color
 * @return void        0 on success, or -1 on error.
 */
function SDL_FillRect(
    SDL_Surface $src,
    SDL_Rect $rect,
    int $color
):int {
    return 0;
}

/**
 * 
 * @param  SDL_Surface     $src
 * @param  array<SDL_Rect> $rect
 * @param  int             $count
 * @param  int             $color
 * @return int
 */
function SDL_FillRects(
    SDL_Surface $src,
    array $rect,
    int $count,
    int $color
):int {
    return 0;
}

/**
 * Evaluates to true if the surface needs to be locked before access.
 * define SDL_MUSTLOCK(S) (((S)->flags & SDL_RLEACCEL) != 0)
 * @param  SDL_Surface $src
 * @return bool
 */
function SDL_MUSTLOCK(SDL_Surface $src):bool {
    return true;
}

/**
 * Sets up a surface for directly accessing the pixels.
 *
 * Between calls to `SDL_LockSurface()` / `SDL_UnlockSurface()`, you can write
 * to and read from `$surface->pixels`, using the pixel format stored in
 * `$surface->format`.  Once you are done accessing the surface, you should
 * use `SDL_UnlockSurface()` to release it.
 *
 * Not all surfaces require locking.  If `SDL_MUSTLOCK($surface)` evaluates
 * to 0, then you can read and write to the surface at any time, and the
 * pixel format of the surface will not change.
 *
 * No operating system or library calls should be made between lock/unlock
 * pairs, as critical system locks may be held during this time.
 * @param  SDL_Surface $src
 * @return int         0, or -1 if the surface couldn't be locked.
 */
function SDL_LockSurface(SDL_Surface $src):int {
    return 0;
}

function SDL_UnlockSurface(SDL_Surface $src):void {
}

/**
 * Performs a fast blit from the source surface to the destination surface.
 *
 *  This assumes that the source and destination rectangles are
 *  the same size.  If either `$srcrect` or `$dstrect` are `NULL`, the entire
 *  surface (`$src` or `$dst`) is copied.  The final blit rectangles are saved
 *  in `$srcrect` and `$dstrect` after all clipping is performed.
 *
 *  The blit function should not be called on a locked surface.
 * @param  SDL_Surface   $src
 * @param  SDL_Rect      $srcrect
 * @param  SDL_Surface   $dst
 * @param  SDL_Rect|null $dstrect
 * @return void          returns 0, otherwise it returns -1.
 */
function SDL_UpperBlit(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect = null,
):void {
}

/**
 * This is a semi-private blit function and it performs low-level surface blitting only.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_LowerBlit(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect,
):void {
}

/**
 * This is the public scaled blit function, `SDL_BlitScaled()`, and it performs rectangle validation and clipping before passing it to `SDL_LowerBlitScaled()`.
 * @param  SDL_Surface   $src
 * @param  SDL_Rect      $srcrect
 * @param  SDL_Surface   $dst
 * @param  SDL_Rect|null $dstrect
 * @return void
 */
function SDL_UpperBlitScaled(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect = null
):void {
}

/**
 * This is a semi-private blit function and it performs low-level surface scaled blitting only.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_LowerBlitScaled(
    SDL_Surface $src,
    SDL_rect &$srcrect,
    SDL_Surface $dst,
    SDL_rect &$dstrect,
):void {
}

/**
 * Perform a fast, low quality, stretch blit between two surfaces of the same pixel format.
 * 
 * This function uses a static buffer, and is not thread-safe.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $srcrect
 * @param  SDL_Surface $dst
 * @param  SDL_Rect    $dstrect
 * @return void
 */
function SDL_SoftStretch(
    SDL_Surface $src,
    SDL_rect $srcrect,
    SDL_Surface $dst,
    SDL_rect $dstrect
):void {
}

/**
 * Save a surface to a seekable SDL data stream (memory or file).
 *
 * If `$freedst` is non-zero, the stream will be closed after being written.
 * @param  SDL_Surface $src
 * @param  SDL_RWops   $dst
 * @param  int         $freedst
 * @return int         0 if successful or -1 if there was an error.
 */
function SDL_SaveBMP_RW(
    SDL_Surface $src,
    SDL_RWops &$dst,
    int $freedst
):int {
    return 0;
}

/**
 * stream are "partially" supported (only when `PHP_STREAM_AS_STDIO`).
 * @param  SDL_Surface $src
 * @param  string      $path
 * @return int
 */
function SDL_SaveBMP(
    SDL_Surface $src,
    string $path
):int {
    return 0;
}

/**
 * Sets the RLE acceleration hint for a surface.
 * 
 * If RLE is enabled, colorkey and alpha blending blits are much faster, but the surface must be locked before directly accessing the pixels.
 * @param  SDL_Surface $src
 * @param  int         $flag
 * @return void        0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceRLE(
    SDL_Surface $src,
    int $flag
):void {
}

/**
 * Sets the color key (transparent pixel) in a blittable surface.
 * 
 * You can pass SDL_RLEACCEL to enable RLE accelerated blits.
 * @param  SDL_Surface $src  The surface to update. 
 * @param  int         $flag Non-zero to enable colorkey and 0 to disable colorkey.
 * @param  int         $key  key The transparent pixel in the native surface format.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetColorKey(
    SDL_Surface $src,
    int $flag,
    int $key = 0
):int {
    return 0;
}

/**
 * Gets the color key (transparent pixel) in a blittable surface.
 * @param  SDL_Surface $src The surface to update. 
 * @param  int         $key A pointer filled in with the transparent pixel in the native surface format.
 * @return int         0 on success, or -1 if the surface is not valid or colorkey is not enabled.
 */
function SDL_GetColorKey(
    SDL_Surface $src,
    int &$key
):int {
    return 0;
}

/**
 * Set an additional color value used in blit operations.
 * @param  SDL_Surface $src The surface to update.
 * @param  int         $r   The red color value multiplied into blit operations.
 * @param  int         $g   The green color value multiplied into blit operations.
 * @param  int         $b   The blue color value multiplied into blit operations.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceColorMod(
    SDL_Surface $src,
    int $r,
    int $g,
    int $b
):int {
    return 0;
}

/**
 * Get the additional color value used in blit operations.
 * @param  SDL_Surface $src The surface to query.
 * @param  int         $r   A pointer filled in with the current red color value.
 * @param  int         $g   A pointer filled in with the current green color value.
 * @param  int         $b   A pointer filled in with the current blue color value.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_GetSurfaceColorMod(
    SDL_Surface $src,
    int &$r,
    int &$g,
    int &$b
):int {
    return 0;
}

/**
 * Set an additional alpha value used in blit operations.
 * @param  SDL_Surface $src   The surface to update.
 * @param  int         $alpha The alpha value multiplied into blit operations.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_SetSurfaceAlphaMod(
    SDL_Surface $src,
    int $alpha
):int {
    return 0;
}

/**
 * Get the additional alpha value used in blit operations.
 * @param  SDL_Surface $src The surface to query.
 * @param  int         $a   A pointer filled in with the current alpha value.
 * @return int         0 on success, or -1 if the surface is not valid.
 */
function SDL_GetSurfaceAlphaMod(
    SDL_Surface $src,
    int &$a
):int {
    return 0;
}

/**
 * Set the blend mode used for blit operations.
 * @param  SDL_Surface $src       The surface to update.
 * @param  int         $blendmode ::SDL_BlendMode to use for blit blending.
 * @return int         0 on success, or -1 if the parameters are not valid.
 */
function SDL_SetSurfaceBlendMode(
    SDL_Surface $src,
    int $blendmode,
):int {
    return 0;
}

/**
 * Set the blend mode used for blit operations.
 * @param  SDL_Surface $src       The surface to update.
 * @param  int         $blendmode ::SDL_BlendMode to use for blit blending.
 * @return int         0 on success, or -1 if the parameters are not valid.
 */
function SDL_GetSurfaceBlendMode(
    SDL_Surface $src,
    int $blendmode,
):int {
    return 0;
}

/**
 * Sets the clipping rectangle for the destination surface in a blit.
 *
 * If the clip rectangle is NULL, clipping will be disabled.
 *
 * If the clip rectangle doesn't intersect the surface, the function will
 * return SDL_FALSE and blits will be completely clipped.  Otherwise the
 * function returns SDL_TRUE and blits to the surface will be clipped to
 * the intersection of the surface area and the clipping rectangle.
 *
 * Note that blits are automatically clipped to the edges of the source
 * and destination surfaces.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $cliprect
 * @return void
 */
function SDL_SetClipRect(
    SDL_Surface $src,
    SDL_Rect $cliprect,
):void {
}

/**
 * Gets the clipping rectangle for the destination surface in a blit.
 *
 * `$rect` must be a pointer to a valid rectangle which will be filled with the correct values.
 * @param  SDL_Surface $src
 * @param  SDL_Rect    $rect
 * @return void
 */
function SDL_GetClipRect(
    SDL_Surface $src,
    SDL_Rect &$rect
):void {
}

/**
 * Creates a new surface of the specified format, and then copies and maps
 * the given surface to it so the blit of the converted surface will be as
 * fast as possible.  If this function fails, it returns `NULL`.
 *
 * The `$flags` parameter is passed to `SDL_CreateRGBSurface()` and has those
 * semantics.  You can also pass `::SDL_RLEACCEL` in the flags parameter and
 * SDL will try to RLE accelerate colorkey and alpha blits in the resulting
 * surface.
 * @param  SDL_Surface     $src
 * @param  SDL_PixelFormat $format
 * @param  int             $flag
 * @return void
 */
function SDL_ConvertSurface(
    SDL_Surface $src,
    SDL_PixelFormat $format,
    int $flag
):void {
}

/**
 * 
 * @param  SDL_Surface $src
 * @param  int         $format
 * @param  int         $flags
 * @return void
 */
function SDL_ConvertSurfaceFormat(
    SDL_Surface $src,
    int $format,
    int $flags = 0
):void {
}

/**
 * Load a surface from a seekable SDL data stream (memory or file).
 *
 * If `$freesrc` is non-zero, the stream will be closed after being read.
 *
 * The new surface should be freed with `SDL_FreeSurface()`.
 * @param  SDL_RWops        $src
 * @param  int              $freesrc
 * @return null|SDL_Surface the new surface, or NULL if there was an error.
 */
function SDL_LoadBMP_RW(SDL_RWops $src, int $freesrc):null|SDL_Surface {
    return null;
}

/**
 * Load a surface from a file.
 * 
 * stream are supported.
 * @param  string|resource  $file
 * @return null|SDL_Surface
 */
function SDL_LoadBMP(string $file):null|SDL_Surface {
    return null;
}


/**
 * Copy a number of rectangles on the window surface to the screen.
 * @param  SDL_Window $window
 * @param  array      $rects
 * @param  int        $numrect
 * @return int        0 on success, or -1 on error.
 */
function SDL_UpdateWindowSurfaceRects(
    SDL_Window $window,
    array $rects,
    int $numrect = 0
):int {
    return 0;
}

/**
 * Copy the window surface to the screen.
 * @param  SDL_Window $window
 * @return int        0 on success, or -1 on error.
 */
function SDL_UpdateWindowSurface(SDL_Window $window):int {
    return 0;
}

/**
 * Create a system cursor.
 * @param  int        $id one of the `SDL_Cursor::*` constants.
 * @return SDL_Cursor
 */
function SDL_CreateSystemCursor(int $id):SDL_Cursor {
    return new self(
        '',
        0,
        0,
        0,
        0,
        0,
    );
}

/**
 * Frees a cursor created with `SDL_CreateCursor()`.
 * @param  SDL_Cursor $cursor
 * @return void
 */
function SDL_FreeCursor(SDL_Cursor $cursor):void {
}

/**
 * Set the title of a window, in UTF-8 format.
 * @param  SDL_Window $window
 * @param  string     $title
 * @return void
 */
function SDL_SetWindowTitle(
    SDL_Window $window,
    string $title,
):void {
}

/**
 * 
 * @return int
 */
function SDL_NumJoysticks():int {
    return 0;
}

/**
 * Get the name of a joystick by index.
 * @param  int         $index joystick index (starts from 0).
 * @return null|string
 */
function SDL_JoystickNameForIndex(int $index):null|string {
    return '';
}

/**
 * Open a joystick connection by index.
 * @param  int               $index joystick index (starts from 0).
 * @return null|SDL_Joystick
 */
function SDL_JoystickOpen(int $index):null|object {
    return null;
}

/**
 * Close a joystick connection.
 * @param  SDL_Joystick $joystick
 * @return void
 */
function SDL_JoystickClose(object $joystick):void {
}

/**
 * Get the name of a joystick.
 * @param  SDL_Joystick $joystick
 * @return void
 */
function SDL_JoystickName(object $joystick):void {
}

/**
 * Get the current value of an axis.
 * @param  SDL_Joystick $joystick
 * @param  int          $axis     `0` is the `x` axis and `1` is the `y` axis.
 * @return int
 */
function SDL_JoystickGetAxis(
    object $joystick,
    int $axis,
):int {
    return 0;
}

/**
 * Get the number of buttons on the joystick.
 * @param  SDL_Joystick $joystick
 * @return int
 */
function SDL_JoystickNumButtons(
    object $joystick,
):int {
    return 0;
}

/**
 * Check if a joystick is used by a videogame by index.
 * @param  int  $index joystick index (starts from 0).
 * @return bool
 */
function SDL_IsGameController(int $index):bool {
    return true;
}

/**
 * 
 * @return string
 */
function SDL_GetError():string {
    return '';
}

/**
 * 
 * @param  mixed          $renderer
 * @param  mixed          $texture
 * @param  null|SDL_Rect  $srcrect
 * @param  null|SDL_Rect  $dstrect
 * @param  float          $angle
 * @param  null|SDL_Point $center
 * @param  int            $flip
 * @return int
 */
function SDL_RenderCopyEx(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_Rect $dstrect = null,
    float $angle,
    null|SDL_Point $center = null,
    int $flip,
):int {
    return 0;
}

/**
 * 
 * @param  mixed           $renderer
 * @param  mixed           $texture
 * @param  null|SDL_Rect   $srcrect
 * @param  null|SDL_FRect  $dstrect
 * @param  float           $angle
 * @param  null|SDL_FPoint $center
 * @param  int             $flip
 * @return int
 */
function SDL_RenderCopyExF(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect|SDL_FRect $srcrect = null,
    null|SDL_FRect $dstrect = null,
    float $angle,
    null|SDL_FPoint $center = null,
    int $flip,
):int {
    return 0;
}

/**
 * Destroy a texture.
 * @param  resource $texture
 * @return void
 */
function SDL_DestroyTexture(mixed $texture):void {
}

/**
 * Get a snapshot of the current state of the keyboard.
 * @param  null|int   &$numkeys if non-NULL, receives the length of the returned array.
 * @return array<int> An array of key states. Indexes into this array are obtained by using `SDL_Scancode_*` values.
 */
function SDL_GetKeyboardState(null|int &$numkeys):array {
    return [];
}

/**
 * Draw a line between two points.
 * @param  resource $renderer
 * @param  int      $x1
 * @param  int      $y1
 * @param  int      $x2
 * @param  int      $y2
 * @return int
 */
function SDL_RenderDrawLine(
    mixed $renderer,
    int $x1,
    int $y1,
    int $x2,
    int $y2,
):int {
    return 0;
}

/**
 * Draw a line between two points.
 * @param  resource $renderer
 * @param  float    $x1
 * @param  float    $y1
 * @param  float    $x2
 * @param  float    $y2
 * @return int
 */
function SDL_RenderDrawLineF(
    mixed $renderer,
    float $x1,
    float $y1,
    float $x2,
    float $y2,
):int {
    return 0;
}

/**
 * 
 * @param  resource      $renderer
 * @param  resource      $texture
 * @param  null|SDL_Rect $srcrect
 * @param  null|SDL_Rect $dstrect
 * @return int
 */
function SDL_RenderCopy(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_Rect $dstrect = null,
):int {
    return 0;
}
/**
 * 
 * @param  resource       $renderer
 * @param  resource       $texture
 * @param  null|SDL_Rect  $srcrect
 * @param  null|SDL_FRect $dstrect
 * @return int
 */
function SDL_RenderCopyF(
    mixed $renderer,
    mixed $texture,
    null|SDL_Rect $srcrect = null,
    null|SDL_FRect $dstrect = null,
):int {
    return 0;
}

/**
 * This function returns the number of CPU cores available.
 * @return int
 */
function SDL_GetCPUCount():int {
    return 0;
}

/**
 * This function returns the L1 cache line size of the CPU
 *
 * This is useful for determining multi-threaded structure padding or SIMD prefetch sizes.
 * @return int
 */
function SDL_GetCPUCacheLineSize():int {
    return 0;
}

/**
 * This function returns true if the CPU has the RDTSC instruction.
 * @return int
 */
function SDL_HasRDTSC():int {
    return 0;
}

/**
 * This function returns true if the CPU has AltiVec features.
 * @return int
 */
function SDL_HasAltiVec():int {
    return 0;
}

/**
 * This function returns true if the CPU has MMX features.
 * @return int
 */
function SDL_Has3DNow():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE features.
 * @return int
 */
function SDL_HasSSE():int {
    return 0;
}

/**
 * This function returns true if the CPU has HasSSE2 features.
 * @return int
 */
function SDL_HasSSE2():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE3 features.
 * @return int
 */
function SDL_HasSSE3():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.1 features.
 * @return int
 */
function SDL_HasSSE41():int {
    return 0;
}

/**
 * This function returns true if the CPU has SSE4.2 features.
 * @return int
 */
function SDL_HasSSE42():int {
    return 0;
}

/**
 * This function returns the amount of RAM configured in the system, in MB.
 * @return int
 */
function SDL_GetSystemRAM():int {
    return 0;
}

/**
 * 
 * @param  string $error
 * @return int    unconditionally returns -1.
 */
function SDL_SetError(string $error):int {
    return 0;
}

/**
 * 
 * @return string
 */
function SDL_ClearError():string {
    return '';
}

/**
 * 
 * @param  SDL_Event $event
 * @return int
 */
function SDL_WaitEvent(SDL_Event $event):int {
    return 0;
}

/**
 * Get the path where the application resides.
 *
 * Get the "base path". This is the directory where the application was run from, which is probably the installation directory, and may or may not be the process's current working directory.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call SDL_free() on the pointer when you are done with it, or it will be a memory leak. This is not necessarily a fast call, though, so you should call this once near startup and save the string if you need it.
 *
 * Some platforms can't determine the application's path, and on other platforms, this might be meaningless. In such cases, this function will return NULL.
 * 
 * @param  string            $org
 * @param  string            $app
 * @return null|false|string String of base dir in UTF-8 encoding, or NULL on error.
 */
function SDL_GetPrefPath(
    string $org,
    string $app,
):null|false|string {
    return null;
}

/**
 * Get the user-and-app-specific path where files can be written.
 *
 * Get the "pref dir". This is meant to be where users can write personal files (preferences and save games, etc) that are specific to your application. This directory is unique per user, per application.
 *
 * This function will decide the appropriate location in the native filesystem, create the directory if necessary, and return a string of the absolute path to the directory in UTF-8 encoding.
 *
 * On Windows, the string might look like: "C:\\Users\\bob\\AppData\\Roaming\\My Company\\My Program Name\\"
 *
 * On Linux, the string might look like: "/home/bob/.local/share/My Program Name/"
 *
 * On Mac OS X, the string might look like: "/Users/bob/Library/Application Support/My Program Name/"
 *
 * (etc.)
 *
 * You specify the name of your organization (if it's not a real organization, your name or an Internet domain you own might do) and the name of your application. These should be untranslated proper names.
 *
 * Both the org and app strings may become part of a directory name, so please follow these rules:
 *
 *    - Try to use the same org string (including case-sensitivity) for
 *      all your applications that use this function.
 *    - Always use a unique app string for each one, and make sure it never
 *      changes for an app once you've decided on it.
 *    - Unicode characters are legal, as long as it's UTF-8 encoded, but...
 *    - ...only use letters, numbers, and spaces. Avoid punctuation like
 *      "Game Name 2: Bad Guy's Revenge!" ... "Game Name 2" is sufficient.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call SDL_free() on the pointer when you are done with it, or it will be a memory leak. This is not necessarily a fast call, though, so you should call this once near startup and save the string if you need it.
 *
 * You should assume the path returned by this function is the only safe place to write files (and that SDL_GetBasePath(), while it might be writable, or even the parent of the returned path, aren't where you should be writing things).
 *
 * Some platforms can't determine the pref path, and on other platforms, this might be meaningless. In such cases, this function will return NULL.
 * @return null|string UTF-8 string of user dir in platform-dependent notation. NULL if there's a problem (creating directory failed, etc).
 */
function SDL_GetBasePath():null|string {
    return null;
}

/**
 * Return true if an OpenGL extension is supported for the current context.
 * @param  string $ext
 * @return bool
 */
function SDL_GL_ExtensionSupported(string $ext):bool {
    return true;
}

/**
 * Set an OpenGL window attribute before window creation.
 * @param  int $attr
 * @param  int $value
 * @return int
 */
function SDL_GL_SetAttribute(
    int $attr,
    int $value,
):int {
    return 0;
}

/**
 * Get the actual value for an attribute from the current context.
 * @param  int $attr
 * @param  int &$value
 * @return int
 */
function SDL_GL_GetAttribute(
    int $attr,
    int &$value,
):int {
    return 0;
}

/**
 * Create an OpenGL context for use with an OpenGL window, and make it current.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_GL_CreateContext(SDL_Window $window):void {
}

/**
 * Delete an OpenGL context.
 * @param  SDL_GLContext $context
 * @return void
 */
function SDL_GL_DeleteContext(
    SDL_GLContext $context
):void {
}

/**
 * Set up an OpenGL context for rendering into an OpenGL window.
 * 
 * The context must have been created with a compatible window.
 * @param  SDL_Window    $window
 * @param  SDL_GLContext $context
 * @return null|int
 */
function SDL_GL_MakeCurrent(
    SDL_Window $window,
    SDL_GLContext $context,
):null|int {
    return null;
}

/**
 * Get the currently active OpenGL window.
 * @return SDL_Window
 */
function SDL_GL_GetCurrentWindow():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Get the currently active OpenGL context.
 * @return SDL_GLContext
 */
function SDL_GL_GetCurrentContext():SDL_GLContext {
    /** @var SDL_GLContext $o */
    return $o;
}

/**
 * Get the size of a window's underlying drawable (for use with glViewport).
 * 
 * This may differ from SDL_GetWindowSize if we're rendering to a high-DPI drawable, i.e. the window was created with SDL_WINDOW_ALLOW_HIGHDPI on a platform with high-DPI support (Apple calls this "Retina"), and not disabled by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
 * @param  SDL_Window $window Window from which the drawable size should be queried
 * @param  int        $w      Pointer to variable for storing the width, may be NULL
 * @param  int        $h      Pointer to variable for storing the height, may be NULL
 * @return void
 */
function SDL_GL_GetDrawableSize(
    SDL_Window $window,
    int &$w,
    int &$h,
):void {
}

/**
 * Swap the OpenGL buffers for a window, if double-buffering is supported.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_GL_SwapWindow(
    SDL_Window $window
):void {
}

/**
 * Set the swap interval for the current OpenGL context.
 * @param  int $interval 0 for immediate updates, 1 for updates synchronized with the vertical retrace. If the system supports it, you may specify -1 to allow late swaps to happen immediately instead of waiting for the next retrace.
 * @return int 0 on success, or -1 if setting the swap interval is not supported.
 */
function SDL_GL_SetSwapInterval(int $interval):int {
    return 0;
}

/**
 * Get the swap interval for the current OpenGL context.
 * @return int 0 if there is no vertical retrace synchronization, 1 if the buffer swap is synchronized with the vertical retrace, and -1 if late swaps happen immediately instead of waiting for the next retrace. If the system can't determine the swap interval, or there isn't a valid current context, this will return 0 as a safe default.
 */
function SDL_GL_GetSwapInterval():int {
    return 0;
}

/**
 * Get the window which currently has keyboard focus.
 * @return void
 */
function SDL_GetKeyboardFocus():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Get the current key modifier state for the keyboard.
 * @return int
 */
function SDL_GetModState():int {
    return 0;
}

/**
 * Set the current key modifier state for the keyboard.
 * 
 * This does not change the keyboard state, only the key modifier flags.
 * @return void
 */
function SDL_SetModState(int $modstate):void {
}

/**
 * Get the key code corresponding to the given scancode according to the current keyboard layout.
 * 
 * See `SDLK_*` constants for details.
 * @param  int $scancode
 * @return int
 */
function SDL_GetKeyFromScancode(int $scancode):int {
    return 0;
}

/**
 * Get the scancode corresponding to the given key code according to the current keyboard layout.
 * 
 * See `SDLK_*` constants for details.
 * @param  int $key
 * @return int
 */
function SDL_GetScancodeFromKey(int $key):int {
    return 0;
}

/**
 * Get a human-readable name for a scancode.
 * 
 * 
 * @param  int    $scancode
 * @return string The name for the scancode.
 *                         If the scancode doesn't have a name, this function returns an empty string ("").
 */
function SDL_GetScancodeName(int $scancode):string {
    return '';
}

/**
 * Get a scancode from a human-readable name
 * @param  string $name
 * @return int    scancode, or `SDL_SCANCODE_UNKNOWN` if the name wasn't recognized
 */
function SDL_GetScancodeFromName(string $name):int {
    return 0;
}

/**
 * Get a human-readable name for a key.
 * @param  int    $key
 * @return string a UTF-8 string that stays valid at least until the next call to this function. If you need it around any longer, you must copy it.  If the key doesn't have a name, this function returns an empty string ("").
 */
function SDL_GetKeyName(int $key):string {
    return '';
}

/**
 * Get a key code from a human-readable name
 * @param  string $name
 * @return int    key code, or SDLK_UNKNOWN if the name wasn't recognized.
 */
function SDL_GetKeyFromName(string $name):int {
    return 0;
}

/**
 * Start accepting Unicode text input events.
 * 
 * This function will show the on-screen keyboard if supported.
 * @return void
 */
function SDL_StartTextInput():void {
}

/**
 * Return whether or not Unicode text input events are enabled.
 * @return bool
 */
function SDL_IsTextInputActive():bool {
    return true;
}

/**
 * Stop receiving any text input events.
 * 
 * This function will hide the on-screen keyboard if supported.
 * @return void
 */
function SDL_StopTextInput():void {
}

/**
 * Set the rectangle used to type Unicode text inputs.
 * 
 * This is used as a hint for IME and on-screen keyboard placement.
 * @param  SDL_Rect $rect
 * @return void
 */
function SDL_SetTextInputRect(
    SDL_Rect $rect
):void {
}

/**
 * Returns whether the platform has some screen keyboard support.
 * 
 * Not all screen keyboard functions are supported on all platforms.
 * @return bool `true` if some keyboard support is available else `false`.
 */
function SDL_HasScreenKeyboardSupport():bool {
    return true;
}

/**
 * Returns whether the screen keyboard is shown for given window.
 * @param  SDL_Window $window The window for which screen keyboard should be queried.
 * @return bool       `true` if screen keyboard is shown else `false`.
 */
function SDL_IsScreenKeyboardShown(
    SDL_Window $window
):bool {
    return true;
}


/**
 * Create a modal message box.
 * 
 * This function should be called on the thread that created the parent window, or on the main thread if the messagebox has no parent. 
 * It will block execution of that thread until the user clicks a button or closes the messagebox.
 * @param  SDL_MessageBoxData $messageboxdata messageboxdata The SDL_MessageBoxData structure with title, text, etc.
 * @param  int                $buttonid       buttonid The pointer to which user id of hit button should be copied.
 * @return int                -1 on error, otherwise 0 and buttonid contains user id of button hit or -1 if dialog was closed.
 */
function SDL_ShowMessageBox(SDL_MessageBoxData $messageboxdata, int &$buttonid):int {
    return 0;
}

/**
 * Create a cursor, using the specified bitmap data and mask (in MSB format).
 * 
 * The cursor width must be a multiple of 8 bits.
 * 
 * The cursor is created in black and white according to the following:
 * 
 * | data | mask | resulting pixel on screen                 |
 * |------|------|-------------------------------------------|
 * | 0    | 1    | White                                     |
 * | 1    | 1    | Black                                     |
 * | 0    | 0    | Transparent                               |
 * | 1    | 0    | Inverted color if possible, black if not. |
 * 
 * @param  string          $data
 * @param  string          $mask
 * @param  int             $w
 * @param  int             $h
 * @param  int             $hot_x
 * @param  int             $hot_y
 * @return null|SDL_Cursor
 */
function SDL_CreateCursor(
    string $data,
    string $mask,
    int $w,
    int $h,
    int $hot_x,
    int $hot_y
): null|SDL_Cursor {
    return null;
}

/**
 * Create a color cursor.
 * @param  SDL_Surface     $surface
 * @param  int             $x
 * @param  int             $y
 * @return null|SDL_Cursor
 */
function SDL_CreateColorCursor(
    SDL_Surface $surface,
    int $x,
    int $y,
): null|SDL_Cursor {
    return null;
}

/**
 * Set the active cursor.
 * @param  SDL_Cursor $cursor
 * @return void
 */
function SDL_SetCursor(
    SDL_Cursor $cursor,
):void {
}

/**
 * Return the active cursor.
 * @return SDL_Cursor
 */
function SDL_GetCursor():SDL_Cursor {
    return new SDL_Cursor('', 0, 0, 0, 0, 0);
}


/**
 * Return the default cursor.
 * @return SDL_Cursor
 */
function SDL_GetDefaultCursor():SDL_Cursor {
    return new SDL_Cursor('', 0, 0, 0, 0, 0);
}

/**
 * Toggle whether or not the cursor is shown.
 * 
 * @param  bool $toggle toggle 1 to show the cursor, 0 to hide it, -1 to query the current state.
 * @return bool `true` if the cursor is shown, or `false` if the cursor is hidden.
 */
function SDL_ShowCursor(bool $toggle):bool {
    return true;
}

/**
 * Get the window which currently has mouse focus.
 * @return SDL_Window
 */
function SDL_GetMouseFocus():SDL_Window {
    /** @var SDL_Window $o */
    return $o;
}

/**
 * Retrieve the current state of the mouse.
 * 
 * The current button state is returned as a button bitmask, which can be tested using the `SDL_BUTTON(X)` macros (check the `C` documentation), and x and y are set to the mouse cursor position relative to the focus window for the currently selected mouse. 
 * You can pass `NULL` for either x or y.
 * @param  null|int $x
 * @param  null|int $y
 * @return int
 */
function SDL_GetMouseState(
    null|int &$x = null,
    null|int &$y = null,
):int {
    return 0;
}

/**
 * Retrieve the relative state of the mouse.
 * 
 * The current button state is returned as a button bitmask, which can be tested using the `SDL_BUTTON(X)` macros (cehck the `C` documentation), and x and y are set to the mouse deltas since the last call to SDL_GetRelativeMouseState().
 * @param  null|int $x
 * @param  null|int $y
 * @return int
 */
function SDL_GetRelativeMouseState(
    null|int &$x = null,
    null|int &$y = null,
):int {
    return 0;
}

/**
 * Moves the mouse to the given position within the window.
 * @param  SDL_Window $window The window to move the mouse into, or NULL for the current mouse focus.
 * @param  int        $x      The x coordinate within the window.
 * @param  int        $y      The y coordinate within the window.
 * @return void
 */
function SDL_WarpMouseInWindow(
    SDL_Window $window,
    int $x,
    int $y
):void {
}

/**
 * Set relative mouse mode.
 * 
 * While the mouse is in relative mode, the cursor is hidden, and the driver will try to report continuous motion in the current window. 
 * Only relative motion events will be delivered, the mouse position will not change.
 * 
 * This function will flush any pending mouse motion.
 * 
 * @param  bool $enabled Whether or not to enable relative mode.
 * @return int  0 on success, or -1 if relative mode is not supported.
 */
function SDL_SetRelativeMouseMode(bool $enabled):int {
    return 0;
}

/**
 * Query whether relative mouse mode is enabled.
 * @return bool
 */
function SDL_GetRelativeMouseMode():bool {
    return true;
}


/**
 * Create a mutex, initialized unlocked.
 * @return SDL_mutex
 */
function SDL_CreateMutex():SDL_mutex {
    return new SDL_mutex;
}

/**
 * Lock the mutex.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_LockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Try to lock the mutex
 * @param  SDL_mutex $mutex
 * @return int       0, SDL_MUTEX_TIMEDOUT, or -1 on error
 */
function SDL_TryLockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Unlock the mutex.
 * 
 * WARNING: It is an error to unlock a mutex that has not been locked by the current thread, and doing so results in undefined behavior.
 * @param  SDL_mutex $mutex
 * @return int       0, or -1 on error.
 */
function SDL_UnlockMutex(SDL_mutex $mutex):int {
    return 0;
}

/**
 * Destroy a mutex.
 * @param  SDL_mutex $mutex
 * @return void
 */
function SDL_DestroyMutex(SDL_mutex $mutex):void {
}

/**
 * Create a semaphore, initialized with value, returns NULL on failure.
 * @param  int          $value
 * @return null|SDL_sem
 */
function SDL_CreateSemaphore(int $value): null|SDL_sem {
    return null;
}

/**
 * This function suspends the calling thread until the semaphore pointed to by `$sem` has a positive count.
 * It then atomically decreases the semaphore count.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemWait(SDL_sem $sem):int {
    return 0;
}


/**
 * Non-blocking variant of SDL_SemWait().
 * @param  SDL_sem $sem
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait would block, and -1 on error.
 */
function SDL_SemTryWait(SDL_sem $sem):int {
    return 0;
}

/**
 * Atomically increases the semaphore's count (not blocking).
 * @param  SDL_sem $sem
 * @return int     0, or -1 on error.
 */
function SDL_SemPost(SDL_sem $sem):int {
    return 0;
}

/**
 * Returns the current count of the semaphore.
 * @param  SDL_sem $sem
 * @return int
 */
function SDL_SemValue(SDL_sem $sem):int {
    return 0;
}

/**
 * Variant of SDL_SemWait() with a timeout in milliseconds.
 * 
 * On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_sem $sem
 * @param  int     $ms
 * @return int     0 if the wait succeeds, `SDL_MUTEX_TIMEDOUT` if the wait does not succeed in the allotted time, and -1 on error.
 */
function SDL_SemWaitTimeout(SDL_sem $sem, int $ms):int {
    return 0;
}

/**
 * Destroy a semaphore.
 * @param  SDL_sem $sem
 * @return void
 */
function SDL_DestroySemaphore(SDL_sem $sem):void {
}

/**
 * Create a condition variable.
 * 
 * Typical use of condition variables:
 *
 * Thread A:
 * ```c
 * SDL_LockMutex(lock);
 * while ( ! condition ) {
 *     SDL_CondWait(cond, lock);
 * }
 * SDL_UnlockMutex(lock);
 * ```
 *
 * Thread B:
 * ```c
 * SDL_LockMutex(lock);
 * ...
 * condition = true;
 * ...
 * SDL_CondSignal(cond);
 * SDL_UnlockMutex(lock);
 * ```
 *
 * There is some discussion whether to signal the condition variable
 * with the mutex locked or not.  There is some potential performance
 * benefit to unlocking first on some platforms, but there are some
 * potential race conditions depending on how your code is structured.
 * 
 * In general it's safer to signal the condition variable while the
 * mutex is locked.
 * @param  int      $value
 * @return SDL_cond
 */
function SDL_CreateCond(int $value):SDL_cond {
    return new SDL_cond(0);
}

/**
 * Wait on the condition variable, unlocking the provided mutex.
 * 
 * WARNING: The mutex must be locked before entering this function!
 * 
 * The mutex is re-locked once the condition variable is signaled.
 * @param  SDL_cond  $condition
 * @param  SDL_mutex $mutex
 * @return int       0 when it is signaled, or -1 on error.
 */
function SDL_CondWait(
    SDL_cond $condition,
    SDL_mutex $mutex
):int {
    return 0;
}

/**
 * Restart one of the threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondSignal(SDL_cond $cond):int {
    return 0;
}

/**
 * Restart all threads that are waiting on the condition variable.
 * @param  SDL_cond $cond
 * @return int      0 or -1 on error.
 */
function SDL_CondBroadcast(SDL_cond $cond):int {
    return 0;
}

/**
 * Waits for at most \c ms milliseconds, and returns 0 if the condition variable is signaled, `SDL_MUTEX_TIMEDOUT` if the condition is not signaled in the allotted time, and -1 on error.
 * 
 * WARNING: On some platforms this function is implemented by looping with a delay of 1 ms, and so should be avoided if possible.
 * @param  SDL_cond  $cond
 * @param  SDL_mutex $mutex
 * @param  int       $ms
 * @return int
 */
function SDL_CondWaitTimeout(SDL_cond $cond, SDL_mutex $mutex, int $ms):int {
    return 0;
}

/**
 * Destroy a condition variable.
 * @param  SDL_cond $cond
 * @return void
 */
function SDL_DestroyCond(SDL_cond $cond):void {
}

/**
 * Get the human readable name of a pixel format.
 * @param  int    $format
 * @return string
 */
function SDL_GetPixelFormatName(int $format):string {
    return '';
}

/**
 * Convert one of the enumerated pixel formats to a bpp and RGBA masks.
 * @param  int  $format
 * @param  int  $bpp
 * @param  int  $Rmask
 * @param  int  $Gmask
 * @param  int  $Bmask
 * @param  int  $Amask
 * @return bool `true`, or `false` if the conversion wasn't possible.
 */
function SDL_PixelFormatEnumToMasks(
    int $format,
    int &$bpp,
    int &$Rmask,
    int &$Gmask,
    int &$Bmask,
    int &$Amask
):bool {
    return true;
}

/**
 * Convert a bpp and RGBA masks to an enumerated pixel format.
 * @param  int  $format
 * @param  int  $bpp
 * @param  int  $Rmask
 * @param  int  $Gmask
 * @param  int  $Bmask
 * @param  int  $Amask
 * @return bool The pixel format, or `SDL_PIXELFORMAT_UNKNOWN` if the conversion wasn't possible.
 */
function SDL_MasksToPixelFormatEnum(
    int $format,
    int $bpp,
    int $Rmask,
    int $Gmask,
    int $Bmask,
    int $Amask
):bool {
    return true;
}

/**
 * Create an SDL_PixelFormat structure from a pixel format enum.
 * @param  int             $ncolors
 * @return SDL_PixelFormat
 */
function SDL_AllocFormat(int $ncolors):SDL_PixelFormat {
    /** @var SDL_PixelFormat $o*/
    $o = new stdClass;
    return $o;
}

/**
 * Set the palette for a pixel format structure.
 * @param  SDL_PixelFormat $format
 * @param  SDL_Palette     $palette
 * @return int
 */
function SDL_SetPixelFormatPalette(
    SDL_PixelFormat $format,
    SDL_Palette $palette
):int {
    return 0;
}

/**
 * Set a range of colors in a palette.
 * @param  SDL_Palette $palette The palette to modify.
 * @param  array       $colors  An array of colors to copy into the palette.
 * @param  int         $first   The index of the first palette entry to modify.
 * @param  int         $ncolors The number of entries to modify.
 * @return int         0 on success, or -1 if not all of the colors could be set.
 */
function SDL_SetPaletteColors(
    SDL_Palette $palette,
    array $colors,
    int $first,
    int $ncolors
):int {
    return 0;
}

/**
 * Get the RGB components from a pixel of the specified format.
 * @param  int             $pixel
 * @param  SDL_PixelFormat $format
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @return void
 */
function SDL_GetRGB(
    int $pixel,
    SDL_PixelFormat $format,
    int &$r,
    int &$g,
    int &$b
):void {
}

/**
 * Get the RGBA components from a pixel of the specified format.
 * @param  int             $pixel
 * @param  SDL_PixelFormat $format
 * @param  int             $r
 * @param  int             $g
 * @param  int             $b
 * @param  int             $a
 * @return void
 */
function SDL_GetRGBA(
    int $pixel,
    SDL_PixelFormat $format,
    int &$r,
    int &$g,
    int &$b,
    int &$a
):void {
}

/**
 * Calculate a 256 entry gamma ramp for a gamma value.
 * @param  float $gamma
 * @param  array $ramp
 * @return void
 */
function SDL_CalculateGammaRamp(float $gamma, array &$ramp):void {
}

/**
 * Gets the name of the platform.
 * @return string
 */
function SDL_GetPlatform():string {
    return '';
}

/**
 * Get the current power supply details.
 * @param  null|int $sec Seconds of battery life left. You can pass a `NULL` here if
 *                       you don't care. Will return -1 if we can't determine a
 *                       value, or we're not running on a battery.
 * @param  null|int $pct Percentage of battery life left, between 0 and 100. You can
 *                       pass a NULL here if you don't care. Will return -1 if we
 *                       can't determine a value, or we're not running on a battery.
 * @return string   The state of the battery (if any).
 */
function SDL_GetPowerInfo(null|int &$sec = null, null|int &$pct = null):string {
    return '';
}

/**
 * 
 * @param  resource      $renderer
 * @param  int           $format
 * @param  int           $access
 * @param  int           $w
 * @param  int           $h
 * @return null|resource
 */
function SDL_CreateTexture(
    mixed $renderer,
    int $format,
    int $access,
    int $w,
    int $h,
):mixed {
}

/**
 * 
 * @param  resource $renderer
 * @param  resource $texture
 * @return null|int
 */
function SDL_SetRenderTarget(
    mixed $renderer,
    mixed $texture,
):null|int {
    return null;
}

/**
 * 
 * @param  resource $renderer
 * @param  null|int $width
 * @param  null|int $height
 * @return resource
 */
function SDL_GetRendererOutputSize(
    mixed $renderer,
    null|int &$width = null,
    null|int &$height = null,
):mixed {
}


/**
 * 
 * @param  resource $texture
 * @param  null|int $format
 * @param  null|int $access
 * @param  null|int $width
 * @param  null|int $height
 * @return int
 */
function SDL_QueryTexture(
    mixed $texture,
    null|int &$format = null,
    null|int &$access = null,
    null|int &$width = null,
    null|int &$height = null,
):int {
    return 0;
}

/**
 * 
 * @return SDL_RWops
 */
function SDL_AllocRW():SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  string    $path
 * @param  string    $mode
 * @return SDL_RWops
 */
function SDL_RWFromFile(
    string $path,
    string $mode,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  string    $buf
 * @param  int       $size
 * @return SDL_RWops
 */
function SDL_RWFromConstMem(
    string $buf,
    int $size,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}


/**
 * 
 * @param  string    $buf
 * @param  int       $size
 * @return SDL_RWops
 */
function SDL_RWFromMem(
    string &$buf,
    int $size
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * PHP change: this function support PHP stream
 * SDL_RWFromFP will be used for real file
 * SDL_RWFromMem will be used for other stream
 * (inspired from gd extension)
 * @param  resource  $fp
 * @param  bool      $autoclose
 * @return SDL_RWops
 */
function SDL_RWFromFP(
    mixed $fp,
    bool $autoclose,
):SDL_RWops {
    /** @var SDL_RWops */
    $o = new stdClass;
    return $o;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return void
 */
function SDL_FreeRW(SDL_RWops $area):void {
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWsize(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $offset
 * @param  int       $whence
 * @return int
 */
function SDL_RWseek(
    SDL_RWops $area,
    int $offset,
    int $whence
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWtell(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_RWclose(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  string    $string
 * @param  mixed     $buf
 * @param  int       $size
 * @param  int       $n
 * @return int
 */
function SDL_RWread(
    SDL_RWops $area,
    string &$buf,
    int $size = 1,
    int $n = 0
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  string    $buf
 * @param  int       $size
 * @param  int       $n
 * @return int
 */
function SDL_RWwrite(
    SDL_RWops $area,
    string $buf,
    int $size = 0,
    int $n = 0
): int {
    return 0;
}

/**
 * Read endian functions.
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadU8(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadLE16(SDL_RWops $area): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE16(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadLE32(SDL_RWops $area):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE32(SDL_RWops $area):int {
    return 0;
}

function SDL_ReadLE64(SDL_RWops $area): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @return int
 */
function SDL_ReadBE64(SDL_RWops $area):int {
    return 0;
}

/**
 * Write endian functions.
 * 
 * Write an item of native format to the specified endianness.
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteU8(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE16(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE16(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE32(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE32(
    SDL_RWops $area,
    int $value
):int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteLE64(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * 
 * @param  SDL_RWops $area
 * @param  int       $value
 * @return int
 */
function SDL_WriteBE64(
    SDL_RWops $area,
    int $value
): int {
    return 0;
}

/**
 * This function cleans up all initialized subsystems. 
 * You should call it upon all exit conditions.
 * @param  int $flags
 * @return int
 */
function SDL_InitSubSystem(int $flags):int {
    return 0;
}

/**
 * This function cleans up specific SDL subsystems.
 * @param  int $flags
 * @return int
 */
function SDL_QuitSubSystem(int $flags):int {
    return 0;
}

/**
 * This function returns a mask of the specified subsystems which have previously been initialized.
 * 
 * If `$flags` is 0, it returns a mask of all initialized subsystems.
 * @param  int $flags
 * @return int
 */
function SDL_WasInit(int $flags):int {
    return 0;
}

/**
 * Copy a block of pixels of one format to another format.
 * @param  int        $width
 * @param  int        $height
 * @param  int        $src_format
 * @param  SDL_Pixels $src
 * @param  int        $src_pitch
 * @param  int        $dst_format
 * @param  SDL_Pixels $dst
 * @param  int        $dst_pitch
 * @return int        0 on success, or -1 if there was an error.
 */
function SDL_ConvertPixels(
    int $width,
    int $height,
    int $src_format,
    SDL_Pixels $src,
    int $src_pitch,
    int $dst_format,
    SDL_Pixels $dst,
    int $dst_pitch
):int {
    return 0;
}

/**
 * Get the code revision of SDL that is linked against your program.
 * 
 * Returns an arbitrary string (a hash value) uniquely identifying the
 * exact revision of the SDL library in use, and is only useful in comparing
 * against other revisions. It is NOT an incrementing number.
 * @return string
 */
function SDL_GetRevision():string {
    return '';
}

/**
 * Get the revision number of SDL that is linked against your program.
 * 
 * Returns a number uniquely identifying the exact revision of the SDL
 * library in use. It is an incrementing number based on commits to
 * hg.libsdl.org.
 * @return int
 */
function SDL_GetRevisionNumber():int {
    return 0;
}

/**
 * Macro to determine SDL version program was compiled against.
 * 
 * This macro fills in a SDL_version structure with the version of the
 * library you compiled against. This is determined by what header the
 * compiler uses. Note that if you dynamically linked the library, you might
 * have a slightly newer or older version at runtime. That version can be
 * determined with SDL_GetVersion(), which, unlike SDL_VERSION(),
 * is not a macro.
 * @param  array $version a SDL_version struct to initialize.
 * @return void
 */
function SDL_VERSION(array &$version):void {
}

/**
 * This macro turns the version numbers into a numeric value: (1,2,3) -> (1203)
 * 
 * This assumes that there will never be more than 100 patchlevels.
 * @param  int $x
 * @param  int $y
 * @param  int $z
 * @return int
 */
function SDL_VERSIONNUM(
    int $x,
    int $y,
    int $z
):int {
    return 0;
}

/**
 * This macro will evaluate to true if compiled with SDL at least X.Y.Z.
 * @param  int  $x
 * @param  int  $y
 * @param  int  $z
 * @return bool
 */
function SDL_VERSION_ATLEAST(
    int $x,
    int $y,
    int $z
):bool {
    return true;
}

/**
 * Get the number of video drivers compiled into SDL.
 * @return int
 */
function SDL_GetNumVideoDrivers():int {
    return 0;
}


/**
 * Get the name of a built in video driver.
 * 
 * The video drivers are presented in the order in which they are normally checked during initialization.
 * @param  int    $driverIndex
 * @return string
 */
function SDL_GetVideoDriver(int $driverIndex): string {
    return '';
}

/**
 * Initialize the video subsystem, optionally specifying a video driver.
 * 
 * This function initializes the video subsystem; setting up a connection
 * to the window manager, etc, and determines the available display modes
 * and pixel formats, but does not initialize a window or graphics mode.
 * @param  null|string $driver Initialize a specific driver by name, or NULL for the default video driver.
 * @return string      0 on success, -1 on error.
 */
function SDL_VideoInit(null|string $driver = null):int {
    return 0;
}

/**
 * Shuts down the video subsystem.
 * 
 * This function closes all windows, and restores the original video mode.
 * @return void
 */
function SDL_VideoQuit():void {
}

/**
 * Returns the name of the currently initialized video driver.
 * @return string The name of the current video driver or NULL if no driver has been initialized.
 */
function SDL_GetCurrentVideoDriver():string {
    return '';
}

/**
 * Returns the number of available video displays.
 * @return int
 */
function SDL_GetNumVideoDisplays():int {
    return 0;
}

/**
 * Get the name of a display in UTF-8 encoding.
 * @param  int    $displayIndex
 * @return string The name of a display, or NULL for an invalid display index.
 */
function SDL_GetDisplayName(int $displayIndex):string {
    return '';
}

/**
 * Get the desktop area represented by a display, with the primary display located at 0,0.
 * @param  int      $displayIndex
 * @param  SDL_Rect $rect
 * @return array    0 on success, or -1 if the index is out of range.
 */
function SDL_GetDisplayBounds(
    int $displayIndex,
    SDL_Rect &$rect
):array {
    return [];
}

/**
 * Returns the number of available display modes.
 * @param  int $displayIndex
 * @return int
 */
function SDL_GetNumDisplayModes(int $displayIndex):int {
    return 0;
}

/**
 * Fill in information about a specific display mode.
 * 
 * The display modes are sorted in this priority:
 *    - bits per pixel -> more colors to fewer colors
 *    - width -> largest to smallest
 *    - height -> largest to smallest
 *    - refresh rate -> highest to lowest
 * @param  int   $displayIndex
 * @param  int   $modeIndex
 * @return array
 */
function SDL_GetDisplayMode(
    int $displayIndex,
    int $modeIndex
):array {
    return [];
}

/**
 * Fill in information about the desktop display mode.
 * @param  int   $displayIndex
 * @return array
 */
function SDL_GetDesktopDisplayMode(int $displayIndex):array {
    return [];
}

/**
 * Fill in information about the current display mode.
 * @param  int   $displayIndex
 * @return array
 */
function SDL_GetCurrentDisplayMode(int $displayIndex):array {
    return[];
}

/**
 * Get the closest match to the requested display mode.
 * 
 * The available display modes are scanned, and `$closest` is filled in with the
 * closest mode matching the requested mode and returned.  The mode format and
 * refresh_rate default to the desktop mode if they are 0.  The modes are
 * scanned with size being first priority, format being second priority, and
 * finally checking the refresh_rate.  If all the available modes are too
 * small, then `NULL` is returned.
 * @param  int                  $displayIndex The index of display from which mode should be queried.
 * @param  SDL_DisplayMode      $mode         The desired display mode.
 * @param  SDL_DisplayMode      $closest      A pointer to a display mode to be filled in with the closest match of the available display modes.
 * @return null|SDL_DisplayMode The passed in value `$closest`, or `NULL` if no matching video mode was available.
 */
function SDL_GetClosestDisplayMode(
    int $displayIndex,
    SDL_DisplayMode $mode,
    SDL_DisplayMode $closest
):null|SDL_DisplayMode {
    return null;
}

/**
 * Returns whether the screensaver is currently enabled (default on).
 * @return bool
 */
function SDL_IsScreenSaverEnabled():bool {
    return true;
}

/**
 * Allow the screen to be blanked by a screensaver.
 * @return void
 */
function SDL_EnableScreenSaver():void {
}

/**
 * Prevent the screen from being blanked by a screensaver.
 * @return void
 */
function SDL_DisableScreenSaver():void {
}

/**
 * Get the display index associated with a window.
 * @param  SDL_Window $window
 * @return void       The display index of the display containing the center of the window, or -1 on error.
 */
function SDL_GetWindowDisplayIndex(SDL_Window $window):void {
}

/**
 * Set the display mode used when a fullscreen window is visible.
 * 
 * By default the window's dimensions and the desktop format and refresh rate
 *  are used.
 * @param  SDL_Window      $window The window for which the display mode should be set.
 * @param  SDL_DisplayMode $mode   The mode to use, or NULL for the default mode.
 * @return int             0 on success, or -1 if setting the display mode failed.
 */
function SDL_SetWindowDisplayMode(
    SDL_Window $window,
    SDL_DisplayMode $mode
):int {
    return 0;
}

/**
 * Fill in information about the display mode used when a fullscreen window is visible.
 * @param  SDL_Window      $window
 * @param  SDL_DisplayMode $mode
 * @return int
 */
function SDL_GetWindowDisplayMode(
    SDL_Window $window,
    SDL_DisplayMode $mode
):int {
    return 0;
}

/**
 * Get the pixel format associated with the window.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowPixelFormat(SDL_Window $window):int {
    return 0;
}

/**
 * Get the numeric ID of a window, for logging purposes.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowID(SDL_Window $window): int {
    return 0;
}

/**
 * Get the window flags.
 * @param  SDL_Window $window
 * @return int
 */
function SDL_GetWindowFlags(SDL_Window $window):int {
    return 0;
}

/**
 * Set the icon for a window.
 * @param  SDL_Window  $window The window for which the icon should be set.
 * @param  SDL_Surface $icon   The icon for the window.
 * @return void
 */
function SDL_SetWindowIcon(
    SDL_Window $window,
    SDL_Surface $icon
):void {
}

/**
 * Set the position of a window.
 * 
 * The window coordinate origin is the upper left of the display.
 * @param  SDL_Window $window The window to reposition.
 * @param  int        $x      The x coordinate of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @param  int        $y      The y coordinate of the window, `SDL_WINDOWPOS_CENTERED`, or `SDL_WINDOWPOS_UNDEFINED`.
 * @return void
 */
function SDL_SetWindowPosition(
    SDL_Window $window,
    int $x,
    int $y
):void {
}

/**
 * 
 * @param  int $display
 * @return int
 */
function SDL_WINDOWPOS_CENTERED_DISPLAY(int $display):int {
    return 0;
}

/**
 * 
 * @param  int $display
 * @return int
 */
function SDL_WINDOWPOS_UNDEFINED_DISPLAY(int $display):int {
    return 0;
}

/**
 * Get the position of a window.
 * 
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the x position, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the y position, may be `NULL`.
 * @return void
 */
function SDL_GetWindowPosition(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the size of a window's client area.
 * You can't change the size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to resize.
 * @param  int        $x      The width of the window, must be >0.
 * @param  int        $y      The height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the minimum size of a window's client area.
 * 
 * You can't change the minimum size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to set a new minimum size.
 * @param  int        $x      The minimum width of the window, must be >0.
 * @param  int        $y      The minimum height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowMinimumSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the minimum size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the minimum width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the minimum height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowMinimumSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the maximum size of a window's client area.
 * 
 * You can't change the maximum size of a fullscreen window, it automatically matches the size of the display mode.
 * @param  SDL_Window $window The window to set a new maximum size.
 * @param  int        $x      The maximum width of the window, must be >0.
 * @param  int        $y      The maximum height of the window, must be >0.
 * @return void
 */
function SDL_SetWindowMaximumSize(
    SDL_Window $window,
    int $x,
    int $y,
):void {
}

/**
 * Get the maximum size of a window's client area.
 * @param  SDL_Window $window The window to query.
 * @param  null|int   $x      Pointer to variable for storing the maximum width, may be `NULL`.
 * @param  null|int   $y      Pointer to variable for storing the maximum height, may be `NULL`.
 * @return void
 */
function SDL_GetWindowMaximumSize(
    SDL_Window $window,
    null|int &$x = null,
    null|int &$y = null,
):void {
}

/**
 * Set the border state of a window.
 * 
 * This will add or remove the window's `SDL_WINDOW_BORDERLESS` flag and
 * add or remove the border from the actual window. This is a no-op if the
 * window's border already matches the requested state.
 * 
 * You can't change the border state of a fullscreen window.
 * @param  SDL_Window $window   The window of which to change the border state.
 * @param  bool       $bordered SDL_FALSE to remove border, SDL_TRUE to add border.
 * @return void
 */
function SDL_SetWindowBordered(
    SDL_Window $window,
    bool $bordered
):void {
}

/**
 * Show a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_ShowWindow(SDL_Window $window):void {
}

/**
 * Hide a window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_HideWindow(SDL_Window $window):void {
}

/**
 * Raise a window above other windows and set the input focus.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_RaiseWindow(SDL_Window $window):void {
}

/**
 * Make a window as large as possible.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_MaximizeWindow(SDL_Window $window):void {
}

/**
 * Minimize a window to an iconic representation.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_MinimizeWindow(SDL_Window $window):void {
}

/**
 * Restore the size and position of a minimized or maximized window.
 * @param  SDL_Window $window
 * @return void
 */
function SDL_RestoreWindow(SDL_Window $window):void {
}

/**
 * Set a window's fullscreen state.
 * @param  SDL_Window $window
 * @param  int        $flags
 * @return void       0 on success, or -1 if setting the display mode failed.
 */
function SDL_SetWindowFullscreen(
    SDL_Window $window,
    int $flags
):void {
}

/**
 * Set a window's input grab mode.
 * @param  SDL_Window $window  The window for which the input grab mode should be set.
 * @param  bool       $grabbed This is SDL_TRUE to grab input, and SDL_FALSE to release input.
 * @return void
 */
function SDL_SetWindowGrab(
    SDL_Window $window,
    bool $grabbed
):void {
}

/**
 * Get a window's input grab mode.
 * @param  SDL_Window $window
 * @return bool       This returns SDL_TRUE if input is grabbed, and SDL_FALSE otherwise.
 */
function SDL_GetWindowGrab(SDL_Window $window):bool {
    return true;
}

/**
 * Set the brightness (gamma correction) for a window.
 * @param  SDL_Window $window
 * @param  float      $brightness
 * @return int        0 on success, or -1 if setting the brightness isn't supported.
 */
function SDL_SetWindowBrightness(
    SDL_Window $window,
    float $brightness
):int {
    return 0;
}

/**
 * Get the brightness (gamma correction) for a window.
 * @param  SDL_Window $window
 * @return void       The last brightness value passed to `SDL_SetWindowBrightness()`.
 */
function SDL_GetWindowBrightness(SDL_Window $window):void {
}

/**
 * Get the gamma ramp for a window.
 * @param  SDL_Window $window The window from which the gamma ramp should be queried.
 * @param  array      $red    A pointer to a 256 element array of 16-bit quantities to hold the translation table for the red channel, or `NULL`.
 * @param  array      $green  A pointer to a 256 element array of 16-bit quantities to hold the translation table for the green channel, or `NULL`.
 * @param  array      $blue   A pointer to a 256 element array of 16-bit quantities to hold the translation table for the blue channel, or `NULL`.
 * @return int        0 on success, or -1 if gamma ramps are unsupported.
 */
function SDL_GetWindowGammaRamp(
    SDL_Window $window,
    array &$red,
    array &$green,
    array &$blue
):int {
    return 0;
}

/**
 * Get the title of a window, in UTF-8 format.
 * @param  SDL_Window $window
 * @return string
 */
function SDL_GetWindowTitle(SDL_Window $window):string {
    return '';
}

/**
 * Return whether the given window is a shaped window.
 * @param  SDL_Window $window The window to query for being shaped.
 * @return null|bool  `true` if the window is a window that can be shaped, `false` if the window is unshaped or `NULL`.
 */
function SDL_IsShapedWindow(SDL_Window $window):null|bool {
    return null;
}

/**
 * Get the shape parameters of a shaped window.
 * @param  SDL_Window          $window     The shaped window whose parameters should be retrieved.
 * @param  SDL_WindowShapeMode $shape_mode An empty shape-mode structure to fill, 
 *                                         or `NULL` to check whether the window has a shape.
 * @return int                 0 if the window has a shape and, provided shape_mode was not `NULL`, 
 *                                        shape_mode has been filled with the mode data, `SDL_NONSHAPEABLE_WINDOW` if 
 *                                        the `SDL_Window` given is not a shaped window, or `SDL_WINDOW_LACKS_SHAPE` if 
 *                                        the `SDL_Window*` given is a shapeable window currently lacking a shape.
 */
function SDL_GetShapedWindowMode(
    SDL_Window $window,
    SDL_WindowShapeMode &$shape_mode
):int {
    return 0;
}