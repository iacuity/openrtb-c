#include<stdio.h>
#include<stdlib.h>

char *str = "TEST";

int main() {
        int *i =  malloc(sizeof(int));

        free(str);
        return 0;
}
