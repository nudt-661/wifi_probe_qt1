#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QList>
#include <QTimer>
#include "maclist.h"
#include "wifilist.h"
#include "getwifidata.h"
#include "sniff80211.h"
#include <QStringList>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<macList::mac_list> *mlist;
    QList<wifiList::wifi_list> *wlist;
    //QStringList *text;


private slots:
    void on_wifiTextBrowser_sourceChanged(const QUrl &arg1);
    void stopthread();
    void dealdone();
    void dealStart();
    void dealExit();
    void dealComboBoxChanged();
    void dealmacCommoBoxChanged();

protected:
    void timerEvent(QTimerEvent *);


private:

    Ui::Widget *ui;
    getWifiData *thread;
    QList<char*> *devmac;
    char ap[32];
    QPoint *point;
    QPainterPath *path;
    int timerHandler;
    int trafficindex;
    //void paintEvent(QPaintEvent *);

};

#endif // WIDGET_H
