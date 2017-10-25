/*************************************************************************
	> File Name: lib.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 18时20分41秒
 ************************************************************************/
#ifndef LIBC 
#define LIBC LIBC
#include<stdio.h>
#include<aeshead.h>
#include<global.h>
//u8Xu8
u8 byteXbyte(u8 A,u8 B)
{
    u8 result=0;
    return result;
}
//xTimes
u8 xTimes(u8 byte)
{
    u8 temp=byte<<1;
    byte=byte>>7;
    if(byte)
        temp=temp^0x1B;
    return temp;
}
//对于一个字节数组(4个字节),向左循环移动n位
void leftShift(u8 *row,int n)
{
    n=n%4;
    u8 temp[4];
    for(int i=0;i<4;i++)
        temp[i]=row[i];
    for(int i=0;i<4-n;i++)
        row[i]=temp[i+n];
    for(int i=0;i<n;i++)
        row[4-n+i]=temp[i];
}
//显示n个字节
void dispByte(u8 *b,int n)
{
    for(int i=0;i<n;i++)
    {
        if(0==i%4&&i!=0)
            printf("\n");
        printf("0x%02x\t",b[i]);
    }
    printf("\n");
}
//显示状态
void dispState(u8 *state)
{
    for(int i=0;i<(DATALENGTH/8);i++)
        printf("%02x",state[i]);
    printf("\n");
}
//显示第row行密钥
void dispKey(int row)
{
    for(int i=0;i<(KEYLENGTH/8);i++)
        printf("%02x",W[4*row+i/4][i%4]);
    printf("\n");
}
void dispSbox()
{
    printf("\t\t以下显示S盒:\n\t\t\t");
    for(int i=0;i<16;i++)
        printf("0x%02x\t",i);
    printf("\n");
    for(int i=0;i<256;i++)
    {
        if(i%16==0)
            printf("\n0x%x0\t\t",i/16);
        printf("0x%02x\t",S[i]);
    }
    printf("\n\t\tS盒显示结束\n");
}
#endif
/*
int main()
{
    u8 test[4]={0x1,0x2,0x3,0x4};
    dispByte(test,4);
    leftShift(test,1);
    dispByte(test,4);
    leftShift(test,2);
    dispByte(test,4);
    leftShift(test,3);
    dispByte(test,4);
    leftShift(test,4);
    dispByte(test,4);
    return 0;
}

int main()
{
    u8 rc=0x01;
    for(int i=0;i<256;i++)
    {
        if(i%4==0)
            printf("\n");
        printf("0x%02x\t",rc);
        rc=xTimes(rc);
    }
    printf("\n");
}
*/
