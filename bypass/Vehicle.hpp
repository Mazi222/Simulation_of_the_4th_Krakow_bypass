//
// Created by mazi on 18.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP

#include <string>

class Vehicle {
public:
    Vehicle(){speed=1;}
    void set_speed(const int& new_speed)
    {
        speed=new_speed;
    }
    const int& get_speed() const
    {
        return speed;
    }

    const std::string& get_destination() const;

    virtual ~Vehicle() = default;
protected:
    int speed;
    std::string destination;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
