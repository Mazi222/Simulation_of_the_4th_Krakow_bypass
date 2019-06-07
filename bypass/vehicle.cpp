#include "Vehicle.hpp"
#include  <QDebug>
Vehicle::Vehicle(int i, bool _direction, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent), direction(_direction)
{
    speed=1;
    setPos(0,0);
    if(direction){
        setPixmap(QPixmap(":/Images/car.png"));
    }
    else {
        setPixmap(QPixmap(":/Images/car2.png"));

    }
}

void Vehicle::set_speed(const int& new_speed)
{
    speed=new_speed;
}

const int& Vehicle::get_speed() const
{
    return speed;
}

void Vehicle::move(const int& x,const int& y, const int& width_of_scene)
{
    if(direction){
        setPos(width_of_scene-60*x,10+55*y);
    }
    else {
        setPos(width_of_scene-60*x,10+55*y);
    }
}
