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
