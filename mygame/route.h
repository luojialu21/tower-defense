#ifndef ROUTE_H
#define ROUTE_H
#include<QPoint>
#include<QPainter>

//用来让敌军按照这些点移动的类

class route
{
private:
    route*my_nextpos;//下一个点
    QPoint my_pos;//当前点

public:
    route(QPoint pos);
    void nextpos(route*nextpos);//下一个点
    route*getnextpos();
    QPoint getPos();
};

#endif // ROUTE_H
