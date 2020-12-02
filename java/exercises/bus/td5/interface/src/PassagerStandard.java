package tec;

class PassagerStandard extends PassagerAbstrait {

    PassagerStandard(String n, int dest) {
        super(n, dest);
    }

    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceAssise())
            v.monteeDemanderAssis(this);
        else if (v.aPlaceDebout())
            v.monteeDemanderDebout(this);
    }

    void choixPlaceArret(Vehicule v, int numeroArret) {}
}