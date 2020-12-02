package tec;

class PassagerStresse extends PassagerAbstrait {

    PassagerStresse(String n, int dest) {
        super(n , dest);
    }

    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceAssise())
            v.monteeDemanderAssis(this);
        else if (v.aPlaceDebout())
            v.monteeDemanderDebout(this);
    }

    void choixPlaceArret(Vehicule v, int numeroArret) {
        if (distanceDest(numeroArret) <= 3)
            if (v.aPlaceDebout()) 
                changerEnDebout();
    }
}