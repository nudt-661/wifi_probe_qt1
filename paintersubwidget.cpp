#include "paintersubwidget.h"
#include<QDebug>
#include<QPalette>
#include<QPushButton>
#include <QDesktopWidget>
#include<QRect>
#include<QRect>
#include<QScreen>
extern int SCAN_MODE;
PainterSubWidget::PainterSubWidget(QWidget *parent) : QWidget(parent)
{
    int i=0;
    for(i=0;i<TRAFFIC_NUM;i++)
    {
        this->pointY[i]=0;
    }
    QScreen *screen=QGuiApplication::primaryScreen();
    QRect mm=screen->availableGeometry();
    this->setPaintWindowSize(mm.x(),mm.y(),mm.width(),mm.height());
    this->setGeometry(x+0.08*w,y+0.08*h,w*0.82,h*0.85);
    qDebug()<<this->x<<this->y<<this->w<<this->h;
    //this->setGeometry(60,50,650,350);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background,Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //this->setFixedSize(600,350);
    this->setFixedSize(w*0.82,h*0.83);
    this->setWindowModality(Qt::ApplicationModal);
    //image=QImage(540,270,QImage::Format_ARGB32);
    image=QImage(0.75*w,0.68*h,QImage::Format_ARGB32);
    QColor backcolor=qRgb(0,0,0);
    image.fill(backcolor);

    b.setParent(this);
    b.setGeometry(0.35*w,0.744*h,0.08*w,0.07*h);
    //b.setGeometry(270,310,60,30);
    b.setText("Exit");
    b.show();
    connect(&b,&QPushButton::clicked,this,&PainterSubWidget::dealexit);

}
void PainterSubWidget::setPaintWindowSize(int x, int y, int w, int h)
{
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;

}
void PainterSubWidget::dealexit(){
    this->close();
    SCAN_MODE=1;
}
void PainterSubWidget::paintNewPoint(int y0,int y1,int index)
{
    painter.begin(this);
    QPen pen;
    pen.setColor(QColor(0,255,255));
    pen.setWidth(2);
    QPen penPoint;
    penPoint.setWidth(5);
    penPoint.setColor(QColor(255,0,255));
    painter.setPen(pen);
    //int pointx=50,pointy=280;
    int pointx=0.062*w,pointy=0.7*h;
    //int width=540-pointx+10;
    //qDebug()<<"display"<<this->pointY[i];
    painter.drawLine(pointx+kx*index,pointy-y0*ky,pointx+kx*(index+1),pointy-(y1)*ky);
    painter.setPen(penPoint);
    painter.drawPoint(pointx+kx*index,pointy-ky*y0);
    painter.end();
}
void PainterSubWidget::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //int pointY[60]={0};
    painter.begin(this);
    int i=0;
    double max=0.0;
    max=(double)pointY[0];
    for(i=1;i<60;i++)
    {
        if((double)pointY[i]>=max)
        {
            max=(double)pointY[i];
        //qDebug()<<pointY[i];
        }
    }
    //painter.drawImage(30,30,image);
    painter.drawImage(0.04*w,0.06*h,image);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor(139,139,139));
    painter.setPen(pen);
    //painter.setPen(QColor(139,139,139));
    painter.drawLine(0,0,this->width()-1,0);
    painter.drawLine(0,0,0,this->height()-1);
    painter.drawLine(this->width()-1,0,this->width()-1,this->height()-1);
    painter.drawLine(0,this->height()-1,this->width()-1,this->height()-1);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    //int pointx=50,pointy=280;
    int pointx=0.062*w,pointy=0.7*h;
    //int width=540-pointx+10;
    int width=0.75*w-pointx+0.03*w;
    //int height=240;
    int height=0.6*h;
    pen.setWidth(1);
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    //painter.drawRect(5,5,520-10,260-10);
    painter.drawLine(pointx,pointy,width+pointx,pointy);
    painter.drawLine(pointx,pointy-height,pointx,pointy);
    kx=(double)width/59.0;

    ky=0.0;
    if(max!=0)
    {
        ky=(double)height/max;
    }
    pen.setColor(QColor(0,255,255));
    pen.setWidth(2);
    QPen penPoint;
    penPoint.setWidth(5);
    penPoint.setColor(QColor(255,0,255));

    for(i=0;i<TRAFFIC_NUM-1;i++)
    {
        painter.setPen(pen);
        //qDebug()<<"display"<<this->pointY[i];
        painter.drawLine(pointx+kx*i,pointy-(this->pointY[i])*ky,pointx+kx*(i+1),pointy-(this->pointY[i+1])*ky);
        painter.setPen(penPoint);
        painter.drawPoint(pointx+kx*i,pointy-ky*(this->pointY[i]));
    }
    painter.drawPoint(pointx+kx*(i-1),pointy-ky*(this->pointY[i-1]));
    painter.end();
    /*painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor(0,160,230));
    //painter.setBrush(QColor(255,160,90));
    static QPointF points[4]={QPointF(30,40),QPointF(60,150),QPointF(150,160),QPointF(220,100)};

    painter.drawPolygon(points,4);
    painter.end();
    */

}
