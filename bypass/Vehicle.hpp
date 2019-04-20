//
// Created by mazi on 18.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP

#include <string>

class Vehicle {
public:
    virtual void move() = 0;

    void set_speed(const double& new_speed);

    const double& get_speed() const;
    const std::string& get_destination() const;

    virtual ~Vehicle();
protected:
    double speed;
    double acceleration;
    double retardation;

    std::string destination;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
