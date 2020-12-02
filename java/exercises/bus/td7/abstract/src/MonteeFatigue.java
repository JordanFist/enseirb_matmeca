package tec;

class MonteeFatigue extends PassagerAbstrait {

    MonteeFatigue(String n, int dest, Arret a) {
	super(n, dest, a);
    }
    
    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceAssise())
	    v.monteeDemanderAssis(this);
    }
}
