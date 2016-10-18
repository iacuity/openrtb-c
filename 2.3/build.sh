#!/bin/bash

gcc -g src/openrtb_test.c src/openrtb_2_3.c -I./include/ -I/usr/local/include/json-c/ /usr/local/lib/libjson-c.a

./a.out
