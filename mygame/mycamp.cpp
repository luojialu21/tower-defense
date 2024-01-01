#include "mycamp.h"

mycamp::mycamp(QPoint pos,QString path)
{
    m_pos=pos;
    m_path=path;
    lei=nullptr;
    m_exist=false;
    choiceexist=false;
}
void mycamp::makechoice(rolechoice *r)
{
    this->r=r;
}
bool mycamp::exist()//是否有我方人员
{
    return m_exist;
}

QPoint mycamp::getmypos()
{
    return m_pos;
}
void mycamp::draw(QPainter *painter)const//在像素点放置石台
{

    painter->drawPixmap(m_pos.x(),m_pos.y(),m_path);
     painter->drawPixmap(m_pos.x()-15,m_pos.y()+28,m_path);
      painter->drawPixmap(m_pos.x()+15,m_pos.y()+28,m_path);

}
 bool mycamp:: clickin(QPoint p)//玩家点击是否合法
 {
     if(p.x()>m_pos.x()-30&&p.x()<m_pos.x()+30)
     {
         if(p.y()>m_pos.y()-30&&p.y()<m_pos.y()+30)
             return true;
         else {
             return false;
         }
     }
     else {
         return false;
     }
 }
 rolechoice*mycamp::get()
 {
     return r;
 }
void mycamp::setmycamp(bool e)
{
    m_exist=e;
}
