#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUF_SIZE 500

void transfer(int fd_in, int fd_out)
{
    char buf[MAX_BUF_SIZE];
    int rc;
    rc = read(fd_in, buf, MAX_BUF_SIZE);
    if (rc == -1)
    {
        perror("read");
        exit(1);
    }
    rc = write(fd_out, buf, MAX_BUF_SIZE);
    if (rc == -1)
    {
        perror("write");
        exit(1);
    }
}

char *ls[] = {"ls", "-l", NULL};
char *tr[] = {"grep", "main", "exo4.c", NULL};
char **commandes[] = {ls, tr};
int nb_commandes = sizeof (commandes) / sizeof(char *);

int main(int argc, char *argv[])
{
    int status;
    int pipefd[2];
    int prev_in, rc;
    pid_t pid, pid2;

    prev_in = STDIN_FILENO;

    for (int i = 0; i < nb_commandes; ++i)
    {
        pipefd[0] = -1; pipefd[1] = -1;
        if (i < nb_commandes - 1)
        {
            rc = pipe(pipefd);
            if (rc == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();

        switch (pid)
        {
        case -1:
            perror("failed to fork");
            exit(1);
            break;
        case 0:
            if (i > 0)
            {
                //assert(prev_in != STDIN_FILENO);
                rc = dup2(prev_in, STDIN_FILENO);
                if (rc == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(prev_in);
            }

            if (i < nb_commandes - 1)
            {
                //assert(pipefd[1] != -1)
                rc = dup2(pipefd[1], STDERR_FILENO);
                if (rc == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(pipefd[1]);
                close(pipefd[0]);
            }

            rc = execvp(commandes[i][0], commandes[i]);
            if (rc == -1)
            {
                perror("error execvp");
                exit(1);
            }
            break;
        default:
            if (i < nb_commandes - 1)
                close(pipefd[1]);
            if (prev_in != STDIN_FILENO) //ou si i > 0 pareil
                close(prev_in);
            prev_in = pipefd[0];

            do {
                pid2 = wait(&status);
                if(pid2 == -1) {
                    perror("wait");
                    exit(1);
                }
            } while(pid2 != pid);
            if (WIFEXITED(status)) { //toutes les erreurs

            } 
            break;
        }
    }
    return 0;
}