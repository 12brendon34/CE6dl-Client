#pragma once

//common chrome types
struct vec3 {
	float x;
	float y;
	float z;
};

struct vec4 {
	float x;
	float y;
	float z;
	float w;
};

struct quat {
	float x;
	float y;
	float z;
	float w;
};

struct mtx34 {
	float m[3][4];
};

//chrome engine 5 structs, may be inaccurate
class EElementControlNavigation {
public:
	typedef enum TYPE {
		NavUp = 0,
		NavDown = 1,
		NavLeft = 2,
		NavRight = 3,
		TabForward = 4,
		TabBackward = 5,
		Accepted = 6,
		Cancelled = 7,
		ENUM_COUNT = 8
	} TYPE;
};

//chrome engine 5 structs, may be inaccurate
class EUIFocusChangeReason {
public:
	typedef enum TYPE {
		Manual = 0,
		NavUp = 1,
		NavDown = 2,
		NavLeft = 3,
		NavRight = 4,
		TabForward = 5,
		TabBackward = 6,
		DisableTabForward = 7
	} TYPE;
};

class EUIMessage {
public:
	struct SUIMessage {
		int m_message;
		int m_senderId;
		int m_iParam;
		float m_fParam1;
		float m_fParam2;
	};

	typedef enum TYPE {
		NONE = 0,
		PRESS = 1,
		DOUBLE_PRESS = 2,
		NAV_UP = 3,
		NAV_DOWN = 4,
		NAV_LEFT = 5,
		NAV_RIGHT = 6,
		TAB_FORWARD = 7,
		TAB_BACKWARD = 8,
		FREEZE_MOUSE = 9,
		UNFREEZE_MOUSE = 10,
		FREEZE_INPUTS = 11,
		UNFREEZE_INPUTS = 12,
		HTML_LINK_CLICKED = 13,
		_GAMESCRIPT_MESSAGES_ = 4096
	} TYPE;
};

class EKey {
public:
	typedef enum TYPE {
		_NONE = 0,
		_ESCAPE = 1,
		_1 = 2,
		_2 = 3,
		_3 = 4,
		_4 = 5,
		_5 = 6,
		_6 = 7,
		_7 = 8,
		_8 = 9,
		_9 = 10,
		_0 = 11,
		_MINUS = 12,
		_EQUALS = 13,
		_BACK = 14,
		_TAB = 15,
		_Q = 16,
		_W = 17,
		_E = 18,
		_R = 19,
		_T = 20,
		_Y = 21,
		_U = 22,
		_I = 23,
		_O = 24,
		_P = 25,
		_LBRACKET = 26,
		_RBRACKET = 27,
		_RETURN = 28,
		_LCONTROL = 29,
		_A = 30,
		_S = 31,
		_D = 32,
		_F = 33,
		_G = 34,
		_H = 35,
		_J = 36,
		_K = 37,
		_L = 38,
		_SEMICOLON = 39,
		_APOSTROPHE = 40,
		_GRAVE = 41,
		_LSHIFT = 42,
		_BACKSLASH = 43,
		_Z = 44,
		_X = 45,
		_C = 46,
		_V = 47,
		_B = 48,
		_N = 49,
		_M = 50,
		_COMMA = 51,
		_PERIOD = 52,
		_SLASH = 53,
		_RSHIFT = 54,
		_MULTIPLY = 55,
		_LMENU = 56,
		_SPACE_ = 57,
		_CAPITAL = 58,
		_F1 = 59,
		_F2 = 60,
		_F3 = 61,
		_F4 = 62,
		_F5 = 63,
		_F6 = 64,
		_F7 = 65,
		_F8 = 66,
		_F9 = 67,
		_F10 = 68,
		_NUMLOCK = 69,
		_SCROLL = 70,
		_NUMPAD7 = 71,
		_NUMPAD8 = 72,
		_NUMPAD9 = 73,
		_SUBTRACT = 74,
		_NUMPAD4 = 75,
		_NUMPAD5 = 76,
		_NUMPAD6 = 77,
		_ADD = 78,
		_NUMPAD1 = 79,
		_NUMPAD2 = 80,
		_NUMPAD3 = 81,
		_NUMPAD0 = 82,
		_DECIMAL = 83,
		_OEM_102 = 86,
		_F11 = 87,
		_F12 = 88,
		_F13 = 100,
		_F14 = 101,
		_F15 = 102,
		_KANA = 112,
		_ABNT_C1 = 115,
		_CONVERT = 121,
		_NOCONVERT = 123,
		_YEN = 125,
		_ABNT_C2 = 126,
		_NUMPADEQUALS = 141,
		_PREVTRACK = 144,
		_AT = 145,
		_COLON = 146,
		_UNDERLINE = 147,
		_KANJI = 148,
		_STOP = 149,
		_AX = 150,
		_UNLABELED = 151,
		_NEXTTRACK = 153,
		_NUMPADENTER = 156,
		_RCONTROL = 157,
		_MUTE = 160,
		_CALCULATOR = 161,
		_PLAYPAUSE = 162,
		_MEDIASTOP = 164,
		_VOLUMEDOWN = 174,
		_VOLUMEUP = 176,
		_WEBHOME = 178,
		_NUMPADCOMMA = 179,
		_DIVIDE = 181,
		_SYSRQ = 183,
		_RMENU = 184,
		_PAUSE = 197,
		_HOME = 199,
		_UP_ = 200,
		_PRIOR = 201,
		_LEFT = 203,
		_RIGHT = 205,
		_END = 207,
		_DOWN = 208,
		_NEXT = 209,
		_INSERT = 210,
		_DELETE = 211,
		_LWIN = 219,
		_RWIN = 220,
		_APPS = 221,
		_POWER = 222,
		_SLEEP = 223,
		_WAKE = 227,
		_WEBSEARCH = 229,
		_WEBFAVORITES = 230,
		_WEBREFRESH = 231,
		_WEBSTOP = 232,
		_WEBFORWARD = 233,
		_WEBBACK = 234,
		_MYCOMPUTER = 235,
		_MAIL = 236,
		_MEDIASELECT = 237,
		_MOUSE_WHEEL_UP = 241,
		_MOUSE_WHEEL_DN = 242,
		_MOUSE_BUTTON1 = 61440,
		_MOUSE_BUTTON2 = 61441,
		_MOUSE_BUTTON3 = 61442
	} TYPE;
};

class EJoy {
public:
	typedef enum TYPE {
		_AXIS_THUMBLX = 0,
		_AXIS_X = 0,
		_FIRST_AXIS = 0,
		_AXIS_THUMBLY = 1,
		_AXIS_Y = 1,
		_AXIS_LEFTTRIGGER = 2,
		_AXIS_Z = 2,
		_AXIS_RX = 3,
		_AXIS_THUMBRX = 3,
		_AXIS_RY = 4,
		_AXIS_THUMBRY = 4,
		_AXIS_RIGHTTRIGGER = 5,
		_AXIS_RZ = 5,
		_AXIS_SLIDER_0 = 6,
		_AXIS_SLIDER_1 = 7,
		_AXIS_POV_0 = 8,
		_AXIS_POV_1 = 9,
		_AXIS_POV_2 = 10,
		_AXIS_POV_3 = 11,
		_LAST_AXIS = 11,
		_BUTTON_1 = 3840,
		_BUTTON_A = 3840,
		_BUTTON_2 = 3841,
		_BUTTON_B = 3841,
		_BUTTON_3 = 3842,
		_BUTTON_X = 3842,
		_BUTTON_4 = 3843,
		_BUTTON_Y = 3843,
		_BUTTON_5 = 3844,
		_BUTTON_LEFTSHOULDER = 3844,
		_BUTTON_6 = 3845,
		_BUTTON_RIGHTSHOULDER = 3845,
		_BUTTON_7 = 3846,
		_BUTTON_BACK = 3846,
		_BUTTON_8 = 3847,
		_BUTTON_START = 3847,
		_BUTTON_9 = 3848,
		_BUTTON_LEFTTHUMB = 3848,
		_BUTTON_10 = 3849,
		_BUTTON_RIGHTTHUMB = 3849,
		_BUTTON_11 = 3850,
		_BUTTON_DPADUP = 3850,
		_BUTTON_12 = 3851,
		_BUTTON_DPADDOWN = 3851,
		_BUTTON_13 = 3852,
		_BUTTON_DPADLEFT = 3852,
		_BUTTON_14 = 3853,
		_BUTTON_DPADRIGHT = 3853,
		_BUTTON_15 = 3854,
		_BUTTON_16 = 3855
	} TYPE;
};