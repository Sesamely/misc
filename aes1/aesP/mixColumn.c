/*************************************************************************
	> File Name: mixColumn.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 20时44分30秒
 ************************************************************************/

#include<stdio.h>
#include<aeshead.h>
#include<global.h>
#include<lib.c>

u8 wordXword(u8 *row,u8 *col)
{
    u8 temp=0;
    for(int i=0;i<4;i++)
        temp^=index3[((log3[row[i]]+log3[col[i]])%255)];
    return temp;
}
//发现每次多项式乘法只是将CX右移动一位
void changeCx(u8 *cx)
{
    u8 temp=cx[3];
    for(int i=0;i<3;i++)
        cx[3-i]=cx[2-i];
    cx[0]=temp;
}
//列混合
void mixColumn(u8 *state)
{
    u8 cx[] ={0x02,0x03,0x01,0x01};
    u8 temp[DATALENGTH/8]={};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            temp[4*j+i]=wordXword(cx,(u8 *)&state[4*j]);
        changeCx(cx);
    }
    for(int i=0;i<(DATALENGTH/8);i++)
        state[i]=temp[i];
}
/*
int main()
{
    u8 col[4]={0xd2,0xf5,0x70,0x6c};
    u8 row[4]={0x02,0x03,0x01,0x01};
    for(int i=0;i<4;i++)
    {
        printf("\n0x%02x\n",wordXword(row,col));
        changeCx(row);
    }
    return 0;
}
*/
/*int main()
{
    u8 test[DATALENGTH/8]={
        0x87,0x6e,0x46,0xa6,
        0xf2,0x4c,0xe7,0x8c,
        0x4d,0x90,0x4a,0xd8,
        0x97,0xec,0xc3,0x95
    };
    dispByte(test,16);
    mixColumn(test);
    printf("\n");
    dispByte(test,16);
    return 0;
}
*/
