//
// Created by fajcon on 18.05.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_ROAD_H
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_ROAD_H


#include "BypassSection.hpp"

class Road : public BypassSection{
private:
    int startIndex;
    int endIndex;
    int maxSpeed;
public:
    Road(int startIndex, int endIndex, int maxSpeed);

    int getStartIndex() const override;

    int getEndIndex() const override;

    int getMaxSpeed() const override;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_ROAD_H
