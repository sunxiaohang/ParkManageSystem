#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
private:
    QString cardId=QString("%1").arg("000000");//six digital card id
    bool cardStatus=false;//true is parked, false is unparked
    int taken=-1;
public:
    QString getCardID();
    void setCardID(QString cardId);
    bool getCardStatus();
    void setCardStatus(bool status);
    int getTaken();
    void setTaken(int taken);
    Card operator=(const Card card);
    Card(QString cardId);
    Card();
};

#endif // CARD_H
