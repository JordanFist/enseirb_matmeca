package tec;

public class ArretPoli extends Arret {
    void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (!v.aPlaceAssise())
	    v.arretDemanderDebout(p);
    }
}
