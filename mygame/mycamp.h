#ifndef MYCAMP_H
#define MYCAMP_H

#include"leiwujie.h"
#include"rolechoice.h"
class leiwujie;
class rolechoice;
class mycamp
{
private:
    QPoint m_pos;//中心点
    QString m_path;//图片路径
   rolechoice*r;

public:
    mycamp(QPoint pos,QString path=(":/images/towerpos.png"));
    QPoint getmypos();//中心点
    leiwujie*lei;//在这个位置的防御塔
    void draw(QPainter*painter) const;
    void setmycamp(bool e);//我方有人攻击之后这个变成true
    bool exist();//有没有我方
    bool clickin(QPoint p);//玩家点击是否合法
    bool m_exist;
    bool choiceexist;
    void makechoice(rolechoice*r);
    rolechoice*get();//获得选择框

};

#endif // MYCAMP_H
