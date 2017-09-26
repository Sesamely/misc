/*************************************************************************
	> File Name: storageMatrixInFile.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月24日 星期日 14时49分09秒
 ************************************************************************/


#include<stdio.h>
#include"./matrix.h"

typedef int bool;
//storage file for the matrix
bool storageMatrix(double M[][MAXCOL],int n,char *filename)
{
    FILE *fp;
    if((fp=fopen(filename,"r"))!=NULL)
    {
        printf("!<%s>! exits ,suggest changing the filename for saving!",filename);
        return false;
    }
    if((fp=fopen(filename,"w"))==NULL)
    {
        printf("the wstream for save the martix error!!!\n");
        return false;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(0==j%10)
                fprintf(fp,"\n");
            fprintf(fp,"%.4lf\t",M[i][j]);
        }
        fprintf(fp,"\n\n");
    }
    fclose(fp);
    return true;
}
