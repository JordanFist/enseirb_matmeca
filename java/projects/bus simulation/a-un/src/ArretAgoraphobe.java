package tec;

class ArretAgoraphobe implements Arret {
    static final private ArretAgoraphobe ARRET_AGORAPHOBE = new ArretAgoraphobe();

	public static ArretAgoraphobe createArretAgoraphobe() {
		return ARRET_AGORAPHOBE;
	}
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (!v.aPlaceDebout() || !v.aPlaceAssise())
	    v.arretDemanderSortie(p);
    }
}
