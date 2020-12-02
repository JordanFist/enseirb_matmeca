#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //write et ssize_t et STDIN_FILENO

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        size_t len = strlen(argv[i]);
        ssize_t res = write(1, argv[i], len); //STDOUT_FILENO = 1 (sortie standard)
        // ssizet est un entier signé
        if (res == -1) {
            // si on ecrit dans 3 on rentre dans ce if
            perror("Je suis dans mon write");
            exit(1);
        }
        if (res != len) {
            perror("Ma fonction n'a pas tout ecrit");
            exit(1);
        }
        write(1, "\n", 1); //pas de '' sinon c'est un char et non un char*
    }
    return 0;
}