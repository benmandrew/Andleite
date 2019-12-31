
#include "modulemanager.h"

ModuleManager::ModuleManager() {
    window = new Window();
    input = new Input();
    map = new Map();
    player = new Creature();
    raycaster = new RayCaster();
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
    raycaster->init(map);
    player->init(PLAYER_BMP_PATH, map);
    return true;
}

bool ModuleManager::pollInput() {
    input->pollEvents();
    return input->doQuit();
}

void ModuleManager::runFrame() {
    raycaster->raycastSightlines(player->getPos());
}

void ModuleManager::draw() {
    window->clear();
    map->blitMap();
    window->blit(map->getSurface(), map->getRect());
    window->blit(player->getSprite());
    window->flip();
}
