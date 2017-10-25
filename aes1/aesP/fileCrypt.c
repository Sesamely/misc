/*************************************************************************
	> File Name: io.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月25日 星期三 09时38分14秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<en_decrypt.c>
#define BUFFERSIZE 4096
#define FILENAMESIZE 64

int EDFile(char *filename,u8 *mainKey,int en)
{
    int rcnt=0,wcnt=0;
    unsigned char buff[BUFFERSIZE];
    char tempname[FILENAMESIZE]={};
    FILE *frp,*fwp;
    if((frp=fopen(filename,"rb"))==NULL)
        return 1;
    if(en)
        strcat(tempname,"EN");
    else
        strcat(tempname,"DE");
    strcat(tempname,filename);
    strcpy(filename,tempname);
    if((fwp=fopen(filename,"wb"))==NULL)
        return 2;

    generateNewS(0xFE);
    expandKey(mainKey);

    do{
        rcnt=fread(buff,sizeof(unsigned char),BUFFERSIZE,frp);
        
        if(rcnt!=BUFFERSIZE&&(rcnt-1)%16!=0)
            rcnt=((rcnt-1)/16+1)*16;
        for(int i=0;i<rcnt/16;i++)
            if(en)
                encrypt((u8 *)&buff[16*i]);
            else
                decrypt((u8 *)&buff[16*i]);
        
        wcnt=fwrite(buff,sizeof(unsigned char),rcnt,fwp);
    }while(BUFFERSIZE==rcnt&&rcnt==wcnt);
    
    fclose(frp);
    fclose(fwp);

    return 0;
}

int main()
{
    u8 mainKey[] = {
        0x00,0x01,0x20,0x01,
        0x71,0x01,0x98,0xae,
        0xda,0x79,0x17,0x14,
        0x60,0x15,0x35,0x94
    };
    char filename[FILENAMESIZE]={};
    int en=0;
    
    printf("输入要操作的文件名字\n>");
    scanf("%s",filename);
    getchar();

    printf("选择操作(0为解密,1为加密)\n>");
    scanf("%d",&en);
    getchar();

    if(!EDFile(filename,mainKey,en))
        printf("success!\n");
    return 0;
}
