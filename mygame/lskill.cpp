#include "lskill.h"
#include<QLabel>
#include<QMovie>
lskill::lskill()
{

}
lskill::lskill(QPoint towpos,QPoint tar,int hurt,wushaung*wu,MainWindow*m,QPixmap path)
{
    this->wu=wu;
    this->m=m;
    this->hh=nullptr;
    this->path=path;
    this->tar=tar;
   fix0=-1;fix1=-1;
    this->towpos=towpos;
    this->leihurt=hurt;
    this->cur=towpos;
}
lskill::lskill(QPoint towpos,QPoint tar,int hurt,hanghao*hh,MainWindow*m,QPixmap path)
{
    this->wu=nullptr;
    this->m=m;
    this->hh=hh;
    this->path=path;
    this->tar=tar;
    this->fix0=-1;
    this->fix1=-1;
    this->role=-1;
    this->towpos=towpos;
    this->leihurt=hurt;
    this->cur=towpos;
}

QPoint lskill::gettar()
{
    return tar;
}
void lskill::setfix(int style, int style1)
{
        fix0=style;
        fix1=style1;

}
void lskill::hit()
{
   int random=rand()%18;
    if(random==1&&(fix0==1||fix1==1))
    {
        QApplication::processEvents(QEventLoop::AllEvents);
        QLabel*label=new QLabel(m);
        QMovie*movie;
        label->setGeometry(tar.x()-180,tar.y()-280,400,400);
        if(role==0)
             movie=new QMovie(":/images/lei.gif");
        else if(role==1)
            movie=new QMovie(":/images/xiao.gif");
        else {
            movie=new QMovie(":/images/wu.gif");
        }
        label->setMovie(movie);
        movie->start();
        label->show();
        QObject::connect(movie, &QMovie::frameChanged, [=](int frameNumber) {
            // GIF 动画执行一次就结束
            if (frameNumber == movie->frameCount() - 1) {
                movie->stop();
                label->clear();
                delete label;
                delete movie;
            }
        });
     }
    if(fix0==3)//狂暴
        leihurt=leihurt*2;
    if(fix1==3)//狂暴
        leihurt=leihurt*2;
    if(m->getenemy().indexOf(wu)!=-1)
    {
        if(fix1==0||fix0==0)//放血
        {
            wu->setstate();
        }
        if(fix1==2||fix0==2)
        {
            wu->setstateice();
        }
            wu->hurt(leihurt);
    }
    if(hh!=nullptr)
        hh->hurt(leihurt);
    m->removels(this);
}
void lskill::move()
{
    QPropertyAnimation *ani=new QPropertyAnimation(this,"cur");
    ani->setDuration(300);
    ani->setStartValue(towpos);
    ani->setEndValue(tar);
     connect(ani,SIGNAL(finished()),this,SLOT(hit()));
    ani->start();

}
void lskill::draw(QPainter*painter)
{
    painter->drawPixmap(cur.x()-50,cur.y()-100,120,120,path);

}
QPoint lskill::getpos()
{
    return cur;
}
void lskill::setpos(QPoint q)
{
    cur=q;
}
