/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 14时45分28秒
 ************************************************************************/

#include<stdio.h>
#include"./en_decrypt.c"
int main()
{
    generateNewS(0xFE);

    u8 mainKey[] = {
        0x00,0x01,0x20,0x01,
        0x71,0x01,0x98,0xae,
        0xda,0x79,0x17,0x14,
        0x60,0x15,0x35,0x94
    };

    u8 msg[] = {
        0x00,0x01,0x00,0x01,
        0x01,0xa1,0x98,0xaf,
        0xda,0x78,0x17,0x34,
        0x86,0x15,0x35,0x66
    };
    dispState(msg);

    encrypt(msg,mainKey);
    dispState(msg);

    decrypt(msg,mainKey);
    dispState(msg);
    return 0;
}
