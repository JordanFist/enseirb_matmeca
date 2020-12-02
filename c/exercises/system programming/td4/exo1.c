#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMES 10000
#define MAX_BUF_SIZE 1000
#define MESSAGE "Hello_World ! "

void transfer(int fd_in, int fd_out) {
    char buf[MAX_BUF_SIZE];
    int rc;
    rc = read(fd_in, buf, MAX_BUF_SIZE);
    if(rc == -1) {
        perror("read");
        exit(1);
    }
    rc = write(fd_out, buf, MAX_BUF_SIZE);
    if(rc == -1) {
        perror("write");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int pipefd[2];
    int rc = pipe(pipefd);
    int status;
    if (rc == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid_fork = fork();

	switch(pid_fork) {
		case -1:
			perror("failed to fork");
			exit(1);
			break;
		case 0: //sortie = 0 pour le fils
            close(pipefd[1]); //pas besoin d'ecrire
            transfer(pipefd[0], STDOUT_FILENO);
            close(pipefd[0]);
            break;
		default: // sortie = pid du pere int > 0 
            close(pipefd[0]); //pas besoin de lire
            for (int i = 0; i < TIMES; ++i) {
                rc = write(pipefd[1], MESSAGE, strlen(MESSAGE));
                if (rc == -1) {
                    perror("write");
                    exit(1);
                }
                if (rc != strlen(MESSAGE)) {
                    perror("pas entier");
                    exit(1);
                }
            }
            close(pipefd[1]);

            wait(&status);
            printf("\nOn attend que le fils termine : \n");
            if(WIFEXITED(status)) {
                printf("exited, status=%d\n", WIFEXITED(status));
            } else if (WIFSIGNALED(status)) {
                printf("signaled, status=%d\n", WIFSIGNALED(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped, status=%d\n", WIFSTOPPED(status));
            } else if (WEXITSTATUS(status)) {
                printf("exitStatus, status=%d\n", WEXITSTATUS(status));
            } else if (WTERMSIG(status)) {
                printf("termSig, status=%d\n", WTERMSIG(status));
            } else if (WCOREDUMP(status)) {
                printf("coreDump, status=%d\n", WCOREDUMP(status));
            } else if (WSTOPSIG(status)) {
                printf("stopSig, status=%d\n", WSTOPSIG(status));
            }
			break;
	}
    return 0;
}
