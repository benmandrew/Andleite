#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__
#pragma once

#include "observer.h"
#include "input.h"
#include "entity.h"
#include "raycaster.h"

class GameManager : Observer {
private:
    bool updated = true;
public:
    Input* input;
    Map* map;
    Entity* player;
    RayCaster* raycaster;

    std::vector<Entity*> entities;

    GameManager();
    ~GameManager();

    bool init();

    bool pollInput();
    void runFrame();

    bool isUpdated();
    void setUpdated(bool newUpdated);

    void onNotify(int event);

};

#endif