#ifndef LSKILL_H
#define LSKILL_H
#include"mainwindow.h"
#include<QPropertyAnimation>

class wushaung;
class hanghao;
class lskill:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint cur READ getpos WRITE setpos)
private:
    QPoint cur;//火球当前位置
    QPoint tar;//无双士兵位置
    QPoint towpos;//雷无桀位置

    QPixmap path;//图片位置
   int leihurt;
    wushaung*wu;//目标敌人
    hanghao*hh;//目标夯昊
    MainWindow *m;

private slots:
    void hit();//打中敌人

public:
    lskill();
    lskill(QPoint towpos,QPoint tar,int hurt,wushaung*wu,MainWindow*m,QPixmap p);
    lskill(QPoint towpos,QPoint tar,int hurt,hanghao*hh,MainWindow*m,QPixmap p);
    QPoint getpos();//当前位置
    void setpos(QPoint p);
     int role;//0是雷无桀，1是萧瑟，2是无心
    QPoint gettar();
    int fix0,fix1;
    void setfix(int style,int style1);//词缀的位置和种类
    void move();//火球移动
    void draw(QPainter*painter);
};

#endif // LSKILL_H
