
#include "modulemanager.h"

ModuleManager::ModuleManager() {
    window = new Window();
    input = new Input();
    map = new Map();
    spriteIndex = new SpriteIndex();
    player = new Creature();
    raycaster = new RayCaster();
}

ModuleManager::~ModuleManager() {
    delete window;
    delete input;
    delete map;
    delete spriteIndex;
    delete player;
    delete raycaster;
}

bool ModuleManager::init() {
    input->addObserver(player);
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
        return false;
    }
    spriteIndex->init(RESOURCES_PATH);
    map->init(spriteIndex);
    raycaster->init(map);
    player->init(spriteIndex->get("player"), map);
    return true;
}

bool ModuleManager::pollInput() {
    input->pollEvents();
    return input->doQuit();
}

void ModuleManager::runFrame() {
    map->visibleToSeen();
    raycaster->raycastSightlines(player->getPos());
}

void ModuleManager::draw() {
    window->clear();
    map->blitMap();
    window->blit(map->getSurface(), map->getRect());
    window->blit(player->getSprite());
    window->flip();
}
