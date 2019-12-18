#include "vec2.h"

Vec2 Vec2::operator+(const Vec2 other) const {
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2 other) const {
    return {x - other.x, y - other.y};
}

void Vec2::operator+=(const Vec2 other) {
    x += other.x;
    y += other.y;
}

bool Vec2::operator!=(const Vec2 other) {
    return x != other.x || y != other.y;
}