#include "card.h"

Card::Card(QString cardId)
{
    this->cardId=cardId;
}
QString Card::getCardID()
{
    return cardId;
}
bool Card::getCardStatus()
{
    return cardStatus;
}
void Card::setCardStatus(bool status)
{
    this->cardStatus=status;
}
