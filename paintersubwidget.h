#ifndef PAINTERSUBWIDGET_H
#define PAINTERSUBWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QList>
#include<QPaintEvent>
#include<QtGui>
#include<QPushButton>
#include"maclist.h"
class PainterSubWidget : public QWidget
{
    Q_OBJECT
public:
    int pointY[TRAFFIC_NUM];
    void paintNewPoint(int y0,int y1,int index);
    void setPaintWindowSize(int x,int y,int w,int h);
    explicit PainterSubWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void dealexit();
private:
    QPainter painter;
    QImage image;
    QPushButton b;
    double kx;
    double ky;
    int x;
    int y;
    int w;
    int h;
};

#endif // PAINTERSUBWIDGET_H
