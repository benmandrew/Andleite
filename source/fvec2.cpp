#include "fvec2.h"

FVec2 FVec2::operator+(const FVec2 other) const {
    return {x + other.x, y + other.y};
}

FVec2 FVec2::operator-(const FVec2 other) const {
    return {x - other.x, y - other.y};
}

FVec2 FVec2::operator*(const float other) const {
    return {x * other, y * other};
}

void FVec2::operator+=(const FVec2 other) {
    x += other.x;
    y += other.y;
}

bool FVec2::operator!=(const FVec2 other) {
    return x != other.x || y != other.y;
}

IVec2 FVec2::toInt() {
    return {x, y};
}
