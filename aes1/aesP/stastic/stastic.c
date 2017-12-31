/*************************************************************************
	> File Name: stastic.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 22时24分07秒
 ************************************************************************/

#include<stdio.h>
#include<global.h>
#include<math.h>

int analysisSbox()
{
//------------------------------------------
//    generateNewS(MULTIPLATOR);
//    dispSbox();
//------------------------------------------
    int matrix[256][256]={};
    int x1=0,x2=0,y1=0,y2=0;
    int deltaX=0,deltaY=0;
    int sum=0;
    for(x1=0;x1<256;x1++)
    {
        for(x2=0;x2<256;x2++)
        {
            deltaX=x1^x2;
            y1=S[x1];
            y2=S[x2];
            deltaY=y1^y2;
            matrix[deltaX][deltaY]++;
        }
    }
    //printf("\n\n以下显示对于每个deltaX的deltaY的值\n\n");
    //for(int i=0;i<256;i++)
    //{
    //    for(int j=0;j<256;j++)
    //        printf("%d ",matrix[i][j]);
    //    printf("\n");
    //}
            
    for(int i=0;i<256;i++)
    {
        int max=matrix[i][0];
        for(int j=0;j<256;j++)
            if(matrix[i][j]>max)
                max=matrix[i][j];
        matrix[i][0]=max;
    }
    //printf("\n\n\n对于每个deltaX的最大的deltaY的值(差分次数)\n");
    for(int i=0;i<256;i++)
        sum+=matrix[i][0];
    printf("S盒相关参数>>>>> 差分次数：%lf\t\t",(double)sum/256);
//-------------------------------------------------------------------------------------
    //计算线性相关r
    double result=0;
    double X_=0,Y_=0;
    double XY_=0;
    double X2_=0,Y2_=0;
    for(int i=0;i<256;i++)
    {   X_+=i;
        Y_+=S[i];
        XY_+=i*S[i];
        X2_+=i*i;
        Y2_+=S[i]*S[i];
    }
    X_/=256;
    Y_/=256;
    XY_/=256;
    X2_/=256;
    result=(XY_-X_*Y_)/sqrt((X2_-X_*X_)*(Y2_-Y_*Y_));
    printf("S盒的线性度为：%lf\n",result);
    return 0;
}
