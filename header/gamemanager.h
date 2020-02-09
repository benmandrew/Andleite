#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__
#pragma once

#include "observer.h"
#include "input.h"
#include "creature.h"
#include "raycaster.h"

class GameManager : Observer {
public:
    Input* input;
    Map* map;
    Creature* player;
    RayCaster* raycaster;

    std::vector<Creature*> entities;

    GameManager();
    ~GameManager();

    bool init();

    bool pollInput();
    void draw();
    void runFrame();

    void onNotify(int event);

};

#endif