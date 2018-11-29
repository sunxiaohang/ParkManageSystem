#ifndef PARKSYSTEM_H
#define PARKSYSTEM_H
#define MAX_NUM_EACH_COLUMN 10
#include <QTime>
#include "card.h"
class ParkSystem
{
private:
    bool PARKAREA[2][MAX_NUM_EACH_COLUMN]={{false}};
    int freeCount=MAX_NUM_EACH_COLUMN*2;
    bool entenceFlag=false;//true is open
    bool exitFlag=false;// true is open
public:
    int randomSelect();
    int randomExit();
    void setParkArea(Card card);
    int getFreeArea();
    bool getEntenceFlag();
    bool getExitFlag();
    void setEntenceFlag(bool flag);
    void setParkAreaArray(Card *cardList);
    void setExitFlag(bool flag);
    void exitCar();
    bool validateRandomArea(int position);
    bool validateRandomTakenArea(int position);
    ParkSystem();
};

#endif // PARKSYSTEM_H
