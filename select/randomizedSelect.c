/*************************************************************************
	> File Name: randomizedSelect.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 18时28分05秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define MAX 50

//声明
void dispA(int a[],int length);
void swap(int a[],int i,int j);
int randomParttion(int a[],int start,int end);
int randomizedSelect(int a[],int start,int end,int i);

/*
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
    i=randomizedSelect(a,0,length-1,input);
    
    printf("第%d小的元素是: %d\n",input,a[i]);
    dispA(a,length);
}
*/

//实现期望为线性的选择算法
int randomizedSelect(int a[],int start,int end,int i)
{
    //递归终止
    if(start==end)
        return a[start]; 

    srand((unsigned int)time(NULL)) ;

    int tmp=rand()%(end - start + 1)+start;     //end与start之间的随机数字
    int mid;                                    //记录一次交换之后的原来a[end]的位置
    int l;                                      //第几小的元素
    swap(a,tmp,end);                            //构建随机
    
    mid=randomParttion(a,start,end);
    l=mid-start+1;

    if(l==i)
        return mid;
    else if(l<i)
        return randomizedSelect(a,mid+1,end,i-l);
    else 
        return randomizedSelect(a,start,mid-1,i);

}


//交换数组中的两个元素位置
void swap(int a[],int i,int j)
{
    int temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

//依据数组最后的元素,小于其的在其左边,大于其的在其右边
int randomParttion(int a[],int start,int end)
{
    int p=a[end];
    while(start<end)
    {
        while(start<end&&a[start]<p)
            start++;
        while(start<end&&a[end]>p)
            end--;
        swap(a,start,end);
    }
    return start;
}

//按照位置显示数组
void dispA(int a[],int length)
{
    for(int i=0;i<length;i++)
        printf("%d  ",a[i]);
    printf("\n");
}
