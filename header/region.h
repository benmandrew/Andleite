#pragma once

#include <vector>
#include "vec2.h"

class Region;

enum TileType {
    wall, open, edge
};

struct Tile {
    TileType type;
    Region* region;

    Tile(TileType _type=TileType::wall, Region* _region=nullptr)
        : region(_region), type(_type) {
    }
};

class Region {
private:
    static int top_id;
    int id;
    AABB bounds;
public:
    Region();

    void addTile(Vec2 tilePos);
    void setBounds(Vec2 topLeft, Vec2 bottomRight);
    bool boundsCollide(
        const Region other, const bool expand=false) const;

    bool operator==(const Region other) const;
    bool operator!=(const Region other) const;
};

struct Connector {
    Vec2 pos;
    Region* left;
    Region* right;
};

class RegionGraph {
    std::vector<int> subsets;
    std::vector<Connector> connectors;

public:
    void calcMST();
    int findSubset(const int connectorIndex) const;
    void unionSubsets(const int i, const int j);
};