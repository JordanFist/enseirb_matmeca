#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SIZE 1024

int main()
{
    char buff[BUFF_SIZE];
    int fd = open("~", O_WRONLY);
    char msg = "ça doit etre les burgers";
    write(fd, msg, sizeof(msg));
    close(fd);
    return 0;
}
