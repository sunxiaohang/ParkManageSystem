#ifndef VALIDATECARD_H
#define VALIDATECARD_H
#include "card.h"
#include <QtSql>

class ValidateCard
{
private:
    QSqlDatabase dbConn;
    QSqlQuery query;
public:
    ValidateCard();
    bool parkCar(Card card);
    bool leaveCar(Card card);
    bool validatePark(Card card);
    bool validateLeave(Card card);
};

#endif // VALIDATECARD_H
