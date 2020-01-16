
#include "gamemanager.h"

GameManager::GameManager() {
    input = new Input();
    map = new Map();
    player = new Creature();
    entities.push_back(player);
    raycaster = new RayCaster();
}

GameManager::~GameManager() {
    delete input;
    delete map;
    delete player;
    delete raycaster;
}

bool GameManager::init() {
    input->addObserver(this);
    input->addObserver(player);
    if (!window->init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
        return false;
    }
    spriteIndex->init(RESOURCES_PATH);
    map->init(spriteIndex);
    raycaster->init(map);
    player->init(SpriteEnum::PLAYER, map);
    return true;
}

bool GameManager::pollInput() {
    input->pollEvents();
    return input->doQuit();
}

void GameManager::runFrame() {
    map->visibleToSeen();
    raycaster->raycastSightlines(player->getPos());
}
