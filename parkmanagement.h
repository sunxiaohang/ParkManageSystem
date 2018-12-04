#ifndef PARKMANAGEMENT_H
#define PARKMANAGEMENT_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include "validatecard.h"
#include "parksystem.h"
#include <QTimer>
#include <QLabel>
#include <QPainter>

#define MAX_NUM_EACH_COLUMN 10
#define MOVE_SHAPE_SIZE 40

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
    QPushButton *RandomCar;
    QString randomCardId;
    QString leaveCardId;
    QPushButton *willingToLeaveCar;
    QPushButton *movementCar;
    QLabel *MessageBox;
    void init();
    void restoreSqlDate();
    void userInterface();
    void automaticRun();
    void setTempTakenArea(int position);
    void setTakenArea(Card card);
    QString randomGenerateCardId();
    int animationParkPosition;
signals:
    void randomCarSignals();
    void verifyEntenceSignals();
    void verifyExitSignals();
    void selectExitCarSignals();
public slots:
    void timeDone();
    void randomTimerEntenceDone();
    void randomTimerExitDone();
    void randomCar();
    void disposalEntence();
    void disposalExit();
    void ParkAnimationFinished();
    void disposalLeaveSelect();
private:
    Ui::ParkManagement *ui;
    ValidateCard validateCard;
    ParkSystem parkSystem;
    QTimer *timer;
    QTimer *randomTimerEntence;
    QTimer *randomTimerExit;
    QPushButton *buttonArray[2][MAX_NUM_EACH_COLUMN];
    int initialGeometryX;
    int initialGeometryY;
};

#endif // PARKMANAGEMENT_H
