#ifndef MACLIST_H
#define MACLIST_H

#include <QWidget>
#include <QString>
class macList : public QWidget
{
    Q_OBJECT
public:
    explicit macList(QWidget *parent = 0);
    struct mac_list{
        char devmac[32];
        char ap[32];
    };
    bool searchMacKey(QList<macList::mac_list> *mlist,char key[32]);
signals:

public slots:
};

#endif // MACLIST_H
