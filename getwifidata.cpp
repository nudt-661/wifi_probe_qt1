#include "getwifidata.h"
#include "sniff80211.h"
#include "wifilist.h"
#include "maclist.h"
#include "device.h"
#include <QList>
#include <QDebug>
extern char wlanName[100];

getWifiData::getWifiData(QThread *parent) : QThread(parent)
{
//    this->mlist=*mlist;
  //  this->wlist=*wlist;
    flag=false;
}
getWifiData::getWifiData(QList<macList::mac_list> *mlist,QList<wifiList::wifi_list> *wlist)
{
    this->mlist=mlist;
    this->wlist=wlist;
    flag=false;
    //this->trafficIndex=0;
    //sniff80211 s;

}
void getWifiData::doChange()
{
    //qDebug()<<"-------------------do change-----------------";
    emit change();
}
void getWifiData::dodisplay()
{
    emit display();
}
void getWifiData::run()
{

    //char dev[100]={'\0'};
    //char mac[100];
    //memcpy(dev, "wlan1", 5);
    //dev[6] = 0;
    memset(wlanName,'\0',100);
    device d;
    d.getNetName(wlanName);
    qDebug()<<wlanName;
    d.set_promisc_mode(wlanName/*,true*/);
    //int fd;
    sniff80211 s;
    s.setFlag();
    connect(&s,&sniff80211::datachanged,this,&getWifiData::doChange);
    connect(&s,&sniff80211::macupdate,this,&getWifiData::dodisplay);
    //timerHandler = this->startTimer(200);
    this->fd=d.init_socket(wlanName);
    qDebug()<<this->fd;
    while(!flag)
        s.recieve_packet(this->fd,(this->wlist),(this->mlist));

    qDebug()<<"++++++++++++++++++++++++++++++++";
}
void getWifiData::setFlag(bool flag)
{
    this->flag=flag;
}
