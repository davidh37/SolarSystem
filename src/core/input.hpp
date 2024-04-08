#pragma once
#include "common.hpp"

namespace input {
    enum Keycode {
        KEY_NONE,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_UP,
        KEY_LEFT,
        KEY_DOWN,
        KEY_RIGHT,
        KEY_DELETE,
        KEY_SPACE,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_ESC,
        KEY_BOARD_TOTAL,
        /* boundary between keyboard and non keyboard*/
        KEY_MOUSE_LEFT,
        KEY_MOUSE_RIGHT,
        KEY_MOUSE_WHEEL_DOWN,
        KEY_MOUSE_WHEEL_UP,
        KEY_TOTAL
    };

    enum Keystate {
        RELEASED = -1,
        UP = 0,
        DOWN = 1,
        PRESSED = 2,
    };

    void queryInputs();
	bool hasQuit();
    bool hasResized();
	void getMousePosition(int &x, int &y);
	Keystate getKeyState(Keycode key);
}
