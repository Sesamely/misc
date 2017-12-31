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

//S盒置换
void byteSub(u8 *state)
{
    for(int i=0;i<(DATALENGTH/8);i++)
        state[i]=S[state[i]];
}
//逆S盒置换
void _byteSub(u8 *state)
{
    for(int i=0;i<DATALENGTH/8;i++)
        state[i]=_S[state[i]];
}

#endif
