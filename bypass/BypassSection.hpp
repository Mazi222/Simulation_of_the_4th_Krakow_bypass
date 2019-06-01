//
// Created by fajcon on 18.05.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASSSECTION_H
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASSSECTION_H


class BypassSection {
public:
    virtual int getStartIndex() const;

    virtual int getEndIndex() const;

    virtual int getMaxSpeed() const;

    virtual bool hasEntry() const;

    virtual bool hasDeparture() const;

    virtual int getProbabilityOfFlow() const;

};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_BYPASSSECTION_H
