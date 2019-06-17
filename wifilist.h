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
        char ssid[32];
        char apMac[32];
    };
    bool searchKey(QList<wifiList::wifi_list> *wlist,char key[32]);
signals:

public slots:
};

#endif // WIFILIST_H
