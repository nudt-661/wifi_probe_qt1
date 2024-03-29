#include "maclist.h"

macList::macList(QWidget *parent) : QWidget(parent)
{

}
int macList::searchMacKey(QList<macList::mac_list> *mlist,char key[20],char ap[20],int *traffic,int *traffic_index,int *channel)
{
    //qDebug()<<"--------------------------";
    if(!mlist->isEmpty())
    {

        QList<macList::mac_list>::iterator iter = mlist->begin();
        int i=0;
        for(;iter != mlist->end();iter++)
        {
            //qDebug()<<"mlist"<<iter->devmac<<iter->ap<<"key"<<key<<"ap"<<ap;
            if(strcmp(iter->devmac,key)==0)
            {
                //qDebug()<<"find key !!!!!!!!!!!!!!!!!!!!!!!"<<key;
                if(memcmp(iter->ap,ap,17)==0)
                {
                    //qDebug()<<"find ap !!!!!!!!!!!!!!!!!!!!!!!"<<ap;
                    int j=0;
                    for(j=0;j<TRAFFIC_NUM;j++)
                    {
                        traffic[j]=iter->traffic[j];
                    }
                    *traffic_index=iter->index;
                    *channel=iter->channel;

                    return i;
                }
                /*
                else
                {
                    return -1;
                }*/
            }
            i++;
        }

    }
    return -1;
}
void macList::initTrafficList(trafficList *TL,int traffic,QString time)
{
    *TL=(trafficList)malloc(sizeof(trafficNode));
    (*TL)->time=time;
    (*TL)->traffic=traffic;
    (*TL)->next=*TL;
    qDebug()<<"insert head successful";
}

void macList::addTraffic(trafficList head, int traffic, QString time,int len, int index)
{
    if(index>=len)//detect parameter legitimacy
    {
        return;
    }
    if(index==0)
    {
        if(head==NULL)
        {
            qDebug()<<"insert traffic list\n"<<"insert head";
            initTrafficList(&head,traffic,time);
        }
        else//the list is full,update head.
        {
            qDebug()<<"change traffic list\n"<<"change head";
            head->time=time;

            head->traffic=traffic;
        }
    }
    else
    {
        qDebug()<<"+++++++++++++++++++++++++++++++";
        trafficNode *tl;
        tl=head;
        qDebug()<<"+++++++++++++++++++++++++++++++";
        int currentLen=1;//use to save the current length of list
        while(tl->next!=head)
        {
            currentLen++;
            tl=tl->next;
        }
        if(currentLen<len)//the list is not full
        {
            qDebug()<<"insert traffic list\n"<<"current index:"<<currentLen-1;
            trafficNode *newNode=(trafficNode *)malloc(sizeof(trafficNode));
            newNode->time=time;
            newNode->traffic=traffic;
            newNode->next=tl->next;
            tl->next=newNode;
        }
        else//the list is full,update data at index of list.
        {
            int i=0;
            tl=head;
            while(i!=index)//move pointer to index
            {
                i++;
                tl=tl->next;
            }
            tl->time=time;
            tl->traffic=traffic;
        }
    }
}
void macList::changeTrafficData(trafficList head, int traffic, QString time, int len, int index)
{
    qDebug()<<"change traffic list\n"<<"index:"<<index;
    if(index>=len)
    {
        return;
    }
    trafficList tl;
    tl=head;
    int i=0;
    qDebug()<<"$$$$$$$$$$$$$$$$$$$";
    /*while(tl->next!=head&&i!=index)
    {
        qDebug()<<"######";
        i++;
        tl=tl->next;
    }*/
    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$";
    tl->time=time;
    tl->traffic=traffic;
    qDebug()<<"**********************************";
}
