package tec;

import tec.PassagerAbstrait;

abstract class TestPassagerAbstrait {

    abstract protected PassagerAbstrait creerPassager(String nom, int destination);

    //********************************************************
    /* Etat apres instanciation
    * Un seul cas
    */
    void testInstanciation() {
        PassagerAbstrait p = creerPassager("xxx", 3);

        assert false == p.estAssis();
        assert false == p.estDebout();
        assert true == p.estDehors();
    }

    /* Gestion des changement d'état.
    * Changer Debout puis Dehors puis assis.
    */
    void testGestionEtat() {
        PassagerAbstrait p = creerPassager("yyy", 3);

        p.changerEnDebout();
        assert false == p.estAssis();
        assert true == p.estDebout();
        assert false == p.estDehors();

        p.changerEnDehors();
        assert false == p.estAssis();
        assert false == p.estDebout();
        assert true == p.estDehors();

        p.changerEnAssis();
        assert true == p.estAssis();
        assert false == p.estDebout();
        assert false == p.estDehors();
    }
}