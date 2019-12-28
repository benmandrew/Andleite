
#include "modulemanager.h"

ModuleManager::ModuleManager() {
    window = new Window();
    input = new Input();
    map = new Map();
    player = new Creature();
}

ModuleManager::~ModuleManager() {
    delete window;
    delete input;
    delete map;
    delete player;
}

bool ModuleManager::init() {
    input->addObserver(player);
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
        return false;
    }
    map->init();
    player->init(PLAYER_BMP_PATH, map);
    return true;
}

void ModuleManager::blitWorld() {
    window->clear();
    window->blit(map->getSurface(), map->getRect());
    window->blit(player->getSprite());
    window->flip();
}