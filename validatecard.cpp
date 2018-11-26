#include "validatecard.h"
#include <iostream>
using namespace std;

ValidateCard::ValidateCard()
{
    //initial mysql datesource profile
    QPluginLoader loader;
    loader.setFileName("/usr/lib/qt/plugins/sqldrivers/libqsqlmysql.so");
    qDebug()<<loader.load();
    dbConn=QSqlDatabase::addDatabase("QODBC");
    dbConn.setHostName("localhost");
    dbConn.setPort(3306);
    dbConn.setDatabaseName("db_parkid");
    dbConn.setUserName("root");
    dbConn.setPassword("admin");
    dbConn.open();
    query=(QSqlQuery)dbConn;
}
bool ValidateCard::parkCar(Card card){
    QString parkCarQuery="update table_card set cardStatus=true where cardId=\""+card.getCardID()+"\"";
    if(validatePark(card)){
        query.exec(parkCarQuery);
        return true;
    }else{
        return false;
    }
}
bool ValidateCard::leaveCar(Card card){
    QString leaveCarQuery="update table_card set cardStatus=false where cardId=\""+card.getCardID()+"\"";
    if(validateLeave(card)){
        query.exec(leaveCarQuery);
        return true;
    }else{
        return false;
    }
}
bool ValidateCard::validatePark(Card card){
    QString validateCardQuery="select * from table_card where cardId=\""+card.getCardID()+"\"";
    query.exec(validateCardQuery);
    QString RealCardId;
    bool RealCardStatus=false;
    while(query.next()){
        RealCardId=query.value(0).toString();
        RealCardStatus=query.value(1).toBool();
    }
    if(RealCardId==card.getCardID()&&RealCardStatus==card.getCardStatus())
    {
        return true;
    }else{
        return false;
    }
}
bool ValidateCard::validateLeave(Card card){
    QString validateCardQuery="select * from table_card where cardId=\""+card.getCardID()+"\"";
    query.exec(validateCardQuery);
    QString RealCardId;
    bool RealCardStatus=true;
    while(query.next()){
        RealCardId=query.value(0).toString();
        RealCardStatus=query.value(1).toBool();
    }
    if(RealCardId==card.getCardID()&&RealCardStatus==card.getCardStatus())
    {
        return true;
    }else{
        return false;
    }
}
