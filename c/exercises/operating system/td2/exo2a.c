#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int *ptr1, *ptr2, *ptr3;
    //char *cmd;
    pid_t pid = getpid();
    system("dd if=/dev/zero of=bigFile bs=1k count=8");

    int fd = open("./bigFile", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    printf("pid : %d\n", pid);

    ptr1 = mmap(NULL, 8192, PROT_NONE | PROT_WRITE, MAP_SHARED, fd, 0);
    ptr2 = mmap(NULL, 8192, PROT_NONE | PROT_WRITE, MAP_SHARED, fd, 0);
    ptr3 = mmap(NULL, 8192, PROT_NONE | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr1 == MAP_FAILED) {
        perror("map1 failed");
        exit(1);
    } 
    if (ptr2 == MAP_FAILED) {
        perror("map2 failed");
        exit(1);
    } 
    if (ptr3 == MAP_FAILED) {
        perror("map3 failed");
        exit(1);
    } 

    ptr1[0] = 1;ptr1[1] = 1;ptr1[2] = 1;ptr1[3] = 1;
    
    ptr2[4] = 2;ptr2[5] = 2;ptr2[6] = 2;ptr2[7] = 2;
    
    ptr3[8] = 3;ptr3[9] = 3;ptr3[10] = 3;ptr3[11] = 3;
    
    munmap(ptr1, 8196);
    munmap(ptr2, 8196);
    munmap(ptr3, 8196);
    close(fd);

    return 0;
}
