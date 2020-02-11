#ifndef __FVEC2_H_INCLUDED__
#define __FVEC2_H_INCLUDED__
#pragma once

#include "ivec2.h"

class IVec2;

class FVec2 {
public:
    float x, y;

    FVec2 operator+(const FVec2 other) const;
    FVec2 operator-(const FVec2 other) const;
    FVec2 operator*(const float other) const;

    void operator+=(const FVec2 other);

    bool operator!=(const FVec2 other);
    IVec2 toInt();
};

#endif