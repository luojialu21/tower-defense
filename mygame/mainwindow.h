#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QString>
#include<QObject>
#include<QPixmap>
#include"mycamp.h"
#include"route.h"
#include"ui_mainwindow.h"
#include"wushaung.h"
#include"leiwujie.h"
#include "startfrom.h"
#include"lskill.h"
#include"hanghao.h"
#include"rolechoice.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class leiwujie;
class mycamp;
class wushaung;
class lskill;
class rolechoice;
class hanghao;
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    int hp;//我方血量
    int chivalrous;//我方侠义值，用来增加成员
    int m_waves;//当前的波数
    bool win;//是否赢
    bool lose;
    int height,width;//自定义图片的长宽
    int m_fix;//记录上一次点击的词缀
    QPixmap m_path;//图片位置
    QList<mycamp>m_camp;//我方阵营位置
    QList<leiwujie*>m_leiwujie;//雷无桀 
    QList<wushaung*>m_wu;//无双城士兵
    QList<hanghao*>m_h;//近战夯昊单位
    QList<lskill*>ls;//雷无桀的火球
    QList<rolechoice*>rc;//选择框
    int kfix;//狂暴的数量
    int ffix;//放血的数量
    int bfix;//冰冻的数量
    int qfix;//群攻的数量
public:
    MainWindow(double height,double width,QWidget *parent = nullptr);
    ~MainWindow();
      Ui::MainWindow *ui;
      QList<route*>m_route;//路径像素点
      QList<route*>h_route;//夯昊路径像素点
    void setroute1();//自定义地图中设置敌人行动路径

    void sethanghaoroute1();//自定义地图设置敌人行动路径
    void hurt();//大本营的血量
    void remove(wushaung*w);//敌人死亡或者到达重点
    void removels(lskill*s);//移除火球
    void removehanghao(hanghao*h);
    void removechoice(rolechoice*r);//移除选择框
    void launch(lskill*s);//发射火球
    QList<wushaung*>getenemy();//返回敌人链表
    QString getPath();//返回图片所在路径
    void setPath(QPixmap path);//设置图片路径
    void route1();//第一关敌人路线
    void hanghao_route1();//第一关夯昊路线
    void mycamppos1();//第一关我方防御塔位置
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent*);
    void drawfix(QPainter *p);
private slots://槽
    void updateMap();//重画地图实现移动
    bool enemyarrive();//游戏开始
    bool hanghaoarrive();//近战攻击夯昊开始
};
#endif // MAINWINDOW_H
