#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "window.h"
#include "map.h"

void mainLoop(
    Window* window,
    Input* input,
    Map* map,
    Creature* player) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        input->pollEvents();
        quit = input->doQuit();
        window->clear();
        window->blit(map->getSurface(), map->getRect());
        window->blit(player->getSprite());
        window->flip();
    }
}

int main(int argc, char* args[]) {
    Window* window = new Window();
    Input* input = new Input();
    Map* map = new Map();
    Creature* player = new Creature();
    input->addObserver(player);
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
    } else {
        map->init();
        player->init(PLAYER_BMP_PATH);
        mainLoop(window, input, map, player);
    }
    delete window;
    delete input;
    delete player;
    SDL_Quit();
    return 0;
}
