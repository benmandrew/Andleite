#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__
#pragma once

#include "window.h"
#include "raycaster.h"

struct GameManager : Observer {
    Window* window;
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

};

#endif