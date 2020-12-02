#include "Chaine.hpp"
//#include "Personne.hpp"

#include <cstdio>

void annexe(const Chaine &s)
{
    printf("taile : %u\n", s.taille());
}

Chaine &print(Chaine &s)
{
    s.debug();
    return s;
}
/*
void afficheNom(Personne& p) {
    printf("nom : %s\n", p._nom);
}*/

int main(int argc, char *argv[])
{
    /*
    Chaine chaine("test");
    Chaine *p;
    p = new Chaine("test"); 
    printf("%d\n", chaine.taille());
    printf("%d\n", p->taille());
    chaine.annexe(chaine);
    printf("%c\n", chaine.get(2));
    */
    /*
    Chaine s1("une chaine");
    Chaine s2(s1);
    Chaine s3 = s1;

    s1.debug();
    s2.debug();
    s3.debug();
    */

    /*
    Chaine c("message");
    printf("%p %p\n",&(print(c)), &c);
    
    
    Chaine s1("une chaine");
    Chaine s2("coucou");

    s2 = s1;
    s2.debug();
    */

    //TD3



    return 0;
}