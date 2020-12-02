#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	pid_t pid_pere = getpid();
	printf("Pid_pere : %d\t", pid_pere);
	//fflush(stdout);
	
	switch(fork()) {
		case -1:
			perror("failed to fork");
			exit(1);
			break;
		case 0:
			printf("[%d à %d]", getpid(), getppid());
			break;
		default:
			break;
	}
    return 0;
}
