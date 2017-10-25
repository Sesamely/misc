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
    strcat(tempname,"New");
    strcat(tempname,filename);
    strcpy(filename,tempname);
    if((fwp=fopen(filename,"wb"))==NULL)
        return 2;

    generateNewS(0xFE);

    do{
        rcnt=fread(buff,sizeof(unsigned char),BUFFERSIZE,frp);
        
        if(rcnt%16)
            rcnt=(rcnt/16+1)*16;
        for(int i=0;i<rcnt/16;i++)
            if(en)
                encrypt((u8 *)&buff[16*i],mainKey);
            else
                decrypt((u8 *)&buff[16*i],mainKey);
        
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
    scanf("%s",filename);
    getchar();
    scanf("%d",&en);

    EDFile(filename,mainKey,en);

    return 0;
}
