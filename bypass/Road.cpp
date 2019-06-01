//
// Created by fajcon on 18.05.19.
//

#include "Road.hpp"

int Road::getStartIndex() const {
    return startIndex;
}

int Road::getEndIndex() const {
    return endIndex;
}

int Road::getMaxSpeed() const {
    return maxSpeed;
}

Road::Road(int startIndex, int endIndex, int maxSpeed) : startIndex(startIndex), endIndex(endIndex),
                                                         maxSpeed(maxSpeed) {}


