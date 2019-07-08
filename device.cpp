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
device::device()
{

}
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
int device::init_socket(const char* eth)
{
    qDebug()<<"init socket\n";
    int ret = 0;
    int fd = -1;
    if (!set_promisc_mode(eth, true))
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
            freq=2467;
            break;
        case 13:
            freq=2472;
            break;
        default:
            qDebug()<<"channel value error";
            break;
    }
    struct iwreq iwreq;
    memset(&iwreq,0,sizeof(iwreq));
    strncpy(iwreq.ifr_ifrn.ifrn_name,"wlan0\0",IF_NAMESIZE-1);
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
