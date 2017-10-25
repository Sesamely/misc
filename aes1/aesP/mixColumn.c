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

//多项式乘
u8 wordXword(u8 *row,u8 *col)
{
    u8 temp=0;
    u8 result=0;
    for(int i=0;i<4;i++)
    {
        if(row[i]!=0&&col[i]!=0)
            temp=index3[((log3[row[i]]+log3[col[i]])%255)];
        else temp=(u8)0;
        result^=temp;
    }
    return result;
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
//列混合的逆
void _mixColumn(u8 *state)
{
    u8 cx[] ={0x0e,0x0b,0x0d,0x09};
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

