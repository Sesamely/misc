/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 15时31分51秒
 ************************************************************************/


#include "../encrypt.c"

int main()
{

    u8 c=0;
    u32 word=0;
    printf("请输入s盒输入(十进制数):\n>");
    scanf("%d",&c);
    printf("您输入的十进制数的十六进制表示为:\n>0x%x\n",c);
    subByte(&c);
    printf("S盒输出十进制数为:\n>%d\n十六进制数为:\n>0x%x\n",c,c);
  
    printf("\n以下显示列混合结果:\n");
    u8 ch[4]={0x2f,0x18,0xf3,0x4c};
    dispWord((u32 *)ch);
    mixColumn((u32 *)ch);
    dispWord((u32 *)ch);
    printf("\n");
    u8 ch2[4]={0xd2,0xf5,0x70,0x6c};
    dispWord((u32 *)ch2);
    mixColumn((u32 *)ch2);
    dispWord((u32 *)ch2);
    return 0;
}

int main1()
{
    u8 n1=0x02,n2=0x6c,n3=0;
    n3=mult(n1,n2);
    printf("%x\n",0x6d^0xf5^0x70^0x48);
}
