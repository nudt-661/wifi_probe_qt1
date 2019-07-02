#ifndef WIFILIST_H
#define WIFILIST_H

#include <QWidget>
#include <QList>
#include <QString>

class wifiList : public QWidget
{
    Q_OBJECT
public:
    explicit wifiList(QWidget *parent = 0);
    struct wifi_list{
        char ssid[100];
        char apMac[20];
        //int channel;
    };
    bool searchKey(QList<wifiList::wifi_list> *wlist,char key[20]);
signals:

public slots:
};

#endif // WIFILIST_H
