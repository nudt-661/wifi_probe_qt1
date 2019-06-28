#ifndef MACLIST_H
#define MACLIST_H

#include <QPainter>
#include <QWidget>
#include <QString>
#include <QList>
#include <QDebug>
#include "wifilist.h"
#define TRAFFIC_NUM  60
class macList : public QWidget
{
    Q_OBJECT
public:
    typedef struct trafficNode{
        int traffic;
        QString time;
        struct trafficNode *next;
    }devTraffic,*trafficList;
    void initTrafficList(trafficList *TL,int traffic,QString time);
    //trafficList createTrafficList(int n);
    void addTraffic(trafficList head,int traffic,QString time,int len,int index);
    void changeTrafficData(trafficList head,int traffic,QString time,int len,int index);
    explicit macList(QWidget *parent = 0);
    struct mac_list{
        char devmac[20];
        char ap[20];
        int traffic[TRAFFIC_NUM];
        //QString time[TRAFFIC_NUM];
        int index;
        //trafficList macTraffic;
    };
    int searchMacKey(QList<macList::mac_list> *mlist,char key[20],char ap[20],int *traffic,int *traffic_index);
signals:

public slots:
private:

};

#endif // MACLIST_H
