
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

void GameManager::onNotify(int event) {

}
