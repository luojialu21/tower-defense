#ifndef WUSHAUNG_H
#define WUSHAUNG_H
#include"mainwindow.h"
#include"leiwujie.h"
#include"route.h"
#include"hanghao.h"
#include<cmath>
#include<QMovie>
class MainWindow;
class leiwujie;
class route;
class hanghao;
inline bool arrivecorrect(QPoint p,int r,QPoint  p1,int r1)//达到这个点
{
    int x=p.x()-p1.x();
    int y=p.y()-p1.y();//(x,y)(x1,y1)
    double l=sqrt(x*x+y*y);//圆心距离小于半径和
    if(l<(r+r1))
        return true;
    else {
        return false;
    }

}
class wushaung:public QObject
{
    Q_OBJECT
private:
    float hp;//敌军血量
    float maxhp;//最大血量
    float speed;//敌军行动速度
    int damage;//敌军的攻击伤害
    bool alive;//当前士兵是不是活的
    bool canmove;
    bool lose_blood;//放血状态
    route*m_moveway;//按照之前的路线移动
    MainWindow*m;
    QTimer *t1;
    QPoint m_pos;//当前位置（图片左上角）
   QPixmap path;//图片存储路径
   QPixmap fix0;//闪现词缀
   QPixmap fix1;//加速词缀
    bool ice;
    QList<leiwujie*>attcker;//正在攻击这对敌人的雷无桀
    QList<hanghao*>attacker;//正在攻击这对敌人的夯昊
private slots:
    void makealive();//敌人是否活着，活着的敌人可以移动
public slots:
     void hurt(int h);//敌人受伤
public:
    wushaung(route*r,MainWindow*m,float hp, QPixmap s=QPixmap(":/images/single.png"));
    ~wushaung();
    void draw(QPainter*p) const;
    void makestop();
    void goahead();
    void move();//敌人移动
    int fixnum;//词缀0是闪现，1是神速
    QPoint getpos();//获取位置
    //void hurt(int h);//敌人受伤
    void setstate();//放血状态
    void setstateice();//冰冻状态
    void leave(leiwujie*l);//离开雷无桀攻击范围
    void leave(hanghao*h);
    void addattack(hanghao*h);
    void addattack(leiwujie*l);
};

#endif // WUSHAUNG_H
