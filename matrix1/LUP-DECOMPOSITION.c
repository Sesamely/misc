/*************************************************************************
	> File Name: LUP-DECOMPOSITION.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 15时42分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"./matrix.h"
typedef int bool;


//LUP-DECOMPOSITION(source from the Introduction to Algorithms)
bool LUP_DECOMPOSITION(double M[][MAXCOL],int n,int *P)
{
    for(int k=0;k<n;k++)
    {
        //search the absolute max in kth column start from kth row
        //then swap with kth row
        //nota that : below happens in the matrix(k-n)
        double max=fabs(M[k][k]);
        int maxloc=k;
        for(int i=k+1;i<n;i++)
            if(fabs(M[i][k])>max)
            {
                max=fabs(M[i][k]);
                maxloc=i;
            }

        if(0.000000001>max)
        {
            printf("singular matrix!!!");
            return false;
        }
        // change P
        int tempForP=P[k];
        P[k]=P[maxloc];
        P[maxloc]=tempForP;
        // swap the rows
        // NOTED THAT : swap the whole rows of the matrix!!!
        if(maxloc!=k)
            for(int i=0;i<n;i++)
            {
                double tempForSwap=M[k][i];
                M[k][i]=M[maxloc][i];
                M[maxloc][i]=tempForSwap;
            }
        //A ----> four parts
        for(int i=k+1;i<n;i++)
        {
            M[i][k]/=M[k][k]; 

            for(int j=k+1;j<n;j++)
                M[i][j]-=M[i][k]*M[k][j];
        }
    }
    return true;
}

//according to Ax=b
//B is the b , M preserves the U and L ,and n is the orders of M
//x is the 'x'  of Ax=b
void LUP_SOLVE(double *B,double M[][MAXCOL],int n,int *P,double *x)
{
    double y[MAXCOL]={};
    
    for(int i=0;i<n;i++)
    {
        double sum=0;
        for(int j=0;j<i;i++)
           sum+=M[i][j]*y[j];
        y[i]=B[P[i]]-sum;
    }
    for(int i=n-1;i>=0;i--)
    {
        double sum=0.0;
        for(int j=n-1;j>i;i--)
            sum+=M[i][j]*x[j];
        x[i]=(y[i]-sum)/M[i][i];
    }
}


void LUP_SOLVE_extend(double B[][MAXCOL],int column,double M[][MAXCOL],int n,int *P)
{
    double y[MAXCOL]={};
    
    for(int i=0;i<n;i++)
    {
        double sum=0;
        for(int j=0;j<i;j++)
           sum+=M[i][j]*y[j];
        y[i]=B[P[i]][column]-sum;
    }
    for(int i=n-1;i>=0;i--)
    {
        double sum=0.0;
        for(int j=n-1;j>i;j--)
            sum+=M[i][j]*B[j][column];
        B[i][column]=(y[i]-sum)/M[i][i];
    }
}


