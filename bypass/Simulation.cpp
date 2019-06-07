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
    clean_flow_value();
    if(direction)
    {
        flow[0]=250;
        flow[1]=750;
        flow[2]=1250;
        flow[3]=1650;
        flow[4]=2150;
        flow[5]=2500;
        flow[6]=3000;
        flow[7]=3750;
        flow[8]=4500;
        flow[9]=4900;
        flow[10]=5500;
        flow[11]=6300;
        flow[12]=7000;
    }
    else {
        int k=7496;
        flow[0]=k-250;
        flow[1]=k-750;
        flow[2]=k-1250;
        flow[3]=k-1650;
        flow[4]=k-2150;
        flow[5]=k-2500;
        flow[6]=k-3000;
        flow[7]=k-3750;
        flow[8]=k-4500;
        flow[9]=k-4900;
        flow[10]=k-5500;
        flow[11]=k-6300;
        flow[12]=k-7000;
    }
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
        check_flow(number_of_cell,speed);
        if(speed > 0) {
            cells_of_bypass_line_right[(number_of_cell + speed) %
                                       cells_of_bypass_line_right.size()] = cells_of_bypass_line_right[number_of_cell];
            cells_of_bypass_line_right[number_of_cell] = nullptr;
        }
    }
    else if (line == LEFT_LINE)
    {

        int speed = cells_of_bypass_line_left[number_of_cell]->get_speed();
        check_flow(number_of_cell,speed);
        if(speed > 0) {
            cells_of_bypass_line_left[(number_of_cell + speed) %
                                      cells_of_bypass_line_left.size()] = cells_of_bypass_line_left[number_of_cell];
            cells_of_bypass_line_left[number_of_cell] = nullptr;
        }

    } else if(line == TEMP_LINE){
        int speed = cells_of_bypass_line_temp[number_of_cell]->get_speed();
        check_flow(number_of_cell,speed);
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
    for (int i = 0; i < 7496; ++i) {
        cells_of_bypass_line_right.push_back(nullptr);
        cells_of_bypass_line_left.push_back(nullptr);
        cells_of_bypass_line_temp.push_back(nullptr);
    }
    if(direction)
    {
        bypass.addBypassSection(std::make_shared<Road>(0, 320, 4)); //Nowa Huta po wjedzie
        bypass.addBypassSection(std::make_shared<Junction>(321, 330, 4, false, true, 10));//zjazd S7 - Trakt papieski
        bypass.addBypassSection(std::make_shared<Road>(331, 404, 4));
        bypass.addBypassSection(std::make_shared<Junction>(405, 451, 4, true, false, 100));//wjazd Trakt papieski - S7
        bypass.addBypassSection(std::make_shared<Road>(452, 598, 4));
        bypass.addBypassSection(std::make_shared<Junction>(599, 659, 4, false, true, 10));//zjazd S7 - A4 na Tarnów
        bypass.addBypassSection(std::make_shared<Road>(660, 786, 3));
        bypass.addBypassSection(std::make_shared<Junction>(787, 860, 5, true, false, 100)); //wjazd S7 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(861,1061, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1062, 1129, 5, false, true, 10));//zjazd A4 - 94
        bypass.addBypassSection(std::make_shared<Road>(1130,1250, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1251, 1371, 5, true, false, 100)); //wjazd 94 - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(1372,1892, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1893, 1919, 5, false, true, 10));//zjazd A4 - Zbigniewa Herberta
        bypass.addBypassSection(std::make_shared<Road>(1920,1973, 5));
        bypass.addBypassSection(std::make_shared<Junction>(1974, 1999, 5, true, false, 100)); //wjazd Zbigniewa Herberta - A4 na Katowice
        bypass.addBypassSection(std::make_shared<Road>(2000,2240, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2241, 2267, 5, false, true, 10));//zjazd A4 - Zakopianka
        bypass.addBypassSection(std::make_shared<Road>(2268,2315, 5));
        bypass.addBypassSection(std::make_shared<Junction>(2316, 2336, 5, true, false, 100)); //wjazd Zakopianka - A4 na Katowice
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
        bypass.addBypassSection(std::make_shared<Junction>(4132, 4167, 5, false, true, 10));//zjazd A4 - Balice II
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
        bypass.addBypassSection(std::make_shared<Junction>(5080, 5104, 4, false, true, 10));//zjazd 94
    //////////-----------------
    //////////-----------------
        bypass.addBypassSection(std::make_shared<Road>(5105,5555, 4));
            bypass.addBypassSection(std::make_shared<Junction>(5556, 5583, 4, false, true, 10));//zjazd zielonki
        bypass.addBypassSection(std::make_shared<Road>(5584, 5624, 4));
            bypass.addBypassSection(std::make_shared<Junction>(5625, 5652, 4, true, false, 100)); //wjazd  zielonki
        bypass.addBypassSection(std::make_shared<Road>(5653, 6017, 4));
        bypass.addBypassSection(std::make_shared<Junction>(6018, 6045, 4, false, true, 10));//zjazd węgrzce
            bypass.addBypassSection(std::make_shared<Junction>(6046, 6073, 4, true, false, 100)); //wjazd węgrzce
        bypass.addBypassSection(std::make_shared<Road>(6074, 6411, 4));
        bypass.addBypassSection(std::make_shared<Junction>(6412, 6439, 4, false, true, 10));//zjazd batowice
        bypass.addBypassSection(std::make_shared<Road>(6440, 6480, 4));
            bypass.addBypassSection(std::make_shared<Junction>(6481, 6508, 4, true, false, 100)); //wjazd batowice
        bypass.addBypassSection(std::make_shared<Road>(6509, 6678, 4));
        bypass.addBypassSection(std::make_shared<Junction>(6679, 6706, 4, false, true, 10));//zjazd mistrzejowice
        bypass.addBypassSection(std::make_shared<Road>(6707, 6734, 4));
            bypass.addBypassSection(std::make_shared<Junction>(6735, 6762, 4, true, false, 100)); //wjazd mistrzejowice
        bypass.addBypassSection(std::make_shared<Road>(6763, 6910, 4));
        bypass.addBypassSection(std::make_shared<Junction>(6911, 6944, 4, false, true, 10));//zjazd grębałów
        bypass.addBypassSection(std::make_shared<Road>(6945, 6985, 4));
            bypass.addBypassSection(std::make_shared<Junction>(6986, 7013, 4, true, false, 100)); //wjazd grębałów
        bypass.addBypassSection(std::make_shared<Road>(7014, 7322, 4));
        bypass.addBypassSection(std::make_shared<Junction>(7323, 7367, 4, false, true, 10));//zjazd huta
        bypass.addBypassSection(std::make_shared<Road>(7368, 7451, 4));
            bypass.addBypassSection(std::make_shared<Junction>(7452, 7496, 4, true, false, 100)); //wjazd huta
    }
    else {
        bypass.addBypassSection ( std::make_shared<Junction> ( 0 , 44 , 4 , true , false , 100)); //wjazd huta
        bypass.addBypassSection ( std::make_shared<Road> ( 45 , 128 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 129 , 173 , 4 , false , true , 10));//zjazd huta
        bypass.addBypassSection ( std::make_shared<Road> ( 174 , 482 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 483 , 510 , 4 , true , false , 100)); //wjazd grębałów
        bypass.addBypassSection ( std::make_shared<Road> ( 511 , 551 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 552 , 585 , 4 , false , true , 10));//zjazd grębałów
        bypass.addBypassSection ( std::make_shared<Road> ( 586 , 733 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 734 , 761 , 4 , true , false , 100)); //wjazd mistrzejowice
        bypass.addBypassSection ( std::make_shared<Road> ( 762 , 789 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 790 , 817 , 4 , false , true , 10));//zjazd mistrzejowice
        bypass.addBypassSection ( std::make_shared<Road> ( 818 , 987 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 988 , 1015 , 4 , true , false , 100)); //wjazd batowice
        bypass.addBypassSection ( std::make_shared<Road> ( 1016 , 1056 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 1057 , 1084 , 4 , false , true , 10));//zjazd batowice
        bypass.addBypassSection ( std::make_shared<Road> ( 1085 , 1422 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 1423 , 1450 , 4 , true , false , 100)); //wjazd węgrzce
        bypass.addBypassSection ( std::make_shared<Junction> ( 1451 , 1478 , 4 , false , true , 10));//zjazd węgrzce
        bypass.addBypassSection ( std::make_shared<Road> ( 1479 , 1843 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 1844 , 1871 , 4 , true , false , 100)); //wjazd zielonki
        bypass.addBypassSection ( std::make_shared<Road> ( 1872 , 1912 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 1913 , 1940 , 4 , false , true , 10));//zjazd zielonki
        bypass.addBypassSection ( std::make_shared<Road> ( 1941 , 2391 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 2392 , 2416 , 4 , false , true , 10));//zjazd 94
        bypass.addBypassSection ( std::make_shared<Road> ( 2417 , 2550 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 2551 , 2575 , 4 , true , false , 100)); //wjazd - 94
        bypass.addBypassSection ( std::make_shared<Road> ( 2576 , 2600 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 2601 , 2617 , 4 , false , true , 10));//zjazd 94
        bypass.addBypassSection ( std::make_shared<Junction> ( 2618 , 2634 , 4 , true , false , 100)); //wjazd 79 - 94
        bypass.addBypassSection ( std::make_shared<Road> ( 2635 , 2663 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 2664 , 2703 , 4 , false , true , 10));//zjazd 94 - 79
        bypass.addBypassSection ( std::make_shared<Junction> ( 2704 , 2737 , 4 , false , true , 10));//zjazd 94 - 7
        bypass.addBypassSection ( std::make_shared<Road> ( 2738 , 3058 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 3059 , 3091 , 4 , true , false , 100)); //wjazd A4 - S52
        bypass.addBypassSection ( std::make_shared<Road> ( 3092 , 3152 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 3153 , 3193 , 5 , false , true , 10));//zjazd S52 - A4
        bypass.addBypassSection ( std::make_shared<Junction> ( 3194 , 3274 , 5 , true , false , 100)); //wjazd Balice - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 3275 , 3328 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 3329 , 3364 , 5 , false , true , 10));//zjazd A4 - Balice II
        bypass.addBypassSection ( std::make_shared<Road> ( 3365 , 3872 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 3873 , 3906 , 5 , true , false , 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 3907 , 3936 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 3937 , 3997 , 5 , false , true , 10));//zjazd A4 - 780
        bypass.addBypassSection ( std::make_shared<Road> ( 3998 , 4144 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 4145 , 4174 , 5 , true , false , 100)); //wjazd Tyniecka - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 4175 , 4215 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 4216 , 4244 , 5 , false , true , 10));//zjazd A4 - Tyniecka
        bypass.addBypassSection ( std::make_shared<Road> ( 4245 , 4578 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 4579 , 4608 , 5 , true , false , 100)); //wjazd 44 - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 4609 , 4682 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 4683 , 4706 , 5 , false , true , 10));//zjazd A4 - 44
        bypass.addBypassSection ( std::make_shared<Road> ( 4707 , 5160 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 5161 , 5181 , 5 , true , false , 100)); //wjazd Zakopianka - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 5182 , 5229 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 5230 , 5256 , 5 , false , true , 10));//zjazd A4 - Zakopianka
        bypass.addBypassSection ( std::make_shared<Road> ( 5257 , 5497 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 5498 , 5523 , 5 , true , false , 100)); //wjazd Zbigniewa Herberta - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 5524 , 5577 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 5578 , 5604 , 5 , false , true , 10));//zjazd A4 - Zbigniewa Herberta
        bypass.addBypassSection ( std::make_shared<Road> ( 5605 , 6125 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 6126 , 6246 , 5 , true , false , 100)); //wjazd 94 - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 6247 , 6367 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 6368 , 6435 , 5 , false , true , 10));//zjazd A4 - 94
        bypass.addBypassSection ( std::make_shared<Road> ( 6436 , 6636 , 5));
        bypass.addBypassSection ( std::make_shared<Junction> ( 6637 , 6710 , 5 , true , false , 100)); //wjazd S7 - A4 na Katowice
        bypass.addBypassSection ( std::make_shared<Road> ( 6711 , 6837 , 3));
        bypass.addBypassSection ( std::make_shared<Junction> ( 6838 , 6898 , 4 , false , true , 10));//zjazd S7 - A4 na Tarnów
        bypass.addBypassSection ( std::make_shared<Road> ( 6899 , 7045 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 7046 , 7092 , 4 , true , false , 100));//wjazd Trakt papieski - S7
        bypass.addBypassSection ( std::make_shared<Road> ( 7093 , 7166 , 4));
        bypass.addBypassSection ( std::make_shared<Junction> ( 7167 , 7176 , 4 , false , true , 10));//zjazd S7 - Trakt papieski
       bypass.addBypassSection ( std::make_shared<Road> ( 7177 , 7496 , 4)); //Nowa Huta po wjedzie
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

void Simulation::check_flow(const int &number_of_cell,const int &speed)
{
    for(std::size_t i=0;i<13;++i)
    {
        if(number_of_cell<flow[i] && number_of_cell+speed >= flow[i])
        {
            flow_value[i]+=1;
            break;
        }
    }
}
std::array<std::size_t,13>& Simulation::get_flow_value()
{
    return flow_value;
}

void Simulation::clean_flow_value()
{
    for(std::size_t i=0;i<13;++i)
    {
        flow_value[i]=0;
    }
}
