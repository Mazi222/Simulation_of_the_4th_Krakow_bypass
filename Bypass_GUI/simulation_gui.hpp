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
#include <QTextEdit>
#include <QSlider>
#include "car_graphic.hpp"
#include "bypass/Simulation.hpp"

class Simulation_GUI: public QGraphicsView
{
     Q_OBJECT
private:
    QGraphicsScene *scene;
    Simulation *simulation_to_tarnow;
    Simulation *simulation_from_tarnow;
    QTimer *timer;
    std::array<int,12> partition_points;
    int hide_in_menu;
    int sum_of_cars=0;
//menu declarations
    std::vector<QPushButton *> buttons;
    QGridLayout *menu_layout;
    QGraphicsView *menu_view;
    QPushButton *counter;
    QPushButton *display;

//bypass declarations
    QGraphicsView *bypass_view;
    QPushButton *go_back_button;
    QImage *bypass_image;
    std::vector<QSlider *> sliders;
    int part_of_bypass;
    int partial_sum_of_cars;
    QPushButton *partial_sum_of_cars_view;

//menu functions
    void generate_menu();
    void create_buttons();
    void connect_buttons();
    void add_buttons_to_layout();
    void change_menu(const int i);

//bypass functions
    void generate_bypass(const int i);
    void go_back_to_menu();
    void set_sliders(int i);

public:
    Simulation_GUI();
    ~Simulation_GUI();
public slots:
    void move_cars_beta();
    void set_sum_of_cars();
    void set_partial_sum_of_cars();
};

#endif // SIMULATION_GUI_H
