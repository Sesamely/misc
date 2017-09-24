/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 19时33分21秒
 ************************************************************************/

#include<stdio.h>
#include"./getMatrix.c"

void getMatrix(double M[][MAXCOL],char *s,int n);
void dispMatrix(const double M[][MAXCOL],int n);

int main()
{
    double M[MAXROW][MAXCOL]={};
    char s[20];
    int n=0;
    printf("please input the data filename:\n>");
    scanf("%s",s);
    printf("please input the matrix's rows( or cols ):\n>");
    scanf("%d",&n);
    getMatrix(M,s,n);
    dispMatrix(M,n);
    return 0;
}
