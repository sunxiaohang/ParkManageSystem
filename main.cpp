#include "parkmanagement.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    ParkManagement w;
    w.show();
    return a.exec();
}
