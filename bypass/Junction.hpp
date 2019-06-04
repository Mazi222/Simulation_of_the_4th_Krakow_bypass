//
// Created by fajcon on 19.05.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_JUNCTION_H
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_JUNCTION_H

#include "BypassSection.hpp"

class Junction : public BypassSection{
private:
    int startIndex;
    int endIndex;
    int maxSpeed;
    bool entry;
    bool departure;
    int probabilityOfFlow; //from 1 to 100
public:
    Junction(int startIndex, int endIndex, int maxSpeed, bool entry, bool departure, int probabilityOfFlow);

    int getStartIndex() const override;

    int getEndIndex() const override;

    int getMaxSpeed() const override;

    bool hasEntry() const override;

    bool hasDeparture() const override;

    int getProbabilityOfFlow() const override;

    void setProbabilityOfFlow(int x);
};




#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_JUNCTION_H
