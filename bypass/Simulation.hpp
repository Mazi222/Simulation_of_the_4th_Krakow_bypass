//
// Created by mazi on 19.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP


#include <QGraphicsScene>
#include <array>
#include <memory>
#include <vector>
#include "Bypass.hpp"
#include "Vehicle.hpp"
#include "Road.hpp"
#include "Junction.hpp"


#define LEFT_LINE 1
#define RIGHT_LINE 2
#define TEMP_LINE 3

class Simulation {
public:
    Simulation(QGraphicsScene *_scene, bool direction);
    void start_simulation();
    ~Simulation() = default;

private: //temporary
    void stepWithEntry(int number_of_cell);
    void stepWithDepartue(int number_of_cell);
    void step(int number_of_cell);
    bool enterRoad(const int &number_of_cell);

public:
    void simulate_beta();
    void initializeBypass();
    void next_step();

public:
    std::vector<std::shared_ptr<Vehicle>>& get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>>& get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>>& get_cells_of_bypass_line_tmp();

private:

    bool check_change_of_line(const int &number_of_cell) const;
    void change_right(const int &number_of_cell);
    void change_left(const int &number_of_cell);

    void accelerate(const int &number_of_cell);
    void retardation(const int &number_of_cell);
    void randomized(const int &number_of_cell);

    void move(const int &number_of_cell);
    Bypass bypass;

//    void get_data();
//    void notify_observer() const;
private:
    QGraphicsScene *scene;
    int vmax=5;
    int line;
    int test = 0;
    bool direction;
    //std::vector<std::shared_ptr<Bypass>> bypasses;
    std::vector<std::shared_ptr<Vehicle>> cells_of_bypass_line_right;
    std::vector<std::shared_ptr<Vehicle>> cells_of_bypass_line_left;
    std::vector<std::shared_ptr<Vehicle>> cells_of_bypass_line_temp;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_SIMULATION_HPP
