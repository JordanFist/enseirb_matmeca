#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define SIZE 256

int main(int argc, char const *argv[])
{
    char buffer[SIZE];
    int res;
    int fd = open("donnees.txt", O_RDONLY);
    int fd_copy = dup(fd);

    res = read(fd, buffer, 4);
    if (res == -1) {
        perror("read");
        exit(1);
    }
    res = read(fd_copy, buffer + 4, 4);
    if (res == -1) {
        perror("read");
        exit(1);
    }

    write(1, buffer, 4);
    if (res == -1) {
        perror("write");
        exit(1);
    }
    write(1, buffer+4, 4);
    if (res == -1) {
        perror("write");
        exit(1);
    }

    close(fd);
    close(fd_copy);
    return 0;
}
