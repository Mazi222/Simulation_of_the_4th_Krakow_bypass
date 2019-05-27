//
// Created by mazi on 19.04.19.
//

#include <iostream>
#include <unistd.h>
#include <random>
//#include <zconf.h>
#include "Simulation.hpp"

Simulation::Simulation() {
//    get_data();
    initializeBypass();
}

void Simulation::start_simulation() {
    for(int i=0;i<50000;++i) {
        next_step();
//        notify_observer();
    }
}

void Simulation::next_step() {
    for(int number_of_cell=cells_of_bypass_line_right.size()-1; number_of_cell>=0;--number_of_cell)
    {
        if(bypass.getPtrBypassSection(number_of_cell)->hasEntry()){
            stepWithEntry(number_of_cell);
        } else if (bypass.getPtrBypassSection(number_of_cell)->hasDeparture()){
            step(number_of_cell);
        }else {
            step(number_of_cell);
        }
    }
}

void Simulation::accelerate(const int &number_of_cell) {

    if(line==RIGHT_LINE)
    {
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        cells_of_bypass_line_right[number_of_cell]->set_speed(std::min(speed+1,vmax));
    } else if (line == LEFT_LINE)
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        cells_of_bypass_line_left[number_of_cell]->set_speed(std::min(speed + 1, vmax));
    } else if(line == TEMP_LINE){
        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        cells_of_bypass_line_temp[number_of_cell]->set_speed(std::min(speed + 1, vmax));
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
    } else if (line == LEFT_LINE)
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
    } else if(line == TEMP_LINE){

        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        for(int cell=number_of_cell+1;cell<=number_of_cell+speed;++cell)
        {
            if(cells_of_bypass_line_temp[cell] != nullptr)
            {
                speed = cell - number_of_cell - 1;
                break;
            }
        }
        if(bypass.getPtrBypassSection(number_of_cell)->getEndIndex() - number_of_cell < speed){
            speed = bypass.getPtrBypassSection(number_of_cell)->getEndIndex() - number_of_cell;
        }
        cells_of_bypass_line_temp[number_of_cell]->set_speed(speed);
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
    } else if(line == TEMP_LINE && i==2){
        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        cells_of_bypass_line_temp[number_of_cell]->set_speed(std::max(speed - 1, 0));
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
    else if (line == LEFT_LINE)
    {
        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        if (number_of_cell + speed < cells_of_bypass_line_left.size())
            cells_of_bypass_line_left[number_of_cell + speed] = cells_of_bypass_line_left[number_of_cell];
        cells_of_bypass_line_left[number_of_cell] = nullptr;
    } else if(line == TEMP_LINE){
        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        if (number_of_cell + speed < cells_of_bypass_line_temp.size())
            cells_of_bypass_line_temp[number_of_cell + speed] = cells_of_bypass_line_temp[number_of_cell];
        cells_of_bypass_line_temp[number_of_cell] = nullptr;
    }

}



/*-----------------------------alfa---------------------------------*/

//void Simulation::add_car_alfa() {
//    std::shared_ptr<Vehicle> ptr_vehicle = std::make_shared<Vehicle>();
////    auto ptr_vehicle = new Vehicle;
//    int i = std::rand()%3;
//    if(i == 1)
//        cells_of_bypass_line_right[0] = ptr_vehicle;
//    else if (i == 2)
//        cells_of_bypass_line_left[0] =  ptr_vehicle;
//}

void Simulation::simulate_alfa() {
    for (int i = 0; i < 50; ++i) {
        cells_of_bypass_line_right.push_back(nullptr);
        cells_of_bypass_line_left.push_back(nullptr);
        cells_of_bypass_line_temp.push_back(nullptr);
    }
    for(int i=0;i<50000;++i){
        sleep(1);
        next_step();
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
        for(int number_of_cell = 0; number_of_cell<=cells_of_bypass_line_temp.size()-1;++number_of_cell) {
            if(bypass.getPtrBypassSection(number_of_cell)->hasEntry() || bypass.getPtrBypassSection(number_of_cell)->hasDeparture()) {
                if (cells_of_bypass_line_temp[number_of_cell] == nullptr) {
                    std::cout << "____.";
                } else {
                    std::cout << "O(" << cells_of_bypass_line_temp[number_of_cell]->get_speed() << ").";
                }
            } else std::cout << "     ";
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
             checked_cell > number_of_cell; --checked_cell) {
            if (cells_of_bypass_line_right[checked_cell] != nullptr) {
                is_needed = true;
                break;
            }
        }
        if (!is_needed)
            return false;

        for (int checked_cell = number_of_cell; //TODO change to function check_if_line_changing_possible()
             checked_cell>=std::max(number_of_cell-vmax,0);--checked_cell){
            if (cells_of_bypass_line_left[checked_cell] != nullptr){
                if(checked_cell+std::min(cells_of_bypass_line_left[checked_cell]->get_speed()+1,vmax)
                   >=number_of_cell+std::min(cells_of_bypass_line_right[number_of_cell]->get_speed()+1,vmax)){
                    is_possible = false;
                    break;
                }
            }
        }
        return is_possible;
    }

    if(line==LEFT_LINE){
        for (int checked_cell = number_of_cell;
             checked_cell>=std::max(number_of_cell-vmax,0);--checked_cell){
            if (cells_of_bypass_line_right[checked_cell] != nullptr) {
                if (checked_cell + std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1, vmax)
                    >= number_of_cell + std::min(cells_of_bypass_line_left[number_of_cell]->get_speed()+1, vmax)) {
                        return false;
                    }
                }
            }
        for (int checked_cell = number_of_cell+vmax;
                checked_cell>=number_of_cell;--checked_cell){
            if (cells_of_bypass_line_right[checked_cell] != nullptr){
                if (checked_cell +std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1,vmax)
                        <= number_of_cell + std::min(cells_of_bypass_line_left[number_of_cell]->get_speed()+1,vmax)){
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

void Simulation::initializeBypass() { //TODO model of real bypass
    int sizeOfBypass = 100;
    bypass.addBypassSection(std::make_shared<Junction>(0, 5, 4, true, false, 100));
    bypass.addBypassSection(std::make_shared<Road>(6, 10, 5));
    bypass.addBypassSection(std::make_shared<Junction>(11, 16, 4, true, false, 100));
    bypass.addBypassSection(std::make_shared<Road>(17,sizeOfBypass, 5));
}

void Simulation::stepWithEntry(int number_of_cell) { //TODO improve random
    std::random_device rd;      //Will be used to obtain a seed for the random number engine
    std::mt19937 mt(rd());      //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dist(1, 100);

    if(cells_of_bypass_line_temp[number_of_cell] != nullptr) {
        line = TEMP_LINE;
        if (!enterRoad(number_of_cell)) {
            accelerate(number_of_cell);
            retardation(number_of_cell);
            randomized(number_of_cell);
            move(number_of_cell);
        }

    }
    if(cells_of_bypass_line_right[number_of_cell] != nullptr) {
        line=RIGHT_LINE;
        if(check_change_of_line(number_of_cell)) {
            change_left(number_of_cell);
            line=LEFT_LINE;
        }
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);

    }
    if(cells_of_bypass_line_left[number_of_cell] != nullptr) {
        line=LEFT_LINE;
        if(check_change_of_line(number_of_cell))
        {
            change_right(number_of_cell);
            line=RIGHT_LINE;
        }
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);
    }
    if(bypass.getPtrBypassSection(number_of_cell)->getStartIndex() == number_of_cell && bypass.getPtrBypassSection(number_of_cell)->getProbabilityOfFlow() >= dist(mt)){
        std::shared_ptr<Vehicle> ptr_vehicle = std::make_shared<Vehicle>();
        cells_of_bypass_line_temp[number_of_cell] = ptr_vehicle;
    }
}

void Simulation::stepWithDepartue(int number_of_cell) {

}

void Simulation::step(int number_of_cell) {
    if(cells_of_bypass_line_right[number_of_cell] != nullptr) {
        line=RIGHT_LINE;
        if(check_change_of_line(number_of_cell)) {
            change_left(number_of_cell);
            line=LEFT_LINE;
        }
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);

    }
    if(cells_of_bypass_line_left[number_of_cell] != nullptr) {
        line=LEFT_LINE;
        if(check_change_of_line(number_of_cell))
        {
            change_right(number_of_cell);
            line=RIGHT_LINE;
        }
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        move(number_of_cell);
    }
}

bool Simulation::enterRoad(const int &number_of_cell) {
    int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
    bool free = true;
    for (int i = number_of_cell+speed; i > number_of_cell-speed; --i) {
        if (cells_of_bypass_line_right[i] != nullptr){
            free = false;
        }
    }
    if(free){
        cells_of_bypass_line_right[number_of_cell] = cells_of_bypass_line_temp[number_of_cell];
        cells_of_bypass_line_temp[number_of_cell] = nullptr;
    }
    return free;
}


