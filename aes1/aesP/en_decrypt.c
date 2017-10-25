/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月12日 星期四 13时48分39秒
 ************************************************************************/

#include<stdio.h>
#include"./global.h"
#include"./aeshead.h"
#include"./lib.c"
#include"./expandK.c"
#include"./byteSub.c"
#include"./shiftRow.c"
#include"./mixColumn.c"
#include"./addRoundKey.c"
#include"./generateNewS.c"

//--------------------------------------------
//encrypt
void rnd(u8 *msg)
{
    byteSub(msg);
    shiftRow(msg);
    mixColumn(msg);
    addRoundKey(msg);
}
void finalRound(u8 *msg)
{
    byteSub(msg);
    shiftRow(msg);
    addRoundKey(msg);
}

void encrypt(u8 *msg,u8 *mainKey)
{
    I=0;    //当前迭代轮数
    //dispState(mainKey);
    //printf("\n");
    expandKey(mainKey);
    //for(int i=0;i<(Nr+1);i++)
    //    dispKey(i);
    addRoundKey(msg);
    //dispState(msg);
    I++;
    while(I<Nr)
    {
        rnd(msg);
        I++;
        //printf("\n");
    }
    finalRound(msg);
}


//---------------------------------------------
//decrypt


void _rnd(u8 *state)
{
    addRoundKey(state);
    _mixColumn(state);
    _shiftRow(state);
    _byteSub(state);
}

void decrypt(u8 *ciphertext,u8 *mainKey)
{
    expandKey(mainKey);

    I=Nr;
    addRoundKey(ciphertext);
    _shiftRow(ciphertext);
    _byteSub(ciphertext);
    
    for(I=Nr-1;I>0;I--)
        _rnd(ciphertext);

    addRoundKey(ciphertext);
}
