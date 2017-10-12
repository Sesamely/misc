/*************************************************************************
	> File Name: byteSub.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 18时42分32秒
 ************************************************************************/

#include<stdio.h>
#include<aeshead.h>
#include<global.h>
//#include<lib.c>
u8 subByte(u8 b)
{
    return S[b];
}
void byteSub(u8 *state)
{
    for(int i=0;i<DATALENGTH;i++)
        state[i]=subByte(state[i]);
}
/*
int main()
{
    u8 msg[DATALENGTH] = {
        0x3c,0x4f,0x03,0xc7
    };
    dispByte(msg,4);
    byteSub(msg);
    dispByte(msg,4);
    return 0;
}
*/
