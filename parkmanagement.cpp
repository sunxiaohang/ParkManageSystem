#include "parkmanagement.h"
#include "ui_parkmanagement.h"
#include "card.h"
#include <iostream>

using namespace std;
ParkManagement::ParkManagement(QWidget *parent) :QMainWindow(parent),ui(new Ui::ParkManagement){
    ui->setupUi(this);
    init();
    userInterface();
}
void ParkManagement::init(){
    //bind view and widget
    parkAreaUp=ui->ParkAreaUp;
    parkAreaDown=ui->ParkAreaDown;
    Entence=ui->Entence;
    Exit=ui->Exit;
    entenceVerify=ui->entenceVerify;
    exitVerify=ui->exitVerify;
    freeArea=ui->freeArea;
    //initial view arguments
    parkAreaUp->setSpacing(1);
    parkAreaDown->setSpacing(1);
    Entence->setStyleSheet("QPushButton{background:red}");
    Exit->setStyleSheet("QPushButton{background:red;}");
    //initial free park area as 0
    freeArea->display(MAX_NUM_EACH_COLUMN*2);
    //initial parkArea with green background
    for(int i=0;i<MAX_NUM_EACH_COLUMN;i++){
        QPushButton *btnUp=new QPushButton(QString());
        QPushButton *btnDown=new QPushButton(QString());
        buttonArray[0][i]=btnUp;
        buttonArray[1][i]=btnDown;
        btnUp->setStyleSheet("QPushButton{background:green;height:180px}");
        btnDown->setStyleSheet("QPushButton{background:green;height:180px}");
        parkAreaUp->addWidget(btnUp);
        parkAreaDown->addWidget(btnDown);
    }
    //initial park system
    parkSystem=ParkSystem();
    //connect signal with slots
    timer=new QTimer();
    connect( timer, SIGNAL(timeout()),this, SLOT(timeDone()) );
}
void ParkManagement::userInterface(){
    Card card=Card("000000");
    if(validateCard.parkCar(card)){
        cout<<"park car successful!"<<endl;
        Entence->setVisible(false);
        timer->start(3000);
        int parkPosition=parkSystem.randomSelect();
        setTakenArea(parkPosition);
    }else{
        cout<<"park falult, validate false!"<<endl;
    }
}
void ParkManagement::timeDone(){
    timer->stop();
    if(!Entence->isVisible()){
        Entence->setVisible(true);
    }
    if(!Exit->isVisible()){
        Exit->setVisible(true);
    }
}
void ParkManagement::setTakenArea(int position){
    int column=position/MAX_NUM_EACH_COLUMN;
    int offset=position%MAX_NUM_EACH_COLUMN;
    buttonArray[column][offset]->setStyleSheet("QPushButton{background:red}");
}
