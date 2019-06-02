//
// Created by mazi on 19.04.19.
//

#include <iostream>
#include "Bypass.hpp"
#include "Road.hpp"


std::shared_ptr<BypassSection> Bypass::getPtrBypassSection(const int index) {
    for (auto &bypassSection : bypassSections) {
        if(bypassSection->getStartIndex() <= index && bypassSection->getEndIndex() >= index){
            return bypassSection;
        }
    }
    return bypassSections[0];
}

void Bypass::addBypassSection(std::shared_ptr<BypassSection> sectionPtr) {
    bypassSections.push_back(sectionPtr);
}

const std::vector<std::shared_ptr<BypassSection>> &Bypass::getBypassSections() const {
    return bypassSections;
}
