package tec;

class MonteeSportif extends PassagerAbstrait {

    MonteeSportif(String n, int dest, Arret a) {
	super(n, dest, a);
    }
    
    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceDebout())
	    v.monteeDemanderDebout(this);
    }
}
