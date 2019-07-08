#ifndef SNIFF80211_H
#define SNIFF80211_H

#include <QWidget>
#include "radiotap_iter.h"
#include "wifilist.h"
#include "maclist.h"
class sniff80211 : public QWidget
{
    Q_OBJECT
public:
    explicit sniff80211(QWidget *parent = 0);
    struct wlan_frame
    {
        uint16_t fc;
        uint16_t duration;
        uint8_t addr1[6];
        uint8_t addr2[6];
        uint8_t addr3[6];
        uint16_t seq;
        union {
            uint16_t qos;
            uint8_t addr4[6];
            struct {
                uint8_t qos;
                uint32_t ht;

            } __attribute__ ((packed)) ht;
            struct {
                uint8_t addr4[6];
                uint16_t qos;
                uint32_t ht;
            } __attribute__ ((packed)) addr4_qos_ht;
        } u;

    } __attribute__ ((packed)) ;
    struct SSID {
        uint8_t version;
        uint8_t length;
        char name[100];
    } __attribute__ ((packed)) ;
    struct beaconInfo {
        uint64_t timestamp;
        uint16_t beacon_interval;
        uint16_t capability_info;
        struct SSID Sname;
    } __attribute__ ((packed)) ;
    struct associationInfo{
        uint16_t capability_Info;
        uint16_t listen_interval;
        struct SSID Sname;
    } __attribute__ ((packed));
    void mac2str(char szMac[20],unsigned char* pMac,const char chKen);
    void print_radiotap_namespace(struct ieee80211_radiotap_iterator *iter);
    int parse_radiotap(const char* radiotap_buf);
    void setFlag();
    int recieve_packet(int socket,QList<wifiList::wifi_list> *wlist,QList<macList::mac_list> *mlist);
    void readWifiDataFromFile(QList<wifiList::wifi_list> *wlist);
    int parse_packet_wlan(const char *buffer,QList<wifiList::wifi_list> *wlist,QList<macList::mac_list> *mlist,int pktlen);

    //根据网络包获取频率
	int get_freq_radiotap(const char* radiotap_buf);
    int get_channel_radiotap(const char* radiotap_buf);
signals:
    void datachanged();
    void macupdate();
public slots:
private:
    int flag;
};

#endif // SNIFF80211_H
