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
    int randArea=qrand() % MAX_NUM_EACH_COLUMN*2;
    while(!validateRandomArea(randArea)){
        randArea=qrand() % MAX_NUM_EACH_COLUMN*2;
    }
    PARKAREA[randArea/MAX_NUM_EACH_COLUMN][randArea%MAX_NUM_EACH_COLUMN]=true;//park area has been taken
    freeCount--;
    return randArea;
}
int ParkSystem::randomExit()
{
    int randArea=qrand() % MAX_NUM_EACH_COLUMN*2;
    while(validateRandomTakenArea(randArea)){
        randArea=qrand() % MAX_NUM_EACH_COLUMN*2;
    }
    PARKAREA[randArea/MAX_NUM_EACH_COLUMN][randArea%MAX_NUM_EACH_COLUMN]=false;//park area has been taken
    freeCount++;
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
        return true;
    }else{
        return false;
    }
}
int ParkSystem::getFreeArea(){
    return freeCount;
}
