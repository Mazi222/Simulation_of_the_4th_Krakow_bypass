#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "simulation_gui.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulation_GUI *gui = new Simulation_GUI();

    return a.exec();
}

