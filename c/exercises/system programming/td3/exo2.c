#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAINE1 "Hello"
#define CHAINE2 "World"

int main(int argc, char const *argv[])
{
    #if defined UTLISER_SORTIE_ERREUR1
        #if defined(UTILISER_FPRINTF1)
            fprintf(stderr, CHAINE1);  
        #else
            write(STDERR_FILENO, CHAINE1, strlen(CHAINE1));
        #endif

    #else
        #if defined(UTILISER_FPRINTF1)
            fprintf(stdout, CHAINE1);  
        #else
            write(STDOUT_FILENO, CHAINE1, strlen(CHAINE1));
        #endif
    #endif

    sleep(2);

    #if defined UTLISER_SORTIE_ERREUR2
        #if defined(UTILISER_FPRINTF2)
            fprintf(stderr, CHAINE2);
        #else
            write(STDERR_FILENO, CHAINE2, strlen(CHAINE2));
        #endif

    #else
        #if defined(UTILISER_FPRINTF2)
            fprintf(stdout, CHAINE2);  
        #else
            write(STDOUT_FILENO, CHAINE2, strlen(CHAINE1));
        #endif
    #endif
    
    #if defined(UTILISER__EXIT)
        _exit(EXIT_SUCCESS);
    #else
        exit(EXIT_SUCCESS);
    #endif
    
    return EXIT_SUCCESS;
}

