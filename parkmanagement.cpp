#include "parkmanagement.h"
#include "ui_parkmanagement.h"
#include "card.h"
#include <iostream>

using namespace std;
ParkManagement::ParkManagement(QWidget *parent) :QMainWindow(parent),ui(new Ui::ParkManagement){
    ui->setupUi(this);
    init();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
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
    RandomCar=ui->RandomCar;
    MessageBox=ui->MessageBox;
    movementCar=ui->movementCar;
    movementCar->setVisible(false);
    initialGeometryX=movementCar->pos().x()+40;
    initialGeometryY=movementCar->pos().y()+65;
    Entence->setStyleSheet("QPushButton{background:red}");
    Exit->setStyleSheet("QPushButton{background:red;}");
    RandomCar->setStyleSheet("QPushButton{background:red;}");
    //initial free park area as 0
    freeArea->display(MAX_NUM_EACH_COLUMN*2);
    //initial parkArea with green background
    for(int i=0;i<MAX_NUM_EACH_COLUMN;i++){
        QPushButton *btnUp=new QPushButton(QString());
        QPushButton *btnDown=new QPushButton(QString());
        buttonArray[0][i]=btnUp;
        buttonArray[1][i]=btnDown;
        btnUp->setObjectName(QString("%1").arg(-1));
        btnDown->setObjectName(QString("%1").arg(-1));
        connect(btnUp, SIGNAL(clicked()), this, SLOT(disposalLeaveSelect()));
        connect(btnDown, SIGNAL(clicked()), this, SLOT(disposalLeaveSelect()));
        btnUp->setStyleSheet("QPushButton{background:green;height:180px}");
        btnDown->setStyleSheet("QPushButton{background:green;height:180px}");
        parkAreaUp->addWidget(btnUp);
        parkAreaDown->addWidget(btnDown);
    }
    //initial park system
    randomCardId="AAAAAA";
    animationParkPosition=-1;
    //connect signal with slots
    timer=new QTimer();
    connect(RandomCar,SIGNAL(clicked()),this,SLOT(randomCar()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeDone()));
    connect(entenceVerify,SIGNAL(clicked()),this,SLOT(disposalEntence()));
    connect(exitVerify,SIGNAL(clicked()),this,SLOT(disposalExit()));
}
void ParkManagement::userInterface(){
    //restore sql date to init park system
    restoreSqlDate();
    //initial a new card to simulate a car entence process
}
void ParkManagement::timeDone(){
    timer->stop();
    if(!Entence->isVisible()){
        Entence->setVisible(true);
    }
    if(!Exit->isVisible()){
        Exit->setVisible(true);
        movementCar->setVisible(false);
//        movementCar->setGeometry(initialGeometryX,initialGeometryY,80,130);
    }
}
void ParkManagement::setTakenArea(Card card){
    int position=card.getTaken();
    if(position<0)return;
    if(position>=2*MAX_NUM_EACH_COLUMN)return;
    int column=position/MAX_NUM_EACH_COLUMN;
    int offset=position%MAX_NUM_EACH_COLUMN;
    buttonArray[column][offset]->setStyleSheet("QPushButton{background:red;height:180px}");
    if(card.getCardID()!="AAAAAA"){
        buttonArray[column][offset]->setText(card.getCardID());
        buttonArray[column][offset]->setObjectName(card.getCardID());
    }
}
void ParkManagement::setTempTakenArea(int position){
    if(position<0)return;
    if(position>=2*MAX_NUM_EACH_COLUMN)return;
    int column=position/MAX_NUM_EACH_COLUMN;
    int offset=position%MAX_NUM_EACH_COLUMN;
    buttonArray[column][offset]->setText(QString("%1").arg(randomCardId));
    buttonArray[column][offset]->setObjectName(QString("%1").arg(randomCardId));
    buttonArray[column][offset]->setStyleSheet("QPushButton{background:gray;height:180px}");
}
void ParkManagement::restoreSqlDate(){
    //restore date from sql
    qDebug()<<"###################ParkSystem start###################";
    Card *cardList=validateCard.initialDataSource();
    parkSystem.setParkAreaArray(cardList);
    qDebug()<<"breaken point";
    for(int i=0;i<2*MAX_NUM_EACH_COLUMN;i++){
        setTakenArea(cardList[i]);
    }
    freeArea->display(parkSystem.getFreeArea());
}
void ParkManagement::disposalEntence(){
    if(randomCardId=="AAAAAA")return;
    Card card=Card(randomCardId);
    if(validateCard.validatePark(card)){
        MessageBox->setText(QString("%1").arg("Park car successful!"));
        Entence->setVisible(false);
        timer->start(4000);
        int parkPosition=parkSystem.randomSelect();
        //QRect initialStatus=QRect(RandomCar->pos().x(), RandomCar->pos().y(),180,70);
        //move animation
        int moveDistance=77*((parkPosition%MAX_NUM_EACH_COLUMN)+1)+3*(parkPosition%MAX_NUM_EACH_COLUMN)+68;
        int scaleWidth=40;
        int scaleHeight=11;
        QPropertyAnimation *parkCarAnimation = new QPropertyAnimation(RandomCar, "geometry");
        RandomCar->setText("M");
        parkCarAnimation->setDuration(3000);
        parkCarAnimation->setKeyValueAt(0,QRect(RandomCar->pos().x(), RandomCar->pos().y(),120,62));
        parkCarAnimation->setKeyValueAt(0.1,QRect(RandomCar->pos().x()+scaleWidth, RandomCar->pos().y()+scaleHeight,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
        parkCarAnimation->setKeyValueAt(0.4,QRect(RandomCar->pos().x()+scaleWidth+moveDistance, RandomCar->pos().y()+scaleHeight,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
        if(parkPosition>=MAX_NUM_EACH_COLUMN){
            parkCarAnimation->setKeyValueAt(0.99,QRect(RandomCar->pos().x()+scaleWidth+moveDistance, RandomCar->pos().y()+scaleHeight+140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
        }else{
            parkCarAnimation->setKeyValueAt(0.99,QRect(RandomCar->pos().x()+scaleWidth+moveDistance, RandomCar->pos().y()+scaleHeight-140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
        }
        parkCarAnimation->setKeyValueAt(1,QRect(RandomCar->pos().x(), RandomCar->pos().y(),120,62));
        parkCarAnimation->setEasingCurve(QEasingCurve::InSine);
        parkCarAnimation->start();
        animationParkPosition=parkPosition;
        setTempTakenArea(parkPosition);
        connect(parkCarAnimation, SIGNAL(finished()), this, SLOT(ParkAnimationFinished()));
        card.setTaken(parkPosition);
        validateCard.parkCar(card);
    }else{
        MessageBox->setText(QString("%1").arg("Park car failed, please check your card!"));
    }
    freeArea->display(parkSystem.getFreeArea());
}
void ParkManagement::disposalExit(){
    if(leaveCardId.toInt()!=-1&&willingToLeaveCar->objectName().toInt()!=-1){
        Card card=Card(willingToLeaveCar->objectName());
        card.setCardStatus(true);
        if(validateCard.validateLeave(card)){
            parkSystem.exitCar();
            willingToLeaveCar->setStyleSheet("QPushButton{background:green;height:180px}");
            willingToLeaveCar->setText("");
            movementCar->setText("M");
            int takenPosition=validateCard.getTakenByCardId(willingToLeaveCar->objectName());
            if(takenPosition>=MAX_NUM_EACH_COLUMN){
                qDebug()<<"down";
                movementCar->setGeometry(RandomCar->pos().x()+willingToLeaveCar->pos().x()+160,RandomCar->pos().y()+98,80,130);
            }else{
                qDebug()<<"up";
                movementCar->setGeometry(RandomCar->pos().x()+willingToLeaveCar->pos().x()+160,RandomCar->pos().y()-162,80,130);
            }
            qDebug()<<QString("willingToLeaveCar name:%1").arg(willingToLeaveCar->objectName());
            qDebug()<<QString("taken position:%1").arg(takenPosition);
            qDebug()<<QString("willingToLeaveCar x:%1").arg(willingToLeaveCar->pos().x());
            qDebug()<<QString("RandomCar x:%1").arg(RandomCar->pos().x());
            movementCar->setVisible(true);
            movementCar->setStyleSheet("QPushButton{background:red;height:130px;width:80}");
            //leave animation
            int moveDistance=1100-77*((animationParkPosition%MAX_NUM_EACH_COLUMN)+1)-3*(animationParkPosition%MAX_NUM_EACH_COLUMN)-68;
            int scaleWidth=20;
            int scaleHeight=45;
            //willingToLeaveCar->setWindowFlags(Qt::WindowStaysOnTopHint);
            QPropertyAnimation *parkCarAnimation = new QPropertyAnimation(movementCar, "geometry");
            parkCarAnimation->setDuration(3000);
            parkCarAnimation->setKeyValueAt(0,QRect(movementCar->pos().x(), movementCar->pos().y(),80,130));
            parkCarAnimation->setKeyValueAt(0.1,QRect(movementCar->pos().x()+scaleWidth, movementCar->pos().y()+scaleHeight,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
            if(takenPosition>=MAX_NUM_EACH_COLUMN){
                parkCarAnimation->setKeyValueAt(0.4,QRect(movementCar->pos().x()+scaleWidth, movementCar->pos().y()+scaleHeight-140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
                parkCarAnimation->setKeyValueAt(1,QRect(movementCar->pos().x()+scaleWidth+moveDistance, movementCar->pos().y()+scaleHeight-140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
            }else{
                parkCarAnimation->setKeyValueAt(0.4,QRect(movementCar->pos().x()+scaleWidth, movementCar->pos().y()+scaleHeight+140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
                parkCarAnimation->setKeyValueAt(1,QRect(movementCar->pos().x()+scaleWidth+moveDistance, movementCar->pos().y()+scaleHeight+140,MOVE_SHAPE_SIZE,MOVE_SHAPE_SIZE));
            }
            Exit->setVisible(false);
            timer->start(4000);
            parkCarAnimation->setEasingCurve(QEasingCurve::InSine);
            parkCarAnimation->start();
            validateCard.leaveCar(card);
        }
    }else{
        willingToLeaveCar->setStyleSheet("QPushButton{background:red;height:180px}");
        leaveCardId=-1;
    }
    freeArea->display(parkSystem.getFreeArea());
}
void ParkManagement::ParkAnimationFinished(){
    if(animationParkPosition==-1)return;
    Card *card=new Card("AAAAAA");
    card->setTaken(animationParkPosition);
    card->setCardStatus(true);
    setTakenArea(*card);
}
void ParkManagement::randomCar(){
    randomCardId=randomGenerateCardId();
    RandomCar->setText(QString("%1").arg(randomCardId));
}
QString ParkManagement::randomGenerateCardId()
{
    int randNum=qrand() % 99;
    if(randNum<10){
        return QString("00000%1").arg(randNum);
    }else{
        return QString("0000%1").arg(randNum);
    }
}
void ParkManagement::disposalLeaveSelect(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    qDebug()<<btn->objectName();
    if(btn->objectName().toInt()!=-1){
        int temp=btn->objectName().toInt();
        leaveCardId=temp>=10?QString("0000%1").arg(temp):QString("00000%1").arg(temp);
        //btn->setStyleSheet("QPushButton{background:blue;height:180px}");
        willingToLeaveCar=btn;
    }
}
