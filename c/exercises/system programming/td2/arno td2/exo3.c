#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define BUFF_SIZE 1024

void lsrec(DIR *dir, char name[], int offset)
{
    struct dirent *current = readdir(dir);
    if (!current)
    {
        printf("something went wrong");
    }
    size_t head_dir_size = strlen(current->d_name);
    while (current)
    {
        size_t i = 0;
        for (; i < offset; i++)
            printf(" ");
        printf("%s\n", current->d_name);
        current = readdir(dir);
        if (current->d_type == DT_DIR)
        {
            char buf[head_dir_size + strlen(current->d_name) + 1];
            sprintf(buf, "%s/%s", name, current->d_name);
            DIR *new_dir = opendir(buf);
            lsrec(new_dir, buf, offset + 3);
        }
    }
    closedir(dir);
}

int main(int argc, char const *argv[])
{
    DIR *dir = opendir("../");
    lsrec(dir, "../", 0);
    return 0;
}
