#include "simulation_gui.hpp"

#include <QTimer>

Simulation_GUI::Simulation_GUI()
{
    scene = new QGraphicsScene();
    setScene(scene);
    generate_menu();
    simulation_to_tarnow = new Simulation(scene,false);
    simulation_from_tarnow = new Simulation(scene,true);

    partition_points[0]=0;
    partition_points[1]=452;
    partition_points[2]=1062;
    partition_points[3]=1372;
    partition_points[4]=1893;

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move_cars_beta()));
    timer->start(1000);

    QTimer *timer2 = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(set_sum_of_cars()));
    timer2->start(100);
}

void Simulation_GUI::set_sum_of_cars()
{
    sum_of_cars=0;

    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_to_tarnow = simulation_to_tarnow->get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_tmp();

    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_from_tarnow = simulation_from_tarnow->get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_tmp();

    for(std::size_t i=0;i<cells_of_bypass_line_right_to_tarnow .size();++i)
    {
        if(cells_of_bypass_line_temp_to_tarnow [i]!=nullptr){
            sum_of_cars+=1;
        }
        if(cells_of_bypass_line_right_to_tarnow [i]!=nullptr){
            sum_of_cars+=1;
        }
        if(cells_of_bypass_line_left_to_tarnow[i]!=nullptr){
            sum_of_cars+=1;
        }
        if(cells_of_bypass_line_temp_from_tarnow [i]!=nullptr){
            sum_of_cars+=1;
        }
        if(cells_of_bypass_line_right_from_tarnow [i]!=nullptr){
            sum_of_cars+=1;
        }
        if(cells_of_bypass_line_left_from_tarnow[i]!=nullptr){
            sum_of_cars+=1;
        }
    }
    counter->setText(QString::number(sum_of_cars));
}

void Simulation_GUI::generate_menu()
{
    menu_view = new QGraphicsView();
    menu_layout = new QGridLayout;
    counter = new QPushButton();
    display = new QPushButton();

    scene->setSceneRect(0,0,1024,585);
    menu_view->setScene(scene);
    menu_view->setFixedSize(1044,590);
    menu_view->setBackgroundBrush(QBrush(QImage(":/Images/map.png")));

    create_buttons();
    connect_buttons();
    add_buttons_to_layout();

    menu_view->setLayout(menu_layout);
    menu_view->show();


}

void Simulation_GUI::create_buttons()
{
    counter->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    display->setText("Sum of all cars:");
    display->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    menu_layout->addWidget(counter,0,10);
    menu_layout->addWidget(display,0,9);

    for(std::size_t i=0;i<27;++i)
    {
        buttons.push_back(new QPushButton);
        buttons[i]->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
        if(i<23){}
           // buttons[i]->setFlat(true);
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
    hide_in_menu=0;
    part_of_bypass=i;
    bypass_view = new QGraphicsView();
    go_back_button = new QPushButton();
    go_back_button->move(10,10);
    go_back_button->setText("Go back");
    scene->addWidget(go_back_button);
    connect(go_back_button,&QPushButton::clicked, this, [=](){this->go_back_to_menu();});
    switch (i) {
    case 0: bypass_image = new QImage(":/Images/Part1.png");
        break;
    case 1: bypass_image = new QImage(":/Images/Part1.png");
        break;
    case 2: bypass_image = new QImage(":/Images/Part2.png");
        break;
    case 3: bypass_image = new QImage(":/Images/Part2.png");
        break;
    case 4: bypass_image = new QImage(":/Images/Part4.png");
        break;
    case 5: bypass_image = new QImage(":/Images/Part5.png");
        break;
    case 6: bypass_image = new QImage(":/Images/Part6.png");
        break;
    case 7: bypass_image = new QImage(":/Images/Part7.png");
        break;
    case 8: bypass_image = new QImage(":/Images/Part8.png");
        break;
    case 9: bypass_image = new QImage(":/Images/Part9.png");
        break;
    case 10: bypass_image = new QImage(":/Images/Part10.png");
        break;
    case 11: bypass_image = new QImage(":/Images/Part11.png");
        break;
    case 12: bypass_image = new QImage(":/Images/Part12.png");
        break;
    case 13: bypass_image = new QImage(":/Images/Part13.png");
        break;
    case 14: bypass_image = new QImage(":/Images/Part14.png");
        break;
    case 15: bypass_image = new QImage(":/Images/Part15.png");
        break;
    default:
        bypass_image = new QImage(":/Images/Part0.png");
        break;
    }

    scene->setSceneRect(0,0,bypass_image->width(),bypass_image->height());
    bypass_view ->setScene(scene);
    bypass_view ->setFixedSize(1024,bypass_image->height()+20);
    bypass_view ->setBackgroundBrush(QBrush(*bypass_image));
    bypass_view ->show();

}

Simulation_GUI::~Simulation_GUI()
{
    for(std::size_t i=0;i<buttons.size();++i)
        delete buttons[i];
    delete menu_layout;
    delete menu_view;

}

void Simulation_GUI::move_cars_beta()
{
    if(bypass_view!=nullptr){
        const int width_of_scene=scene->width();
        simulation_to_tarnow->next_step();
        simulation_from_tarnow->next_step();

        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_to_tarnow = simulation_to_tarnow->get_cells_of_bypass_line_right();
        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_left();
        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_tmp();

        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_from_tarnow = simulation_from_tarnow->get_cells_of_bypass_line_right();
        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_left();
        std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_tmp();

        int j=partition_points[part_of_bypass];
        int k=cells_of_bypass_line_right_to_tarnow .size()-j-1;

        for(std::size_t i=0;i<cells_of_bypass_line_right_to_tarnow .size();++i)
        {
            if(cells_of_bypass_line_temp_to_tarnow [i]!=nullptr){
                cells_of_bypass_line_temp_to_tarnow [i]->move(k-i,5+hide_in_menu,width_of_scene);
            }
            if(cells_of_bypass_line_right_to_tarnow [i]!=nullptr){
                cells_of_bypass_line_right_to_tarnow [i]->move(k-i,4+hide_in_menu,width_of_scene);
            }
            if(cells_of_bypass_line_left_to_tarnow[i]!=nullptr){
                cells_of_bypass_line_left_to_tarnow[i]->move(k-i,3+hide_in_menu,width_of_scene);
            }
            if(cells_of_bypass_line_temp_from_tarnow [i]!=nullptr){
                cells_of_bypass_line_temp_from_tarnow [i]->move(i-j,0+hide_in_menu,width_of_scene);
            }
            if(cells_of_bypass_line_right_from_tarnow [i]!=nullptr){
                cells_of_bypass_line_right_from_tarnow [i]->move(i-j,1+hide_in_menu,width_of_scene);
            }
            if(cells_of_bypass_line_left_from_tarnow[i]!=nullptr){
                cells_of_bypass_line_left_from_tarnow[i]->move(i-j,2+hide_in_menu,width_of_scene);
            }
        }
    }
}
void Simulation_GUI::go_back_to_menu()
{
    bypass_view->hide();
    scene->setSceneRect(0,0,1024,585);
    menu_view->show();
    delete go_back_button;
    delete bypass_image;
    hide_in_menu=-5;

}
