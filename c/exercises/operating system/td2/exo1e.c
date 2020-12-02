#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Veuillez renseigner size et len\n");
        exit(1);
    }
    int size = atoi(argv[1]);
    int len = atoi(argv[2]);
    int *tab[size];
    char *cmd;

    for (int i = 0; i < size; ++i) {
        tab[i] = malloc(len);
        if (tab[i] == NULL) {
            perror("malloc failed");
            exit(1);
        }

        if (i % (size/5) == 0) {
            printf("\n\n");
            asprintf(&cmd, "cat /proc/%d/maps", getpid());
            system(cmd);
        }
    }

    

    for (int i = 0; i < size; ++i) 
        free(tab[i]);
    
    return 0;
}


