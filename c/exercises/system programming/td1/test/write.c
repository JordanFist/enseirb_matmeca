#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

#define SIZE 1

int main(int argc, char const *argv[]) {
    ssize_t res = 1;
    ssize_t nblu = 1;
    char buffer[SIZE];
    while (nblu) {
        nblu = read(STDIN_FILENO, buffer, SIZE);

        if (nblu == -1) {
            perror("read");
            exit(1);
        }
        if (nblu == 0) {
            break;
        }
        
        res = write(STDOUT_FILENO, buffer, nblu);
        if (res == -1) {
            perror("pas bon write");
            exit(1);
        }
        if (res != nblu) {
            perror("lenght");
            exit(1);
        }
        write(1, "\n", 1);
        printf("blu=%zd\n", nblu);
    }
    return 0;
}
