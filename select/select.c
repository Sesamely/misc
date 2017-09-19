/*************************************************************************
	> File Name: select.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 19时33分38秒
 ************************************************************************/

#include<stdio.h>
#include "randomizedSelect.c"

void dispA(int a[],int length);
void swap(int a[],int i,int j);
int insertSort_returnMid(int a[],int start,int end);
int selectPro(int a[],int start,int end,int index);
int search(int a[],int start,int end,int data);
int randomParttion(int a[],int start,int end);

int main()
{
    int a[MAX]={};
    int length=0,input=0,i=0;

    printf("初始化数组\n>");
    while(input!=-1)
    {
        scanf("%d",&input);
        getchar();
        if(input!=-1)
            a[length++]=input;
    }
    while(1)
    {
        printf("选择查找第?小的元素\n>");
        scanf("%d",&input);
        getchar();
        if(input<=length&&input>=1)
            break;
        else
            printf("重新输入!!!\n");
    }
    i=selectPro(a,0,length-1,input);
    printf("第%d小的元素是: %d\n",input,a[i]);
}
//插入排序返回中值
int insertSort_returnMid(int a[],int start,int end)
{
    int i,j;
    for(i=start;i<end;i++)
        for(j=i+1;j>start;j--)
            if(a[j]<a[j-1])
                swap(a,j,j-1);
    return a[(start+end)/2];
}
//实现最坏情况为线性时间的选择算法
int b1[(MAX/5+1)]={};                   //记录分割的第n个数组的start
int b2[(MAX/5+1)]={};                   //记录分割的第n个数组的end
int c[(MAX)/5+1]={};                    //记录分割的第n个数组的middle 
int selectPro(int a[],int start,int end,int index)
{
    int i
        ,bi                             //分的组数
        ,midmid                         //分组的中值的中值
        ,loc                            //midmid值在数组a中的位子
        ,p                              //依据loc快速分组(快速排序算法)后midmid值的实际位置
        ,k;                             //*****
    int length=end-start+1;
    //将大数组分成每个5个元素的一组数组,最后一组1-4个元素
    while((i+4)<length)
    {
        b1[bi]=i;
        b2[bi++]=i+4;
        i=i+5;
    }
    if(i!=length)
    {
        b1[bi]=i;
        b2[bi++]=length-1;
    }
    //插入排序,返回中值
    for(int i=0;i<bi;i++)
        c[i]=insertSort_returnMid(a,b1[i],b2[i]);

    midmid=insertSort_returnMid(c,0,bi-1);

    loc=search(a,start,end,midmid);

    swap(a,loc,end);

    p=randomParttion(a,start,end);

    k=p-start+1;
    if(k==index)
        return p;
    else if(k>index)
        return selectPro(a,start,p-1,index);
    else 
        return selectPro(a,p+1,end,index-k);
}
//查找数组中值为data的元素位置并返回
int search(int a[],int start,int end,int data)
{
    int length=end-start+1;
    int k=0;
    while(k<length&&a[k]!=data)
        k++;
    return k;
}

