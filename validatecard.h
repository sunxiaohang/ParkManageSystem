#ifndef VALIDATECARD_H
#define VALIDATECARD_H
#include "card.h"
#include <QtSql>
#define MAX_NUM_EACH_COLUMN 10
class ValidateCard
{
private:
    QSqlDatabase dbConn;
    QSqlQuery query;
    Card InitialPark[MAX_NUM_EACH_COLUMN*2];
public:
    ValidateCard();
    bool parkCar(Card card);
    bool leaveCar(Card card);
    bool validatePark(Card card);
    bool validateLeave(Card card);
    int getTakenByCardId(QString cardId);
    Card* initialDataSource();
};

#endif // VALIDATECARD_H
