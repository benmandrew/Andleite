#ifndef __IVEC2_H_INCLUDED__
#define __IVEC2_H_INCLUDED__
#pragma once

#include <algorithm>
#include "fvec2.h"

class FVec2;

class IVec2 {
public:
    int x, y;

    IVec2 operator+(const IVec2 other) const;
    IVec2 operator-(const IVec2 other) const;
    IVec2 operator*(const float other) const;

    void operator+=(const IVec2 other);

    bool operator!=(const IVec2 other);

    FVec2 toFloat();
};

struct AABB {
    IVec2 topLeft, bottomRight;

    bool collidesWith(
        const AABB other, const bool expand=false) const;

    AABB getUnion(const AABB other) const;
};

#endif