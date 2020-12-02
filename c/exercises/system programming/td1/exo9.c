#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct nopad {
    char c;
    long l;
};

int main(int argc, char *argv[]) {
    struct nopad valeur;
    ssize_t res = read(0, &valeur, sizeof(valeur));
    //int64_t peut etre remplace par long mais moins precis
    //ca depend des machines c'est mieux int64_t
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
    fprintf(stderr, "J'ai lu: %c\n", valeur.c);
    fprintf(stderr, "J'ai lu: %ld", valeur.l);
    write(1, "\n", 1);

    return 0;
}