#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    long x = -1;
    ssize_t res = read(0, &x, sizeof(long));
    //int64_t peut etre remplace par long mais moins precis
    //ca depend des machines c'est mieux int64_t
    if (res == -1)
    {
        perror("Je suis dans mon write");
        exit(1);
    }
    if (res != sizeof(long))
    {
        perror("Mon write a pas tout ecrit");
        exit(1);
    }
    fprintf(stderr, "J'ai lu: %ld", x);
    write(1, "\n", 1);
    return 0;
}