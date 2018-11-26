#ifndef PARKMANAGE_H
#define PARKMANAGE_H
#include "parkmanagement.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#define MAX_NUM_EACH_COLUMN 10
namespace Ui {
class ParkManagement;
class parkmanage;
}
class parkmanage
{
public:
    parkmanage();
private:
    QHBoxLayout *parkAreaUp;
    QHBoxLayout *parkAreaDown;
    bool parkCheck[2][MAX_NUM_EACH_COLUMN];
    QPushButton *Entence;
    QPushButton *Exit;
    QPushButton *entenceVerify;
    QPushButton *exitVerify;
    QLCDNumber *freeArea;
};

#endif // PARKMANAGE_H
