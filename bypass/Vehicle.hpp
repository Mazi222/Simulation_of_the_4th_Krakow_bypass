//
// Created by mazi on 18.04.19.
//

#ifndef SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
#define SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

#include <string>

class Vehicle: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Vehicle(int i=0,bool _direction=false, QGraphicsItem *parent=0);
    void set_speed(const int& new_speed);

    void move(const int& x,const int& y, const int& width_of_scenes);

    const int& get_speed() const;
    const std::string& get_destination() const;

    virtual ~Vehicle() = default;

protected:
    bool direction;
    int speed;
    std::string destination;
};


#endif //SIMULATION_OF_THE_4TH_KRAKOW_BYPASS_VEHICLE_HPP
