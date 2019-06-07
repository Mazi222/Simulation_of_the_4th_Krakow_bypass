#include "simulation_gui.hpp"


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
    partition_points[5]=2337;
    partition_points[6]=2889;
    partition_points[7]=3353;
    partition_points[8]=4133;
    partition_points[9]=4759;
    partition_points[10]=5105;
    partition_points[11]=6018;
    partition_points[12]=6679;
    partition_points[13]=7496;
    partition_points[14]=7496;

    time_to_start_func=10;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move_cars_beta()));
    timer->start(time_to_start_func);

    connect(timer, SIGNAL(timeout()),this,SLOT(set_sum_of_cars()));
    QTimer *timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()),this,SLOT(set_flow_of_cars()));
    timer2->start(2000);
    timer_of_flow=0;
}

void Simulation_GUI::generate_menu()
{
    menu_view = new QGraphicsView();
    menu_layout = new QGridLayout;

    counter = new QPushButton();
    display = new QPushButton();
    display_2 = new QPushButton();
    create_plot = new QPushButton();
    for(int i=0;i<24;++i)
    {
        view_of_flow.push_back(new QPushButton);
    }


    scene->setSceneRect(0,0,1124,585);
    menu_view->setScene(scene);
    menu_view->setFixedSize(1144,590);
    menu_view->setBackgroundBrush(QBrush(QImage(":/Images/map.png")));

    create_buttons();
    connect_buttons();
    add_buttons_to_layout();

    menu_view->setLayout(menu_layout);
    menu_view->show();


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

void Simulation_GUI::create_buttons()
{
    counter->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    display->setText("Sum of all cars:");
    display->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    display_2->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    display_2->setText("Junction - From / To");
    create_plot->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    create_plot->setText("Show plot of flow");
    connect(create_plot, &QPushButton::clicked, this, [=](){this->create_plots();});
    menu_layout->addWidget(counter,0,9);
    menu_layout->addWidget(display,0,8);
    for(std::size_t i=0;i<24;++i)
    {
        view_of_flow[i]->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    }

    for(std::size_t i=0;i<23;++i)
    {
        buttons.push_back(new QPushButton());//QString::number(i)
        buttons[i]->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
        if(i<23)//{buttons[i]->setText(QString::number(i));}
            buttons[i]->setFlat(true);
    }
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


void Simulation_GUI::generate_bypass(const int x)
{
    int i;
    if(x==14 | x==13)
        i=0;
    else if(x==12 || x==11)
        i=1;
    else if(x==10)
        i=2;
    else if(x==9)
        i=3;
    else if(x==8 || x==7)
        i=4;
    else if(x==6 || x==5)
        i=5;
    else if(x==4 || x==3)
        i=6;
    else if(x==2 || x==1)
        i=7;
    else if(x==0)
        i=8;
    else if(x==22 || x==21)
        i=9;
    else if(x==20 || x==19)
        i=10;
    else if(x==18)
        i=11;
    else
        i=12;
    hide_in_menu=0;
    part_of_bypass=i;
    bypass_view = new QGraphicsView();
    partial_sum_of_cars_view = new QPushButton();
    name_of_partition = new QPushButton();
    go_back_button = new QPushButton();

    scene->addWidget(go_back_button);
    connect(go_back_button,&QPushButton::clicked, this, [=](){this->go_back_to_menu();});
    switch (i) {
    case 0:
        bypass_image = new QImage(":/Images/Part1.png");
        name_of_partition->setText("Nowa Huta - Trakt Papieski");
        break;
    case 1:
        bypass_image = new QImage(":/Images/Part2.png");
        name_of_partition->setText("Trakt Papieski - A4/97");
        break;
    case 2:
        bypass_image = new QImage(":/Images/Part3.png");
        name_of_partition->setText("A4/97 - A4/94");
        break;
    case 3:
        bypass_image = new QImage(":/Images/Part4.png");
        name_of_partition->setText("A4/94 - A4 Herberta");
        break;
    case 4:
        bypass_image = new QImage(":/Images/Part5.png");
        name_of_partition->setText("A4 Herberta - Zakopianska");
        break;
    case 5: bypass_image = new QImage(":/Images/Part6.png");
        name_of_partition->setText("Zakopianska - A4/44");
        break;
    case 6: bypass_image = new QImage(":/Images/Part7.png");
        name_of_partition->setText("A4/44 - Tyniecka");
        break;
    case 7: bypass_image = new QImage(":/Images/Part8.png");
        name_of_partition->setText("Tyniecka - Balice");
        break;
    case 8: bypass_image = new QImage(":/Images/Part9.png");
        name_of_partition->setText("Balice - 94/7");
        break;
    case 9: bypass_image = new QImage(":/Images/Part10.png");
        name_of_partition->setText("94/7 - 94");
        break;
    case 10:bypass_image = new QImage(":/Images/Part11.png");
        name_of_partition->setText("94-Węgrzce");
        break;
    case 11:bypass_image = new QImage(":/Images/Part12.png");
        name_of_partition->setText("Węgrzce-Mistrzejowice");
        break;
    case 12:bypass_image = new QImage(":/Images/Part13.png");
        name_of_partition->setText("Mistrzejowice - Nowa Huta");
        break;
    }

    go_back_button->move(bypass_image->width()/2-100,20);
    go_back_button->setText("Go back");
    name_of_partition->move(bypass_image->width()/2+50,20);
    scene->addWidget(name_of_partition);
    scene->setSceneRect(0,0,bypass_image->width(),bypass_image->height());

    partial_sum_of_cars_view->move(bypass_image->width()/2,20);
    connect(timer, SIGNAL(timeout()),this,SLOT(set_partial_sum_of_cars()));

    scene->addWidget(partial_sum_of_cars_view);
    bypass_view ->setScene(scene);
    bypass_view ->setFixedSize(1024,bypass_image->height()+20);
    bypass_view ->setBackgroundBrush(QBrush(*bypass_image));
    bypass_view ->show();

}

Simulation_GUI::~Simulation_GUI()   //TODO
{
    for(std::size_t i=0;i<buttons.size();++i)
        delete buttons[i];
    delete menu_layout;
    delete menu_view;
}

void Simulation_GUI::move_cars_beta()
{
    if(bypass_view!=nullptr){
        timer_of_flow+=1;
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
    scene->setSceneRect(0,0,1124,585);
    menu_view->show();
    disconnect(timer, SIGNAL(timeout()),this,SLOT(set_partial_sum_of_cars()));
    delete name_of_partition;
    delete partial_sum_of_cars_view;
    delete go_back_button;
//    for(int i=0;i<sliders.size();++i)
//    {
//        sliders[i]->move(0,-500);
//    }
    delete bypass_image;
    hide_in_menu=-6;

}

void Simulation_GUI::add_buttons_to_layout()
{
    //Left buttons
    menu_layout->addWidget(buttons[0],1,0);
    menu_layout->addWidget(buttons[1],2,0,1,2);
    menu_layout->addWidget(buttons[2],3,0,1,2);
    menu_layout->addWidget(buttons[3],4,0,1,2);
    //Left/Down buttons
    menu_layout->addWidget(buttons[4],5,0,1,2);
    menu_layout->addWidget(buttons[5],6,1);
    //Down buttons
    menu_layout->addWidget(buttons[6],7,1,1,2);
    menu_layout->addWidget(buttons[7],7,3);
    menu_layout->addWidget(buttons[8],7,4);
    menu_layout->addWidget(buttons[9],7,5);
    menu_layout->addWidget(buttons[10],7,6);
    menu_layout->addWidget(buttons[11],6,6,1,2);

    //Right buttons
    menu_layout->addWidget(buttons[12],5,6,1,2);
    menu_layout->addWidget(buttons[13],4,6,1,2);
    menu_layout->addWidget(buttons[14],3,6,1,2);
    menu_layout->addWidget(buttons[15],2,7);

    //Right/Up buttons
    menu_layout->addWidget(buttons[17],1,6,2,1);

    //Up buttons
    menu_layout->addWidget(buttons[18],0,5,2,1);
    menu_layout->addWidget(buttons[19],0,4);
    menu_layout->addWidget(buttons[20],0,3);
    menu_layout->addWidget(buttons[21],0,2);
    menu_layout->addWidget(buttons[22],0,1,2,1);

    //View buttons
    menu_layout->addWidget(display_2,0,10,1,2);

    menu_layout->addWidget(view_of_flow[0],1,8);
    menu_layout->addWidget(view_of_flow[1],2,8);
    menu_layout->addWidget(view_of_flow[2],3,8);
    menu_layout->addWidget(view_of_flow[3],4,8);
    menu_layout->addWidget(view_of_flow[4],5,8);
    menu_layout->addWidget(view_of_flow[5],6,8);
    menu_layout->addWidget(view_of_flow[6],7,8);
    menu_layout->addWidget(view_of_flow[7],8,8);

    menu_layout->addWidget(view_of_flow[8],1,9);
    menu_layout->addWidget(view_of_flow[9],2,9);
    menu_layout->addWidget(view_of_flow[10],3,9);
    menu_layout->addWidget(view_of_flow[11],4,9);
    menu_layout->addWidget(view_of_flow[12],5,9);
    menu_layout->addWidget(view_of_flow[13],6,9);
    menu_layout->addWidget(view_of_flow[14],7,9);
    menu_layout->addWidget(view_of_flow[15],8,9);

    menu_layout->addWidget(view_of_flow[16],1,10);
    menu_layout->addWidget(view_of_flow[17],2,10);
    menu_layout->addWidget(view_of_flow[18],3,10);
    menu_layout->addWidget(view_of_flow[19],4,10);

    menu_layout->addWidget(view_of_flow[20],1,11);
    menu_layout->addWidget(view_of_flow[21],2,11);
    menu_layout->addWidget(view_of_flow[22],3,11);
    menu_layout->addWidget(view_of_flow[23],4,11);

    view_of_flow[0]->setText("Nowa Huta \n- Trakt Papieski");
    view_of_flow[1]->setText("A4/97 - A4/94");
    view_of_flow[2]->setText("A4/94 \n- A4 Herberta");
    view_of_flow[3]->setText("A4 Herberta \n- Zakopianska");
    view_of_flow[4]->setText("Zakopianska \n- A4/44");
    view_of_flow[5]->setText("A4/44 \n- Tyniecka");
    view_of_flow[6]->setText("Tyniecka \n- Balice");
    view_of_flow[7]->setText("Balice \n- 94/7");

    view_of_flow[16]->setText("94/7 - 94");
    view_of_flow[17]->setText("94 \n- Węgrzce");
    view_of_flow[18]->setText("Węgrzce \n- Mistrzejowice");
    view_of_flow[19]->setText("Mistrzejowice\n - Nowa Huta");


    menu_layout->addWidget(create_plot,5,10,4,2);
    //Additional buttons
//    menu_layout->addWidget(buttons[23],7,8);
//    menu_layout->addWidget(buttons[24],7,9);
//    menu_layout->addWidget(buttons[25],7,10);
//    menu_layout->addWidget(buttons[26],7,11);


}

void Simulation_GUI::set_sliders(int i)
{
    if(i==0)
    {
        sliders[0]->move(50*60,20);
        sliders[1]->move(50*60,300);
        sliders[2]->move(115*60,20);
        sliders[3]->move(115*60,300);
    }
    else if(i==1)
    {
        sliders[0]->move(195*60,20);
        sliders[1]->move(195*60,300);
        sliders[2]->move(395*60,20);
        sliders[3]->move(395*60,300);
    }
    else if(i==2)
    {
        sliders[0]->move(125*60,20);
        sliders[1]->move(125*60,300);
        sliders[2]->move(235*60,20);
        sliders[3]->move(235*60,300);
    }
    else if(i==4)
    {
        sliders[0]->move(25*60,20);
        sliders[1]->move(25*60,300);
        sliders[2]->move(63*60,20);
        sliders[3]->move(63*60,300);
    }
    else {
        if(!sliders.empty()){
            sliders[0]->move(-100,-100);
            sliders[1]->move(-100,-100);
            sliders[2]->move(-100,-100);
            sliders[3]->move(-100,-100);
         }
    }

}

void Simulation_GUI::set_partial_sum_of_cars()
{

    partial_sum_of_cars=0;

    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_to_tarnow = simulation_to_tarnow->get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_to_tarnow  = simulation_to_tarnow->get_cells_of_bypass_line_tmp();

    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_right_from_tarnow = simulation_from_tarnow->get_cells_of_bypass_line_right();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_left_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_left();
    std::vector<std::shared_ptr<Vehicle>> &cells_of_bypass_line_temp_from_tarnow  = simulation_from_tarnow->get_cells_of_bypass_line_tmp();

    for(std::size_t i=partition_points[part_of_bypass];i<partition_points[part_of_bypass+1];++i)
    {
        if(cells_of_bypass_line_temp_to_tarnow [i]!=nullptr){
            partial_sum_of_cars+=1;
        }
        if(cells_of_bypass_line_right_to_tarnow [i]!=nullptr){
            partial_sum_of_cars+=1;
        }
        if(cells_of_bypass_line_left_to_tarnow[i]!=nullptr){
            partial_sum_of_cars+=1;
        }
        if(cells_of_bypass_line_temp_from_tarnow [i]!=nullptr){
            partial_sum_of_cars+=1;
        }
        if(cells_of_bypass_line_right_from_tarnow [i]!=nullptr){
            partial_sum_of_cars+=1;
        }
        if(cells_of_bypass_line_left_from_tarnow[i]!=nullptr){
            partial_sum_of_cars+=1;
        }
    }
    partial_sum_of_cars_view->setText(QString::number(partial_sum_of_cars));
}

void Simulation_GUI::set_flow_of_cars()
{
    std::array<std::size_t,13> &flow_values_to_tarnow = simulation_to_tarnow->get_flow_value();
    std::array<std::size_t,13> &flow_values_from_tarnow = simulation_from_tarnow->get_flow_value();
    view_of_flow[8]->setText(QString::number(flow_values_to_tarnow[0])+"/"+QString::number(flow_values_from_tarnow[0]));
    view_of_flow[9]->setText(QString::number(flow_values_to_tarnow[1])+"/"+QString::number(flow_values_from_tarnow[1]));
    view_of_flow[10]->setText(QString::number(flow_values_to_tarnow[2])+"/"+QString::number(flow_values_from_tarnow[2]));
    view_of_flow[11]->setText(QString::number(flow_values_to_tarnow[3])+"/"+QString::number(flow_values_from_tarnow[3]));
    view_of_flow[12]->setText(QString::number(flow_values_to_tarnow[4])+"/"+QString::number(flow_values_from_tarnow[4]));
    view_of_flow[13]->setText(QString::number(flow_values_to_tarnow[5])+"/"+QString::number(flow_values_from_tarnow[5]));
    view_of_flow[14]->setText(QString::number(flow_values_to_tarnow[6])+"/"+QString::number(flow_values_from_tarnow[6]));
    view_of_flow[15]->setText(QString::number(flow_values_to_tarnow[7])+"/"+QString::number(flow_values_from_tarnow[7]));

    view_of_flow[20]->setText(QString::number(flow_values_to_tarnow[8])+"/"+QString::number(flow_values_from_tarnow[8]));
    view_of_flow[21]->setText(QString::number(flow_values_to_tarnow[9])+"/"+QString::number(flow_values_from_tarnow[9]));
    view_of_flow[22]->setText(QString::number(flow_values_to_tarnow[10])+"/"+QString::number(flow_values_from_tarnow[10]));
    view_of_flow[23]->setText(QString::number(flow_values_to_tarnow[11])+"/"+QString::number(flow_values_from_tarnow[11]));

    if(timer_of_flow==3600){
        timer_of_flow=0;
        for(int i=0;i<13;++i){
            flow_in_hour.push_back(flow_values_to_tarnow[i]);
            flow_in_hour.push_back(flow_values_from_tarnow[i]);
        }
        simulation_to_tarnow->clean_flow_value();
        simulation_from_tarnow->clean_flow_value();
    }
}

void Simulation_GUI::create_plots()
{
//    QGraphicsScene *plot_scene = new QGraphicsScene();
//    plot_scene->setSceneRect(0,0,1124,585);
//    QGraphicsView *view = new QGraphicsView();
//    view->setScene(plot_scene);
//    view->setFixedSize(1144,590);
}
