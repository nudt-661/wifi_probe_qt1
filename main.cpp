#include "widget.h"
#include <QApplication>
#include <stdlib.h>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QDebug>
int SCAN_MODE;
int FLOW_MODE;
char wlanName[100];
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    /*system("sudo ifconfig wlan0 down");
    system("sudo iwconfig wlan0 mode monitor");
    system("sudo ifconfig wlan0 up");*/
    Widget w;

    //w.setWindowFlags(/*Qt::WindowMinMaxButtonsHint && */Qt::FramelessWindowHint);

    QDesktopWidget* desktopWidget =QApplication::desktop();

    QRect deskRect = desktopWidget->availableGeometry();

    w.setGeometry(deskRect.x(),0,deskRect.width(),deskRect.height());
    //qDebug() << deskRect.x()<< deskRect.y() << deskRect.width() <<deskRect.height();
    w.showFullScreen();
    //w.show();
    return a.exec();
}
