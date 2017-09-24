/*************************************************************************
	> File Name: getIn.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 18时58分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"./matrix.h"
#ifndef RANGE
#define RANGE 5000
#endif
typedef int bool;

//get matrix from the file
void getMatrix(double M[][MAXCOL],char *s,int n)
{
    int i=0,j=0;
    double temp=0.0;
    const char *string=s;

    FILE *fp;

    fp=fopen(s,"r");
    if(NULL==fp)
        printf("openning istream fail!!!\n");
    while(!feof(fp))
    {
        if(fscanf(fp,"%lf",&temp))
            M[i][j++]=temp;
        else
            printf("error when fscanf\n");
        if(j==n)
        {
            j=0;
            i++;
        }
        if(i==n)
            break;
    }
    fclose(fp);
}
//display the matrix
void dispMatrix(const double M[][MAXCOL],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%.4lf\t\t",M[i][j]);
        printf("\n");
    }
    printf("\n\n");
}
//display the array
void dispArray(int *P,int n)
{
    for(int i=0;i<n;i++)
        printf("%d\t",P[i]);
    printf("\n\n");
}
//auto generate a unit matrix
void autoCreateI(double B[][MAXCOL],int order)
{
    for(int i=0;i<order;i++)
        B[i][i]=1;
}
//generate random matrix
bool generateRandomMatrix(int n,char *filename)
{
    srand((unsigned)time(NULL));
    double randomNumber=0;
    FILE *fp;
    if((fp=fopen(filename,"r"))!=NULL)
    {
        printf("%s exists,suggset change the filename!\n",filename);
        return false;
    }
    if((fp=fopen(filename,"w+"))==NULL)
    {
        printf("openning write stream error!!!\n");
        return false;
    } 
    for(int i=0;i<n;i++)
    {  
        for(int j=0;j<n;j++)
        {
            randomNumber=(((double)(rand()%RANGE))/10);
            fprintf(fp,"%.1lf\t",randomNumber);
        }
        fprintf(fp,"\n\n");
    }
    fclose(fp);
    return true;
}
























