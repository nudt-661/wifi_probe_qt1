#ifndef DEVICE_H
#define DEVICE_H


class device
{
public:
    device();
    bool set_promisc_mode(const char*eth/*,bool promisc*/);
    int init_socket(const char* eth);
    int get_hwinfo(char *eth,unsigned char* mac);
    void setChannel(int fd,int channel);
    int getNetName(char netName[100]);

};

#endif // DEVICE_H
