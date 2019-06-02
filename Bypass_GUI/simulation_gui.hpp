#ifndef SIMULATION_GUI_H
#define SIMULATION_GUI_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include <memory>
#include "car_graphic.hpp"
#include "bypass/Simulation.hpp"

class Simulation_GUI: public QGraphicsView
{
     Q_OBJECT
private:
    QGraphicsScene *scene;
    Simulation *simulation;
//menu declarations
    std::vector<QPushButton *> buttons;
    QGridLayout *menu_layout;
    QGraphicsView *menu_view;

//bypass declarations
    QGraphicsView *bypass_view;
    std::vector<Car_Graphic *> cars_beta;

//menu functions
    void generate_menu();
    void create_buttons();
    void connect_buttons();
    void add_buttons_to_layout();
    void change_menu(const int i);

//bypass functions
    void generate_bypass(const int i);
    void getCarsBeta();

public:
    Simulation_GUI();
    ~Simulation_GUI();
public slots:
    void moveCarsBeta();
};

#endif // SIMULATION_GUI_H
