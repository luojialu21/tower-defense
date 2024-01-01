#include "wushaung.h"
wushaung::wushaung(route*r,MainWindow*m,float hp,QPixmap path):
    QObject (nullptr)
{
    this->path=path;
    this->m=m;
    this->hp=hp;
    maxhp=hp;
    speed=1;
    fixnum=-1;
    fix0=QPixmap(":/images/miss.png");
    fix1=QPixmap(":/images/speed.png");
    alive=false;
    ice=false;
    canmove=true;
    lose_blood=false;//放血状态
    m_pos=r->getPos();
    m_moveway=r->getnextpos();



}
void wushaung::setstateice()
{
    canmove=false;
    ice=true;
}
void wushaung::setstate()
{
    lose_blood=true;

}
void wushaung::makealive()
{
    alive=true;
}
void wushaung::makestop()
{
    canmove=false;
}

wushaung::~wushaung()
{
    attcker.clear();
    m_moveway=nullptr;
    m=nullptr;


}
void wushaung::addattack(leiwujie*l)
{
    attcker.push_back(l);
}
void wushaung::addattack(hanghao*h)
{
    attacker.push_back(h);
}

void wushaung::draw(QPainter*p) const
{
    if(alive==true)
    {
        p->save();
        if(fixnum==0)//闪现
        {
            p->drawPixmap(m_pos.x()-75,m_pos.y()-105,130,130,fix0);
            p->drawPixmap(m_pos.x()-35,m_pos.y()-105,130,130,fix0);
        }
        else if(fixnum==1)//加速
        {
            p->drawPixmap(m_pos.x()-90,m_pos.y()-120,160,160,fix1);
            p->drawPixmap(m_pos.x()-50,m_pos.y()-120,160,160,fix1);
        }
        if(lose_blood==true)//正在放血
        {
            QPixmap ps=QPixmap(":/images/hurt.png");
            p->drawPixmap(m_pos.x()-60,m_pos.y()-120,100,100,ps);
            p->drawPixmap(m_pos.x()-20,m_pos.y()-120,100,100,ps);
        }

        p->drawPixmap(m_pos.x()-30,m_pos.y()-120,40,90,path);
        p->drawPixmap(m_pos.x()+10,m_pos.y()-120,40,90,path);
        if(ice==true)//冰冻
        {
            QPixmap pss=QPixmap(":/images/ice.png");
            p->drawPixmap(m_pos.x()-125,m_pos.y()-210,300,300,pss);
        }
        p->setPen(QPen(QBrush(Qt::red),2,Qt::SolidLine));
        p->drawLine(m_pos+QPoint(20+hp/maxhp*20,-120),m_pos+QPoint(40,-120));
        p->drawLine(m_pos+QPoint(-15+hp/maxhp*20,-120),m_pos+QPoint(5,-120));

        p->setPen(QPen(QBrush(Qt::cyan),2,Qt::SolidLine));
        p->drawLine(m_pos+QPoint(20,-120),m_pos+QPoint(20+hp/maxhp*20,-120));
        p->drawLine(m_pos+QPoint(-15+hp/maxhp*20,-120),m_pos+QPoint(-15,-120));

        p->restore();


    }

}
void wushaung::move()
{
    if(alive==true&&ice==false&&(canmove==true||fixnum==0))//如果当前活着，并且有闪现功能活着没遇到夯昊
    {
        if(arrivecorrect(m_pos,1,m_moveway->getPos(),1)==true)//到了指定点的位置
    {
        if(m_moveway->getnextpos()!=nullptr)//下一个位置
        {
            m_pos=m_moveway->getPos();
           m_moveway=m_moveway->getnextpos();
        }
        else//到达终点
        {
            m->hurt();
            m->remove(this);
            return;
        }
    }
        else {//在移动的路上
            if(fixnum==1)//加速功能
                speed=2;
            if(lose_blood==true)
                hurt(1);
        QPoint next=m_moveway->getPos();

        QVector2D normalized(next-m_pos);
       normalized.normalize();
       m_pos=m_pos+normalized.toPoint()*speed;//建立坐标系，原来的坐标按照斜率增减
        }
    }

}
void wushaung::goahead()
{
    if(ice==false)
        canmove=true;
}
void wushaung::hurt(int h)
{
    hp=hp-h;
    if(hp<=0)//当前士兵死亡
    {
        for(int i=0;i<attcker.length();++i)
        {
            attcker[i]->remove();
        }
        for(int i=0;i<attacker.length();++i)
        {
            attacker[i]->remove();
        }
        this->m->remove(this);
    }
}

void wushaung::leave(leiwujie *l)
{
    attcker.removeOne(l);//出了攻击区域
}
void wushaung::leave(hanghao *h)//出了夯昊攻击区域
{
    attacker.removeOne(h);
    h=nullptr;
}
QPoint wushaung::getpos()
{
    return m_pos;
}

