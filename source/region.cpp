
#include "region.h"

int Region::top_id = 0;

Region::Region(){
    id = top_id;
    top_id++;
}

void Region::addTile(Vec2 tilePos) {
    AABB single = {tilePos, tilePos};
    // Create an AABB of a single tile so that I
    // don't have to rewrite the intersection code
    if (bounds.collidesWith(single)) {
        return;
    }
    bounds = bounds.getUnion(single);
}

void Region::setBounds(Vec2 topLeft, Vec2 bottomRight) {
    bounds = {topLeft, bottomRight};
}

bool Region::boundsCollide(
        const Region other, const bool expand) const {
    return bounds.collidesWith(other.bounds, expand);
}

bool Region::operator==(const Region other) const {
    return id == other.id;
}

bool Region::operator!=(const Region other) const {
    return id != other.id;
}