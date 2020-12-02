#include "Chaine.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
    Chaine chaine("test");
    Chaine *p;
    p = new Chaine("test"); 
    printf("%d\n", chaine.taille());
    printf("%d\n", p->taille());
    //chaine.annexe(chaine);
    printf("%c\n", chaine.get(2));

    delete(p);
    return 0;
}