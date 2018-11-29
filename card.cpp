#include "card.h"

Card::Card(QString cardId)
{
    this->cardId=cardId;
}
Card::Card()
{
    this->cardId="AAAAAA";
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
int Card::getTaken()
{
    return taken;
}
void Card::setTaken(int taken)
{
    this->taken=taken;
}
void Card::setCardID(QString cardId)
{
    this->cardId=cardId;
}
Card Card::operator=(Card card){
    Card newCard=Card();
    newCard.cardId=card.getCardID();
    newCard.cardStatus=card.getCardStatus();
    newCard.taken=card.getTaken();
    return newCard;
}
