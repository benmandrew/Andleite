#include "ivec2.h"

IVec2 IVec2::operator+(const IVec2 other) const {
    return {x + other.x, y + other.y};
}

IVec2 IVec2::operator-(const IVec2 other) const {
    return {x - other.x, y - other.y};
}

IVec2 IVec2::operator*(const float other) const {
    return {x * other, y * other};
}

void IVec2::operator+=(const IVec2 other) {
    x += other.x;
    y += other.y;
}

bool IVec2::operator!=(const IVec2 other) {
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
    IVec2 newTopLeft = {
        std::min(topLeft.x, other.topLeft.x),
        std::min(topLeft.y, other.topLeft.y)};
    IVec2 newBottomRight = {
        std::max(bottomRight.x, other.bottomRight.x),
        std::max(bottomRight.y, other.bottomRight.y)};
    return AABB{newTopLeft, newBottomRight};
}