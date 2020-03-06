#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__
#pragma once

#include <string>
#include <map>

constexpr static int SCREEN_WIDTH = 1280;
constexpr static int SCREEN_HEIGHT = 960;
constexpr static float ASPECT_RATIO = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

constexpr static int TILE_NUM_X = 45;
constexpr static int TILE_NUM_Y = (int)(TILE_NUM_X / ASPECT_RATIO);

constexpr static int ROOM_ATTEMPT_NUM = 200;
constexpr static int ROOM_MIN_SIZE = 4;
constexpr static int ROOM_MAX_SIZE = 8;

constexpr static float OPEN_CONNECTOR_RATIO = 0.08f;

enum SpriteEnum {
    HIDDEN,
    WALL_SEEN,
    WALL_VISIBLE,
    FLOOR_SEEN,
    FLOOR_VISIBLE,
    PLAYER
};

static std::map<std::string, SpriteEnum> spriteNameMap = {
    {"hidden", HIDDEN},
    {"wall_seen", WALL_SEEN},
    {"wall_visible", WALL_VISIBLE},
    {"floor_seen", FLOOR_SEEN},
    {"floor_visible", FLOOR_VISIBLE},
    {"player", PLAYER}
};

const static std::string RESOURCES_PATH = "./resources";
constexpr static int N_RAYCAST = 270;
constexpr static float RAYCAST_DIST = 50.0f;

#endif