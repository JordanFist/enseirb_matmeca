#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFF_SIZE 1024

int main(int argc, char const *argv[])
{
    /* declaration */
    int fd = open("abc.txt", O_RDONLY);
    int fd_copy = dup(fd);
    int fd_new = open("abc.txt", O_RDONLY);
    char buff1[BUFF_SIZE];
    char buff2[BUFF_SIZE];
    char buff3[BUFF_SIZE];

    /* read & write */
    int ret1 = read(fd, buff1, 5);
    int ret2 = read(fd_copy, buff2, 6);
    int ret3 = read(fd_new, buff3, 5);
    write(fileno(stdout), "fd: ", 4);
    write(fileno(stdout), buff1, 5);
    write(fileno(stdout), "\nfd_copy: ", 10);
    write(fileno(stdout), buff2, 6);
    write(fileno(stdout), "\nfd_new: ", 9);
    write(fileno(stdout), buff3, 6);
    write(fileno(stdout), "\n", 1);

    return 0;
}
