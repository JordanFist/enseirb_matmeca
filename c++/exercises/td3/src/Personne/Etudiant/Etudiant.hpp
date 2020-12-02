#ifndef ETUDIANT_H
#define ETUDIANT_H
#include <Personne.hpp>

namespace enseirb {
class Etudiant : Personne {
    private:
    Chaine _filiere;
    Chaine _enseignement;

    public:
    Etudiant(const Chaine&, const Chaine&, const Chaine&);
    Chaine filiere();
    Chaine enseignement();
    void setEnseignement(Chaine&);
    Chaine& nom();
};
}

#endif