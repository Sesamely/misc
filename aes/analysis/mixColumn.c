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
//发现每次多项式乘法后只是将CX右移动一位
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

int main()
{
    u8 col[4]={0xd2,0xf5,0x70,0x6c};
    u8 row[4]={0x02,0x03,0x01,0x01};
    u8 result[4]={};
    printf("\n以下显示列混合运算结果\n(当时检查最后一位出现问题,原因是从3的对数表找出的两个数的和应该 mod255 而不是 mod256 )\n!!!(a^255=e,a^256=a)\n");
    dispByte(col,4);
    for(int i=0;i<4;i++)
    {
        result[i]=wordXword(row,col);
        changeCx(row);
    }
    dispByte(result,4);
    return 0;
}
/*
int main()
{
    u8 test[DATALENGTH/8]={
        0x08,0x95,0x00,0x19,
        0x77,0xbd,0x80,0xd9,
        0x1d,0xf0,0x49,0xe9,
        0x74,0xa4,0x34,0x88
    };
    dispState(test);
    mixColumn(test);
    printf("\n");
    dispState(test);
    return 0;
}
*/
