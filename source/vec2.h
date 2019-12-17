#pragma once

struct Vec2 {
    int x, y;

    Vec2 operator+(Vec2 other);
    Vec2 operator-(Vec2 other);

    void operator+=(Vec2 other);

    bool operator!=(Vec2 other);
};