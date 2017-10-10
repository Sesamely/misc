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
u8 CX[][4]={
    {0x02,0x03,0x01,0x01},
    {0x01,0x02,0x03,0x01},
    {0x01,0x01,0x02,0x03},
    {0x03,0x01,0x01,0x02}
};
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
};//amount 51
u8 SBox[] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};//sbox
u8 index3[] = {
0x01, 0x03, 0x05, 0x0f, 0x11, 0x33, 0x55, 0xff, 0x1a, 0x2e, 0x72, 0x96, 0xa1, 0xf8, 0x13, 0x35, 
0x5f, 0xe1, 0x38, 0x48, 0xd8, 0x73, 0x95, 0xa4, 0xf7, 0x02, 0x06, 0x0a, 0x1e, 0x22, 0x66, 0xaa, 
0xe5, 0x34, 0x5c, 0xe4, 0x37, 0x59, 0xeb, 0x26, 0x6a, 0xbe, 0xd9, 0x70, 0x90, 0xab, 0xe6, 0x31, 
0x53, 0xf5, 0x04, 0x0c, 0x14, 0x3c, 0x44, 0xcc, 0x4f, 0xd1, 0x68, 0xb8, 0xd3, 0x6e, 0xb2, 0xcd, 
0x4c, 0xd4, 0x67, 0xa9, 0xe0, 0x3b, 0x4d, 0xd7, 0x62, 0xa6, 0xf1, 0x08, 0x18, 0x28, 0x78, 0x88, 
0x83, 0x9e, 0xb9, 0xd0, 0x6b, 0xbd, 0xdc, 0x7f, 0x81, 0x98, 0xb3, 0xce, 0x49, 0xdb, 0x76, 0x9a, 
0xb5, 0xc4, 0x57, 0xf9, 0x10, 0x30, 0x50, 0xf0, 0x0b, 0x1d, 0x27, 0x69, 0xbb, 0xd6, 0x61, 0xa3, 
0xfe, 0x19, 0x2b, 0x7d, 0x87, 0x92, 0xad, 0xec, 0x2f, 0x71, 0x93, 0xae, 0xe9, 0x20, 0x60, 0xa0, 
0xfb, 0x16, 0x3a, 0x4e, 0xd2, 0x6d, 0xb7, 0xc2, 0x5d, 0xe7, 0x32, 0x56, 0xfa, 0x15, 0x3f, 0x41, 
0xc3, 0x5e, 0xe2, 0x3d, 0x47, 0xc9, 0x40, 0xc0, 0x5b, 0xed, 0x2c, 0x74, 0x9c, 0xbf, 0xda, 0x75, 
0x9f, 0xba, 0xd5, 0x64, 0xac, 0xef, 0x2a, 0x7e, 0x82, 0x9d, 0xbc, 0xdf, 0x7a, 0x8e, 0x89, 0x80, 
0x9b, 0xb6, 0xc1, 0x58, 0xe8, 0x23, 0x65, 0xaf, 0xea, 0x25, 0x6f, 0xb1, 0xc8, 0x43, 0xc5, 0x54, 
0xfc, 0x1f, 0x21, 0x63, 0xa5, 0xf4, 0x07, 0x09, 0x1b, 0x2d, 0x77, 0x99, 0xb0, 0xcb, 0x46, 0xca, 
0x45, 0xcf, 0x4a, 0xde, 0x79, 0x8b, 0x86, 0x91, 0xa8, 0xe3, 0x3e, 0x42, 0xc6, 0x51, 0xf3, 0x0e, 
0x12, 0x36, 0x5a, 0xee, 0x29, 0x7b, 0x8d, 0x8c, 0x8f, 0x8a, 0x85, 0x94, 0xa7, 0xf2, 0x0d, 0x17, 
0x39, 0x4b, 0xdd, 0x7c, 0x84, 0x97, 0xa2, 0xfd, 0x1c, 0x24, 0x6c, 0xb4, 0xc7, 0x52, 0xf6, 0x01
};//3的指数表
u8 log3[] = {
0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1a, 0xc6, 0x4b, 0xc7, 0x1b, 0x68, 0x33, 0xee, 0xdf, 0x03, 
0x64, 0x04, 0xe0, 0x0e, 0x34, 0x8d, 0x81, 0xef, 0x4c, 0x71, 0x08, 0xc8, 0xf8, 0x69, 0x1c, 0xc1, 
0x7d, 0xc2, 0x1d, 0xb5, 0xf9, 0xb9, 0x27, 0x6a, 0x4d, 0xe4, 0xa6, 0x72, 0x9a, 0xc9, 0x09, 0x78, 
0x65, 0x2f, 0x8a, 0x05, 0x21, 0x0f, 0xe1, 0x24, 0x12, 0xf0, 0x82, 0x45, 0x35, 0x93, 0xda, 0x8e, 
0x96, 0x8f, 0xdb, 0xbd, 0x36, 0xd0, 0xce, 0x94, 0x13, 0x5c, 0xd2, 0xf1, 0x40, 0x46, 0x83, 0x38, 
0x66, 0xdd, 0xfd, 0x30, 0xbf, 0x06, 0x8b, 0x62, 0xb3, 0x25, 0xe2, 0x98, 0x22, 0x88, 0x91, 0x10, 
0x7e, 0x6e, 0x48, 0xc3, 0xa3, 0xb6, 0x1e, 0x42, 0x3a, 0x6b, 0x28, 0x54, 0xfa, 0x85, 0x3d, 0xba, 
0x2b, 0x79, 0x0a, 0x15, 0x9b, 0x9f, 0x5e, 0xca, 0x4e, 0xd4, 0xac, 0xe5, 0xf3, 0x73, 0xa7, 0x57, 
0xaf, 0x58, 0xa8, 0x50, 0xf4, 0xea, 0xd6, 0x74, 0x4f, 0xae, 0xe9, 0xd5, 0xe7, 0xe6, 0xad, 0xe8, 
0x2c, 0xd7, 0x75, 0x7a, 0xeb, 0x16, 0x0b, 0xf5, 0x59, 0xcb, 0x5f, 0xb0, 0x9c, 0xa9, 0x51, 0xa0, 
0x7f, 0x0c, 0xf6, 0x6f, 0x17, 0xc4, 0x49, 0xec, 0xd8, 0x43, 0x1f, 0x2d, 0xa4, 0x76, 0x7b, 0xb7, 
0xcc, 0xbb, 0x3e, 0x5a, 0xfb, 0x60, 0xb1, 0x86, 0x3b, 0x52, 0xa1, 0x6c, 0xaa, 0x55, 0x29, 0x9d, 
0x97, 0xb2, 0x87, 0x90, 0x61, 0xbe, 0xdc, 0xfc, 0xbc, 0x95, 0xcf, 0xcd, 0x37, 0x3f, 0x5b, 0xd1, 
0x53, 0x39, 0x84, 0x3c, 0x41, 0xa2, 0x6d, 0x47, 0x14, 0x2a, 0x9e, 0x5d, 0x56, 0xf2, 0xd3, 0xab, 
0x44, 0x11, 0x92, 0xd9, 0x23, 0x20, 0x2e, 0x89, 0xb4, 0x7c, 0xb8, 0x26, 0x77, 0x99, 0xe3, 0xa5, 
0x67, 0x4a, 0xed, 0xde, 0xc5, 0x31, 0xfe, 0x18, 0x0d, 0x63, 0x8c, 0x80, 0xc0, 0xf7, 0x70, 0x07
};//3的对数表
//ByteSub
void subByte(u8 *B)
{
    //u8 l=(*B)&0x0F;
    //u8 h=(*B)>>4;
    //u32 loc=h*((u32)16)+l;
    *B=SBox[*B];
}
//S盒变换
void BoxS(u8 *state,int n)
{
    for(int i=0;i<n;i++)
        subByte(&state[i]);
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
//CF(2^8)上的乘法
u8 mult(u8 n1,u8 n2)
{
    //u32 low1=n1&0x0F;
    //u32 hig1=n1>>4;
    //u32 loc1=hig1*(u32)16+low1;
    //u32 low2=n2&0x0F;
    //u32 hig2=n2>>4;
    //u32 loc2=hig2*(u32)16+low2;
    u32 temp1=log3[n1];
    u32 temp2=log3[n2];
    u32 temp=(temp1+temp2)%255;
    return index3[temp];
}
//列混合
void mixColumn(u32 *word)
{
    u8 temp[4]={};
    for(int i=0;i<4;i++)
        temp[i]=((u8 *)word)[i];
    *word=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            ((u8 *)word)[i]^=mult(CX[i][j],temp[j]);
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
//轮密钥产生算法
void generateK(const u32 *mainKey,u32 *W)
{
    int i=0;
    for(;i<4;i++)
        W[i]=mainKey[i];
    for(;i<4*(10+1);i++)
    {
        u32 temp=W[i-1];
        if(i%4==0)
        {
            u32 Rcon=0;
            *(u8 *)&Rcon=RC[(i/4)%51];
            Rotl(&temp);
            for(int i=0;i<4;i++)
                subByte(&(((u8 *)&temp)[i]));
            temp=temp^Rcon;
        }
        W[i]=W[i-1]^temp;
    }
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
/*
int main()
{
    u8 msg[16]={};
    for(int i=0;i<16;i++)
        msg[i]=i+1;
    for(int i=0;i<16;i+=4)
    {
        u32 *temp=(u32 *)(&msg[i]);
        dispWord(temp);
    }
    BoxS(msg,16);
    for(int i=0;i<16;i+=4)
    {
        u32 *temp=(u32 *)(&msg[i]);
        dispWord(temp);
    }
}
int main()
{
    u8 n1=0x2,n2=0x6c,n3=0;
    n3=mult(n1,n2);
    printf("0x%x x 0x%x = 0x%x\n",n1,n2,n3);
}
int main()
{
    u8 c[4]={0x2f,0x18,0xf3,0x4c};
    dispWord((u32 *)c);
    mixColumn((u32 *)c);
    dispWord((u32 *)c);
    return 0;
}
*/
