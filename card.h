#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
private:
    QString cardId=QString("%1").arg("000000");//six digital card id
    bool cardStatus=false;//true is parked, false is unparked
public:
    QString getCardID();
    bool getCardStatus();
    void setCardStatus(bool status);
    Card(QString cardId);
};

#endif // CARD_H
