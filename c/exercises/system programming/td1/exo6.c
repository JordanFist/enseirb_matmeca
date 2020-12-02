#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#define BUFSIZE 256
int main(int argc, char *argv[]) {
    char buffer[BUFSIZE];
    ssize_t nblu = 1;
    ssize_t res;
    while (nblu) {
        
        nblu = read(0, buffer, BUFSIZE); 

        if (nblu == -1) {
            perror("mon read");
            exit(1);
        }
        if (nblu == 0) {
            break;
        }

        printf("blu=%zd", nblu);
        res = write(1, buffer, nblu); // pas de strlen sur ce qu'on a lu c'est des octets pas des bits

        if (res == -1) {
            perror("mon write");
            exit(1);
        }
        if (res != nblu) {
            perror("write n'a pas tout ecrit");
            exit(1);
        }
        write(1, "\n", 1); 
    }
    return 0;
}