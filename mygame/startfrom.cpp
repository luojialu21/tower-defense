#include "startfrom.h"
#include<QLabel>
#include<QMovie>
#include<QMediaPlayer>
#include<QMediaPlaylist>
startfrom::startfrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startfrom)
{
    ui->setupUi(this);

    QApplication::processEvents(QEventLoop::AllEvents);
    QLabel*label=new QLabel(this);
    QMovie*movie;
    label->setGeometry(0,0,1250,730);

    movie=new QMovie(":/images/pv.gif");
    QSize si(1250,730);
    movie->setScaledSize(si);
    label->setMovie(movie);
    movie->start();
    label->show();
    QMediaPlayer * player1=new QMediaPlayer;

    player1->setMedia(QUrl::fromEncoded("qrc:/music/pv.mp3"));

    //player1->setVolume(30);
    player1->play();
    ui->pushButton_4->raise();
    connect(ui->pushButton_4,&QPushButton::clicked,[=]()
    {//跳过动画
        movie->stop();
        label->clear();
        player1->stop();
        delete player1;
        delete label;
        delete movie;
        ui->pushButton_4->hide();
    });
    QObject::connect(movie, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画执行一次就结束
        if (frameNumber == movie->frameCount() - 1) {
            movie->stop();
            label->clear();
            player1->stop();
            delete player1;
            delete label;
            delete movie;
            ui->pushButton_4->hide();
        }

    });

    connect(ui->pushButton,&QPushButton::clicked,[=]()//点击button进入第一关
       { QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl::fromEncoded("qrc:/music/2.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        QMediaPlayer *music = new QMediaPlayer();
        music->setPlaylist(playlist);
        music->play();
           MainWindow*m=new MainWindow(1233,720,parent);
           m-> setPath(QPixmap(":/images/background1.jpg"));
           m->route1();//最佳敌人行动路线
           m-> hanghao_route1();//最佳夯昊行动路线
           m->show();
           connect(ui->pushButton_3,&QPushButton::clicked,[=]()//点击button3导出地图
           {
               ofstream f;
               f.open("mapout.txt",ios::out);
               f<<1233<<" "<<720<<endl;
               for(int i=0;i<m->m_route.length();++i)
               {
                   int x=m->m_route[i]->getPos().x();
                   int y=m->m_route[i]->getPos().y();
                   f<<x<<" "<<y<<endl;
               }

               f.close();

           });

       });
    connect(ui->pushButton_2,&QPushButton::clicked,[=]()//点击button2自定义地图
    {
        ifstream f;
        f.open("map.txt",ios::in);
        double height,width;
        f>>height>>width;
        f.close();

        MainWindow*m=new MainWindow(height,width,parent);
        m-> setPath(QPixmap(":/images/background1.jpg"));
        m->setroute1();//自定义敌人路线
        m->sethanghaoroute1();//自定义夯昊行动轨迹
        m->show();
        connect(ui->pushButton_3,&QPushButton::clicked,[=]()//点击button3导出地图
        {
            ofstream f;
            f.open("mapout.txt",ios::out);
            f<<height<<" "<<width<<endl;
            for(int i=0;i<m->m_route.length();++i)
            {
                int x=m->m_route[i]->getPos().x();
                int y=m->m_route[i]->getPos().y();

                f<<x<<" "<<y<<endl;
            }

            f.close();
        });
    });


}

startfrom::~startfrom()
{
    delete ui;
}
void startfrom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path(":/images/background.png");
    painter.drawPixmap(0,0,1280,720,path);
}
