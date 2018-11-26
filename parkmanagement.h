#ifndef PARKMANAGEMENT_H
#define PARKMANAGEMENT_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include "validatecard.h"
#include "parksystem.h"
#include <QTimer>

#define MAX_NUM_EACH_COLUMN 10

namespace Ui {
class ParkManagement;
class parkmanage;
class ValidateCard;
class Card;
}

class ParkManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParkManagement(QWidget *parent = nullptr);
//    ~ParkManagement();
    QHBoxLayout *parkAreaUp;
    QHBoxLayout *parkAreaDown;
    QPushButton *Entence;
    QPushButton *Exit;
    QPushButton *entenceVerify;
    QPushButton *exitVerify;
    QLCDNumber *freeArea;
    void init();
    void userInterface();
    void setTakenArea(int position);
public slots:
    void timeDone();
private:
    Ui::ParkManagement *ui;
    ValidateCard validateCard;
    ParkSystem parkSystem;
    QTimer *timer;
    QPushButton *buttonArray[2][MAX_NUM_EACH_COLUMN];
};

#endif // PARKMANAGEMENT_H
