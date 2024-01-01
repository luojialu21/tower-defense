#ifndef HANGHAO_H
#define HANGHAO_H
#include"mainwindow.h"
#include"route.h"
#include"wushaung.h"
#include<QVector2D>
#include<QObject>
//近战攻击夯昊
bool arrivecorrect(QPoint p,int r,QPoint  p1,int r1);
class MainWindow;
class wushaung;
class hanghao:public QObject
{
    Q_OBJECT
private:
    float hp;//血量
    int speed;//行动速度
    int damage;//夯昊的攻击伤害
    bool alive;//当前是不是活的
    bool canmove;

    route*m_moveway;//按照之前的路线移动
    MainWindow*m;
    QTimer*time1;
    QPixmap skillpath;
    wushaung*wu;
    QPoint m_pos;//当前位置（图片左上角）
   QPixmap path;//图片存储路径
   QPixmap fix0,fix1;//词缀路径
private slots:
    void beginmove();//是否活着，活着的可以移动，没有遇到敌人的可以移动
    void h_shoot();
public:
   hanghao(route*r,MainWindow*m, QPixmap s=QPixmap(":/images/dog.png"));
    ~hanghao();
    void draw(QPainter*p) const;
    void move();//移动
     int fixnum;//词缀种类，0是狂暴，1是冰系，2是群伤
    QPoint getpos();//获取位置
    void hurt(int h);//受伤
    void check();//在不在攻击范围
    void remove();//这个敌人死亡了不需要发射技能
    wushaung*get();//正在攻击的敌人，一次只能攻击一个
};

#endif // HANGHAO_H




