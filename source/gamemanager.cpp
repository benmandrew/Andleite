
#include "gamemanager.h"

GameManager::GameManager() {
    input = new Input();
    map = new Map();
    player = new Entity();
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
    map->init();
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

bool GameManager::isUpdated() {
    return updated;
}

void GameManager::setUpdated(bool newUpdated) {
    updated = newUpdated;
}

void GameManager::onNotify(int event) {
    switch (event) {
        case InputEvent::KEY_UP:
        case InputEvent::KEY_DOWN:
        case InputEvent::KEY_LEFT:
        case InputEvent::KEY_RIGHT:
            updated = true;
            break;
    }
}
