/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 23时07分44秒
 ************************************************************************/

#include<stdio.h>
#include"./encrypt.c"

int main()
{
    u32 temp=0x60153594;
    u32 Rcon=0;
    ((u8 *)&Rcon)[3]=RC[1];
    printf("0x%x\n",RC[1]);
    dispWord(&Rcon);
    dispWord(&temp);
    Rotl2(&temp);
    dispWord(&temp);
    for(int i=0;i<4;i++)
        subByte(&((u8 *)&temp)[i]);
    dispWord(&temp);
    temp=temp^Rcon;
    dispWord(&temp);
    printf("0x%x\n",0x00012001^0x93fab8ff);
    return 0;
}
