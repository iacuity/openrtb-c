#!/bin/bash

<<<<<<< HEAD
gcc -g src/openrtb_test.c src/openrtb_2_3.c -I./include/ -I/usr/local/include/json-c/ /usr/local/lib/libjson-c.a
=======
gcc src/openrtb_test.c src/openrtb_2_3.c -I./include/ -I/usr/local/include/json-c/ /usr/local/lib/libjson-c.a
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f

./a.out
