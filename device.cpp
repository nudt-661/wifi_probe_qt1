#include "device.h"
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <string.h>
#include <unistd.h>
#include <linux/wireless.h>
#include<QDebug>
#include<ifaddrs.h>
#include<arpa/inet.h>
extern char wlanName[100];
device::device()
{

}
bool device::set_promisc_mode(const char* eth/*, bool promisc*/)
{
    //int org_errno = 0;
    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
            return false;

#ifdef SOCKET
    struct ifreq ifreq;
    memset(&ifreq, 0, sizeof(ifreq));
    strncpy(ifreq.ifr_name, eth, IF_NAMESIZE - 1);
    ioctl(fd, SIOCGIFFLAGS, &ifreq);
    // check if eth is up
    if (!(ifreq.ifr_flags & IFF_UP))
        {
            printf("%s is not up yet.\n", eth);
            return false;
    }
    if (promisc)
            ifreq.ifr_flags |= IFF_PROMISC;
    else
            ifreq.ifr_flags &= ~IFF_PROMISC;
    ioctl(fd, SIOCSIFFLAGS, &ifreq);
    if (close(fd))
            return false;
    return true;
#else

    struct iwreq iwreq;
    memset(&iwreq, 0, sizeof(iwreq));
    strncpy(iwreq.ifr_ifrn.ifrn_name, eth, IF_NAMESIZE - 1);
    ioctl(fd, SIOCGIWMODE, &iwreq);
    // check if eth is up
    //if (!(iwreq.ifr_flags & IFF_UP))
    {
        //printf("%s is not up yet.\n", eth);
        //return false;
    }
    if (1)
            iwreq.u.mode |= IW_MODE_MONITOR;
    else
            iwreq.u.mode &= ~IW_MODE_MONITOR;
    //ioctl(fd, SIOCSIWMODE, iwreq);
    //int i;
    if (ioctl(fd, SIOCSIWMODE, &iwreq) == -1)
    {
        printf("monitor set failed!!!!!\n");
        return false;
    }
    //for (i=0; i<1000; i++)
    {
        if (ioctl(fd, SIOCGIWFREQ, &iwreq) == -1)
            printf("freq get failed!!!!!\n");
        //printf("iwreq.u.freq m=%d, e=%d\n", iwreq.u.freq.m, iwreq.u.freq.e);
        //sleep(1);
    }
    iwreq.u.freq.m = 2412*100000;
    iwreq.u.freq.e = 1;
    iwreq.u.freq.i = 0;
    iwreq.u.freq.flags = 0;
    if (ioctl(fd, SIOCSIWFREQ, &iwreq) == -1)
        printf("freq set failed!!!!\n");
    return true;
#endif
}
/*
bool device::set_promisc_mode(const char*eth,bool promisc){
    //int org_errno = 0;
    qDebug()<<"set promisc mode";
    int fd;
    struct ifreq ifreq;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        return false;
    memset(&ifreq, 0, sizeof(ifreq));
    strncpy(ifreq.ifr_name, eth, IF_NAMESIZE - 1);
    ioctl(fd, SIOCGIFFLAGS, &ifreq);
        // check if eth is up
    if (!(ifreq.ifr_flags & IFF_UP))
    {
        printf("%s is not up yet.\n", eth);
                return false;
    }


    if (promisc)
        ifreq.ifr_flags |= IFF_PROMISC;
    else
        ifreq.ifr_flags &= ~IFF_PROMISC;
    ioctl(fd, SIOCSIFFLAGS, &ifreq);

    if (close(fd))
        return false;
    return true;
}
*/
int device::init_socket(const char* eth)
{
    //qDebug()<<"init socket"<<"eth"<<"\n";
    int ret = 0;
    int fd = -1;
    //qDebug()<<"eth"<<eth;
    if (!set_promisc_mode(eth/*, true*/))
    {

        qDebug()<<"set to promisc mode failed\n";
        return -1;
    }
    fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    //if(fd==-1);
    //qDebug()<<fd<<'\n';
    struct ifreq req;
    strcpy(req.ifr_name, eth);
    ioctl(fd, SIOCGIFINDEX, &req);
    struct sockaddr_ll addr;
    addr.sll_family = PF_PACKET;
    addr.sll_ifindex = req.ifr_ifindex;
    addr.sll_protocol = htons(ETH_P_ALL);
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_ll));
    return fd;
}
int device::get_hwinfo(char *eth,unsigned char *mac)
{
    struct ifreq ifr;
    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        return false;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, eth, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0)
    {
        printf("Could not get arptype\n");
        return -1;
    }
    printf("ARPTYPE %d\n%s\n", ifr.ifr_hwaddr.sa_family,ifr.ifr_hwaddr.sa_data);
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

    return ifr.ifr_hwaddr.sa_family;
}
void device::setChannel(int fd, int channel)
{
    int freq=0;
    switch(channel)
    {
        case 1:
            freq=2412;
        break;
        case 2:
            freq=2417;
            break;
        case 3:
            freq=2422;
            break;
        case 4:
            freq=2427;
            break;
        case 5:
            freq=2432;
            break;
        case 6:
            freq=2437;
            break;
        case 7:
            freq=2442;
            break;
        case 8:
            freq=2447;
            break;
        case 9:
            freq=2452;
            break;
        case 10:
            freq=2457;
            break;
        case 11:
            freq=2462;
            break;
        case 12:
            freq=5180;//2467;
            break;
        case 13:
            freq=5200;//2472;
            break;
        case 14:
            freq=5220;
            break;
        case 15:
            freq=5240;
            break;
        case 16:
            freq=5745;
            break;
        case 17:
            freq=5765;
            break;
        case 18:
            freq=5785;
            break;
        case 19:
            freq=5805;
            break;
        case 20:
            freq=5825;
            break;
        default:
            qDebug()<<"channel value error";
            break;
    }
    struct iwreq iwreq;
    memset(&iwreq,0,sizeof(iwreq));
    //qDebug()<<"++++++++++++++++++"<<wlanName;
    strncpy(iwreq.ifr_ifrn.ifrn_name,wlanName,IF_NAMESIZE-1);
    if(ioctl(fd,SIOCGIWFREQ,&iwreq)==-1)
    {
        qDebug()<<"freq get failed";
        return;
    }
    iwreq.u.freq.m=freq*100000;
    iwreq.u.freq.e=1;
    iwreq.u.freq.i=0;
    iwreq.u.freq.flags=0;
    if(ioctl(fd,SIOCSIWFREQ,&iwreq)==-1)
    {
        qDebug()<<"channel set failed";
        return;
    }
    //qDebug()<<"channel"<<channel<<"set";
}
int device::getNetName(char netName[100])
{
    //struct sockaddr_in *sin =NULL;
    struct ifaddrs *ifa = NULL,*ifList;
    char mac[16]={'\0'};
    if(getifaddrs(&ifList)<0)
    {
        return -1;
    }

    for(ifa=ifList;ifa != NULL;ifa=ifa->ifa_next)
    {
        //if(ifa->ifa_addr->sa_family == AF_INET)
        //{
        struct ifreq ifreq;
        int sock;

        //printf("iterfaceName:%s\n",ifa->ifa_name);
        if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
        {
            printf("socket create error!!!\n");
            return -1;
        }
        strcpy(ifreq.ifr_name,ifa->ifa_name);
        if(ioctl(sock,SIOCGIFHWADDR,&ifreq)<0)
        {
            printf("ioctl error");
            return -1;
        }
        memset(mac,'\0',16);
        memset(netName,'\0',100);
        snprintf(mac,16,"%02x%02x%02x%02x%02x%02x\0",
                (unsigned char)ifreq.ifr_hwaddr.sa_data[0],
                (unsigned char)ifreq.ifr_hwaddr.sa_data[1],
                (unsigned char)ifreq.ifr_hwaddr.sa_data[2],
                (unsigned char)ifreq.ifr_hwaddr.sa_data[3],
                (unsigned char)ifreq.ifr_hwaddr.sa_data[4],
                (unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
        if(strcmp(mac,"08beac0560ee\0")==0)
        {
                //printf("iterfaceName:%s\n",ifa->ifa_name);
                //printf("%s\n",mac);
                strcpy(netName,ifa->ifa_name);
                break;
        }
        //}
    }
    freeifaddrs(ifList);
    return 0;
}
