#ifndef __REGION_H_INCLUDED__
#define __REGION_H_INCLUDED__
#pragma once

#include <vector>
#include "ivec2.h"

class Region;
class Map;

enum TileType {
    wall, open, edge
};

enum TileVisibility {
    visible, hidden, seen
};

struct Tile {
    TileType type;
    TileVisibility visibility;
    Region* region;
    bool updated;

    Tile(TileType _type=wall,
        TileVisibility _visibility=hidden,
        Region* _region=nullptr)
        : region(_region), visibility(_visibility),
        type(_type), updated(true) {
    }
};

class Region {
private:
    const int id;
    AABB bounds;
public:
    Region(int topID);

    int getID() const;
    void addTile(IVec2 tilePos);
    void setBounds(IVec2 topLeft, IVec2 bottomRight);
    bool boundsCollide(
        const Region other, const bool expand=false) const;

    bool operator==(const Region other) const;
    bool operator!=(const Region other) const;
};

struct Connector {
    IVec2 pos;
    int left;
    int right;
};

class RegionGraph {
    std::vector<int> subsets;
    std::vector<Connector> connectors;
    int nVertex;

    int findSubset(const int connectorIndex) const;
    void unionSubsets(const int i, const int j);

public:
    RegionGraph(const std::vector<Connector> _connectors, const int _nVertex);

    void reduceToMST();
    void etchConnectors(Map* map);
    void etchConnectorsWithProbability(Map* map, const float openRatio) const;
};

#endif