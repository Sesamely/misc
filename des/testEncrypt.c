/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月26日 星期二 19时58分31秒
 ************************************************************************/

#include<stdio.h>
#include"./DESencryp.c"
#include"./generateKey.c"

int main()
{ 
    char M[MESSAGELENGTH]={
        0,0,1,1,0,0,0,0,
        0,0,1,1,0,0,0,1,
        0,0,1,1,0,0,1,0,
        0,0,1,1,0,0,1,1,
        0,0,1,1,0,1,0,0,
        0,0,1,1,0,1,0,1,
        0,0,1,1,0,1,1,0,
        0,0,1,1,0,1,1,1
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
    dispM_C(M);
    Encrypt(M,RealK,C);
    dispM_C(C);
    return 0;
}