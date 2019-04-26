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
    for(int i=0;i<cells_of_bypass_line_right.size();++i)
    {
        line=right;
        if(cells_of_bypass_line_right[i] == nullptr)
            continue;
        if(check_change_of_line(i))
            change_left(i);
        accelerate(i);
        retardation(i);
        randomized(i);
        move(i);

        line=left;
        if(cells_of_bypass_line_left[i] == nullptr)
            continue;
        if(check_change_of_line(i))
            change_right(i);
        accelerate(i);
        retardation(i);
        randomized(i);
        move(i);
    }
}
