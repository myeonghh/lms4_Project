#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

struct test
{
    int a;
    char b[50];
    int c;
    int d;
    
};


int main(void)
{
    struct test list[3] ={{1, "aa", 2, 3},{1, "bb", 2, 3}};


    printf("===> %d\n", list[2].d);

    



    return 0;
}