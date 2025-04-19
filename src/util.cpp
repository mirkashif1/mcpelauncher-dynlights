#include <sys/time.h>
#include "util.h"
#include "key_mapping.h"

int64_t getEpochTime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

unsigned long unsignedDiff(unsigned long a, unsigned long b) {
    if(a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int clamp(int min, int v, int max) {
    if(v < min) {
        return min;
    }
    if(v > max) {
        return max;
    }
    return v;
}

std::string keyToString(int key) {
    KeyCode keyCode = (KeyCode)key;
    if((keyCode >= KeyCode::NUM_0 && keyCode <= KeyCode::NUM_9) || (keyCode >= KeyCode::A && keyCode <= KeyCode::Z)) {
        return std::string((char*)&key);
    }
    if(keyCode >= KeyCode::NUMPAD_0 && keyCode <= KeyCode::NUMPAD_9) {
        return "NUMPAD_" + std::to_string((int)keyCode - (int)KeyCode::NUMPAD_0);
    }
    if(keyCode >= KeyCode::FN1 && keyCode <= KeyCode::FN12) {
        return "F" + std::to_string((int)keyCode - (int)KeyCode::FN1 + 1);
    }
    switch(keyCode) {
    case KeyCode::BACK:
        return "BACK";
    case KeyCode::BACKSPACE:
        return "BACKSPACE";
    case KeyCode::TAB:
        return "TAB";
    case KeyCode::ENTER:
        return "ENTER";
    case KeyCode::LEFT_SHIFT:
        return "LEFT_SHIFT";
    case KeyCode::RIGHT_SHIFT:
        return "RIGHT_SHIFT";
    case KeyCode::LEFT_CTRL:
        return "LEFT_CTRL";
    case KeyCode::RIGHT_CTRL:
        return "RIGHT_CTRL";
    case KeyCode::PAUSE:
        return "PAUSE";
    case KeyCode::CAPS_LOCK:
        return "CAPS_LOCK";
    case KeyCode::ESCAPE:
        return "ESCAPE";
    case KeyCode::SPACE:
        return "SPACE";
    case KeyCode::PAGE_UP:
        return "PAGE_UP";
    case KeyCode::PAGE_DOWN:
        return "PAGE_DOWN";
    case KeyCode::END:
        return "END";
    case KeyCode::HOME:
        return "HOME";
    case KeyCode::LEFT:
        return "LEFT";
    case KeyCode::UP:
        return "UP";
    case KeyCode::RIGHT:
        return "RIGHT";
    case KeyCode::DOWN:
        return "DOWN";
    case KeyCode::INSERT:
        return "INSERT";
    case KeyCode::DELETE:
        return "DELETE";
    case KeyCode::NUM_LOCK:
        return "NUM_LOCK";
    case KeyCode::SCROLL_LOCK:
        return "SCROLL_LOCK";
    case KeyCode::SEMICOLON:
        return "SEMICOLON";
    case KeyCode::EQUAL:
        return "EQUAL";
    case KeyCode::COMMA:
        return "COMMA";
    case KeyCode::MINUS:
        return "MINUS";
    case KeyCode::NUMPAD_ADD:
        return "NUMPAD_ADD";
    case KeyCode::NUMPAD_SUBTRACT:
        return "NUMPAD_SUBTRACT";
    case KeyCode::NUMPAD_MULTIPLY:
        return "NUMPAD_MULTIPLY";
    case KeyCode::NUMPAD_DIVIDE:
        return "NUMPAD_DIVIDE";
    case KeyCode::PERIOD:
        return "PERIOD";
    case KeyCode::NUMPAD_DECIMAL:
        return "NUMPAD_DECIMAL";
    case KeyCode::SLASH:
        return "SLASH";
    case KeyCode::GRAVE:
        return "GRAVE";
    case KeyCode::LEFT_BRACKET:
        return "LEFT_BRACKET";
    case KeyCode::BACKSLASH:
        return "BACKSLASH";
    case KeyCode::RIGHT_BRACKET:
        return "RIGHT_BRACKET";
    case KeyCode::APOSTROPHE:
        return "APOSTROPHE";
    case KeyCode::MENU:
        return "MENU";
    case KeyCode::LEFT_SUPER:
        return "LEFT_SUPER";
    case KeyCode::RIGHT_SUPER:
        return "RIGHT_SUPER";
    case KeyCode::LEFT_ALT:
        return "LEFT_ALT";
    case KeyCode::RIGHT_ALT:
        return "RIGHT_ALT";
    default:
        return "UNKNOWN";
    };
}