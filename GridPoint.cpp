//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "GridPoint.h"

GridPoint::GridPoint() : x(0), y(0) { }

GridPoint::GridPoint(int x, int y) : x(x), y(y) { }

GridPoint GridPoint::GetPointFromIndex(int index, int width) {
    return GridPoint(index % width, index / width);
}

int GridPoint::GetIndexFromPoint(const GridPoint &point, int width) {
    return point.y * width + point.x;
}

int GridPoint::ManDistance(const GridPoint &value) {
    return (std::abs(x - value.x) + std::abs(y - value.y));
}

