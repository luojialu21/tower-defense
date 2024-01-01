#ifndef ROLECHOICE_H
#define ROLECHOICE_H
#include"mainwindow.h"
class MainWindow;
class rolechoice
{
private:
    MainWindow*m;
    QPoint pos;
    QPixmap px;
public:
    rolechoice(QPoint pos,MainWindow*m,QPixmap px=QPixmap(":/images/select.jpg"));
    ~rolechoice();
    void remove();//选择完要移除框
    void draw(QPainter*p);
    QPoint getpos();
    bool clickin(QPoint p);
};

#endif // ROLECHOICE_H
