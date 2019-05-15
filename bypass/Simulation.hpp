//
// Created by mazi on 19.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP


#include <array>
#include <memory>
#include <vector>
#include "Bypass.hpp"
#include "Vehicle.hpp"

#define LEFT_LINE false
#define RIGHT_LINE true

class Simulation {
public:
    Simulation();
    void start_simulation();
    ~Simulation() = default;

private: //temporary
    void add_car_alfa();

public:
    void simulate_alfa();

private:

    bool check_change_of_line(const int &number_of_cell) const;
    void change_right(const int &number_of_cell);
    void change_left(const int &number_of_cell);

    void accelerate(const int &number_of_cell);
    void retardation(const int &number_of_cell);
    void randomized(const int &number_of_cell);

    void move(const int &number_of_cell);


//    void get_data();
    void next_step();
//    void notify_observer() const;
private:
    int vmax=5;
    bool line;
    std::vector<std::shared_ptr<Bypass>> bypasses;
    std::vector<std::shared_ptr<Vehicle>> cells_of_bypass_line_right;
    std::vector<std::shared_ptr<Vehicle>> cells_of_bypass_line_left;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
