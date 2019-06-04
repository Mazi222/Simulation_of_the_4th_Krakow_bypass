//
// Created by mazi on 19.04.19.
//

#include <iostream>
#include <unistd.h>
#include <random>
#include "Simulation.hpp"

Simulation::Simulation(QGraphicsScene *_scene,bool _direction) {
    scene=_scene;
    direction=_direction;
    initializeBypass();
}

void Simulation::start_simulation() {
    for(int i=0;i<50000;++i) {
        next_step();
    }
}

void Simulation::next_step() {

    for(int number_of_cell=cells_of_bypass_line_right.size()-1; number_of_cell>=0;--number_of_cell)
    {
        vmax = bypass.getPtrBypassSection(number_of_cell)->getMaxSpeed();
        if (bypass.getPtrBypassSection(number_of_cell)->hasEntry()) {
            stepWithEntry(number_of_cell);
        } else if (bypass.getPtrBypassSection(number_of_cell)->hasDeparture()) {
            stepWithDepartue(number_of_cell);
        } else {
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
        bool test = false;
        int speed = cells_of_bypass_line_right[number_of_cell]->get_speed();
        for(int cell=number_of_cell+1;(cell<=number_of_cell+speed && cell < cells_of_bypass_line_right.size());++cell)
        {
            if(cells_of_bypass_line_right[cell] != nullptr)
            {
                speed = cell - number_of_cell - 1;
                test = true;
                break;
            }
        }
        if(number_of_cell+speed >= cells_of_bypass_line_right.size() && !test) {
            for (int cell = 0; cell <= number_of_cell + speed - cells_of_bypass_line_right.size(); ++cell) {
                if(cells_of_bypass_line_right[cell] != nullptr) {
                    speed = (cells_of_bypass_line_right.size()-1 - number_of_cell) + cell;
                    break;
                }
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
        if(number_of_cell+speed >= cells_of_bypass_line_left.size() && test == false) {
            for (int cell = 0; cell <= number_of_cell + speed - cells_of_bypass_line_left.size(); ++cell) {
                if(cells_of_bypass_line_left[cell] != nullptr) {
                    speed = (cells_of_bypass_line_left.size()-1 - number_of_cell) + cell;
                    break;
                }
            }
        }
        cells_of_bypass_line_left[number_of_cell]->set_speed(speed);
    } else if(line == TEMP_LINE){

        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        for(int cell=number_of_cell+1;(cell<=number_of_cell+speed && cell <= bypass.getPtrBypassSection(number_of_cell)->getEndIndex());++cell)
        {
            if(cells_of_bypass_line_temp[cell] != nullptr)
            {
                speed = cell - number_of_cell - 1;
                break;
            }
        }
        if(bypass.getPtrBypassSection(number_of_cell)->getEndIndex() - number_of_cell < speed && bypass.getPtrBypassSection(number_of_cell)->hasEntry()){
            speed = bypass.getPtrBypassSection(number_of_cell)->getEndIndex() - number_of_cell;
        }
        cells_of_bypass_line_temp[number_of_cell]->set_speed(speed);
    }

}

void Simulation::randomized(const int &number_of_cell) {
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
        if(speed > 0) {
            cells_of_bypass_line_right[(number_of_cell + speed) %
                                       cells_of_bypass_line_right.size()] = cells_of_bypass_line_right[number_of_cell];
            cells_of_bypass_line_right[number_of_cell] = nullptr;
        }
    }
    else if (line == LEFT_LINE)
    {

        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        if(speed > 0) {
            cells_of_bypass_line_left[(number_of_cell + speed) %
                                      cells_of_bypass_line_left.size()] = cells_of_bypass_line_left[number_of_cell];
            cells_of_bypass_line_left[number_of_cell] = nullptr;
        }

    } else if(line == TEMP_LINE){
        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        if(speed > 0) {
            if (number_of_cell + speed < cells_of_bypass_line_temp.size())
                cells_of_bypass_line_temp[number_of_cell + speed] = cells_of_bypass_line_temp[number_of_cell];
            cells_of_bypass_line_temp[number_of_cell] = nullptr;
        }
    }

}


bool Simulation::check_change_of_line(const int &number_of_cell) const {
    if(line==RIGHT_LINE) {
        if(cells_of_bypass_line_left[number_of_cell] != nullptr)
            return false;
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
        if(cells_of_bypass_line_right[number_of_cell] != nullptr)
            return false;
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

void Simulation::initializeBypass() {
    for (int i = 0; i < 5105; ++i) {
        cells_of_bypass_line_right.push_back(nullptr);
        cells_of_bypass_line_left.push_back(nullptr);
        cells_of_bypass_line_temp.push_back(nullptr);
    }
    if(direction)
    {
        bypass.addBypassSection(std::make_shared<Road>(0, 320, 4)); //Nowa Huta po wjeździe
        bypass.addBypassSection(std::make_shared<Junction>(321, 330, 4, false, true, 10));//zjazd S7 - Trakt papieski
        bypass.addBypassSection(std::make_shared<Road>(331, 405, 4));
        bypass.addBypassSection(std::make_shared<Junction>(406, 451, 4, true, false, 100));//wjazd Trakt papieski - S7
        bypass.addBypassSection(std::make_shared<Road>(452, 598, 4));//
        bypass.addBypassSection(std::make_shared<Junction>(599, 659, 4, false, true, 10));//zjazd S7 - A4 na Tarnów
        bypass.addBypassSection(std::make_shared<Road>(660, 787, 3));
        bypass.addBypassSection(std::make_shared<Junction>(788, 860, 5, true, false, 100)); //wjazd S7 - A4 na Katowice///
        bypass.addBypassSection(std::make_shared<Road>(861,1061, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1062, 1129, 5, false, true, 10));//zjazd A4 - 94//
        bypass.addBypassSection(std::make_shared<Road>(1130,1250, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1251, 1371, 5, true, false, 100)); //wjazd 94 - A4 na Katowice//
        bypass.addBypassSection(std::make_shared<Road>(1372,1892, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1893, 1919, 5, false, true, 10));//zjazd A4 - Zbigniewa Herberta//
        bypass.addBypassSection(std::make_shared<Road>(1920,1973, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1974, 1999, 5, true, false, 100)); //wjazd Zbigniewa Herberta - A4 na Katowice//
        bypass.addBypassSection(std::make_shared<Road>(2000,2240, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2241, 2267, 5, false, true, 10));//zjazd A4 - Zakopianka
        bypass.addBypassSection(std::make_shared<Road>(2268,2315, 5));//
        bypass.addBypassSection(std::make_shared<Junction>(2316, 2336, 5, true, false, 100)); //wjazd Zakopianka - A4 na Katowice//
        bypass.addBypassSection(std::make_shared<Road>(2337,2790, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2791, 2814, 5, false, true, 10));//zjazd A4 - 44
        bypass.addBypassSection(std::make_shared<Road>(2815,2888, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2889, 2918, 5, true, false, 100)); //wjazd 44 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(2919,3252, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3253, 3281, 5, false, true, 10));//zjazd A4 - Tyniecka
        bypass.addBypassSection(std::make_shared<Road>(3282,3322, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3323, 3352, 5, true, false, 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(3353,3499, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3500, 3560, 5, false, true, 10));//zjazd A4 - 780
        bypass.addBypassSection(std::make_shared<Road>(3561,3590, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3591, 3624, 5, true, false, 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(3625,4132, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4133, 4167, 5, false, true, 10));//zjazd A4 - Balice II
        bypass.addBypassSection(std::make_shared<Road>(4168,4221, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4222, 4302, 5, true, false, 100)); //wjazd Balice - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Junction>(4303, 4343, 5, false, true, 10));//zjazd S52 - A4
        bypass.addBypassSection(std::make_shared<Road>(4344,4404, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4405, 4437, 4, true, false, 100)); //wjazd A4 - S52
        bypass.addBypassSection(std::make_shared<Road>(4438,4758, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4759, 4792, 4, false, true, 10));//zjazd 94 - 7
        bypass.addBypassSection(std::make_shared<Junction>(4793, 4832, 4, false, true, 10));//zjazd 94 - 79
        bypass.addBypassSection(std::make_shared<Road>(4833,4861, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4862, 4878, 4, true, false, 100)); //wjazd 79 - 94
        bypass.addBypassSection(std::make_shared<Junction>(4879, 4895, 4, false, true, 10));//zjazd 94
        bypass.addBypassSection(std::make_shared<Road>(4896,4920, 4));
        bypass.addBypassSection(std::make_shared<Junction>(4921, 4945, 4, true, false, 100)); //wjazd  - 94
        bypass.addBypassSection(std::make_shared<Road>(4946,5079, 4));
        bypass.addBypassSection(std::make_shared<Junction>(5080, 5105, 4, false, true, 10));//zjazd 94
    }
    else {
        bypass.addBypassSection(std::make_shared<Junction>(0, 24, 4, false, true, 10));//zjazd 94
        bypass.addBypassSection(std::make_shared<Road>(25,158, 4));
        bypass.addBypassSection(std::make_shared<Junction>(159, 183, 4, true, false, 100)); //wjazd  - 94
        bypass.addBypassSection(std::make_shared<Road>(184,208, 4));
        bypass.addBypassSection(std::make_shared<Junction>(209, 225, 4, false, true, 10));//zjazd 94
        bypass.addBypassSection(std::make_shared<Junction>(226, 242, 4, true, false, 100)); //wjazd 79 - 94
        bypass.addBypassSection(std::make_shared<Road>(243,271, 5));
        bypass.addBypassSection(std::make_shared<Junction>(272, 311, 4, false, true, 10));//zjazd 94 - 79
        bypass.addBypassSection(std::make_shared<Junction>(312, 345, 4, false, true, 10));//zjazd 94 - 7
        bypass.addBypassSection(std::make_shared<Road>(346,666, 5));
        bypass.addBypassSection(std::make_shared<Junction>(667, 699, 4, true, false, 100)); //wjazd A4 - S52
        bypass.addBypassSection(std::make_shared<Road>(700,760, 5));
        bypass.addBypassSection(std::make_shared<Junction>(761, 801, 5, false, true, 10));//zjazd S52 - A4
        bypass.addBypassSection(std::make_shared<Junction>(802, 882, 5, true, false, 100)); //wjazd Balice - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(883,936, 5));
        bypass.addBypassSection(std::make_shared<Junction>(937, 972, 5, false, true, 10));//zjazd A4 - Balice II
        bypass.addBypassSection(std::make_shared<Road>(973,1480, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1481, 1514, 5, true, false, 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(1515,1544, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1545, 1605, 5, false, true, 10));//zjazd A4 - 780
        bypass.addBypassSection(std::make_shared<Road>(1606,1752, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1753, 1782, 5, true, false, 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(1783,1823, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1824, 1852, 5, false, true, 10));//zjazd A4 - Tyniecka
        bypass.addBypassSection(std::make_shared<Road>(1853, 2186, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2187, 2216, 5, true, false, 100)); //wjazd 44 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(2217,2290, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2291, 2314, 5, false, true, 10));//zjazd A4 - 44
        bypass.addBypassSection(std::make_shared<Road>(2315, 2768, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2769, 2789, 5, true, false, 100)); //wjazd Zakopianka - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(2790, 2837, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2838, 2864, 5, false, true, 10));//zjazd A4 - Zakopianka
        bypass.addBypassSection(std::make_shared<Road>(2865, 3105, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3106, 3131, 5, true, false, 100)); //wjazd Zbigniewa Herberta - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(3132, 3185, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3186, 3212, 5, false, true, 10));//zjazd A4 - Zbigniewa Herberta
        bypass.addBypassSection(std::make_shared<Road>(3213, 3733, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3734, 3854, 5, true, false, 100)); //wjazd 94 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(3855, 3975, 5));
        bypass.addBypassSection(std::make_shared<Junction>(3976, 4043, 5, false, true, 10));//zjazd A4 - 94
        bypass.addBypassSection(std::make_shared<Road>(4044,4244, 5));
        bypass.addBypassSection(std::make_shared<Junction>(4245, 4318, 5, true, false, 100)); //wjazd S7 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(4319, 4445, 3));
        bypass.addBypassSection(std::make_shared<Junction>(4446, 4506, 4, false, true, 10));//zjazd S7 - A4 na Tarnów
        bypass.addBypassSection(std::make_shared<Road>(4507, 4653, 4));
        bypass.addBypassSection(std::make_shared<Junction>(4654, 4700, 4, true, false, 100));//wjazd Trakt papieski - S7
        bypass.addBypassSection(std::make_shared<Road>(4701, 4774, 4));
        bypass.addBypassSection(std::make_shared<Junction>(4775, 4784, 4, false, true, 10));//zjazd S7 - Trakt papieski
        bypass.addBypassSection(std::make_shared<Road>(4785, 5105, 4)); //Nowa Huta po wjedzie
    }
}

void Simulation::stepWithEntry(int number_of_cell) {
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


    if(bypass.getPtrBypassSection(number_of_cell)->getStartIndex() == number_of_cell && bypass.getPtrBypassSection(number_of_cell)->getProbabilityOfFlow() >= dist(mt)){
        std::shared_ptr<Vehicle> ptr_vehicle = std::make_shared<Vehicle>(number_of_cell,direction);
        cells_of_bypass_line_temp[number_of_cell] = ptr_vehicle;
        scene->addItem(ptr_vehicle.get());
    }
}

void Simulation::stepWithDepartue(int number_of_cell) {

    std::random_device rd;      //Will be used to obtain a seed for the random number engine
    std::mt19937 mt(rd());      //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dist(1, 100);

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

    if(cells_of_bypass_line_right[number_of_cell] != nullptr) {
        line=RIGHT_LINE;
        if(cells_of_bypass_line_temp[number_of_cell] == nullptr && bypass.getPtrBypassSection(number_of_cell)->getStartIndex() <= number_of_cell && bypass.getPtrBypassSection(number_of_cell)->getEndIndex() >= number_of_cell && bypass.getPtrBypassSection(number_of_cell)->getProbabilityOfFlow() >= dist(mt)){
            cells_of_bypass_line_temp[number_of_cell] = cells_of_bypass_line_right[number_of_cell];
            cells_of_bypass_line_right[number_of_cell] = nullptr;
        } else {
            if (check_change_of_line(number_of_cell)) {
                change_left(number_of_cell);
                line = LEFT_LINE;
            }
            accelerate(number_of_cell);
            retardation(number_of_cell);
            randomized(number_of_cell);
            move(number_of_cell);
        }
    }
    if(cells_of_bypass_line_temp[number_of_cell] != nullptr) {
        line = TEMP_LINE;
        accelerate(number_of_cell);
        retardation(number_of_cell);
        randomized(number_of_cell);
        if (cells_of_bypass_line_temp[number_of_cell]->get_speed() > bypass.getPtrBypassSection(number_of_cell)->getEndIndex()-number_of_cell)
        {
            scene->removeItem(cells_of_bypass_line_temp[number_of_cell].get());
            cells_of_bypass_line_temp[number_of_cell]= nullptr;
        } else {
            move(number_of_cell);
        }
    }


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
    bool free = true;
    for (int checked_cell = number_of_cell;
         checked_cell>=std::max(number_of_cell-vmax,0);--checked_cell){
        if (cells_of_bypass_line_right[checked_cell] != nullptr) {
            if (checked_cell + std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1, vmax)
                >= number_of_cell + std::min(cells_of_bypass_line_temp[number_of_cell]->get_speed()+1, vmax)) {
                free = false;
            }
        }
    }
    for (int checked_cell = number_of_cell+vmax;
         checked_cell>=number_of_cell;--checked_cell){
        if (cells_of_bypass_line_right[checked_cell] != nullptr){
            if (checked_cell +std::min(cells_of_bypass_line_right[checked_cell]->get_speed()+1,vmax)
                <= number_of_cell + std::min(cells_of_bypass_line_temp[number_of_cell]->get_speed()+1,vmax)){
                free = false;
            }
        }
    }
    if(cells_of_bypass_line_right[number_of_cell] != nullptr){
        free = false;
    }
    if(free){
        cells_of_bypass_line_right[number_of_cell] = cells_of_bypass_line_temp[number_of_cell];
        cells_of_bypass_line_temp[number_of_cell] = nullptr;
    }
    return free;
}


std::vector<std::shared_ptr<Vehicle>>& Simulation::get_cells_of_bypass_line_right()
{
    return cells_of_bypass_line_right;
}
std::vector<std::shared_ptr<Vehicle>>& Simulation::get_cells_of_bypass_line_left()
{
    return cells_of_bypass_line_left;
}
std::vector<std::shared_ptr<Vehicle>>& Simulation::get_cells_of_bypass_line_tmp()
{
    return cells_of_bypass_line_temp;
}
