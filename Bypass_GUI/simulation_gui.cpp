#include "simulation_gui.hpp"

#include <QTimer>

Simulation_GUI::Simulation_GUI()
{
    scene = new QGraphicsScene();
    setScene(scene);
    generate_menu();
    simulation = new Simulation(scene);
    simulation->initializeBypass();
}



void Simulation_GUI::generate_menu()
{
    menu_view = new QGraphicsView();
    menu_layout = new QGridLayout;
    scene->setSceneRect(0,0,1024,585);


    menu_view->setScene(scene);
    menu_view->setFixedSize(1024,585);
    menu_view->setBackgroundBrush(QBrush(QImage(":/Images/map.png")));

    create_buttons();
    connect_buttons();
    add_buttons_to_layout();

    menu_view->setLayout(menu_layout);
    menu_view->show();

}

void Simulation_GUI::create_buttons()
{
    for(std::size_t i=0;i<27;++i)
    {
        buttons.push_back(new QPushButton);
        buttons[i]->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
        if(i<23)
            buttons[i]->setFlat(true);
    }
}

void Simulation_GUI::add_buttons_to_layout()
{
    //Left buttons
    menu_layout->addWidget(buttons[0],1,0);
    menu_layout->addWidget(buttons[1],2,0);
    menu_layout->addWidget(buttons[2],3,0);
    menu_layout->addWidget(buttons[3],4,0);

    //Left/Down buttons
    menu_layout->addWidget(buttons[4],5,1);
    menu_layout->addWidget(buttons[5],6,1);

    //Down buttons
    menu_layout->addWidget(buttons[6],6,2);
    menu_layout->addWidget(buttons[7],6,3);
    menu_layout->addWidget(buttons[8],6,4);
    menu_layout->addWidget(buttons[9],6,5);
    menu_layout->addWidget(buttons[10],6,6);
    menu_layout->addWidget(buttons[11],6,7);

    //Right buttons
    menu_layout->addWidget(buttons[12],5,7);
    menu_layout->addWidget(buttons[13],4,7);
    menu_layout->addWidget(buttons[14],3,7);
    menu_layout->addWidget(buttons[15],2,7);
    menu_layout->addWidget(buttons[16],1,7);

    //Right/Up buttons
    menu_layout->addWidget(buttons[17],1,6);

    //Up buttons
    menu_layout->addWidget(buttons[18],0,5);
    menu_layout->addWidget(buttons[19],0,4);
    menu_layout->addWidget(buttons[20],0,3);
    menu_layout->addWidget(buttons[21],0,2);
    menu_layout->addWidget(buttons[22],0,1);


    //Additional buttons
    menu_layout->addWidget(buttons[23],7,8);
    menu_layout->addWidget(buttons[24],7,9);
    menu_layout->addWidget(buttons[25],7,10);
    menu_layout->addWidget(buttons[26],7,11);
}

void Simulation_GUI::change_menu(const int i)
{
    menu_view->hide();
    generate_bypass(i);
}

void Simulation_GUI::connect_buttons()
{
    using namespace std::placeholders;
    for(std::size_t i =0;i<buttons.size();++i)
        connect(buttons[i], &QPushButton::clicked, this, [=](){this->change_menu(i);});
}


void Simulation_GUI::generate_bypass(const int i)
{
    bypass_view = new QGraphicsView();
    QImage bypass_image(":/Images/highway.png");

    scene->setSceneRect(0,0,bypass_image.width(),bypass_image.height());
    bypass_view ->setScene(scene);
    bypass_view ->setFixedSize(1024,bypass_image.height()+20);
    bypass_view ->setBackgroundBrush(QBrush(bypass_image));
    bypass_view ->show();

   // addCarsBeta();
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(moveCarsBeta()));
    timer->start(1);
}

Simulation_GUI::~Simulation_GUI()
{
    for(std::size_t i=0;i<buttons.size();++i)
        delete buttons[i];
    delete menu_layout;
    delete menu_view;

}

void Simulation_GUI::moveCarsBeta()
{

    simulation->next_step();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_to_tarnow = simulation->get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_to_tarnow  = simulation->get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_to_tarnow  = simulation->get_cells_of_bypass_line_tmp();

    for(std::size_t i=0;i<cells_of_bypass_line_right_to_tarnow .size();++i)
    {
        if(cells_of_bypass_line_right_to_tarnow [i]!=nullptr)
        {
            cells_of_bypass_line_right_to_tarnow [i]->move(i,0);
        }
    }
    for(std::size_t i=0;i<cells_of_bypass_line_left_to_tarnow.size();++i)
    {
        if(cells_of_bypass_line_left_to_tarnow[i]!=nullptr){
            cells_of_bypass_line_left_to_tarnow[i]->move(i,1);
        }
    }
    for(std::size_t i=0;i<cells_of_bypass_line_temp_to_tarnow .size();++i)
    {
        if(cells_of_bypass_line_temp_to_tarnow [i]!=nullptr){
            cells_of_bypass_line_temp_to_tarnow [i]->move(i,2);

        }
    }
}
