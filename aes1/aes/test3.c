/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 23时22分39秒
 ************************************************************************/

#include<stdio.h>
#include"./encrypt.c"

int main()
{
    u32 msg[4]={0x86153566,0xda781734,0x01a198af,0x00010001};
    u32 k[4]=  {0x60153594,0xda791714,0x710198ae,0x00012001};
    for(int i=0;i<4;i++)
        msg[i]=msg[i]^k[i];
    dispWords(msg,4);
    for(int i=0;i<4*4;i++)
        subByte(&((u8 *)msg)[i]);
    dispWords(msg,4);
    return 0;
}
