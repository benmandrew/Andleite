
#include "map.h"
#include "region.h"

Region::Region(int topID)
        : id(topID) {
}

int Region::getID() const {
    return id;
}

void Region::addTile(IVec2 tilePos) {
    AABB single = {tilePos, tilePos};
    // Create an AABB of a single tile so that I
    // don't have to rewrite the intersection code
    if (bounds.collidesWith(single)) {
        return;
    }
    bounds = bounds.getUnion(single);
}

void Region::setBounds(IVec2 topLeft, IVec2 bottomRight) {
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


RegionGraph::RegionGraph(std::vector<Connector> _connectors, const int _nVertex) 
        : connectors(_connectors), nVertex(_nVertex) {
    subsets = std::vector<int>(nVertex, -1);
}

int RegionGraph::findSubset(const int connectorIndex) const {
    if (subsets[connectorIndex] == -1) {
        return connectorIndex;
    }
    return findSubset(subsets[connectorIndex]);
}

void RegionGraph::unionSubsets(const int i, const int j) {
    const int iSet = findSubset(i);
    const int jSet = findSubset(j);
    if (iSet != jSet) {
        subsets[iSet] = jSet;
    }
}

// Kruskal's Minimum Spanning Tree Algorithm
void RegionGraph::reduceToMST() {
    std::vector<Connector> result;
    int nEdge = connectors.size();
    int e = 0;
    int i = 0;
    while (e < nVertex - 1 && i < nEdge) {
        Connector nextConnector = connectors[i++];
        int x = findSubset(nextConnector.left);
        int y = findSubset(nextConnector.right);
        if (x != y) {
            result.push_back(nextConnector);
            unionSubsets(x, y);
            e++;
        }
    }
    connectors = result;
}

void RegionGraph::etchConnectors(Map* map) {
    for (Connector connector : connectors) {
        map->setTileType(connector.pos, TileType::open);
    }
}

inline float randProbability() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void RegionGraph::etchConnectorsWithProbability(
    Map* map, const float openRatio) const {
    for (Connector connector : connectors) {
        if (randProbability() <= openRatio){
            map->setTileType(connector.pos, TileType::open);
        }
    }
}