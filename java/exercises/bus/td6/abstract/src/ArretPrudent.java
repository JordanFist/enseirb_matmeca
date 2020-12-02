package tec;

public class ArretPrudent extends Arret {
    
    void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (distanceDestination > 5)
	    v.arretDemanderAssis(p);
	else if (distanceDestination < 3)
	    v.arretDemanderDebout(p);
    }
    
}
