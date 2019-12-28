#ifndef __MODULEMANAGER_H_INCLUDED__
#define __MODULEMANAGER_H_INCLUDED__
#pragma once

#include "window.h"
#include "map.h"

struct ModuleManager {
    Window* window;
    Input* input;
    Map* map;
    Creature* player;

    ModuleManager();
    ~ModuleManager();

    bool init();

    void blitWorld();

};

#endif