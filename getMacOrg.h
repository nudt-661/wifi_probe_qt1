#ifndef GETMACORG_H
#define GETMACORG_H

#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

#define MAC_PREFIX_LEN             10          //mac前缀长度
#define ORG_NAME_LEN              96           //公司名称长度
#define MAC_TYPE_COUNT            52754        //记录个数
//#define MAC_ORG_FILE            "mac2org.log"    //mac前缀对应公司名称文件
#define MAC_ORG_FILE            "mac_org2.log"    //mac前缀对应公司名称文件

#define PRINT_ERROR_POS()  do{                        \
    printf( "File: "__FILE__", Line:%d\n",  __LINE__ ) ; \
}while(0);

//mac前缀和公司名称对应关系
typedef struct mac_org
{
    uint32_t key;//mac前缀作为key
    char org_name[ORG_NAME_LEN];//公司名称
}mac_org;
void print_mac_org(const mac_org *macorg,char org_name[ORG_NAME_LEN]);
uint32_t  macprefix2uint(const char *mac_prefix);
int32_t binary_search(mac_org *macorg, int32_t n, uint32_t key);
int get_org_by_mac(const char *mac_prefix, mac_org **rmg);
int searchOrg(char *mac_prefix,char org_name[ORG_NAME_LEN]);

#ifdef __cplusplus
}
#endif
#endif // GETMACORG_H
