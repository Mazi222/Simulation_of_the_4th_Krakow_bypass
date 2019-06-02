#ifndef CAR_GRAPHIC_H
#define CAR_GRAPHIC_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Car_Graphic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Car_Graphic(int i,QGraphicsItem *parent = 0);
    void move(int i);
};

#endif // CAR_GRAPHIC_H
