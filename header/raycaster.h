#ifndef __RAYCASTER_H_INCLUDED__
#define __RAYCASTER_H_INCLUDED__
#pragma once

#include <math.h>
#include <vector>

#include "constants.h"
#include "vec2.h"
#include "map.h"

class RayCaster {
    Vec2 raycastOffsets[N_RAYCAST];
    Map* map;

public:
    RayCaster();
    void init(Map* _map);

    void raycastSightlines(const Vec2 origin);
    void raycast(const Vec2 start, const Vec2 end);
    bool isWallCollision(const Vec2 pos);
};

#endif