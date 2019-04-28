//
// Created by mazi on 19.04.19.
//

#include <iostream>
#include <zconf.h>
#include "Simulation.hpp"

Simulation::Simulation() {
//    get_data();
}

void Simulation::start_simulation() {
    for(int i=0;i<50000;++i) {
        next_step();
//        notify_observer();
    }
}

void Simulation::next_step() { //TODO zmniejszenie ilosci kodu

    for(int number_of_cell=cells_of_bypass_line_right.size()-1;number_of_cell>=0;--number_of_cell)
    {
        line=RIGHT_LINE;
        if(cells_of_bypass_line_right[number_of_cell] == nullptr)
            continue;
//        if(check_change_of_line(number_of_cell))
//            change_left(number_of_cell);
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);

//        line=LEFT_LINE;
//        if(cells_of_bypass_line_left[number_of_cell] == nullptr)
//            continue;
////        if(check_change_of_line(number_of_cell))
////            change_right(number_of_cell);
//        accelerate(number_of_cell);
//        retardation(number_of_cell);
//        randomized(number_of_cell);
//        move(number_of_cell);
    }
}

void Simulation::accelerate(const int &number_of_cell) {

    if(line==RIGHT_LINE)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::min(speed+1,vmax));
    }
}

void Simulation::retardation(const int &number_of_cell) {
    if(line==RIGHT_LINE)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        for(int cell=number_of_cell+1;cell<=number_of_cell+speed;++cell)
        {
            if(cells_of_bypass_line_right[cell] != nullptr)
            {
                speed = cell - number_of_cell - 1;
                break;
            }
        }
        cells_of_bypass_line_right[number_of_cell]->set_speed(speed);
    }
}

void Simulation::randomized(const int &number_of_cell) {
    //srand(time(NULL));
    int i = std::rand()%3;
    int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
    if(line==RIGHT_LINE && i==0)
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::max(speed-1,0));

}

void Simulation::move(const int &number_of_cell) {
    int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
    if(number_of_cell+speed<cells_of_bypass_line_right.size())
        cells_of_bypass_line_right[number_of_cell + speed] = cells_of_bypass_line_right[number_of_cell];
    cells_of_bypass_line_right[number_of_cell] = nullptr;
}

/*-----------------------------alfa---------------------------------*/
void Simulation::add_car_alfa() {
    std::shared_ptr<Vehicle> ptr_vehicle = std::make_shared<Vehicle>();
//    auto ptr_vehicle = new Vehicle;
    int i = std::rand()%3;
    if(i == 1)
        cells_of_bypass_line_right[0] = ptr_vehicle;
    else if (i == 2)
        cells_of_bypass_line_left[0] =  ptr_vehicle;
}

void Simulation::simulate_alfa() {
    for (int i = 0; i < 50; ++i) {
        cells_of_bypass_line_right.push_back(nullptr);
        cells_of_bypass_line_left.push_back(nullptr);
    }
    for(int i=0;i<50000;++i){
        sleep(1);
        next_step();
        add_car_alfa();
        for(int number_of_cell = 0; number_of_cell<=cells_of_bypass_line_left.size()-1;++number_of_cell) {
            if (cells_of_bypass_line_left[number_of_cell] == nullptr){
                std::cout << "_";
            } else
                std::cout << "O";
        }
        std::cout << std::endl;
        for(int number_of_cell = 0; number_of_cell<=cells_of_bypass_line_right.size()-1;++number_of_cell) {
            if (cells_of_bypass_line_right[number_of_cell] == nullptr){
                std::cout << "_";
            } else
                std::cout << "O";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
