package tec;

class ArretAgoraphobe implements Arret{
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDest){
	if (!v.aPlaceAssise() || !v.aPlaceDebout())
	    v.arretDemanderSortie(p);
    }
}
