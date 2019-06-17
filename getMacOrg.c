/*根据mac前缀(形如00-00-00)查找organzation
先将mac_org.log读取到内存，然后进行折半查找
@auther: Anker @date:2013-12-18
*/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "getMacOrg.h"
void print_mac_org(const mac_org *macorg,char org_name[ORG_NAME_LEN])
{
    //printf("mac key:%d,org_name:%s\n",macorg->key, macorg->org_name);
    strcpy(org_name,macorg->org_name);
}
//将mac前缀转换为数字，前缀格式为:00-00-00
uint32_t  macprefix2uint(const char *mac_prefix)
{
	char mac[8] = {0};
    //printf("mac:%s\n",mac_prefix);
    sscanf(mac_prefix, "%c%c-%c%c-%c%c",&mac[0],&mac[1],&mac[2],&mac[3],&mac[4],&mac[5]);
	return  strtoul(mac,0,16);
}

//二分查找过程
int32_t binary_search(mac_org *macorg, int32_t n, uint32_t key)
{
    //在有序表macorg[0..n-1]中进行二分查找，成功时返回结点的位置，失败时返回-1
	int32_t low = 0, high = n-1, mid; //置当前查找区间上、下界的初值
    //printf("%d %d\n",macorg[low].key,macorg[high].key);
	if(macorg[low].key == key)
	{
		return low;
	}
	if(macorg[high].key == key)
	{
		return high;
	}
	while(low <= high)
	{
		//当前查找区间macorg[low..high]非空
		mid = low + ((high - low) / 2);
		//使用 (low + high) / 2 会有整数溢出的问题
		//（问题会出现在当low + high的结果大于表达式结果类型所能表示的最大值时，
		//这样，产生溢出后再/2是不会产生正确结果的，而low+((high-low)/2)不存在这个问题
		if(macorg[mid].key == key)
		{
			return mid; //查找成功返回
		}
		if(macorg[mid].key > key)
		{
			high = mid - 1; //继续在macorg[low..mid-1]中查找
		}
		else
		{
			low = mid + 1; //继续在macorg[mid+1..high]中查找
		}
	}
	return -1; //当low>high时表示查找区间为空，查找失败
}//BinSeareh

//给定一个mac前缀，获取对应的公司名称
int get_org_by_mac(const char *mac_prefix, mac_org **rmg)
{
    //printf("-------------------------\n");
	mac_org buffer[MAC_TYPE_COUNT];
	size_t read_num;
	uint32_t key = macprefix2uint(mac_prefix);
	int pos = -1;
	FILE *fp;
	if((fp = fopen(MAC_ORG_FILE, "rb")) == NULL)
	{
		printf("Failed to open mac log file: %s,errno:%u,reason:%s\n",MAC_ORG_FILE, errno, strerror(errno));
		//PRINT_ERROR_POS();
		goto FAILED;
	}
	fflush(stdin);
	read_num = fread((void *)buffer, sizeof(mac_org), MAC_TYPE_COUNT, fp);
    //printf("++++++++++++++++  read_num= %d  key= %d   \n",read_num,key);
	if (read_num == 0 && errno != 0)
	{
		printf("Failed to read mac log file: %s,errno:%u,reason:%s\n",MAC_ORG_FILE, errno, strerror(errno));
		//PRINT_ERROR_POS();
		goto FAILED;
	}
	pos = binary_search(buffer, read_num, key);
    //printf("pos = %d\n",pos);
	if (pos != -1)
	{
		*rmg = (mac_org *)malloc(sizeof(mac_org));
		if (rmg == NULL)
		{
			printf("Failed to malloc memory,errno:%u,reason:%s\n",errno,strerror(errno));
			//PRINT_ERROR_POS();
			goto FAILED;
		}
		memset(*rmg, 0, sizeof(mac_org));
		memcpy(*rmg, &buffer[pos], sizeof(mac_org));
	}
	fclose(fp);
	return 0;
	FAILED:
		if(fp)
		{
			fclose(fp);
		}
		return -1;
}

//mac前缀格式是00-00-00
//int main(int argc,char **argv)
int searchOrg(char *mac_prefix,char org_name[ORG_NAME_LEN])
{
    //time_t time1,time2;
    //time(&time1);
    mac_org *pmacorg = NULL;
    //char *mac_prefix = NULL;
    //if (argc != 2)
    //{
        //fprintf(stderr,"Paramer error,please input mac prefix.\n");
        //return -1;
    //}
	if(access(MAC_ORG_FILE, F_OK) != 0)
	{
        //printf("Can not found  mac2org file:%s.\n", MAC_ORG_FILE);
		return -1;
	}
    //mac_prefix = argv[1];
    //printf("%s\n",mac_prefix);
	if (get_org_by_mac(mac_prefix, &pmacorg) == -1)
	{
        //printf("Failed to search mac.\n");
		//PRINT_ERROR_POS();
		return -1;
	}
	if (!pmacorg)
	{
        //printf("Can not find the mac prefix:%s\n", mac_prefix);
	}
	else
	{
        //time(&time2);
        //printf("Successed to find the mac info, cost time:%lds\n", time2 - time1);
        print_mac_org(pmacorg,org_name);
		free(pmacorg);
	}
	return 0;
}




