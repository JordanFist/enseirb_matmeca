#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
    (void)argc;
    char nod_name[] = "~/ProgSys/nod";
    int nod = mknod(nod_name, S_IFIFO | S_IRUSR | S_IWUSR, 0);
    if ((nod == -1) && (nod != EEXIST))
    {
        perror("failure while creating node");
    }
    char buff[BUFF_SIZE];
    int offset = 0;
    int fd = open(argv[0], O_RDONLY);
    while (1)
    {
        int nblu = read(fd, buff + offset, 1);
        if (nblu > 0)
        {
            offset = (offset + 1) % (BUFF_SIZE - 1);
            buff[offset+1] = '\0';
            printf("%s", buff);
        }
    }
    unlink(nod_name);
    close(fd);
    return 0;
}
