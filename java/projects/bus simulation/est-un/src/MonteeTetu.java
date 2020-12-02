package tec;

class MonteeTetu extends PassagerAbstrait {

    MonteeTetu(String n, int dest, Arret a) {
	super(n, dest, a);
    }

    void choixPlaceMontee(Vehicule v) {
        v.monteeDemanderDebout(this);
    }
}
