#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_BUF_SIZE 256
#define HALF_DUPLEX "./versserveur"

int main(int argc, char *argv[]) {
    int out;
    int n;
    char buf[MAX_BUF_SIZE];

    CHK(out = open(HALF_DUPLEX, O_WRONLY));
    if (fd<0)

    return 0;
}