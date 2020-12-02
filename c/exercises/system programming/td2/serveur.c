#include <stdio.h>

#define HALF_DUPLEX "./versserveur"
#define MAX_BUF_SIZE 255

int main (int argc, char *argv[]) {
    int fifo = mknod("/net/ens/mfaverge/versserveur"); // tube vers lequel se connecter

    if (fifo == -1)
        perror("error");
    

}