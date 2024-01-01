#include "leiwujie.h"

leiwujie::~leiwujie()
{
    delete m;
    delete time1;
    delete wu;
    m=nullptr;
    wu=nullptr;
    time1=nullptr;
}
leiwujie:: leiwujie(QPoint pos,MainWindow*m,QPixmap path,int r,QPixmap sp)
{
    m_pos=pos;
    this->r=r;
    this->m=m;
    skillpath=sp;
    wu=nullptr;
    fix0=-1,fix1=-1;
    this->path=path;
    fix_path[0]=QPixmap(":/images/ffix.png");
    fix_path[1]=QPixmap(":/images/qfix.png");
    fix_path[2]=QPixmap(":/images/bfix.png");
    fix_path[3]=QPixmap(":/images/kfix.png");
    time1=new QTimer(this);
    connect(time1,SIGNAL(timeout()),this,SLOT(shoot()));


}
void leiwujie::draw(QPainter *p) const
{
    p->drawPixmap(m_pos.x()-35,m_pos.y()-105,100,140,path);
    if(fix0!=-1)
    {
        p->drawPixmap(m_pos.x()-20,m_pos.y()+26,41,41,fix_path[fix0]);
    }
    if(fix1!=-1)
    {
        p->drawPixmap(m_pos.x()+14,m_pos.y()+26,41,41,fix_path[fix1]);
    }
}

void leiwujie::check()
{
    if(wu!=nullptr)//有敌人在雷无桀射程
    {
        QVector2D normalized(wu->getpos()-m_pos);
        normalized.normalize();
        if(arrivecorrect(m_pos,r,wu->getpos(),1)==false)//一次打一对敌人，这对敌人出了射程
        {
            wu->leave(this);
            wu=nullptr;
           time1->stop();
        }
    }
    else {
        QList<wushaung*>wus=m->getenemy();//全部的敌人
        for(int i=0;i<wus.length();++i)
        {
            if(arrivecorrect(m_pos,r,wus[i]->getpos(),1)==true)
            {
                this->wu=wus[i];
               time1->start(800);
                this->wu->addattack(this);
                break;
            }
        }
    }
}
void leiwujie::setfix(int num,int pos)
{
    if(pos==0)
        fix0=num;
    if(pos==1)
        fix1=num;
}
void leiwujie::shoot()
{

    lskill*ls=new lskill(m_pos,wu->getpos(),16,wu,m,skillpath);
    if(r==180)//雷无桀
    {
        ls->role=0;
    }
    else if(r==240)//萧瑟
        ls->role=1;
    else if(r==300)//无心
        ls->role=2;
    ls->setfix(fix0,fix1);
    ls->move();
    m->launch(ls);//私有成员类外不能访问，传进去在mainwindow里面添加


}
void leiwujie::remove()
{
   wu=nullptr;
   time1->stop();
}

