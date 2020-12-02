package tec;

abstract class Collecte {
    protected int nbPassagersEntres;
    protected int nbPassagersSortis;
    protected int numeroArret;

    Collecte() {
        nbPassagersEntres = 0;
        nbPassagersSortis = 0;
        numeroArret = 0;
    }

    void uneEntree() {
        nbPassagersEntres++;
    }

    void uneSortie() {
        nbPassagersSortis++;
    }

    void changerArret() {
        numeroArret++;
        nbPassagersEntres = 0;
        nbPassagersSortis = 0;
    }
}