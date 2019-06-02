//
// Created by mazi on 19.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASS_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASS_HPP

#include "BypassSection.hpp"
#include <vector>
#include <memory>
class Bypass {
private:
    std::vector<std::shared_ptr<BypassSection>> bypassSections;
public:
    const std::vector<std::shared_ptr<BypassSection>> &getBypassSections() const;

public:
    std::shared_ptr<BypassSection> getPtrBypassSection(const int index);
    void addBypassSection(std::shared_ptr<BypassSection> sectionPtr);
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASS_HPP
