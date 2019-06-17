#include "sniff80211.h"
#include "radiotap_iter.h"
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <unistd.h>
#include <QList>
#include "wifilist.h"
#include "maclist.h"
#include <QDebug>
#include "getwifidata.h"
sniff80211::sniff80211(QWidget *parent) : QWidget(parent)
{

}

void sniff80211::mac2str(char szMac[32],unsigned char* pMac,const char chKen)
{
    char szFormat[]="%02X:%02X:%02X:%02X:%02X:%02X\0";
    int nLen =strlen(szFormat);
    if(chKen != ':')
    {
        int i=0;
        for(i=2;i<nLen;i+=3)
        {
            szFormat[i] = chKen;

        }

    }
    sprintf(szMac,szFormat,pMac[0],pMac[1],pMac[2],pMac[3],pMac[4],pMac[5]);

}
void sniff80211::print_radiotap_namespace(struct ieee80211_radiotap_iterator *iter)
{
    char signal = 0;
    uint32_t phy_freq = 0;
    switch (iter->this_arg_index)
    {
        case IEEE80211_RADIOTAP_TSFT:
            printf("\tTSFT: %llu\n", le64toh(*(unsigned long long *)iter->this_arg));
            break;
        case IEEE80211_RADIOTAP_FLAGS:
            printf("\tflags: %02x\n", *iter->this_arg);
            break;
        case IEEE80211_RADIOTAP_RATE:
            printf("\trate: %.2f Mbit/s\n", (double)*iter->this_arg/2);
            break;
#define IEEE80211_CHAN_A (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM)
#define IEEE80211_CHAN_G (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM)
        case IEEE80211_RADIOTAP_CHANNEL:
            {
                phy_freq = le16toh(*(uint16_t*)iter->this_arg);
                iter->this_arg = iter->this_arg + 2;
                int x = le16toh(*(uint16_t*)iter->this_arg);
                printf("\tfreq: %d type: ", phy_freq);
                if ((x & IEEE80211_CHAN_A) == IEEE80211_CHAN_A)
                {
                    printf("A\n");
                }
                else if ((x & IEEE80211_CHAN_G) == IEEE80211_CHAN_G)
                {
                    printf("G\n");
                }
                else if ((x & IEEE80211_CHAN_2GHZ) == IEEE80211_CHAN_2GHZ)
                {
                    printf("B\n");
                }
                break;
            }
        case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
            signal = *(signed char*)iter->this_arg;
            printf("\tsignal: %d dBm\n", signal);
            break;
        case IEEE80211_RADIOTAP_RX_FLAGS:
            printf("\tRX flags: %#.4x\n", le16toh(*(uint16_t *)iter->this_arg));
            break;
        case IEEE80211_RADIOTAP_ANTENNA:
            printf("\tantenna: %x\n", *iter->this_arg);
            break;
        case IEEE80211_RADIOTAP_RTS_RETRIES:
        case IEEE80211_RADIOTAP_DATA_RETRIES:
        case IEEE80211_RADIOTAP_FHSS:
        case IEEE80211_RADIOTAP_DBM_ANTNOISE:
        case IEEE80211_RADIOTAP_LOCK_QUALITY:
        case IEEE80211_RADIOTAP_TX_ATTENUATION:
        case IEEE80211_RADIOTAP_DB_TX_ATTENUATION:
        case IEEE80211_RADIOTAP_DBM_TX_POWER:
        case IEEE80211_RADIOTAP_DB_ANTSIGNAL:
        case IEEE80211_RADIOTAP_DB_ANTNOISE:
        case IEEE80211_RADIOTAP_TX_FLAGS:
        break;
        default:
            printf("\tBOGUS DATA\n");
            break;
    }
}
int sniff80211::parse_radiotap(const char* radiotap_buf)
{
    struct ieee80211_radiotap_iterator iter;
    int err;
    int j;
    err = ieee80211_radiotap_iterator_init(&iter,
        (struct ieee80211_radiotap_header *)radiotap_buf,
        1000, NULL);
    if (err)
    {
        printf("not valid radiotap...\n");
        return -1;
    }
    j = 0;

    while (!(err = ieee80211_radiotap_iterator_next(&iter)))
    {
        printf("next[%d]: index: %d size: %d\n",
                    j, iter.this_arg_index, iter.this_arg_size);
        if (iter.is_radiotap_ns)
        {
            print_radiotap_namespace(&iter);
        }
        j++;
    }
    return 0;

}

int sniff80211::recieve_packet(int socket,QList<wifiList::wifi_list> *wlist,QList<macList::mac_list> *mlist)
{
    //qDebug()<<"---------1----------";
    int ret=0;
    struct timeval tv;
    static fd_set read_fds;
    char buffer[65535];
#define BUFFER_SIZE 65535
    tv.tv_sec = 10;
    tv.tv_usec = 100;
    //qDebug()<<"---------2----------";
    FD_ZERO(&read_fds);
    //qDebug()<<"---------3----------";
    FD_SET(socket,&read_fds);
    //qDebug()<<"---------4----------";
    ret = select(socket+1,&read_fds,NULL,NULL,&tv);
    //qDebug()<<ret<<"      "<<socket;
    if(ret == -1 && errno ==EINTR)
    {
        return -1;
    }
    else if(ret == 0)
    {
        return -1;
    }
    else if(ret < 0)
    {
        return -1;
    }
    if(FD_ISSET(socket,&read_fds))
    {
        memset(buffer,'\0',BUFFER_SIZE);
        ret =recv(socket,buffer,BUFFER_SIZE,MSG_DONTWAIT);
        if(ret <= 0)
        {
            return -1;
        }
        //qDebug()<<"-------------------";
        parse_packet_wlan(buffer,wlist,mlist);
    }
    return 0;

}
int sniff80211::parse_packet_wlan(const char *buffer,QList<wifiList::wifi_list> *wlist,QList<macList::mac_list> *mlist )
{
    //qDebug()<<"parse packet";
//    int hdrlen = 0;
    uint16_t fc=0;
    uint8_t *ra=NULL;
    uint8_t *ta=NULL;
    uint8_t *bssid=NULL;
//    char mac[32];
    struct ieee80211_radiotap_header* radiotap_header = NULL;
    struct wlan_frame *wh=NULL;
    struct beaconInfo *bi = NULL;
    if(buffer == NULL)
    {
        return -1;
    }
    radiotap_header = (struct ieee80211_radiotap_header*)buffer;
    int radiotap_len = radiotap_header->it_len;
    wh = (struct wlan_frame*)(buffer+radiotap_len);
    fc = le16toh(wh->fc);
//    int wlan_type = (fc & 0xfc);
    int type = (fc & 0xc)>>2;
    int stype = (fc & 0xf0)>>4;
    int toDS = (fc & 0x100)>>8;
    int fromDS = (fc & 0x200)>>9;
    if(type == 0x02)//data frame
    {
        if(stype == 0x00)//data
        {
            if( toDS == 0 && fromDS == 0 )//ibss
            {
                ra = wh->addr1;
                ta = wh->addr2;
                bssid = wh->addr3;
                macList::mac_list tmp;
                char mac[32];

                mac2str(mac,ta,':');
                macList m;
                if(!m.searchMacKey(mlist,mac))
                {
                    strcpy(tmp.devmac,mac);
                    mac2str(mac,bssid,':');

                    //m.searchMacKey(mlist,mac);
                    strcpy(tmp.ap,mac);

                    qDebug() << "add  ibss maclist"<<tmp.ap <<tmp.devmac;
                    //qDebug() <<"--------------------";
                    mlist->append(tmp);
                    //qDebug() <<"--------------------";
                    //emit datachanged();
                }

            }
            else if( toDS == 1 && fromDS == 0 ) //to ap
            {
                bssid = wh->addr1;
                ta = wh->addr2;
                ra = wh->addr3;
                macList::mac_list tmp;
                char mac[32];

                mac2str(mac,ta,':');
                macList m;
                if(!m.searchMacKey(mlist,mac))
                {
                    strcpy(tmp.devmac,mac);
                    mac2str(mac,bssid,':');

                    //m.searchMacKey(mlist,mac);
                    strcpy(tmp.ap,mac);
                    qDebug() << "add to ap maclist"<<tmp.ap <<tmp.devmac;
                    //qDebug() <<"--------------------";
                    mlist->append(tmp);
                    //qDebug() <<"--------------------";
                    //emit datachanged();
                }

            }
            else if( toDS == 0 && fromDS ==1 )//from ap
            {
                ra = wh->addr1;
                bssid = wh->addr2;
                ta = wh->addr3;
                macList::mac_list tmp;
                char mac[32];

                mac2str(mac,ta,':');
                macList m;
                if(!m.searchMacKey(mlist,mac))
                {
                    strcpy(tmp.devmac,mac);
                    mac2str(mac,bssid,':');

                    //m.searchMacKey(mlist,mac);
                    strcpy(tmp.ap,mac);
                    qDebug() << "add from ap maclist"<<tmp.ap <<tmp.devmac;
                    //qDebug() <<"--------------------";
                    mlist->append(tmp);
                    //qDebug() <<"--------------------";
                    //emit datachanged();
                }

            }
            else
            {

            }

        }
        else if(stype == 0x08) //qos data
        {
            ra = wh->addr1;
            ta = wh->addr2;
            bssid = wh->addr3;
            macList::mac_list tmp;
            char mac[32];

            mac2str(mac,ta,':');
            macList m;
            if(!m.searchMacKey(mlist,mac))
            {
                strcpy(tmp.devmac,mac);
                mac2str(mac,bssid,':');

                //m.searchMacKey(mlist,mac);
                strcpy(tmp.ap,mac);
                qDebug() << "add qos data maclist"<<tmp.ap <<tmp.devmac;
                //qDebug() <<"--------------------";
                mlist->append(tmp);
                //qDebug() <<"--------------------";
                //emit datachanged();
            }


        }
    }
    else if(type == 0x01)//control frame
    {
        if(stype == 0x0b)//RTS
        {
            ra = wh->addr1;//STA
            ta = wh->addr2;//STA transimition
        }
        else if(stype == 0x0c)//CTS
        {
            ta = wh->addr1;
        }

    }
    else if(type == 0x0)
    {
        ra = wh->addr1;
        ta = wh->addr2;
        bssid = wh->addr3;
        if(stype == 0x08)//beacon
        {
            bi = (struct beaconInfo*)(buffer+radiotap_len+24);
            char ssid[32];
            memcpy(ssid,bi->Sname.name,bi->Sname.length);
            ssid[bi->Sname.length]='\0';
            wifiList w;
            if(!w.searchKey(wlist,ssid))
            {
                wifiList::wifi_list tmp;
                char mac[32];
                mac2str(mac,bssid,':');
                strcpy(tmp.apMac,mac);
                strcpy(tmp.ssid,ssid);
                qDebug() << "add wifilist"<<tmp.apMac <<tmp.ssid;
                //qDebug() <<"--------------------";
                wlist->append(tmp);
                //qDebug() <<"--------------------";
                emit datachanged();
            }

        }
    }
    else
    {
        return -1;
    }
    return 0;
}
