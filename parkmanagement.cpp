#include "parkmanagement.h"
#include "ui_parkmanagement.h"

ParkManagement::ParkManagement(QWidget *parent) :QMainWindow(parent),ui(new Ui::ParkManagement){
    ui->setupUi(this);
}

ParkManagement::~ParkManagement(){
    delete ui;
}
