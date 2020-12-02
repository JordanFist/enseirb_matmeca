package tec;

class ArretAgoraphobe extends Arret {
    void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (!v.aPlaceDebout() || !v.aPlaceAssise())
	    v.arretDemanderSortie(p);
    }
}
