#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct nopad {
    char c;
    long l;
};

int main(int argc, char *argv[]) {
    struct nopad valeur = {'a', 5};
    ssize_t res = write(1, &valeur, sizeof(struct nopad));
    if (res == -1)
    {
        perror("Je suis dans mon write");
        exit(1);
    }
    if (res != sizeof(struct nopad))
    {
        perror("Mon write a pas tout ecrit");
        exit(1);
    }
    write(1, "\n", 1);
    return 0;
}