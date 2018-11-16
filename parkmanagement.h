#ifndef PARKMANAGEMENT_H
#define PARKMANAGEMENT_H

#include <QMainWindow>

namespace Ui {
class ParkManagement;
}

class ParkManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParkManagement(QWidget *parent = nullptr);
    ~ParkManagement();

private:
    Ui::ParkManagement *ui;
};

#endif // PARKMANAGEMENT_H
