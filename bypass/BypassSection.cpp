//
// Created by fajcon on 18.05.19.
//

#include "BypassSection.hpp"


int BypassSection::getStartIndex() const {
    return 0;
}

int BypassSection::getEndIndex() const {
    return 0;
}

int BypassSection::getMaxSpeed() const {
    return 0;
}

bool BypassSection::hasEntry() const {
    return false;
}

bool BypassSection::hasDeparture() const {
    return false;
}

int BypassSection::getProbabilityOfFlow() const {
    return 0;
}
