#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "window.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

void close(SDL_Surface* player) {
    SDL_FreeSurface(player);
    player = NULL;
}

void mainLoop(
    Window* window,
    SDL_Surface* player) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        window.blit(player, &stretchRect);
        window.update();
    }
}

int main(int argc, char* args[]) {

    Window* window = new Window();
    Creature player;
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
    } else {
        if (!loadMedia("./resources/slime.bmp", pPlayer, window->getPixelFormat())) {
            printf("Failed to load media!\n");
        } else {
            mainLoop(window, *pPlayer);
        }
    }
    close(*pPlayer);
    return 0;
}
