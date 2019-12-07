#include "input.h"

const std::map<SDL_Keycode, InputEvents> Input::inputMap
    = Input::createMap();

void Input::pollEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            auto itr = inputMap.find(e.key.keysym.sym);
            if (itr != inputMap.end()) {
                notify(itr->second);
            }
        }
    }
}

bool Input::doQuit() {
    return quit;
}