#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void type(struct stat *buffer) {
    switch (buffer->st_mode & S_IFMT) {
    case S_IFBLK:
        printf("block device : ");
        break;
    case S_IFCHR:
        printf("character device : ");
        break;
    case S_IFDIR:
        printf("directory : ");
        break;
    case S_IFIFO:
        printf("FIFO/pipe : ");
        break;
    case S_IFLNK:
        printf("symlink : ");
        break;
    case S_IFREG:
        printf("regular file : ");
        break;
    case S_IFSOCK:
        printf("socket : ");
        break;
    default:
        printf("unknown? : ");
        break;
    }
}

int main(int argc, char const *argv[])
{
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("dir");
        exit(1);
    }

    struct dirent* pDirEnt = readdir(dir);
    struct stat buffer;
    int res;
    
    while(pDirEnt != NULL){
        res = stat(pDirEnt->d_name, &buffer);
        if (res == -1) {
            perror("stat");
            exit(1);
        }
        type(&buffer);
        printf("%s\n", pDirEnt->d_name);
        pDirEnt = readdir(dir);
    }
    
    closedir(dir);

    return 0;
}
