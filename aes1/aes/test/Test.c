/*************************************************************************
	> File Name: Test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 20时18分39秒
 ************************************************************************/

#include<stdio.h>
#include"./encrypt.c"
/*
void xTime(u8 *A)
{
    u8 temp=*A>>7;
    *A=*A<<1;
    if(1==temp)
        *A=*A^0x1B;
}
*/
u8 xTime(u8 A)
{
    u8 temp=A<<1;
    A=A>>7;
    if(A)
        temp=temp^0x11B;
    return temp;
}
int main1()
{
    u8 ch[4]={0xd2,0xf5,0x70,0x6c};
    u8 temp[4]={};
    temp[0]=xTime(ch[0])^(xTime(ch[1])^ch[1])^ch[2]^ch[3];
    temp[1]=ch[0]^xTime(ch[1])^(xTime(ch[2])^ch[2])^ch[3];
    temp[2]=ch[0]^ch[1]^xTime(ch[2])^(xTime(ch[3])^ch[3]);
    temp[3]=(xTime(ch[0])^ch[0])^ch[1]^ch[2]^xTime(ch[3]);
    dispWord((u32 *)temp);
    return 0;
}

int main()
{
    u8 ch[4]={0xd2,0xf5,0x70,0x6c};
    u8 temp[4]={};
    temp[0]=xTime(ch[0])^ch[0];
    temp[1]=ch[1];
    temp[2]=ch[2];
    temp[3]=xTime(ch[3]);
    dispWord((u32 *)temp);
    printf("\n0x%x\n",temp[0]^temp[1]^temp[2]^temp[3]);
    return 0;
}
