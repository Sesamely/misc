/*************************************************************************
	> File Name: io.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月25日 星期三 09时38分14秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"./en_decrypt.c"
#include"./md5.c"
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

    generateNewS(0xFE,3,mainKey[0]);
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
    char filename[FILENAMESIZE]={};
    int en;
    u8 mainKey[16] = {};
    char password[FILENAMESIZE] = {};
    printf("***Welcome AEScrypt programe,Please input according to the prompt***\n");
    while(1)
    {
        printf("\n\n\t...Please input the password to de_encrypt...\n\t\t\e[0m➤ \e[0m");
        if (!scanf("%s",password)) { return -1; }
        md5(mainKey,password);
    
        printf("\t...Please input the filename you wanna to de_encrypt...\n\t\t\e[0m➤ \e[0m");
        if (!scanf("%s",filename)) { return -1; }

        printf("\t...Please input '1' to ENcrypt or '0' to DEcrypt...\n\t\t\e[0m➤ \e[0m");
        if (!scanf("%d",&en)) { return -1; }
        getchar();

        int result = EDFile(filename,mainKey,en);
/*
 *        dispByte(mainKey,16);
 *        dispSbox();
 *        disp_Sbox();
 */
        switch(result) {
            case 0:printf("\e[31m...Success...\e[0m\n\n");break;
            case 1:printf("\e[31m...Open file failing...\e[0m\n\n");break;
            case 2:printf("\e[31m...Write file failing...\e[0m\n\n");break;
            default:;
        }
        printf("...Are you willing to continue?(N to stop,ANYOTHER KEY to continue)...");
        if(toupper(getchar())=='N') {
            printf("...Bye~...\n");
            break;
        } 
    }
    return 0;
}
