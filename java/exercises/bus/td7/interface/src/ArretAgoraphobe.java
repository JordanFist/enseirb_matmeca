package tec;

class ArretAgoraphobe implements Arret{
    static final private ArretAgoraphobe ARRET_AGORAPHOBE = new ArretAgoraphobe();

	public static ArretAgoraphobe createArretAgoraphobe() {
		return ARRET_AGORAPHOBE;
	}
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDest){
	if (!v.aPlaceAssise() || !v.aPlaceDebout())
	    v.arretDemanderSortie(p);
    }
}
