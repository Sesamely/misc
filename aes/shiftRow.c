/*************************************************************************
	> File Name: shiftRow.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 19时59分50秒
 ************************************************************************/

#include<stdio.h>
#include<aeshead.h>
#include<lib.c>
#include<global.h>
void shiftRow(u8 *state)
{
    int CXR=0;
    int k=0;
    u8 temp[4][Nb]={};
    for(int j=0;j<Nb;j++)
        for(int i=0;i<4;i++)
            temp[i][j]=state[k++];
    //for(int i=0;i<4;i++)
    //    dispByte((u8 *)temp[i],4);
    //printf("\n");
    switch(Nb)
    {
        case 4:CXR=0;break;
        //case 6:
        //case 8:
        default:CXR=-1;break;
    }
    for(int i=0;i<3;i++)
        leftShift((u8 *)temp[i+1],CX[CXR][i]);
    //for(int i=0;i<4;i++)
    //    dispByte((u8 *)temp[i],4);
    //printf("\n");
    k=0;
    for(int j=0;j<Nb;j++)
        for(int i=0;i<4;i++)
            state[k++]=temp[i][j];
}

void _shiftRow(u8 *state)
{
    int CXR=0;
    int k=0;
    u8 temp[4][Nb]={};
    for(int j=0;j<Nb;j++)
        for(int i=0;i<4;i++)
            temp[i][j]=state[k++];
    switch(Nb)
    {
        case 4:CXR=0;break;
        //case 6:
        //case 8:
        default:CXR=-1;break;
    }
    for(int i=0;i<Nb-1;i++)
        leftShift((u8 *)temp[i+1],Nb-CX[CXR][i]);
    k=0;
    for(int j=0;j<Nb;j++)
        for(int i=0;i<4;i++)
            state[k++]=temp[i][j];
}

