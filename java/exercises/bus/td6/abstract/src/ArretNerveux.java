package tec;

public class ArretNerveux extends Arret {
    void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (p.estAssis() && v.aPlaceDebout())
	    v.arretDemanderDebout(p);
	else if (p.estDebout() && v.aPlaceAssise())
	    v.arretDemanderAssis(p);
    }
}
