#include "route.h"

route::route(QPoint p)
{
    my_pos=p;
    my_nextpos=NULL;
}
void route::nextpos(route *nextpos)
{
    this->my_nextpos=nextpos;
}
route*route::getnextpos()//下一个像素点
{
    return my_nextpos;
}
QPoint route::getPos()//当前像素点
{
    return my_pos;
}
/*void route::draw(QPainter *painter)//画出敌方前进路线
{
    painter->save();
   painter->setPen(Qt::red);
    painter->drawEllipse(my_pos,5,5);//前进路线点画出来

    if(my_nextpos)
    {
        painter->drawLine(my_pos,my_nextpos->getPos());//连线

   }
    painter->restore();
}*/
