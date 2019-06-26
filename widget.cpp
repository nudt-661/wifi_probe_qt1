#include "widget.h"
#include "ui_widget.h"
#include "getwifidata.h"
#include "sniff80211.h"
#include <QPushButton>
#include <QDebug>
#include <QStringList>
#include "getMacOrg.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QPainter>
#include "paintersubwidget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QDesktopWidget* desktopWidget =QApplication::desktop();
    QRect deskRect = desktopWidget->availableGeometry();
    int x=deskRect.x();
    int y=deskRect.y();
    int w=deskRect.width();
    int h=deskRect.height();

    ui->wifi->setGeometry(x+0.01*w,0.01*h,w*0.4,h*0.05);
    ui->device->setGeometry(x+0.43*w,0.01*h,0.56*w,0.05*h);
    ui->wifiTextBrowser->setGeometry(x+0.01*w,0.07*h,w*0.4,h*0.5);
    //ui->wifiListView->setGeometry(x+0.01*w,0.07*h,w*0.4,h*0.5);
    ui->macTextBrowser->setGeometry(x+0.43*w,0.07*h,0.56*w,0.8*h);
    ui->text->setGeometry(x+0.01*w,0.58*h,w*0.4,h*0.05);
    ui->ssidComboBox->setGeometry(x+0.01*w,0.64*h,w*0.4,h*0.1);
    ui->aptextBrowser->setGeometry(x+0.01*w,0.75*h,w*0.4,h*0.08);
    ui->orgTextBrowser->setGeometry(x+0.01*w,0.84*h,w*0.4,h*0.14);
    //ui->graphTextBrowser->setGeometry(x+0.43*w,0.58*h,w*0.56,0.32*h);
    ui->macComboBox->setGeometry(x+0.43*w,0.88*h,w*0.4,0.1*h);
    ui->paintPushButton->setGeometry(x+0.85*w,0.88*h,w*0.14,0.1*h);
    //ui->paintPushButton->setDisabled(true);
    this->timerHandler=0;
    timerHandler=this->startTimer(1000);
    if(timerHandler==0)
        return;
     p=new PainterSubWidget();

    this->mlist=new QList<macList::mac_list>;
    this->wlist=new QList<wifiList::wifi_list>;
    this->devmac=new QList<char*> ;
    memset(this->ap,'\0',32);
    thread=new getWifiData(this->mlist,this->wlist);
    thread->start();


    connect(ui->macComboBox,&QComboBox::currentTextChanged,this,&Widget::dealmacCommoBoxChanged);
    connect(ui->ssidComboBox,&QComboBox::currentTextChanged,this,&Widget::dealComboBoxChanged);
    //connect(ui->startPushButton,&QPushButton::clicked,this,&Widget::dealStart);
    //connect(ui->stopPushButton,&QPushButton::clicked,this,&Widget::stopthread);
    //connect(ui->pushButton,&QPushButton::clicked,this,&Widget::dealExit);
    //connect(ui->pushButton,&QPushButton::clicked,this,&Widget::destroy);
    connect(thread,&getWifiData::change,this,&Widget::dealdone);
    connect(this,&Widget::destroyed,this,&Widget::stopthread);
    connect(ui->paintPushButton,&QPushButton::clicked,this,&Widget::doPaint);
}
void Widget::dealComboBoxChanged()
{
    /*
    if(ui->ssidComboBox->currentText()=="")
    {
        ui->macTextBrowser->clear();
        ui->macTextBrowser->append("no data");
    }
    else
    {*/
        ui->macTextBrowser->clear();
        //ui->graphTextBrowser->clear();
        ui->macComboBox->clear();
        this->devmac->clear();
        memset(this->ap,'\0',32);
        //ui->macComboBox->setCurrentIndex(0);
        ui->aptextBrowser->clear();
        if(!this->wlist->isEmpty())
        {
            QString tmp=ui->ssidComboBox->currentText();
            //wifiList w;
            QList<wifiList::wifi_list>::iterator iter=wlist->begin();
            for(;iter!=wlist->end();iter++)
            {
                QString name=(QString)iter->apMac;
                if(tmp==name)
                {
                    ui->aptextBrowser->clear();
                    ui->orgTextBrowser->clear();
                    ui->aptextBrowser->append(iter->ssid);
                    strcpy(this->ap,iter->apMac);
                    QList<macList::mac_list>::iterator maciter=mlist->begin();
                    for(;maciter!=mlist->end();maciter++)
                    {
                        QString mname=(QString)maciter->ap;
                        if(mname==iter->apMac)
                        {
                            ui->macTextBrowser->append(maciter->devmac);
                            ui->macComboBox->addItem(maciter->devmac);
                            this->devmac->append(maciter->devmac);
                            char *devmac_prefix=NULL;
                            devmac_prefix=(char *)malloc(sizeof(char)*10);
                            for(int i=0;i<8;i+=3)
                            {
                                devmac_prefix[i]=maciter->devmac[i];
                                devmac_prefix[i+1]=maciter->devmac[i+1];
                                if(i+2<6)
                                {
                                    devmac_prefix[i+2]='-';
                                }
                            }
                            devmac_prefix[8]='\0';
                            //qDebug() << (QString)mac_prefix;
                            char devorg_name[ORG_NAME_LEN]={'\0'};
                            int re=searchOrg(devmac_prefix,devorg_name);
                            qDebug() << (QString)devorg_name;
                            ui->macTextBrowser->append((QString)devorg_name);
                            if(re==0)
                                ui->macTextBrowser->append(" ");
                            free(devmac_prefix);
                            devmac_prefix=NULL;
                        }

                    }
                    //int i=0;
                    char *mac_prefix=NULL;
                    mac_prefix=(char *)malloc(sizeof(char)*10);
                    for(int i=0;i<8;i+=3)
                    {
                        mac_prefix[i]=iter->apMac[i];
                        mac_prefix[i+1]=iter->apMac[i+1];
                        if(i+2<6)
                        {
                            mac_prefix[i+2]='-';
                        }
                    }
                    mac_prefix[8]='\0';
                    qDebug() << (QString)mac_prefix;
                    char org_name[ORG_NAME_LEN]={'\0'};
                    searchOrg(mac_prefix,org_name);
                    qDebug() << (QString)org_name;
                    ui->orgTextBrowser->append((QString)org_name);
                    free(mac_prefix);
                    mac_prefix=NULL;
                    break;
                }
            }

        }
//    }
}
void Widget::dealdone()
{
    qDebug()<<"deal wifi data change";

    /*if(!this->mlist->isEmpty())
    {
        QList<macList::mac_list>::iterator iter=mlist->begin();
        ui->macTextBrowser->clear();
        for(;iter!=mlist->end();iter++)
        {
            ui->macTextBrowser->append(iter->devmac);
        }
        //qDebug()<<this->mlist->first().devmac<<this->mlist->first().ap;
    }*/
    if(!this->wlist->isEmpty())
    {
        //qDebug()<<this->wlist->first().apMac<<this->wlist->first().ssid;
        QList<wifiList::wifi_list>::iterator iter=wlist->begin();
        ui->wifiTextBrowser->clear();

        //ui->ssidComboBox->clear();
        for(;iter!=wlist->end();iter++)
        {

            ui->wifiTextBrowser->insertPlainText(iter->apMac);// wlist->first().apMac);
            ui->wifiTextBrowser->insertPlainText(" ");
            ui->wifiTextBrowser->insertPlainText(iter->ssid);//wlist->first().ssid);
            ui->wifiTextBrowser->insertPlainText("\n");


            //ui->wifiTextBrowser->append(iter->apMac);
            //ui->wifiTextBrowser->append(iter->ssid);
            if(ui->ssidComboBox->findText(iter->apMac)==-1)
            {
                ui->ssidComboBox->addItem(iter->apMac);
            }
            //ui->ssidComboBox->addItem(QWidget::tr(iter->ssid));
            //text->append(iter->ssid);

        }
        //ui->wifiTextBrowser->append(wlist->last().ssid);
        //ui->ssidComboBox->addItem(wlist->last().ssid);
    }
    else
        qDebug()<<"is null";
}
void Widget::stopthread()
{
    if(thread->isRunning())
    {
        thread->setFlag(true);
        thread->quit();
        thread->wait();
    }
    this->killTimer(this->timerHandler);
    //delete this->wlist;
    //delete this->mlist;
}
void Widget::dealExit(){
    if(thread->isRunning())
    {
        thread->setFlag(true);
        thread->quit();
        thread->wait();
    }
    if(thread->isFinished())
    {
        qDebug()<<"thread finished";
    }
    //emit destroyed();

    this->destroy();
}
void Widget::dealStart(){
    if(!thread->isRunning())
    {
        thread->setFlag(false);
        //thread=new getWifiData(this->mlist,this->wlist);
        thread->start();
    }
}

Widget::~Widget()
{
    delete ui;

}
void Widget::on_wifiTextBrowser_sourceChanged(const QUrl &arg1){

}

void Widget::timerEvent(QTimerEvent *)
{
    if(!this->mlist->isEmpty())
    {

        QList<macList::mac_list>::iterator iter = mlist->begin();
        for(;iter!=mlist->end();iter++)
        {
            qDebug()<<"change maclist index:"<<iter->devmac<<iter->ap<<iter->index<<iter->traffic[iter->index];
            if(ui->macComboBox->currentText()!="")
            {
                QString tmp=(QString)iter->devmac;
                if(ui->macComboBox->currentText()==tmp)
                {
                    int i;//iter->index;
                    int index=iter->index;
                    for(i=TRAFFIC_NUM-1;i>=0;i--)
                    {
                        p->pointY[i]=iter->traffic[index];
                        //qDebug()<<p->pointY[index];

                        index=(index-1);
                        if(index<0){
                            index=TRAFFIC_NUM-1;
                        }
                    }
                    p->update();
                    //p->paintNewPoint(iter->traffic[iter->index],iter->traffic[(iter->index+1)%60],iter->index);
                }

            }
            else{

                int index=0;
                for(;index<TRAFFIC_NUM;index++)
                {
                    p->pointY[index]=0;
                    //qDebug()<<p->pointY[index];
                }
                p->update();

            }
            iter->index=(iter->index+1)%(60);
            iter->traffic[iter->index]=0;

        }

    }
}
void Widget::dealmacCommoBoxChanged()
{
    //ui->paintPushButton->setDisabled(true);
    if(!this->mlist->isEmpty())
    {

        QList<macList::mac_list>::iterator iter = mlist->begin();
        for(;iter!=mlist->end();iter++)
        {
            //qDebug()<<"change maclist index:"<<iter->devmac<<iter->ap<<iter->index<<iter->traffic[iter->index];
            if(ui->macComboBox->currentText()!="")
            {
                QString tmp=(QString)iter->devmac;
                if(ui->macComboBox->currentText()==tmp)
                {
                    int i;//iter->index;
                    int index=iter->index;
                    for(i=TRAFFIC_NUM-1;i>=0;i--)
                    {
                        p->pointY[i]=iter->traffic[index];
                        //qDebug()<<p->pointY[index];

                        index=(index-1);
                        if(index<0){
                            index=TRAFFIC_NUM-1;
                        }
                    }
                }

            }
            else
            {

                int index=0;
                for(;index<TRAFFIC_NUM;index++)
                {
                    p->pointY[index]=0;
                    //qDebug()<<p->pointY[index];
                }
            }

        }

    }
    //ui->paintPushButton->setEnabled(true);
}
void Widget::doPaint(){

    p->setWindowTitle("流量曲线");

    p->show();

}
