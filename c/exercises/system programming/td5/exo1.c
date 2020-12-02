#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void myhandler(int signum)
{
    fprintf(stderr, "%d", getpid());
}

/*
int main(int argc, char *argv[])
{
    printf("pid %d", getpid());
    signal(SIGUSR1, myhandler);
    
    pause();

    //kill(getpid(), SIGUSR1); //sur un autre programme
    //signal(SIGUSR1, SIG_DFL); //reinstalle le gestionnaire par defaut
   
    return 0;
}
*/

int main(int argc, char *argv[])
{
    struct sigaction sa;
    pid_t pid = getpid();
    printf("pid : %d\n", pid);

    sa.sa_handler = myhandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction(SIGUSR1, &sa, NULL);

    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGUSR1);

    sigsuspend(&set);

    return 0;
}
