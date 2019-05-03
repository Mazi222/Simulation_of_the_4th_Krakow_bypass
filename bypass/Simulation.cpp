//
// Created by mazi on 19.04.19.
//

#include <iostream>
#include <unistd.h>
//#include <zconf.h>
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

        if(cells_of_bypass_line_right[number_of_cell] != nullptr) {
            line=RIGHT_LINE;
//        if(check_change_of_line(number_of_cell))
//            change_left(number_of_cell);
            accelerate(number_of_cell);
            retardation(number_of_cell);
            randomized(number_of_cell);
            move(number_of_cell);
        }
        else if(cells_of_bypass_line_left[number_of_cell] != nullptr) {
            line=LEFT_LINE;
//        if(check_change_of_line(number_of_cell))
//            change_right(number_of_cell);
            accelerate(number_of_cell);
            retardation(number_of_cell);
            randomized(number_of_cell);
            move(number_of_cell);
        }
    }
}

void Simulation::accelerate(const int &number_of_cell) {

    if(line==RIGHT_LINE)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::min(speed+1,vmax));
    } else
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        cells_of_bypass_line_left[number_of_cell]->set_speed(std::min(speed + 1, vmax));
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
    } else
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        for(int cell=number_of_cell+1;cell<=number_of_cell+speed;++cell)
        {
            if(cells_of_bypass_line_left[cell] != nullptr)
            {
                speed = cell - number_of_cell - 1;
                break;
            }
        }
        cells_of_bypass_line_left[number_of_cell]->set_speed(speed);
    }
}

void Simulation::randomized(const int &number_of_cell) {
    //srand(time(NULL));
    int i = std::rand()%3;

    if(line==RIGHT_LINE && i==0)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::max(speed - 1, 0));
    } else if (line == LEFT_LINE && i==1)
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        cells_of_bypass_line_left[number_of_cell]->set_speed(std::max(speed - 1, 0));
    }
}

void Simulation::move(const int &number_of_cell) {
    if(line == RIGHT_LINE)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        if (number_of_cell + speed < cells_of_bypass_line_right.size())
            cells_of_bypass_line_right[number_of_cell + speed] = cells_of_bypass_line_right[number_of_cell];
        cells_of_bypass_line_right[number_of_cell] = nullptr;
    }
    else
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        if (number_of_cell + speed < cells_of_bypass_line_left.size())
            cells_of_bypass_line_left[number_of_cell + speed] = cells_of_bypass_line_left[number_of_cell];
        cells_of_bypass_line_left[number_of_cell] = nullptr;
    }

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
                std::cout << "____.";
            } else
                std::cout << "O("<<cells_of_bypass_line_left[number_of_cell]->get_speed()<<").";
        }
        std::cout << std::endl;
        for(int number_of_cell = 0; number_of_cell<=cells_of_bypass_line_right.size()-1;++number_of_cell) {
            if (cells_of_bypass_line_right[number_of_cell] == nullptr){
                std::cout << "____.";
            } else
                std::cout << "O("<<cells_of_bypass_line_right[number_of_cell]->get_speed()<<").";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

bool Simulation::check_change_of_line(const int &number_of_cell) const {
    if(line==RIGHT_LINE) {
        bool is_needed = false;
        bool is_possible = true;
        for (int checked_cell = //TODO change to function check_if_line_changing_needed()
                number_of_cell + std::min(cells_of_bypass_line_right[number_of_cell]->get_speed() + 1, vmax);
             checked_cell >= number_of_cell; --checked_cell) {
            if (cells_of_bypass_line_right[checked_cell] != nullptr) {
            is_needed = true;
            break;
            }
        }
        if (!is_needed)
            return false;
        for (int checked_cell = number_of_cell; //TODO change to function check_if_line_changing_possible()
             checked_cell>=number_of_cell-vmax;--checked_cell){
            if (cells_of_bypass_line_left[checked_cell] != nullptr){
                if(checked_cell+std::min(cells_of_bypass_line_left[checked_cell]->get_speed()+1,vmax)
                   >=number_of_cell+std::max(cells_of_bypass_line_right[checked_cell]->get_speed(),vmax)){
                    is_possible = false;
                    break;
                }
            }
        }
        return is_possible;
    }

    if(line==LEFT_LINE){
        for (int checked_cell = number_of_cell;
             checked_cell>=number_of_cell-vmax;--checked_cell){
            if (cells_of_bypass_line_right[checked_cell] != nullptr) {
                if (checked_cell + std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1, vmax)
                    >= number_of_cell + std::min(cells_of_bypass_line_left[checked_cell]->get_speed()+1, vmax)) {
                        return false;
                    }
                }
            }
        for (int checked_cell = number_of_cell+vmax;
                checked_cell>=number_of_cell;--checked_cell){
            if (cells_of_bypass_line_right[checked_cell] != nullptr){
                if (checked_cell + std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1,vmax)
                        <= number_of_cell+std::min(cells_of_bypass_line_left[checked_cell]->get_speed()+1,vmax)){
                    return false;
                }
            }
        }
        return true;
    }
}

void Simulation::change_right(const int &number_of_cell) {
    cells_of_bypass_line_right[number_of_cell] = cells_of_bypass_line_left[number_of_cell];
    cells_of_bypass_line_left[number_of_cell] = nullptr;
}

void Simulation::change_left(const int &number_of_cell) {
    cells_of_bypass_line_left[number_of_cell] = cells_of_bypass_line_right[number_of_cell];
    cells_of_bypass_line_right[number_of_cell] = nullptr;
}


