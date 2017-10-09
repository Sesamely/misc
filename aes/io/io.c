/*************************************************************************
	> File Name: io.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月09日 星期一 15时04分46秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define FLUSHSIZE 128
#define FILELENGTH 30
int main(int argc,char *argv[])
{
    FILE *fp,*fpw;
    char filename[FILELENGTH]={0};
    char flu[FLUSHSIZE];
    int readnum=0;
    if(NULL==argv[1])
    {
        printf("请输入要打开的文件名:\n>");
        scanf("%s",filename);
    }
    else
        strcpy(filename,argv[1]);
    if((fp=fopen(filename,"rb"))==NULL)
        return -1;
    strcat(filename,"New");
    do
    {
        readnum=fread(flu,FLUSHSIZE,1,fp);
        if((fpw=fopen(filename,"wb"))==NULL)
            return -1;
        fwrite(flu,FLUSHSIZE,1,fpw);
    }while(FLUSHSIZE==readnum);
    return 0;
}

