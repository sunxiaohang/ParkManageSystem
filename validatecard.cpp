#include "validatecard.h"
#include <iostream>
#include <parksystem.h>
using namespace std;

ValidateCard::ValidateCard()
{
    //initial mysql datesource profile
    dbConn=QSqlDatabase::addDatabase("QSQLITE");
    dbConn.setDatabaseName("db_parkid");
    qDebug()<<dbConn.open();
    query=QSqlQuery(dbConn);
    //initial database
//    query.exec("drop table if exists table_card;");
//    query.exec("create table table_card(cardId varchar(6) not null primary key,cardStatus bool not null default false,taken int default -1);");
//    for(int i=0;i<10;i++){
//        query.exec("insert into table_card values ('00000"+QString("%1").arg(i)+"',false,-1);");
//    }
//    for(int i=10;i<40;i++){
//        query.exec("insert into table_card values ('0000"+QString("%1").arg(i)+"',false,-1);");
//    }
    //initial date source form database
}
Card* ValidateCard::initialDataSource(){
    QString detectiveDataSource="select * from table_card";
    query.exec(detectiveDataSource);
    int position=0;
    while(query.next()){
        if(query.value(1).toBool()==true){
            int cardId=query.value(0).toInt();
            QString cardIdString;
            if(cardId>=10)cardIdString=QString("0000%1").arg(cardId);
            else cardIdString=QString("00000%1").arg(cardId);
            InitialPark[position].setCardID(cardIdString);
            InitialPark[position].setCardStatus(query.value(1).toBool());
            InitialPark[position].setTaken(query.value(2).toInt());
            position++;
        }
    }
    InitialPark[position].setCardID("ZZZZZZ");
    InitialPark[position].setCardStatus(false);
    InitialPark[position].setTaken(-100);
    qDebug()<<QString("get test of =:%1").arg(InitialPark[position].getTaken());
    return InitialPark;
}
bool ValidateCard::parkCar(Card card){
    QString parkCarQuery="update table_card set cardStatus=true,taken="+QString("%1").arg(card.getTaken())+" where cardId=\""+card.getCardID()+"\"";
    query.exec(parkCarQuery);
    return true;
}
bool ValidateCard::leaveCar(Card card){
    QString leaveCarQuery="update table_card set cardStatus=false,taken=-1 where cardId=\""+card.getCardID()+"\"";
    query.exec(leaveCarQuery);
    return true;
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
    qDebug()<<RealCardId;
    if(RealCardId==card.getCardID()&&RealCardStatus==card.getCardStatus())
    {
        return true;
    }else{
        return false;
    }
}
int ValidateCard::getTakenByCardId(QString cardId){
    QString validateCardQuery="select * from table_card where cardId=\""+cardId+"\"";
    qDebug()<<validateCardQuery;
    query.exec(validateCardQuery);
    int position=-1;
    while(query.next()){
        qDebug()<<QString("position : %1").arg(position);
        position=query.value(2).toInt();
    }
    return position;
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
