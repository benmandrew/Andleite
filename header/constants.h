#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__
#pragma once

#include <string>

constexpr static int SCREEN_WIDTH = 1280;
constexpr static int SCREEN_HEIGHT = 960;
constexpr static float ASPECT_RATIO = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

constexpr static int TILE_NUM_X = 45;
constexpr static int TILE_NUM_Y = (int)(TILE_NUM_X / ASPECT_RATIO);

//constexpr static int TILE_SCREEN_SIZE = SCREEN_WIDTH / TILE_NUM_X;

constexpr static int ROOM_ATTEMPT_NUM = 200;
constexpr static int ROOM_MIN_SIZE = 4;
constexpr static int ROOM_MAX_SIZE = 8;

constexpr static float OPEN_CONNECTOR_RATIO = 0.08f;

const static std::string RESOURCES_PATH = "./resources";
const static std::string HIDDEN_SPR = "hidden";
const static std::string FLOOR_SEEN_SPR = "floor_seen";
const static std::string WALL_SEEN_SPR = "wall_seen";
const static std::string FLOOR_VISIBLE_SPR = "floor_visible";
const static std::string WALL_VISIBLE_SPR = "wall_visible";

constexpr static int N_RAYCAST = 90;
constexpr static float RAYCAST_DIST = 50.0f;

enum SpriteEnum {
    HIDDEN,
    SEEN_WALL,
    VISIBLE_WALL,
    SEEN_FLOOR,
    VISIBLE_FLOOR,
    PLAYER
};

#endif