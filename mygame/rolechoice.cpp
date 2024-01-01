#include "rolechoice.h"

rolechoice::rolechoice(QPoint pos,MainWindow*m,QPixmap px)
{
    this->pos=pos;
    this->m=m;
    this->px=px;
}

rolechoice::~rolechoice()
{
   m=nullptr;
}
void rolechoice::remove()//选择完要移除框
{
    m->removechoice(this);
}
QPoint rolechoice::getpos()
{
    return pos;
}
void rolechoice::draw(QPainter*p)
{

    p->drawPixmap(pos.x()-10,pos.y()-30,70,40,px);

}
bool rolechoice::clickin(QPoint p)
{
    if((pos.x()<(p.x()+70))&&(pos.x()>(p.x()-15))&&(pos.y()<(p.y()+35))&&(pos.y()>(p.y()-15)))
            return true;
    else
            return false;
}
