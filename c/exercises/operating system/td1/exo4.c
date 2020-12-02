#include <unistd.h>
#include <asm/unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <sched.h>

/** 
* Valeur à partir de laquelle, on ne capte plus 
* le bruit mais, lorsqu'on lance 2 programmes sur le 
* meme processeur, on est au dessus du seuil
**/
#define SEUIL 50

int main(int argc, char const *argv[])
{
    float diff, diff2;
    int i = 1;
    struct timeval tv[2];
    struct timeval tv2[2];
    gettimeofday(&tv[0], NULL);
    tv2[0] = tv[0]; //meme reference
    while(1) {
        gettimeofday(tv + i, NULL);
        diff = (tv[i].tv_sec-tv[!i].tv_sec) * 1000000
        +(tv[i].tv_usec-tv[!i].tv_usec);
        if (diff > SEUIL) {
            diff2 = (tv[!i].tv_sec-tv2[0].tv_sec) * 1000000 +(tv[!i].tv_usec-tv2[0].tv_usec);
            printf("desordonnancement : %f\n", diff);
            printf("timeslice : %f\n", diff2);
            tv2[0] = tv[i]; 
        }
        i = !i;
    }
    return 0;
}
