#ifndef __RAYCASTER_H_INCLUDED__
#define __RAYCASTER_H_INCLUDED__
#pragma once

#include <math.h>
#include <vector>

#include "constants.h"
#include "ivec2.h"
#include "map.h"

class RayCaster {
    IVec2 raycastOffsets[N_RAYCAST];
    Map* map;

public:
    RayCaster();
    void init(Map* _map);

    void raycastSightlines(const IVec2 origin);
    void raycast(const IVec2 start, const IVec2 end);
    bool isWallCollision(const IVec2 pos);
};

#endif