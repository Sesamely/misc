/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 18时56分57秒
 ************************************************************************/

#include<stdio.h>
#include"./getMatrix.c"
#include"./LUP-DECOMPOSITION.c"
#include"./storageMatrixInFile.c"

void initialP(int *P)
{
    for(int i=0;i<MAXCOL;i++)
        P[i]=i;
}

int main()
{
    double M[MAXROW][MAXCOL]={};//origin
    double B_X[MAXROW][MAXCOL]={};//storage the I and the inverse of the matrix
    int P[MAXCOL]={};
    initialP(P);
    char filename[40];
    char filenameForSave[40];
    int mOrder;
    //initate the matrix according to the prompt
    printf("please input the filename for M:\n>");
    scanf("%s",filename);
    printf("please input the matrix's order:\n>");
    scanf("%d",&mOrder);
//generate a matrix storaged in ./filename
    generateRandomMatrix(mOrder,filename);
//initial matrix
    getMatrix(M,filename,mOrder);
//auto generate I according to the order of the matrix
    autoCreateI(B_X,mOrder);
//LUP-DECOMPOSITION
    LUP_DECOMPOSITION(M,mOrder,P);
//*************************************************
    for(int i=0;i<mOrder;i++)
        LUP_SOLVE_extend(B_X,i,M,mOrder,P);
//save the matrix
    printf("please type the filename for saving the matrix's inverse\n which is suggseted to be named as 'Data/***' and\nCANNOT the same as the filename you have input!!!\n>");
    scanf("%s",filenameForSave);
    storageMatrix(B_X,mOrder,filenameForSave);
    return 0;
}


