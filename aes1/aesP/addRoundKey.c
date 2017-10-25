/*************************************************************************
	> File Name: addRoundKey.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 13时37分53秒
 ************************************************************************/

#include<stdio.h>
#include<global.h>
#include<aeshead.h>
#include<lib.c>

//轮密钥加
//轮密钥加逆(当前I控制轮密钥，所以正逆可以共用)
void addRoundKey(u8 *state)
{
    int kstart=(128/8)*I/4;//开始的字的位置
    for(int i=0;i<(DATALENGTH/8);i++)
        state[i]=state[i]^W[kstart+i/4][i%4];
}


/*
#include<expandK.c>
int main()
{
    
    u8 mainKey[] = {
        0x00,0x01,0x20,0x01,
        0x71,0x01,0x98,0xae,
        0xda,0x79,0x17,0x14,
        0x60,0x15,0x35,0x94
    };
    u8 msg[] = {
        0x00,0x01,0x00,0x01,
        0x01,0xa1,0x98,0xaf,
        0xda,0x78,0x17,0x34,
        0x86,0x15,0x35,0x66
    };
    expandKey(mainKey);

    I=1;
    dispState(msg);
    addRoundKey(msg);
    dispState(msg);
    addRoundKey(msg);
    dispState(msg);
    return 0;
}
*/
