//
// Created by mazi on 19.04.19.
//

#include "Simulation.hpp"

Simulation::Simulation() {
    get_data();
}

void Simulation::start_simulation() {
    next_step();
    notify_observer();
}

void Simulation::next_step() { //TODO zmniejszenie ilosci kodu
    for(int number_of_cell=0;number_of_cell<cells_of_bypass_line_right.size();++number_of_cell)
    {
        line=RIGHT_LINE;
        if(cells_of_bypass_line_right[number_of_cell] == nullptr)
            continue;
        if(check_change_of_line(number_of_cell))
            change_left(number_of_cell);
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);

        line=LEFT_LINE;
        if(cells_of_bypass_line_left[number_of_cell] == nullptr)
            continue;
        if(check_change_of_line(number_of_cell))
            change_right(number_of_cell);
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);
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
    srand(time(NULL));
    int i = std::rand()%3;
    int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
    if(line==RIGHT_LINE && i==0)
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::max(speed-1,0));
}
