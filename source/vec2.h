#pragma once

struct Vec2 {
    int x, y;

    Vec2 operator+(const Vec2 other) const;
    Vec2 operator-(const Vec2 other) const;

    void operator+=(const Vec2 other);

    bool operator!=(const Vec2 other);
};