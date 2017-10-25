#!/bin/bash
#-----------------------------------------------------------------------------------
#可以直接执行该文件(使用该文件使用dos2unix工具转换下)
#或者查看 result.txt 文件
#扩展作业查看 extend.txt 
#------------------------------------------------------------------------------------

#编译byteSub.c
    gcc -I ./ -o byteSub byteSub.c;
#执行
    ./byteSub | sed -e 's/$/\r/' > result.txt
#编译columnMix.c
    gcc -I ./ -o columnMix mixColumn.c;
#执行
    ./columnMix | sed -e 's/$/\r/' >> result.txt;
#删除
    rm -rf byteSub columnMix
#显示
#   cat result.txt;
##################################################
  #########扩展作业(只得到了差分值和线性度)#####
##################################################
    gcc -I ./ -o stastic stastic.c -lm;
    ./stastic | sed -e 's/$/\r/' > extend.txt
    rm -rf stastic;
