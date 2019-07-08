#ifndef GETWIFIDATA_H
#define GETWIFIDATA_H

#include <QThread>
#include <QObject>
#include "getwifidata.h"
#include "wifilist.h"
#include "maclist.h"

class getWifiData : public QThread
{
    Q_OBJECT
public:
    explicit getWifiData(QThread *parent =0 );
    getWifiData(QList<macList::mac_list> *mlist,QList<wifiList::wifi_list> *wlist);
    QList<macList::mac_list> *mlist;
    QList<wifiList::wifi_list> *wlist;
    void setFlag(bool flag);
    int fd;
protected:
    // virtual function of qt thread
    void run();

signals:
    void change();
    void display();

public slots:
    void doChange();
    void dodisplay();
private:
    bool flag;
    //int timerHandler;
    //int trafficIndex;

};

#endif // GETWIFIDATA_H
