#include "maclist.h"

macList::macList(QWidget *parent) : QWidget(parent)
{

}
bool macList::searchMacKey(QList<macList::mac_list> *mlist,char key[32])
{
    if(!mlist->isEmpty())
    {
        QList<macList::mac_list>::iterator iter = mlist->begin();
        for(;iter != mlist->end();iter++)
        {
            if(strcmp(iter->devmac,key)==0)
                return true;
        }

    }
    return false;
}
