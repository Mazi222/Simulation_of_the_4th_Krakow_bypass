#include "car_graphic.h"

Car_Graphic::Car_Graphic(int i, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPos(x()+50*i,y()+50);
    setPixmap(QPixmap(":/Images/car.png"));
}

void Car_Graphic::move(int i)
{
    setPos(x()+i*50,y());
}
