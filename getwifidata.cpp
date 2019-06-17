#include "getwifidata.h"
#include "sniff80211.h"
#include "wifilist.h"
#include "maclist.h"
#include "device.h"
#include <QList>
#include <QDebug>
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
    //sniff80211 s;

}
void getWifiData::doChange()
{
    emit change();
}
void getWifiData::run()
{

    char dev[100]={"wlan0"};
    //char mac[100];
    device d;
    d.set_promisc_mode(dev,true);
    int fd;
    sniff80211 s;
    connect(&s,&sniff80211::datachanged,this,&getWifiData::doChange);
    fd=d.init_socket(dev);
    //d.get_hwinfo(dev,mac);
    //int i=0;
    //for(i=0;i<10;i++)
    while(!flag)
        s.recieve_packet(fd,(this->wlist),(this->mlist));
    //macList::mac_list m;
  // m=mlist.first();
    qDebug()<<"++++++++++++++++++++++++++++++++";
    /*if(!this->mlist->isEmpty())
        qDebug()<<this->mlist->first().devmac<<this->mlist->first().ap;
    if(!this->wlist->isEmpty())
    {
        qDebug()<<this->wlist->first().apMac<<this->wlist->first().ssid;
    }*/
}
void getWifiData::setFlag(bool flag)
{
    this->flag=flag;
}
