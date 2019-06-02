#include "Vehicle.hpp"

Vehicle::Vehicle(int i,QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    speed=1;
    setPos(i*50,50);
    setPixmap(QPixmap(":/Images/car.png"));
}

void Vehicle::set_speed(const int& new_speed)
{
    speed=new_speed;
}

const int& Vehicle::get_speed() const
{
    return speed;
}

void Vehicle::move(int x, int y)
{
    setPos(50*x,25+65*y);
}
