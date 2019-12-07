#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "window.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

const std::string PLAYER_BMP_PATH = "./resources/player.bmp";
const std::string SLIME_BMP_PATH = "./resources/slime.bmp";

void mainLoop(
    Window* window,
    Creature* player) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        window->blit(player);
        window->update();
    }
}

int main(int argc, char* args[]) {
    Window* window = new Window();
    Creature* player = new Creature();
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
    } else {

        player->loadBMP(SLIME_BMP_PATH);

        mainLoop(window, player);
    }
    delete window;
    delete player;
    SDL_Quit();
    return 0;
}
