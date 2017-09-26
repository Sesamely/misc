/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月26日 星期二 19时58分31秒
 ************************************************************************/

#include<stdio.h>
#include"./DESencryp.c"
#include"./generateKey.c"

void inverseK(char K[][48]);

int main()
{ 
    char M[MESSAGELENGTH]={
        1,0,0,0,1,0,1,1,
        1,0,1,1,0,1,0,0,
        0,1,1,1,1,0,1,0,
        0,0,0,0,1,1,0,0,
        1,1,1,1,0,0,0,0,
        1,0,1,0,1,0,0,1,
        0,1,1,0,0,0,1,0,
        0,1,1,0,1,1,0,1
    };
    char K[KEYLENGTH]={
        0,0,1,1,0,0,0,1,
        0,0,1,1,0,0,1,0,
        0,0,1,1,0,0,1,1,
        0,0,1,1,0,1,0,0,
        0,0,1,1,0,1,0,1,
        0,0,1,1,0,1,1,0,
        0,0,1,1,0,1,1,1,
        0,0,1,1,1,0,0,0
    };
    char C[MESSAGELENGTH]={};
    char RealK[16][48]={};
    generateKey(K,RealK);
    inverseK(RealK);
    dispM_C(M);
    Encrypt(M,RealK,C);
    dispM_C(C);
    return 0;
}

void inverseK(char K[][48])
{
    int i=0,j=15;
    while(i<j)
    {
        for(int k=0;k<48;k++)
        {
            char temp=K[i][k];
            K[i][k]=K[j][k];
            K[j][k]=temp;
        }
        i++;
        j--;
    }
}
