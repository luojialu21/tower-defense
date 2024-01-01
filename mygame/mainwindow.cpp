#include "mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include<fstream>
using namespace std;
MainWindow::MainWindow(double height,double width,QWidget *parent):
     QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->height=height;
    this->width=width;
    mycamppos1();
    hp=1;
    m_waves=0;
    m_fix=-1;
    chivalrous=300;
    win=false;
    kfix=0;bfix=0;ffix=0;qfix=0;
    lose=false;
    connect(ui->pushButton,&QPushButton::clicked,[=]()//放血
    {
        if(ffix>0)
            m_fix=0;
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=]()mutable//群攻
    {
        if(qfix>0)
            m_fix=1;
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=]()//冰冻
    {
        if(bfix>0)
            m_fix=2;
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=]()//狂暴
    {
        if(kfix>0)
            m_fix=3;
    });
    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(20);
    QTimer::singleShot(200,this,SLOT(enemyarrive()));


    QTimer::singleShot(200,this,SLOT(hanghaoarrive()));
}
void MainWindow::setPath(QPixmap path)
{
    m_path=path;
}
MainWindow:: ~MainWindow()
{
    delete ui;
   m_camp.clear();
     qDeleteAll(m_leiwujie);
       qDeleteAll(m_wu);
         qDeleteAll(m_h);
           qDeleteAll(ls);
             qDeleteAll(rc);

}
void MainWindow::drawfix(QPainter *p)
{
    p->save();

    p->setPen(QPen(QBrush(Qt::white),2,Qt::SolidLine));
    p->drawText(304,704,QString("%1").arg(ffix));
    p->drawText(377,704,QString("%1").arg(qfix));
    p->drawText(450,704,QString("%1").arg(bfix));
    p->drawText(523,704,QString("%1").arg(kfix));
    p->restore();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,height,width,this->m_path);//背景
    for(int i=0;i<m_camp.length();++i)
        m_camp[i].draw(&painter);//防御塔的位置
    for(int i=0;i<m_leiwujie.length();++i)
        m_leiwujie[i]->draw(&painter);//雷无桀
    for(int i=0;i<m_wu.length();++i)
       m_wu[i]->draw(&painter);//敌人
    for(int i=0;i<m_h.length();++i)
        m_h[i]->draw(&painter);//夯昊（近战单位）
    for(int i=0;i<ls.length();++i)
        ls[i]->draw(&painter);//雷无桀火球
    for(int i=0;i<rc.length();++i)
        rc[i]->draw(&painter);
    if(lose==true)
    {
        QPixmap s=QPixmap(":/images/lose.jpg");
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
       painter.drawPixmap(0,0,1240,720,s);
       return;
    }
    else if(win==true)
    {
        QPixmap s=QPixmap(":/images/end.jpg");
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        painter.drawPixmap(0,0,1240,720,s);
        return;
    }
    drawfix(&painter);

}
void MainWindow::launch(lskill *s)
{
    ls.push_back(s);
}
void MainWindow::setroute1()//自定义地图中设置敌人行动路径
{
    int x,y;
    string s;
    ifstream f;
    f.open("map.txt",ios::in);
    getline(f,s);
   while(f>>x)
   {
       f>>y;
       route*r1=new route(QPoint(x,y));
       if(m_route.size()!=0)
           m_route[m_route.size()-1]->nextpos(r1);
       m_route.push_back(r1);
   }
   f.close();
}
void MainWindow::sethanghaoroute1()//自定义地图设置敌人行动路径
{
    int x,y;
    string s;
    ifstream f;
    f.open("maph.txt",ios::in);
   while(f>>x)
   {
       f>>y;
       route*r1=new route(QPoint(x,y));
       if(h_route.size()!=0)
           h_route[h_route.size()-1]->nextpos(r1);
       h_route.push_back(r1);
   }
   f.close();
}
void MainWindow::hanghao_route1()
{
    route*r1=new route(QPoint(1050,250));
    h_route.push_back(r1);

    route*r2=new route(QPoint(1160,350));
    r1->nextpos(r2);
    h_route.push_back(r2);

    route*r3=new route(QPoint(1130,550));
    r2->nextpos(r3);
    h_route.push_back(r3);

    route*r4=new route(QPoint(930,620));
    r3->nextpos(r4);
    h_route.push_back(r4);

    route*r5=new route(QPoint(760,580));
    r4->nextpos(r5);
    h_route.push_back(r5);

    route*r6=new route(QPoint(520,320));
    r5->nextpos(r6);
    h_route.push_back(r6);

    route*r7=new route(QPoint(680,100));
    r6->nextpos(r7);
    h_route.push_back(r7);
}
//第一关的敌人路线像素点
void MainWindow::route1()
{

    route*r1=new route(QPoint(680,100));
    m_route.push_back(r1);

    route*r2=new route(QPoint(520,320));
    r1->nextpos(r2);
    m_route.push_back(r2);

    route*r3=new route(QPoint(760,580));
    r2->nextpos(r3);
    m_route.push_back(r3);

    route*r4=new route(QPoint(930,620));
    r3->nextpos(r4);
    m_route.push_back(r4);

    route*r5=new route(QPoint(1130,550));
    r4->nextpos(r5);
    m_route.push_back(r5);

    route*r6=new route(QPoint(1160,350));
    r5->nextpos(r6);
    m_route.push_back(r6);

    route*r7=new route(QPoint(1050,250));
    r6->nextpos(r7);
    m_route.push_back(r7);
}
//第一关我方阵营像素点
void MainWindow::mycamppos1()
{
        m_camp.push_back(QPoint(370,198));
        m_camp.push_back(QPoint(390,370));
        m_camp.push_back(QPoint(680,250));
        m_camp.push_back(QPoint(1000,320));
        m_camp.push_back(QPoint(750,600));
        m_camp.push_back(QPoint(1080,650));
}
void MainWindow::mousePressEvent(QMouseEvent *p)
{
    QPoint pos=p->pos();
    QList<mycamp>::iterator i=m_camp.begin();
    while(i!=m_camp.end())
    {
        if(Qt::LeftButton==p->button())//左键点击
        {
            bool temp=i->clickin(pos);
            if(temp==true&&i->exist()==false&&i->choiceexist==false)//点击合法，没有我方
            {//出现选择框
                rolechoice*choice=new rolechoice(i->getmypos(),this);
                rc.push_back(choice);
                i->choiceexist=true;
                i->makechoice(choice);
                //update();
                break;
            }
            else if(i->choiceexist==true&&i->exist()==false)//有选择框了选择三种塔
             {//选择三种塔

                   QPoint my_pos=i->getmypos();
                 if(pos.x()>my_pos.x()+35&&pos.x()<my_pos.x()+55&&pos.y()>my_pos.y()-50&&pos.y()<my_pos.y()+25)
                 {

                    i->lei=new leiwujie(my_pos,this,QPixmap(":/images/leiwujie.png"),180,QPixmap(":/images/fireball.png"));
                     m_leiwujie.push_back(i->lei);//所有的我方
                     i->setmycamp(true);//这个地方有我方

                 }
                 else if(pos.x()>my_pos.x()-45&&pos.x()<my_pos.x()+15&&pos.y()>my_pos.y()-50&&pos.y()<my_pos.y()+25)
                 {

                     i->lei=new leiwujie(my_pos,this,QPixmap(":/images/xiaose.png"),240,QPixmap(":/images/xskill.png"));
                     m_leiwujie.push_back(i->lei);//所有的我方
                     i->setmycamp(true);//这个地方有我方

                 }
                 else if(pos.x()>my_pos.x()+15&&pos.x()<my_pos.x()+35&&pos.y()>my_pos.y()-50&&pos.y()<my_pos.y()+25)
                 {
                     i->lei=new leiwujie(my_pos,this,QPixmap(":/images/wuxin.png"),300,QPixmap(":/images/wskill.png"));
                     m_leiwujie.push_back(i->lei);//所有的我方
                     i->setmycamp(true);//这个地方有我方
                 }
                 i->get()->remove();//移除选择框
                 i->makechoice(nullptr);//选择框
                 i->choiceexist=false;//选择框不存在
                 //update();
                 break;
             }
            else if(temp==true&&i->exist()==true&&m_fix!=-1)//词缀选择
            {
                  if(i->lei->fix0==-1)//第一个位置是空的
                  {     if(m_fix==1)
                            --qfix;
                        else if(m_fix==0)
                          --ffix;
                      else if(m_fix==2)
                          --bfix;
                      else if(m_fix==3)
                          --kfix;
                      i->lei->setfix(m_fix,0);m_fix=-1;
                  }
                  else if(i->lei->fix1==-1)//第二个技能槽是空的
                  {
                      if(m_fix==1)
                          --qfix;
                      else if(m_fix==0)
                          --ffix;
                      else if(m_fix==2)
                          --bfix;
                      else if(m_fix==3)
                          --kfix;
                      i->lei->setfix(m_fix,1);m_fix=-1;
                  }
                  break;
            }
        }
        else if(Qt::RightButton==p->button())//右键点击
        {
            if(i->clickin(pos)==true)
            {
                if(i->lei->fix0!=-1)
                    i->lei->fix0=-1;
                else {
                   i->lei->fix1=-1;
                }

            }
        }
        ++i;
    }

}
void MainWindow::hurt()//敌人进入大本营减一滴血，游戏结束
{
    hp=hp-1;
    win=false;
    lose=true;
}

void MainWindow::remove(wushaung *w)
{   
    m_wu.removeOne(w);//移除当前士兵
    int random=qrand()%8;
    if(random==1)
        ++ffix;
    else if(random==2)
        ++qfix;
    else if(random==3)
        ++bfix;
    else if(random==4)
        ++kfix;
    if(m_wu.empty()==true)
    {
        ++m_waves;
        hanghaoarrive();
        if(enemyarrive()==false)
            win=true;
    }
}
void MainWindow::removehanghao(hanghao*h)
{
    m_h.removeOne(h);
    delete h;
}
void MainWindow::removels(lskill*l)
{
    ls.removeOne(l);
    delete l;

}
void MainWindow::removechoice(rolechoice*r)
{
    rc.removeOne(r);
    delete r;
}
QList<wushaung*>MainWindow::getenemy()
{
    return m_wu;
}
bool MainWindow::enemyarrive()
{
    if(m_waves>=4)//一共四波敌军
        return false;
    int time[10]={150,1500,3000,5000,7000,9000,11000,12000,14000,17000};
    //在这些时间分别出现敌军
      int random_number=qrand()%10;//十个无双城士兵里面随机一个获得词缀
      int random_fix=qrand()%2;//0是闪现，1是神速
    for(int i=0;i<10;++i)
    {
        route*showup;//初始位置，第一个路径像素点的坐标
        showup=m_route.first();
        wushaung*wus=new wushaung(showup,this,128+m_waves*120);
        m_wu.push_back(wus);
        if(i==random_number)
            wus->fixnum=random_fix;
        else if(i==random_number+m_waves)
            wus->fixnum=1-random_fix;
        QTimer::singleShot(time[i],wus,SLOT(makealive()));
    }
    return true;
}
bool MainWindow::hanghaoarrive()
{
    if(m_waves>=4)
        return false;
    int random_number=qrand()%2;//两个夯昊，挑一个获得词缀
    int random_fix=qrand()%1;//0是狂暴，1是冰系，2是群伤
    int time[2]={10000,30000};
    for(int i=0;i<2;++i)
    {
        route*showup;//初始位置，最后一个路径像素点

        showup=h_route.first();
        hanghao*h=new hanghao(showup,this);
        if(random_number==i)
            h->fixnum=random_fix;
        m_h.push_back(h);
        QTimer::singleShot(time[i],h,SLOT(beginmove()));
    }
    return true;
}
void MainWindow::updateMap()//重画地图实现移动
{
    for(int i=0;i<m_wu.size();++i)
           this-> m_wu[i]->move();
    for(int i=0;i<m_h.size();++i)
        this->m_h[i]->move();
    for(int i=0;i<m_leiwujie.length();++i)
        m_leiwujie[i]->check();
    for(int i=0;i<m_h.length();++i)
        m_h[i]->check();
   repaint();//调用paintEvent重画无双城士兵实现移动
}
