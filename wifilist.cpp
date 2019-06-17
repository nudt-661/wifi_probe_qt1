#include "wifilist.h"

wifiList::wifiList(QWidget *parent) : QWidget(parent)
{

}
bool wifiList::searchKey(QList<wifiList::wifi_list> *wlist,char key[32])
{
    if(!wlist->isEmpty())
    {
        QList<wifiList::wifi_list>::iterator iter = wlist->begin();
        for(;iter != wlist->end();iter++)
        {
            if(strcmp(iter->ssid,key)==0)
                return true;
        }
        return false;
    }
}
