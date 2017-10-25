/*************************************************************************
	> File Name: expand.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 17时41分05秒
 ************************************************************************/

#include<stdio.h>
#include<global.h>
#include<aeshead.h>
#include<lib.c>
#include<byteSub.c>

void expandKey(const u8 *mainKey)
{
    u8 temp[4]={};
    u8 Rcon[4]={};
    int i=0;
    for(;i<Nk*4;i++)
        W[i/4][i%4]=mainKey[i];
    for(;i<Nb*(Nr+1)*4;i+=4)
    {
        //temp=W[i/4-1]-----i/4表示的是当前字
        for(int k=0;k<4;k++)
            temp[k]=W[i/4-1][k];
        if((i/4)%Nk==0)
        {
            //rolt变化
            leftShift(temp,1);
            //对于temp,按字节subByte
            for(int k=0;k<4;k++)
                temp[k]=subByte(temp[k]);
            //temp=temp^Rcon
            Rcon[0]=RC[(i/4)/Nk-1];
            for(int k=0;k<4;k++)
                temp[k]=temp[k]^Rcon[k];
        }
        //W[i/4]=W[i/4-Nk]^temp
        for(int k=0;k<4;k++)
            W[i/4][k]=temp[k]^W[i/4-Nk][k];
    }
}
