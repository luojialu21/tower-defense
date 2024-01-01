#ifndef STARTFROM_H
#define STARTFROM_H

#include <QWidget>
#include "ui_startfrom.h"
#include "mainwindow.h"
#include<fstream>
using namespace std;
namespace Ui {
class startfrom;
}

class startfrom : public QWidget
{
    Q_OBJECT

public:
    explicit startfrom(QWidget *parent = nullptr);
    ~startfrom();
    void paintEvent(QPaintEvent*);

private:
    Ui::startfrom *ui;

};

#endif // STARTFROM_H
