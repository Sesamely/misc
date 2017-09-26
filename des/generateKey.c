/*************************************************************************
	> File Name: generateKey.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月26日 星期二 14时39分14秒
 ************************************************************************/

#include<stdio.h>

#ifndef LENGTH
#define LENGTH
#define CDLENGTH 28
#define KEYLENGTH 64
#define REALKEYLENGTH 56
#endif

static const int PS2[] = {
	   14, 17, 11, 24,  1,  5,
		3, 28, 15,  6, 21, 10,
	   23, 19, 12,  4, 26,  8,
	   16,  7, 27, 20, 13,  2,
	   41, 52, 31, 37, 47, 55,
	   30, 40, 51, 45, 33, 48,
	   44, 49, 39, 56, 34, 53,
	   46, 42, 50, 36, 29, 32
};
static const int PS1[] = {
	   57, 49, 41, 33, 25, 17,  9,
		1, 58, 50, 42, 34, 26, 18,
	   10,  2, 59, 51, 43, 35, 27,
	   19, 11,  3, 60, 52, 44, 36,
	   63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
	   14,  6, 61, 53, 45, 37, 29,
	   21, 13,  5, 28, 20, 12,  4
};
static const int tableForLeftCirculate[] = {
  1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1  
};

void permutateSelect1(char *k64,char *C,char *D)
{
    for(int i=0;i<REALKEYLENGTH;i++)
    {
        if(i<CDLENGTH)
            C[i]=k64[PS1[i]-1];
        else
            D[i-CDLENGTH]=k64[PS1[i]-1];
    }
}

void permutateSelect2(char *k48,char *C,char *D)
{
    char tempForCD[REALKEYLENGTH]={};
    for(int i=0;i<REALKEYLENGTH;i++)
    {
        if(i<CDLENGTH)
            tempForCD[i]=C[i];
        else
            tempForCD[i]=D[i-CDLENGTH];
    }
    for(int i=0;i<48;i++)
        k48[i]=tempForCD[PS2[i]-1];
}

void circularShifft1(char *C_D)
{
    char temp=C_D[0];
    for(int i=1;i<CDLENGTH;i++)
        C_D[i-1]=C_D[i];
    C_D[CDLENGTH-1]=temp;
}

void circularShifft2(char *C_D)
{
    char temp1=C_D[0],temp2=C_D[1];
    for(int i=2;i<CDLENGTH;i++)
        C_D[i-2]=C_D[i];
    C_D[CDLENGTH-2]=temp1;
    C_D[CDLENGTH-1]=temp2;
}

void generateKey(char *k64,char k48[][48])
{
    char Ctemp[CDLENGTH]={};
    char Dtemp[CDLENGTH]={};
    permutateSelect1(k64,Ctemp,Dtemp);
    for(int i=0;i<16;i++)
    {
        if(1==tableForLeftCirculate[i])
        {
            circularShifft1(Ctemp);
            circularShifft1(Dtemp);
        }
        else
        {
            circularShifft2(Ctemp);
            circularShifft2(Dtemp);
        }
        permutateSelect2(k48[i],Ctemp,Dtemp);
    }
}

void dispRealKey(char k48[][48])
{
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<48;j++)
        {
            if(j%8==0)
                printf("   ");
            printf("%d ",k48[i][j]);    
        }
        printf("\n");
    }
}
