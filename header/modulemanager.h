#ifndef __MODULEMANAGER_H_INCLUDED__
#define __MODULEMANAGER_H_INCLUDED__
#pragma once

#include "window.h"
#include "raycaster.h"

struct ModuleManager {
    Window* window;
    Input* input;
    Map* map;
    SpriteIndex* spriteIndex;
    Creature* player;
    RayCaster* raycaster;

    ModuleManager();
    ~ModuleManager();

    bool init();

    bool pollInput();
    void draw();
    void runFrame();

};

#endif