/*************************************************************************
	> File Name: prepare.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月09日 星期一 15时52分49秒
 ************************************************************************/

#include<stdio.h>
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void shiftLN(u32 *word4,int N);

u8 RC[]={
    0x1,0x2,0x4,0x8,0x10,
    0x20,0x40,0x80,0x1b,
    0x36,0x6c,0xd8,0xab,
    0x4d,0x9a,0x2f,0x5e,
    0xbc,0x63,0xc6,0x97,
    0x35,0x6a,0xd4,0xb3,
    0x7d,0xfa,0xef,0xc5,
    0x91,0x39,0x72,0xe4,
    0xd3,0xbd,0x61,0xc2,
    0x9f,0x25,0x4a,0x94,
    0x33,0x66,0xcc,0x83,
    0x1d,0x3a,0x74,0xe8,
    0xcb,0x8d
};//amount 50

u8 SBox[] = {

};

//ByteSub
void subByte(u8 *B)
{
    u8 l=(*B)^0x0F;
    u8 h=(*B)>>4;
}



//行移位变换
void shiftRow(u32 *state,int Nb)
{
    int i=0;
    switch(Nb)
    {
        case 4:
        {
            while(i<(4*Nb))
            {
                if(4==i)
                    shiftLN(&state[i],1);
                else if(8==i)
                    shiftLN(&state[i],2);
                else if(12==i)
                    shiftLN(&state[i],3);
                i+=4;
            }
        }break;
        //case 6:
        //case 8:
        default :;
    }
}

//列混合
void mixColumn(u32 *word)
{
    u8 cx[4]={0x03,0x01,0x01,0x02};    
}



//xtimes
void xTimes(u8 *A)
{
    u8 temp=*A>>7;
    *A=*A<<1;
    if(1==temp)
        *A=*A^0x1B;
}
//依据密钥得出算法迭代轮数
//输入为密钥首地址,输出为迭代轮数
int getRotateTimes(u8 *k)
{
    char c=k[0];                //判断是否结束
    int num=0;                  //字节数
    if(k!=NULL)
        while(c!='\0')
            c=k[++num];
    num=(num+1)/4;
    switch(num)
    {
        case 4:return 10;
        case 6:return 12;
        case 8:return 14;
        default: return 0;
    }
}
//Rotl循环移位
void Rotl(u32 *word)
{
    u8 *c=(u8 *)word; 
    u8 temp=*c;
    for(int i=0;i<3;i++)
        c[i]=c[i+1];
    c[3]=temp;
}
//显示一个字的各个字节(由低到高)
void dispWord(const u32 *word)
{
    u8 *c=(u8 *)word;
    for(int i=0;i<4;i++)
        printf("0x%x\t",*c++);
    printf("\n");
}
//对4个字,按字循环左移N位以及右移N位
void shiftLN(u32 *word4,int N)
{
    u32 word[4]={};
    N=N%4;
    for(int i=0;i<4;i++)
        word[i]=word4[i];
    for(int i=0;i<(4-N);i++)
        word4[i]=word[i+N];
    for(int i=0;i<N;i++)
        word4[i+4-N]=word[i];
}
void shiftRN(u32 *word4,int N)
{
    u32 word[4]={};
    N=N%4;
    for(int i=0;i<4;i++)
        word[i]=word4[i];
    for(int i=0;i<(4-N);i++)
        word4[i+N]=word[i];
    for(int i=0;i<N;i++)
        word4[i]=word[i+4-N];
}
//显示N个字
void dispWords(const u32 *word,int n)
{
    for(int i=0;i<n;i++)
    {
        if(0==i%4)
            printf("\n");
        printf("%d\t",word[i]);
    }
    printf("\n");
}

/*int main()
{
    u8 K[25]={};
    for(int i=0;i<24;i++)
        K[i]='A';
    int num=getRotateTimes(K);
    printf("%d\n",num);
    u32 word=1;
    dispWord(&word);
    Rotl(&word);
    dispWord(&word);
    return 0;
}
*/
/*
int main()
{
    u32 word[16];
    for(int i=0;i<16;i++)
        word[i]=i+1;
    dispWords(word,16);
    shiftRow(word,4);
    dispWords(word,16);
    return 0;
}
*/
/*int main()
{
    int i=0;
    int flag=1;
    u8 temp=0x01;
    for(i=0;i<50;i++)
    {
        if(temp!=RC[i])
        {
            flag=0;
            break;    
        }
        xTimes(&temp);    
    }
    xTimes(&temp);
    if(flag&&temp==0x01)
        printf("success!\n");
    else
        printf("\n%d\n",i);
}
*/
