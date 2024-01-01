#include "hanghao.h"
hanghao::hanghao(route*r,MainWindow*m,QPixmap path):
    QObject (nullptr)
{
    this->path=path;
    this->m=m;
    hp=266;
    speed=1;
    damage=10;
    alive=false;
    fixnum=-1;
    m_pos=r->getPos();
    canmove=true;
    fix0=QPixmap(":/images/kuangbao.png");
    fix1=QPixmap(":/images/ice.png");

    m_moveway=r->getnextpos();
    wu=nullptr;
    time1=new QTimer(this);
    connect(time1,SIGNAL(timeout()),this,SLOT(h_shoot()));
    skillpath=QPixmap(":/images/hskill.png");
}
void hanghao::beginmove()
{
    alive=true;
}
hanghao::~hanghao()
{

    m_moveway=nullptr;
    m=nullptr;
    delete time1;
    wu=nullptr;
    time1=nullptr;
}

void hanghao::draw(QPainter*p) const
{
    if(alive==true)
    {
        p->save();
        p->drawPixmap(m_pos.x()-170,m_pos.y()-180,300,300,path);
        if(fixnum==0)//狂暴
            p->drawPixmap(m_pos.x()-245,m_pos.y()-225,500,500,QPixmap(":/images/kuangbao.png"));
        p->setPen(QPen(QBrush(Qt::red),4,Qt::SolidLine));
        p->drawLine(m_pos+QPoint(-15,-70),m_pos+QPoint(25,-70));
        p->setPen(QPen(QBrush(Qt::cyan),4,Qt::SolidLine));
       p->drawLine(m_pos+QPoint(-15,-70),m_pos+QPoint(-15+1.00000*hp/266.0000*40.0000,-70));
        p->restore();

    }

}
wushaung*hanghao::get()
{

    return wu;

}
void hanghao::move()
{
    if(alive==true&&canmove==true)
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
            m->removehanghao(this);
            return;
        }
    }
    else {//在移动的路上
        QPoint next=m_moveway->getPos();

        QVector2D normalized(next-m_pos);
       normalized.normalize();
       m_pos=m_pos+normalized.toPoint()*speed;//建立坐标系，原来的坐标按照斜率增减
    }}

}
void hanghao::hurt(int h)
{
    hp=hp-h;
    if(hp<=0)//当前近战单位死亡
    {
        if(wu!=nullptr)
        {
            wu->goahead();
            wu->leave(this);
        }
        m->removehanghao(this);
    }

}

QPoint hanghao::getpos()
{
    return m_pos;
}
void hanghao::check()
{
    if(wu==nullptr)//有敌人在夯昊射程
    {
        int flag=0;
        QList<wushaung*>wus=m->getenemy();//全部的敌人
        for(int i=0;i<wus.length();++i)
        {
            if(arrivecorrect(m_pos,80,wus[i]->getpos(),1)==true)
            {
                flag=1;
                this->wu=wus[i];
                time1->start(1000);
                this->wu->addattack(this);
                wu->makestop();
                this->canmove=false;
                break;
            }
        }
        if(flag==0)
        {
            this->canmove=true;
        }
    }
}
void hanghao::h_shoot()
{
    lskill*ls=new lskill(m_pos,wu->getpos(),10,wu,m,skillpath);
    if(fixnum==0)//狂暴
        ls->setfix(0,3);
    ls->move();
    lskill*lss=new lskill(wu->getpos(),m_pos,30,this,m,QPixmap(":/images/hitdog.png"));
    lss->move();
    m->launch(lss);
    m->launch(ls);//私有成员类外不能访问，传进去在mainwindow里面添加
}
void hanghao::remove()
{
   wu=nullptr;
   time1->stop();
}
