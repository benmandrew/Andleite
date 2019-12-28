#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "modulemanager.h"

void mainLoop(ModuleManager* m) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        m->input->pollEvents();
        quit = m->input->doQuit();
    }
}

int main(int argc, char* args[]) {
    ModuleManager* m = new ModuleManager();
    if (m->init()) {
        mainLoop(m);
    }
    delete m;
    SDL_Quit();
    return 0;
}
