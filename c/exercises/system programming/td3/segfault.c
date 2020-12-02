#include <stdio.h>

int main(int argc, char const *argv[])
{
    //*((int *)0) = 42;
    int *x = NULL; 
    *x = 2;
    return 0;
}
