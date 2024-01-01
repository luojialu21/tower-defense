#ifndef LEIWUJIE_H
#define LEIWUJIE_H
#include<QTimer>
#include"mainwindow.h"
class MainWindow;
class mycamp;
class wushaung;
class leiwujie:public QObject
{
    Q_OBJECT
protected:
    QPoint m_pos;//位置
    int r;//攻击半径
    MainWindow*m;
    wushaung*wu;
    QTimer*time1;
    QPixmap path;
    QPixmap fix_path[4];
    QPixmap skillpath;
private slots:
    void shoot();
public:
    leiwujie();
    int fix0,fix1;
    leiwujie(QPoint pos,MainWindow*m,QPixmap path,int r,QPixmap sp);
    ~leiwujie();
    void setfix(int style,int pos);//词缀，0是放血，1是群攻，2是冰冻，3是狂暴
    void check();//在不在攻击范围
    void remove();//这个敌人死亡了不需要发射技能
    wushaung*get()
    {
        return wu;
    }
    void draw(QPainter*p) const;
};
#endif
