#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[])
{
    //__pid_t pid;
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644); //0 pour dire que c'est de l'octal
    int status;
    int rc;

    write(fd, "sortie: ", 8);
    write(fd, argv[1], strlen(argv[1]));
    write(fd, "\ncommande: ", 11);
    write(fd, argv[2], strlen(argv[2]));
    write(fd, "\n", 1);
    //printf("sortie: %s\n""comande: %s\n", argv[1], argv[2]);
   
    pid_t pid_fork = fork();

	switch(pid_fork) {
		case -1:
			perror("failed to fork");
			exit(1);
			break;
		case 0:
            rc = dup2(fd, STDOUT_FILENO);

            if (rc == -1) {
                perror("error dup2");
                exit(1);
            }

            close(fd); // fermer chez le fils
            rc = execvp(argv[2], argv + 2); //ou &argv[2]
            if (rc == -1) {
                perror("error execv p");
                exit(1);
            }
            break;
		default:
            close(fd); //fermer chez le pere
            wait(&status);
            printf("On attend que le fils termine : \n");
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