#include "parksystem.h"
#include <iostream>
using namespace std;
ParkSystem::ParkSystem()
{
    //initial qsrand function
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}
int ParkSystem::randomSelect()
{
    int randArea=qrand() % (MAX_NUM_EACH_COLUMN*2);
    while(!validateRandomArea(randArea)){
        randArea=qrand() % (MAX_NUM_EACH_COLUMN*2);
    }
    PARKAREA[randArea/MAX_NUM_EACH_COLUMN][randArea%MAX_NUM_EACH_COLUMN]=true;//park area has been taken
    freeCount--;
    return randArea;
}
int ParkSystem::randomExit()
{
    int randArea=qrand() % (MAX_NUM_EACH_COLUMN*2);
    while(!validateRandomTakenArea(randArea)){
        randArea=qrand() % (MAX_NUM_EACH_COLUMN*2);
    }
    PARKAREA[randArea/MAX_NUM_EACH_COLUMN][randArea%MAX_NUM_EACH_COLUMN]=false;//park area has been taken
    return randArea;
}
bool ParkSystem::validateRandomArea(int position){
    if(PARKAREA[position/MAX_NUM_EACH_COLUMN][position%MAX_NUM_EACH_COLUMN]==true){
        cout<<"this park area has been taken,please try again!"<<endl;
        return false;
    }else{
        return true;
    }
}
bool ParkSystem::validateRandomTakenArea(int position){
    if(PARKAREA[position/MAX_NUM_EACH_COLUMN][position%MAX_NUM_EACH_COLUMN]==true){
        cout<<"this park has no car taken,please try again!"<<endl;
        return true;
    }else{
        return false;
    }
}
int ParkSystem::getFreeArea(){
    return freeCount;
}
void ParkSystem::setEntenceFlag(bool flag){
    this->entenceFlag=flag;
}
void ParkSystem::setExitFlag(bool flag){
    this->exitFlag=flag;
}
bool ParkSystem::getEntenceFlag(){
    return entenceFlag;
}
bool ParkSystem::getExitFlag(){
    return exitFlag;
}
void ParkSystem::setParkArea(Card card){
    int position=card.getTaken();
    int column=position/MAX_NUM_EACH_COLUMN;
    int offset=position%MAX_NUM_EACH_COLUMN;
    PARKAREA[column][offset]=true;
    if(position>=0&&position<=MAX_NUM_EACH_COLUMN*2){
        freeCount--;
    }
}
void ParkSystem::setParkAreaArray(Card* cardList){
    for(int i=0;i<2*MAX_NUM_EACH_COLUMN;i++){
        if(cardList[i].getTaken()==-100||cardList[i].getCardID()=="ZZZZZZ")break;
        setParkArea(cardList[i]);
    }
}
void ParkSystem::exitCar(){
    freeCount++;
}
