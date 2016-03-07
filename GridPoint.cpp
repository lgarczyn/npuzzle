//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "GridPoint.hpp"

GridPoint::GridPoint() : x(0), y(0) { }

GridPoint::GridPoint(int x, int y) : x(x), y(y) { }

GridPoint GridPoint::GetPointFromIndex(int index, int width) {
    return GridPoint(index % width, index / width);
}

int GridPoint::GetIndexFromPoint(const GridPoint &point, int width) {
    return point.y * width + point.x;
}

int GridPoint::ManDistance(const GridPoint &value) {
    return (abs(x - value.x) + abs(y - value.y));
}

int GridPoint::ManDistance(const GridPoint &a, const GridPoint &b) {
    return (abs(a.x - b.x) + abs(a.y - b.y));
}

int GridPoint::ManDistance(int a, int b, int width) {
    return (abs(a % width - b % width) + abs(a / width - b / width));
}

