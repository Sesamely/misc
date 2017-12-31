/*************************************************************************
	> File Name: generateNewS.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 23时47分10秒
 ************************************************************************/

#include<stdio.h>
#include<lib.c>
#include<aeshead.h>
#include<global.h>
#include<stastic.c>
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
void X(u8 *b,int ind,u8 var)
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
    bitresult[0]=bits[(ind)%8]^bits[(ind+1)%8]^bits[(ind+2)%8]^bits[(ind+3)%8]^bits[(ind+4)%8];
    bitresult[1]=bits[(ind+5)%8]^bits[(ind+1)%8]^bits[(ind+2)%8]^bits[(ind+3)%8]^bits[(ind+4)%8];
    bitresult[2]=bits[(ind+5)%8]^bits[(ind+6)%8]^bits[(ind+2)%8]^bits[(ind+3)%8]^bits[(ind+4)%8];
    bitresult[3]=bits[(ind+5)%8]^bits[(ind+6)%8]^bits[(ind+7)%8]^bits[(ind+3)%8]^bits[(ind+4)%8];
    bitresult[4]=bits[(ind+5)%8]^bits[(ind+6)%8]^bits[(ind+7)%8]^bits[(ind+8)%8]^bits[(ind+4)%8];
    bitresult[5]=bits[(ind+5)%8]^bits[(ind+6)%8]^bits[(ind+7)%8]^bits[(ind+8)%8]^bits[(ind+9)%8];
    bitresult[6]=bits[(ind+6)%8]^bits[(ind+7)%8]^bits[(ind+8)%8]^bits[(ind+9)%8]^bits[(ind+10)%8];
    bitresult[7]=bits[(ind+7)%8]^bits[(ind+8)%8]^bits[(ind+9)%8]^bits[(ind+10)%8]^bits[(ind+11)%8];

    *b=0x00;
    for(int i=0;i<8;i++)
    {
        *b^=bitresult[i]<<i;
       // printf("0x%02x\t",bitresult[i]);
    }
    *b=*b^var;
    //printf("\n0x%02x\n\n",*b);
}
void generateNewS(u8 multiplicator,int ind,u8 var)
{
    for(int i=0;i<256;i++)
        if(i==0)
            S[i]=0;
        else 
            S[i]=index3[(log3[i]*multiplicator)%255];
    for(int i=0;i<256;i++)
        X((u8 *)&S[i],ind,var);
}


int main()
{
    u8 m=0x01;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            printf("\n\n次方数：0x%02x\t\t循环开始值 ：%d\n",m^0xFF,j);
            generateNewS(m^0xFF,j,0x63);
            dispSbox();
            analysisSbox();
        }
        m=m<<1;
    }
    return 0;
}
