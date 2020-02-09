
#include "raycaster.h"

RayCaster::RayCaster() {
}

void RayCaster::init(Map* _map) {
    map = _map;
    float step = 2 * M_PI / N_RAYCAST;
    for (int i = 0; i < N_RAYCAST; i++) {
        raycastOffsets[i] = {
            RAYCAST_DIST * cos(i * step),
            RAYCAST_DIST * sin(i * step)};
    }
}

void RayCaster::raycastSightlines(const IVec2 origin) {
    for (int i = 0; i < N_RAYCAST; i++) {
        raycast(origin, origin + raycastOffsets[i]);
    }
}
/*
void RayCaster::raycast(const IVec2 start, const IVec2 end) {
    bool wallCollision = false;
    IVec2 delta = end - start;
    IVec2 pos = start;
    int p = 2 * delta.y - delta.x;
    while (!wallCollision && pos.x < end.x) {
        map->setTileVisibility(pos, TileVisibility::visible);
        wallCollision = isWallCollision(pos);
        if (p >= 0) {
            pos.y++;
            p = p + 2 * delta.y - 2 * delta.x;
        } else {
            p = p + 2 * delta.y;
        }
        pos.x++;
    }
}*/

inline IVec2 getDelta0(const IVec2 dim) {
    IVec2 delta = {0, 0};
    if (dim.x < 0) delta.x = -1; else if (dim.x > 1) delta.x = 1;
    if (dim.y < 0) delta.y = -1; else if (dim.y > 1) delta.y = 1;
    return delta;
}

inline IVec2 getDelta1(const IVec2 dim, const bool swapAxes) {
    IVec2 delta = {0 ,0};
    if (dim.x < 0) delta.x = -1; else if (dim.x > 1) delta.x = 1;
    if (swapAxes) {
        if (dim.y < 0) delta.y = -1; else if (dim.y > 0) delta.y = 1;
        delta.x = 0;
    }
    return delta;
}

void RayCaster::raycast(const IVec2 start, const IVec2 end) {
    IVec2 pos = start;
    const IVec2 dim = end - start;
    int longest = abs(dim.x);
    int shortest = abs(dim.y);
    bool wallCollision = false;
    bool swapAxes;
    if (swapAxes = (longest <= shortest)) {
        longest = abs(dim.y);
        shortest = abs(dim.x);
    }
    const IVec2 delta0 = getDelta0(dim);
    const IVec2 delta1 = getDelta1(dim, swapAxes);

    int numerator = longest >> 1 ;
    int i = 0;
    while (!wallCollision && i <= longest) {
        map->setTileVisibility(pos, TileVisibility::visible);
        wallCollision = isWallCollision(pos);
        numerator += shortest ;
        if (numerator >= longest) {
            numerator -= longest ;
            pos += delta0;
        } else {
            pos += delta1;
        }
        i++;
    }
}

bool RayCaster::isWallCollision(const IVec2 pos) {
    return map->getTile(pos).type == TileType::wall;
}