package tec;

class PassagerIndecis extends PassagerAbstrait {

    PassagerIndecis(String n, int dest) {
        super(n, dest);
    }

    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceDebout())
            v.monteeDemanderDebout(this);
    }

    void choixPlaceArret(Vehicule v, int numeroArret) {
        if (estDebout())
            changerEnAssis();
        else if (estAssis())
            changerEnDebout();
    }
}