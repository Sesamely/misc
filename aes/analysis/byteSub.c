/*************************************************************************
	> File Name: byteSub.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 18时42分32秒
 ************************************************************************/
#ifndef BYTESUB
#define BYTESUB BYTESUB

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
    for(int i=0;i<(DATALENGTH/8);i++)
        state[i]=subByte(state[i]);
}

#endif

#ifndef SUBBYTEUSED 
#define SUBBYTEUSED SUBBYTEUESD
int main()
{
    u8 input=60;
    printf("输入十进制为:\t%d\n",input);
    printf("输入十六进制为:\t0x%02x\n",input);
    input=subByte(input);
    printf("输出十进制为:\t%d\n",input);
    printf("输出十六进制为:\t0x%02x\n",input);
    return 0;
}
#endif
