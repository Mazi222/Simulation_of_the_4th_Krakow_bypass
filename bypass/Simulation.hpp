//
// Created by mazi on 19.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP


#include <array>
#include <memory>
#include "Bypass.hpp"

class Simulation {
public:
    Simulation() = delete;
    explicit Simulation(std::array<std::unique_ptr<Bypass>,100> bypasses_arg);
    void start_simulation();
    ~Simulation() = default;
private:
    void next_step();
    void notify_observer() const;
private:
    std::array<std::unique_ptr<Bypass>,100> bypasses;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
