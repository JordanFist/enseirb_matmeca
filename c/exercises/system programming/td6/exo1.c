#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    key_t key = ftok("/etc/bashrc", 0);
    if (key == -1)
    {
        perror("fail");
        exit(1);
    }

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("fail");
        exit(1);
    }

    int* p = shmat(shmid, NULL, O_RDWR);
    if (p == (int*)-1)
    {
        perror("fail");
        exit(1);
    }

    (*p)++;
    fprintf(stderr, "p = %d\n", *p);

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
