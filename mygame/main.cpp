#include"mainwindow.h"
#include<startfrom.h>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    startfrom w;
    w.show();

    return a.exec();
}
