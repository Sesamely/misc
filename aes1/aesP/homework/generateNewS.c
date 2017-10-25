/*************************************************************************
	> File Name: generateNewS.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 23时47分10秒
 ************************************************************************/

#include<stdio.h>
#include<lib.c>
#include<aeshead.h>
#define NO_USE_1    1
#define USE_2       2
#include<global.h>

//放射
/*
void X(u8 *b)
{
    u8 temp[8];
    temp[0]=b[0]^b[4]^b[5]^b[6]^b[7];
    temp[1]=b[0]^b[1]^b[5]^b[6]^b[7];
    temp[2]=b[0]^b[1]^b[2]^b[6]^b[7];
    temp[3]=b[0]^b[1]^b[2]^b[3]^b[7];
    temp[4]=b[0]^b[1]^b[2]^b[3]^b[4];
    temp[5]=b[1]^b[2]^b[3]^b[4]^b[5];
    temp[6]=b[2]^b[3]^b[4]^b[5]^b[6];
    temp[7]=b[3]^b[4]^b[5]^b[6]^b[7];
    for(int i=0;i<8;i++)
        b[i]=temp[i];
}
*/
void X(u8 *b)
{
    u8 temp=*b;
    u8 bits[8]={};
    u8 bitresult[8]={};
    for(int i=0;i<8;i++)
    {
        bits[i]=temp&0x01;
        temp=temp>>1;
        //printf("0x%02x\t",bits[i]);
    }
    //printf("\n");
    bitresult[0]=bits[0]^bits[4]^bits[5]^bits[6]^bits[7]^0x01;
    bitresult[1]=bits[0]^bits[1]^bits[5]^bits[6]^bits[7]^0x01;
    bitresult[2]=bits[0]^bits[1]^bits[2]^bits[6]^bits[7];
    bitresult[3]=bits[0]^bits[1]^bits[2]^bits[3]^bits[7];
    bitresult[4]=bits[0]^bits[1]^bits[2]^bits[3]^bits[4];
    bitresult[5]=bits[1]^bits[2]^bits[3]^bits[4]^bits[5]^0x01;
    bitresult[6]=bits[2]^bits[3]^bits[4]^bits[5]^bits[6]^0x01;
    bitresult[7]=bits[3]^bits[4]^bits[5]^bits[6]^bits[7];

    *b=0x00;
    for(int i=0;i<8;i++)
    {
        *b^=bitresult[i]<<i;
       // printf("0x%02x\t",bitresult[i]);
    }
    //printf("\n0x%02x\n\n",*b);
}
void generateNewS(u8 multiplicator)
{
    for(int i=0;i<256;i++)
        if(i==0)
            S[i]=0;
        else 
            S[i]=index3[(log3[i]*multiplicator)%255];
    for(int i=0;i<256;i++)
        X((u8 *)&S[i]);
}
/*
int main()
{
    generateNewS();
    dispByte(S,256);
    return 0;
}
*/
