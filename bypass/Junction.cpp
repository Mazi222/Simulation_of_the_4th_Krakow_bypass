//
// Created by fajcon on 19.05.19.
//

#include "Junction.hpp"

Junction::Junction(int startIndex, int endIndex, int maxSpeed, bool entry, bool departure, int probabilityOfFlow) : startIndex(startIndex),
                                                                                                                    endIndex(endIndex),
                                                                                                                    maxSpeed(maxSpeed),
                                                                                                                    entry(entry),
                                                                                                                    departure(departure),
                                                                                                                    probabilityOfFlow(probabilityOfFlow){}

int Junction::getStartIndex() const {
    return startIndex;
}

int Junction::getEndIndex() const {
    return endIndex;
}

int Junction::getMaxSpeed() const {
    return maxSpeed;
}

bool Junction::hasEntry() const {
    return entry;
}

bool Junction::hasDeparture() const {
    return departure;
}

int Junction::getProbabilityOfFlow() const {
    return probabilityOfFlow;
}
