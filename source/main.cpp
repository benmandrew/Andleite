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
    Input* input,
    Creature* player) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        input->pollEvents();
        quit = input->doQuit();
        window->clear();
        window->blit(player);
        window->flip();
    }
}

int main(int argc, char* args[]) {
    Window* window = new Window();
    Input* input = new Input();
    Creature* player = new Creature();

    input->addObserver(player);

    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
    } else {
        player->loadBMP(SLIME_BMP_PATH);
        mainLoop(window, input, player);
    }
    delete window;
    delete input;
    delete player;
    SDL_Quit();
    return 0;
}
