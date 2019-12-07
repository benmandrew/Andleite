#include <map>
#include <SDL2/SDL.h>
#include "observer.h"

enum InputEvents {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

typedef std::map<SDL_Keycode, InputEvents> keyMap;

class Input : public Subject {
private:
    bool quit = false;

    static const std::map<SDL_Keycode, InputEvents> inputMap;
    static std::map<SDL_Keycode, InputEvents> createMap() {
        std::map<SDL_Keycode, InputEvents> m;
        m[SDLK_w] = KEY_UP;
        m[SDLK_s] = KEY_DOWN;
        m[SDLK_a] = KEY_LEFT;
        m[SDLK_d] = KEY_RIGHT;
        return m;
    }
public:
    void pollEvents();
    bool doQuit();
};