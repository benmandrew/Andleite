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

bool AABB::collidesWith(const AABB other, const bool expand) const {
    const int buffer = expand ? 1 : 0;
    return (
        topLeft.x - buffer < other.bottomRight.x &&
        bottomRight.x + buffer > other.topLeft.x &&
        topLeft.y - buffer < other.bottomRight.y &&
        bottomRight.y + buffer > other.topLeft.y);
}


AABB AABB::getUnion(const AABB other) const {
    Vec2 newTopLeft = {
        std::min(topLeft.x, other.topLeft.x),
        std::min(topLeft.y, other.topLeft.y)};
    Vec2 newBottomRight = {
        std::max(bottomRight.x, other.bottomRight.x),
        std::max(bottomRight.y, other.bottomRight.y)};
    return AABB{newTopLeft, newBottomRight};
}