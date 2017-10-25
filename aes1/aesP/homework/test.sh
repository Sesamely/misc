#!/bin/bash

gcc -I ./ stastic.c -lm
./a.out >temp
rm -rf a.out
