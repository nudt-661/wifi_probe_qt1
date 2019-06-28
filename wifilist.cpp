#include "wifilist.h"

wifiList::wifiList(QWidget *parent) : QWidget(parent)
{

}
bool wifiList::searchKey(QList<wifiList::wifi_list> *wlist,char key[20])
{
    if(!wlist->isEmpty())
    {
        QList<wifiList::wifi_list>::iterator iter = wlist->begin();
        for(;iter != wlist->end();iter++)
        {
            if(strcmp(iter->apMac,key)==0)
                return true;
        }
        return false;
    }
}
